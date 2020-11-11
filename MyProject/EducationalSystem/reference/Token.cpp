#include "Token.h"
#include "Token_p.h"
#include "Global.h"

#include <QMutexLocker>
#include <QString>
#include <QDebug>

TokenPrivate::TokenPrivate(Token* token)
    : m_bProcessing(false)
    , m_bLastIsNetworkError(false)
    , m_mutex(new QMutex(QMutex::Recursive))
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
        KMAccountsServer asServer;
        if (asServer.login(m_strUserId, m_strPasswd))
        {
            m_info = asServer.getUserInfo();
            m_info.tTokenExpried = QDateTime::currentDateTime().addSecs(TOKEN_TIMEOUT_INTERVAL);
            return m_info.strToken;
        }
        else
        {
            m_lastErrorCode = asServer.getLastErrorCode();
            m_lastErrorMessage = asServer.getLastErrorMessage();
            m_bLastIsNetworkError = asServer.isNetworkError();
            return QString();
        }
    }
    //
    if (m_info.tTokenExpried >= QDateTime::currentDateTime())
    {
        return m_info.strToken;
    }
    else
    {
        WIZUSERINFO info = m_info;
        KMAccountsServer asServer;
        asServer.setUserInfo(info);

        if (asServer.keepAlive())
        {
            m_info.tTokenExpried = QDateTime::currentDateTime().addSecs(TOKEN_TIMEOUT_INTERVAL);
            return m_info.strToken;
        }
        else
        {
            QString strToken;
            if (asServer.getToken(m_strUserId, m_strPasswd, strToken))
            {
                m_info.strToken = strToken;
                m_info.tTokenExpried = QDateTime::currentDateTime().addSecs(TOKEN_TIMEOUT_INTERVAL);
                return m_info.strToken;
            }
            else
            {
                m_lastErrorCode = asServer.getLastErrorCode();
                m_lastErrorMessage = asServer.getLastErrorMessage();
                m_bLastIsNetworkError = asServer.isNetworkError();
                return QString();
            }
        }
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
    ExecuteOnThread(WIZ_THREAD_NETWORK, [=](){
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

void TokenPrivate::setUserId(const QString& strUserId)
{
    m_strUserId = strUserId;
}

void TokenPrivate::setPasswd(const QString& strPasswd)
{
    m_strPasswd = strPasswd;
}

WIZUSERINFO TokenPrivate::userInfo()
{
    QMutexLocker locker(m_mutex);
    Q_UNUSED(locker);
    //
    WIZUSERINFO ret = m_info;
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
static TokenPrivate* d = 0;
static Token* m_instance = 0;

Token::Token(const QString& strUserId, const QString& strPasswd)
{
    m_instance = this;
    d = new TokenPrivate(this);

    d->setUserId(strUserId);
    d->setPasswd(strPasswd);
}

Token::~Token()
{
    delete d;
    d = 0;
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

void Token::setUserId(const QString& strUserId)
{
    Q_ASSERT(m_instance);

    d->setUserId(strUserId);
}

void Token::setPasswd(const QString& strPasswd)
{
    Q_ASSERT(m_instance);

    d->setPasswd(strPasswd);
}

WIZUSERINFO Token::userInfo()
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
