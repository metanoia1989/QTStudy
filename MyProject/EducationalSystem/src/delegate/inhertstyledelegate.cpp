#include "inhertstyledelegate.h"
#include <QPainter>

InhertStyleDelegate::InhertStyleDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void InhertStyleDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if( option.state & QStyle::State_Selected )//we need this to show selection
    {
        painter->fillRect( option.rect, option.palette.highlight() );
    }

    QStyledItemDelegate::paint(painter,option,index);//standard processing
}
