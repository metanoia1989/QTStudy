#include "utils.h"
#include <QStringList>
#include <QLocale>


QString Utils::sizeFormat(qint64 bytes)
{
    qreal size = bytes;
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";

    QStringListIterator i(list);
    QString unit("bytes");

    while (size >= 1024.0 && i.hasNext()) {
        unit = i.next();
        size /= 1024.0;
    }
    return QString().setNum(size, 'f', 2) + " " + unit;
}

