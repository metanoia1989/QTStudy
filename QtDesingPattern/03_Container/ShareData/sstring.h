#ifndef SSTRING_H
#define SSTRING_H

#include <QSharedDataPointer>
#include <iostream>
#include "stringdata.h"

class SString
{
public:
    SString();
    explicit SString(int len);
    SString(const char *ptr);
    SString& operator+=(const SString& other);
    int length() const;
    int refcount() const { return m_d->ref; }
    friend SString operator+(SString, SString);
    friend std::ostream& operator<<(std::ostream&, const SString&);
    /** 仅用于调试 */
    qlonglong sharedDataAddress() const;

private:
    // 私有实现模式
    QSharedDataPointer<StringData> m_d;
};

#endif // SSTRING_H
