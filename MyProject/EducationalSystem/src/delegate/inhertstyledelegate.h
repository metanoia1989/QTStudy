#ifndef INHERTSTYLEDELEGATE_H
#define INHERTSTYLEDELEGATE_H

#include <QStyledItemDelegate>

class InhertStyleDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit InhertStyleDelegate(QObject *parent = nullptr);

    // 重写样式
    void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};

#endif // INHERTSTYLEDELEGATE_H
