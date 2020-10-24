#include "menubtnstyle.h"
#include <QStyleOptionButton>
#include <QPainter>
#include<QDebug>

void MenuBtnStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option,
                               QPainter *painter, const QWidget *widget) const
{
    if (element == QStyle::CE_PushButtonLabel) {
        qDebug() << "测试是否调用";
        const QStyleOptionButton *btnOption = qstyleoption_cast<const QStyleOptionButton *>(option);
        QStyleOptionButton new_option = *btnOption;
        QIcon icon = btnOption->icon;
        new_option.icon = QIcon();
        QProxyStyle::drawControl(element, &new_option, painter, widget);

        if (icon.isNull()) return;
        QIcon::Mode mode = btnOption->state & State_Enabled ? QIcon::Normal : QIcon::Disabled;
        if (mode == QIcon::Normal && btnOption->state & State_HasFocus)
            mode = QIcon::Active;
        QIcon::State state = QIcon::Off;
        if (btnOption->state & State_On)
            state = QIcon::On;
        QWindow *window = widget == nullptr ? nullptr : widget->window()->windowHandle();
        QPixmap pixmap = icon.pixmap(window, btnOption->iconSize, mode, state);
        int pixmapWidth = pixmap.width() / pixmap.devicePixelRatio();
        int pixmapHeight = pixmap.height() / pixmap.devicePixelRatio();

        QRect iconRect = QRect(QPoint(), QSize(pixmapWidth, pixmapHeight));
        int iconSpacing = 4;
        iconRect.moveCenter(btnOption->rect.center());
        iconRect.moveLeft(btnOption->rect.left() + iconSpacing);
        iconRect = visualRect(btnOption->direction, btnOption->rect, iconRect);
        iconRect.translate(proxy()->pixelMetric(PM_ButtonShiftHorizontal, btnOption, widget),
                           proxy()->pixelMetric(PM_ButtonShiftVertical, btnOption, widget));
        painter->drawPixmap(iconRect, pixmap);
    } else {
        // 其他的control，使用默认渲染机制
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}


//void MenuBtnStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option,
//                               QPainter *painter, const QWidget *widget) const
//{
//    if(element==CE_PushButtonLabel)
//    {
//        if (const QStyleOptionButton *button = qstyleoption_cast<const QStyleOptionButton *>(option))
//        {
//                QRect textRect = button->rect;
//                uint tf = Qt::AlignVCenter | Qt::TextShowMnemonic;
//                if (!proxy()->styleHint(SH_UnderlineShortcut, button, widget))
//                    tf |= Qt::TextHideMnemonic;

//                if (!button->icon.isNull()) {
//                    QRect iconRect;
//                    QIcon::Mode mode = button->state & State_Enabled ? QIcon::Normal : QIcon::Disabled;
//                    if (mode == QIcon::Normal && button->state & State_HasFocus)
//                        mode = QIcon::Active;
//                    QIcon::State state = QIcon::Off;
//                    if (button->state & State_On)
//                        state = QIcon::On;

//                    QWindow *window = widget == nullptr ? nullptr : widget->window()->windowHandle();
//                    QPixmap pixmap = button->icon.pixmap(window, button->iconSize, mode, state);

//                    int pixmapWidth = pixmap.width() / pixmap.devicePixelRatio();
//                    int pixmapHeight = pixmap.height() / pixmap.devicePixelRatio();
//                    int labelWidth = pixmapWidth;
//                    int labelHeight = pixmapHeight;
//                    int iconSpacing = 4;//### 4 is currently hardcoded in QPushButton::sizeHint()
//                    int textWidth = button->fontMetrics.boundingRect(option->rect, tf, button->text).width();
//                    if (!button->text.isEmpty())
//                        labelWidth += (textWidth + iconSpacing);

//                    /*************************************************************/
//                    // Make the icon rectangle always be 10px in from the left edge
//                    /*************************************************************/
//                    iconRect = QRect(10,
//                                     textRect.y() + (textRect.height() - labelHeight) / 2,
//                                     pixmapWidth, pixmapHeight);

//                    iconRect = visualRect(button->direction, textRect, iconRect);

//                    /***********************************/
//                    // Always horizontal align the text
//                    /***********************************/
//                    tf |= Qt::AlignHCenter;


//                    if (button->state & (State_On | State_Sunken))
//                        iconRect.translate(proxy()->pixelMetric(PM_ButtonShiftHorizontal, option, widget),
//                                           proxy()->pixelMetric(PM_ButtonShiftVertical, option, widget));
//                    painter->drawPixmap(iconRect, pixmap);
//                } else {
//                    tf |= Qt::AlignHCenter;
//                }
//                if (button->state & (State_On | State_Sunken))
//                    textRect.translate(proxy()->pixelMetric(PM_ButtonShiftHorizontal, option, widget),
//                                 proxy()->pixelMetric(PM_ButtonShiftVertical, option, widget));

//                if (button->features & QStyleOptionButton::HasMenu) {
//                    int indicatorSize = proxy()->pixelMetric(PM_MenuButtonIndicator, button, widget);
//                    if (button->direction == Qt::LeftToRight)
//                        textRect = textRect.adjusted(0, 0, -indicatorSize, 0);
//                    else
//                        textRect = textRect.adjusted(indicatorSize, 0, 0, 0);
//                }
//                proxy()->drawItemText(painter, textRect, tf, button->palette, (button->state & State_Enabled),
//                             button->text, QPalette::ButtonText);
//            }

//            qDebug() << "调用了吗？？？";
//            return;
//    }

//    // For all other controls, draw the default
//    QProxyStyle::drawControl(element, option, painter, widget);
//}
