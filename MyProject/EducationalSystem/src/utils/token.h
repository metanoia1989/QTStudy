#ifndef SERVICE_TOKEN_H
#define SERVICE_TOKEN_H

#include <QObject>
#include <QDateTime>

struct ESUSERINFO;

class Token : public QObject
{
    Q_OBJECT

public:
    static Token* instance();

    Token(const QString& strUsername, const QString& strPasswd);
    ~Token();

    static USERINFO userInfo();
    static QString token(); // sync
    static void requestToken(); // async
    static void clearToken(); // 注销登录时清除
    static void clearLastError();
    static void setUserId(const QString& strUserId);
    static void setPasswd(const QString& strPasswd);

    static QString lastErrorMessage();
    static int lastErrorCode();
    static bool lastIsNetworkError();

Q_SIGNALS:
    void tokenAcquired(QString strToken);

private:
    USERINFO m_info;
    QString m_strUsername;
    QString m_strPasswd;
    bool m_bProcessing;
    QMutex* m_mutex;
    int m_lastErrorCode;
    QString m_lastErrorMessage;
    bool m_bLastIsNetworkError;
};


#endif // SERVICE_TOKEN_H
