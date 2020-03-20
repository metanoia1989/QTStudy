#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include <QObject>
#include <QString>
#include <QMap>

class Textbook : public QObject
{
    Q_OBJECT
public:
    Textbook(QString title, QString author, QString isbn, uint year,
             QObject *parent = nullptr);
    QString getAuthor() const;
    QString getTitle() const;
    QString getIsbn() const;
    uint getYearPub() const;
    QString toString() const;

public slots:
    void setTitle(const QString& newTitle);
    void setIsbn(const QString& newIsbn);
    void setYearPub(uint newYear);
    void setAuthor(const QString& newAuthor);

private:
    QString m_Title, m_Author, m_Isbn;
    uint m_YearPub;
};

#endif // TEXTBOOK_H
