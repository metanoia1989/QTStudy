#include "token.h"
#include "token_p.h"
#include "global.h"
#include "threads.h"

#include <QMutexLocker>
#include <QString>
#include <QDebug>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>

TokenPrivate::TokenPrivate(Token* token)
    : m_bProcessing(false)
    , m_mutex(new QMutex(QMutex::Recursive))
    , m_bLastIsNetworkError(false)
    , q(token)

{
}

TokenPrivate::~TokenPrivate()
{
    delete m_mutex;
}

QString TokenPrivate::token()
{
    QMutexLocker locker(m_mutex);
    Q_UNUSED(locker);
    //
    if (m_info.strToken.isEmpty())
    {
        QString url = getServerUrl() + "/api/desktop/auth/login";
        qDebug() << "请球URL：" << url;
        QEventLoop loop;
        QNetworkAccessManager mgr;
        QNetworkRequest request;
        request.setUrl(QUrl(url));
//        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/w-www-from-urlencode");

        QByteArray data;
        QUrlQuery params;
        params.addQueryItem("username", m_strUsername);
        params.addQueryItem("password", m_strPasswd);
        data.append(params.toString().toUtf8());
        qDebug() << "请求数据：" << data;
        QNetworkReply *reply = mgr.post(request, data);
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();
        if (reply->error() == QNetworkReply::NoError) {
            QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
            qDebug() << "请求成功：" << json;
            if (json["code"].toInt() == 0) {
                m_info = USERINFO();
                m_info.strUsername = m_strUsername;
                m_info.strToken = json["data"].toObject()["token"].toString();
                int expireIn =   json["data"].toObject()["expire_in"].toInt();
                m_info.tTokenExpried = QDateTime::currentDateTime().addSecs(expireIn * 60);
                return m_info.strToken;
            }
            m_lastErrorMessage = json["msg"].toString();
        } else {
            m_lastErrorMessage = reply->errorString();
        }
        m_lastErrorCode = -1;
        m_bLastIsNetworkError = true;
        qDebug() << "请求出错" << m_lastErrorMessage;
        return QString();

    }

    Q_ASSERT(0);
}

void TokenPrivate::requestToken()
{
    if (m_bProcessing)
    {
        qDebug() << "Querying token...";
        return;
    }
    //
    class GetTokenRunnable : public QObject
    {
        TokenPrivate* m_p;
    public:
        GetTokenRunnable(TokenPrivate* p)
            : m_p(p)
        {
        }

        void run()
        {
            m_p->m_bProcessing = true;
            QString token = m_p->token();
            m_p->m_bProcessing = false;
            Q_EMIT m_p->q->tokenAcquired(token);
        }
    };
    ExecuteOnThread(THREAD_NETWORK, [=](){
        GetTokenRunnable runnable(this);
        runnable.run();
    });
}

void TokenPrivate::clearToken()
{
    m_info.strToken.clear();
}

void TokenPrivate::clearLastError()
{
    m_lastErrorCode = 0;
    m_lastErrorMessage.clear();
}

void TokenPrivate::setUsername(const QString& strUsername)
{
    m_strUsername = strUsername;
}

void TokenPrivate::setPasswd(const QString& strPasswd)
{
    m_strPasswd = strPasswd;
}

USERINFO TokenPrivate::userInfo()
{
    QMutexLocker locker(m_mutex);
    Q_UNUSED(locker);
    //
    USERINFO ret = m_info;
    return ret;
}

int TokenPrivate::lastErrorCode() const
{
    QMutexLocker locker(m_mutex);
    Q_UNUSED(locker);
    //
    return m_lastErrorCode;
}

QString TokenPrivate::lastErrorMessage() const
{
    QMutexLocker locker(m_mutex);
    Q_UNUSED(locker);
    //
    return m_lastErrorMessage;
}

bool TokenPrivate::lastIsNetworkError() const
{
    QMutexLocker locker(m_mutex);
    Q_UNUSED(locker);
    //
    return m_bLastIsNetworkError;
}

// 创建两个对象的指针
static TokenPrivate* d = nullptr;
static Token* m_instance = nullptr;

Token::Token()
{
    m_instance = this;
    d = new TokenPrivate(this);
}

Token::Token(const QString& strUsername, const QString& strPasswd)
{
    m_instance = this;
    d = new TokenPrivate(this);

    d->setUsername(strUsername);
    d->setPasswd(strPasswd);
}

Token::~Token()
{
    delete d;
    d = nullptr;
}

Token* Token::instance()
{
    return m_instance;
}

QString Token::token()
{
    Q_ASSERT(m_instance);
    return d->token();
}

void Token::requestToken()
{
    Q_ASSERT(m_instance);

    d->requestToken();
}

void Token::clearToken()
{
    d->clearToken();
}

void Token::clearLastError()
{
    d->clearLastError();
}

void Token::setUsername(const QString& strUsername)
{
    Q_ASSERT(m_instance);

    d->setUsername(strUsername);
}

void Token::setPasswd(const QString& strPasswd)
{
    Q_ASSERT(m_instance);

    d->setPasswd(strPasswd);
}

USERINFO Token::userInfo()
{
    Q_ASSERT(m_instance);

    return d->userInfo();
}

QString Token::lastErrorMessage()
{
    Q_ASSERT(m_instance);

    return d->lastErrorMessage();
}

bool Token::lastIsNetworkError()
{
    Q_ASSERT(m_instance);

    return d->lastIsNetworkError();
}
int Token::lastErrorCode()
{
    Q_ASSERT(m_instance);

    return d->lastErrorCode();
}
