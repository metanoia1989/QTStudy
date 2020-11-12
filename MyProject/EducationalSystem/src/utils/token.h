#ifndef SERVICE_TOKEN_H
#define SERVICE_TOKEN_H

#include <QObject>
#include <QDateTime>

struct USERINFO;
class TokenPrivate;

class Token : public QObject
{
    Q_OBJECT

public:
    static Token* instance();

    Token();
    Token(const QString& strUsername, const QString& strPasswd);
    ~Token();

    static USERINFO userInfo();
    static QString token(); // sync
    static void requestToken(); // async
    static void clearToken(); // 注销登录时清除
    static void clearLastError();
    static void setUsername(const QString& strUsername);
    static void setPasswd(const QString& strPasswd);

    static QString lastErrorMessage();
    static int lastErrorCode();
    static bool lastIsNetworkError();

signals:
    void tokenAcquired(QString strToken);

    friend class TokenPrivate;
};


#endif // SERVICE_TOKEN_H
