#include "mystring.h"
#include <cstring>

MyString::MyString() : m_Len(0), m_Buffer(new char[1])
{
    m_Buffer[0] = '\0';
}

MyString::MyString(int size)
    : m_Len(size), m_Buffer(0)
{
    using namespace std;
    try {
        m_Buffer = new char[size+1];
        m_Buffer[0] = '\0';
    } catch (bad_alloc&) {
        delete[] m_Buffer;
        cerr << "MyString: Out of Memory" << endl;
    }
}

MyString::MyString(const char *chptr)
    : m_Buffer(0)
{
    copy(chptr);
}

MyString::~MyString()
{
    delete[] m_Buffer;
}

int MyString::length() const
{
    return m_Len;
}

std::ostream& operator<<(std::ostream& os, const MyString& s)
{
    os << s.m_Buffer << "(" << s.m_Len << ")";
    return os;
}

void MyString::copy(const char *chptr)
{
    try {
        m_Len = strlen(chptr);
        m_Buffer = new char[m_Len + 1];
        strncpy(m_Buffer, chptr, m_Len + 1);
    } catch (std::bad_alloc& be) {
        delete[] m_Buffer;
        throw;
    }
}

MyString::MyString(const MyString& str)
{
    copy(str.m_Buffer); 
}

MyString& MyString::operator=(const MyString &a)
{
    if (this != &a) {
        delete[] m_Buffer;
        copy(a.m_Buffer);
    }
    return (*this);
}

MyString operator+(const MyString& a, const MyString& b)
{
    MyString temp = MyString(a.m_Len + b.m_Len);
    strncpy(temp.m_Buffer, a.m_Buffer, a.m_Len);
    strncat(temp.m_Buffer, b.m_Buffer, b.m_Len + 1);
    return temp;
}

MyString& MyString::operator+=(const MyString &other)
{
    int newLen = m_Len + other.m_Len;
    char *newBuffer = 0;
    try {
        newBuffer = new char[newLen+1];
    } catch (std::bad_alloc& be) {
        delete[] m_Buffer;
        throw;
    }
    strncpy(newBuffer, m_Buffer, m_Len);
    strncat(newBuffer, other.m_Buffer, other.m_Len+1);
    m_Len = newLen;
    return *this;
}
