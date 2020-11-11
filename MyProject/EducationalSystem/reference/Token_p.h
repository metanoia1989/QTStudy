﻿#ifndef SERVICE_TOKEN_P_H
#define SERVICE_TOKEN_P_H

#include <QObject>

class QString;
class QDateTime;
class QMutex;

struct USERINFO;

class Token;
class AsyncApi;


class TokenPrivate: QObject
{
    Q_OBJECT

public:
    explicit TokenPrivate(Token* token);
    ~TokenPrivate();

    QString token();
    void requestToken();
    void clearToken();
    void clearLastError();
    void setUserId(const QString& strUserId);
    void setPasswd(const QString& strPasswd);
    USERINFO userInfo();

    int lastErrorCode() const;
    QString lastErrorMessage() const;
    bool lastIsNetworkError() const;

private:
    USERINFO m_info;
    QString m_strUserId;
    QString m_strPasswd;
    bool m_bProcessing;
    QMutex* m_mutex;
    int m_lastErrorCode;
    QString m_lastErrorMessage;
    bool m_bLastIsNetworkError;

    Token* q;
};


#endif // SERVICE_TOKEN_P_H
