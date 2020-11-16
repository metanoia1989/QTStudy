#include "checkboxheader.h"
#include <QPainter>
#include <QStyleOptionButton>
#include <QMouseEvent>

CheckboxHeader::CheckboxHeader(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent)
{
}

void CheckboxHeader::mousePressEvent(QMouseEvent *event)
{
    int index = logicalIndexAt(event->pos());
    if (index != 0) {
        QHeaderView::mousePressEvent(event);
        return;
    }
    int x = sectionPosition(index);
    if ( x + m_x_offset < event->pos().x() < x + m_x_offset + m_width  &&
         m_y_offset < event->pos().y() < m_y_offset + m_height) {
        if (m_state == QStyle::State_On) {
            m_state = QStyle::State_Off;
        }else {
            m_state = QStyle::State_On;
        }
        emit selectAllClicked(m_state);
        viewport()->update();
    }
}

void CheckboxHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    if (logicalIndex == 0) {
        QStyleOptionButton option;
        option.rect = QRect(rect.x() + m_x_offset, rect.y() + m_y_offset, m_width, m_height);
        option.state = QStyle::State_Enabled | QStyle::State_Active;
        if (m_state == QStyle::State_On) {
            option.state |= QStyle::State_On;
        } else if (m_state == QStyle::State_NoChange) {
            option.state |= QStyle::State_NoChange;
        } else {
            option.state |= QStyle::State_Off;
        }
//        style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
        style()->drawControl(QStyle::CE_CheckBox, &option, painter);
    }

}

void CheckboxHeader::updateCheckState(QStyle::StateFlag state)
{
    m_state = state;
    viewport()->update();
}
