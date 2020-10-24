#ifndef MENUBTNSTYLE_H
#define MENUBTNSTYLE_H

#include <QProxyStyle>
#include <QIcon>

class MenuBtnStyle : public QProxyStyle
{
public:
    void drawControl(ControlElement element, const QStyleOption *option,
                     QPainter *painter, const QWidget *widget = nullptr) const override;
};

#endif // MENUBTNSTYLE_H
