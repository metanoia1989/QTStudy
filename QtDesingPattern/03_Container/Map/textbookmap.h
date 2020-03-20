#ifndef QTEXTBOOKMAP_H
#define QTEXTBOOKMAP_H

#include <QString>
#include <QMap>

class Textbook;

class TextbookMap : public QMap<QString, Textbook*>
{
public:
    ~TextbookMap();
    void add(Textbook* text);
    QString toString() const;
};

#endif // QTEXTBOOKMAP_H
