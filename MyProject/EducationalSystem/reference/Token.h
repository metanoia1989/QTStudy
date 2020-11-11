#ifndef SERVICE_TOKEN_H
#define SERVICE_TOKEN_H

#include <QObject>
#include <QDateTime>

class TokenPrivate;

class Token : public QObject
{
    Q_OBJECT

public:
    static Token* instance();

    Token(const QString& strUserId = 0, const QString& strPasswd = 0);
    ~Token();

    static USERINFO userInfo();
    static QString token(); // sync
    static void requestToken(); // async
    static void clearToken();
    static void clearLastError();
    static void setUserId(const QString& strUserId);
    static void setPasswd(const QString& strPasswd);

    static QString lastErrorMessage();
    static int lastErrorCode();
    static bool lastIsNetworkError();

Q_SIGNALS:
    void tokenAcquired(QString strToken);

    friend class TokenPrivate;
};


#endif // SERVICE_TOKEN_H
