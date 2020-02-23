/*********************************************************************************
  *Copyright(C),2014-2015,www.heilqt.com
  *FileName(文件名):  clockplugins
  *Author  (作者):    TobyYi(tanboy@heilqt.com)
  *Version (版本):    2.0.0
  *CreateDate(创建日期):
  *FinishDate(完成日期):
  *Description(描述):
     1.用于主要说明此程序文件完成的主要功能
     2.与其他模块或函数的接口、输出值、取值范围、含义及参数间的控制、顺序、独立及依赖关系

  *Others(其他内容说明):
       others
  *Function List(函数列表):
     1.主要函数列表，每条记录应包含函数名及功能简要说明

     2.
  *History(历史修订记录):
     1.Date: 修改日期
       Author:修改者
       Modification:修改内容简介

     2.

**********************************************************************************/

#include "ysclockplugin.h"

QPoint sec[4] = {QPoint(0, 10), QPoint(3, 0), QPoint(0, -90), QPoint(-3, 0)};
QPoint min[4] = {QPoint(0, 8), QPoint(5, 0), QPoint(0, -70), QPoint(-5, 0)};
QPoint hour[4] = {QPoint(0, 6), QPoint(7, 0), QPoint(0, -50), QPoint(-7, 0)};


YSClockPlugin::YSClockPlugin(QQuickItem *parent):
    QQuickPaintedItem(parent),m_huorColor(Qt::blue),
    m_minColor(Qt::green),m_secColor(Qt::red)
  ,m_lineColor(Qt::black),m_textColor(Qt::white)
  ,m_start(true),m_family("微软雅黑"),m_background(Qt::white),m_title("")
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));//update()会自动产生重绘消息，调用paintEvent()
    timer->start(1000);
}

YSClockPlugin::~YSClockPlugin()
{
}

QColor YSClockPlugin::hourColor()
{
    return m_huorColor;
}

void YSClockPlugin::setHourColor(QColor color)
{
    if(m_huorColor != color){
        m_huorColor = color;
        emit hourColorChanged();
        update();
    }
}

QColor YSClockPlugin::minuteColor()
{
    return m_minColor;
}

void YSClockPlugin::setMinuteColor(QColor color)
{
    if(m_minColor != color){
        m_minColor = color;
        update();
        emit minuteColorChanged();
    }
}

QColor YSClockPlugin::secondColor()
{
    return m_secColor;
}

void YSClockPlugin::setSecondColor(QColor color)
{
    if(m_secColor != color){
        m_secColor = color;
        emit secondColorChanged();
        update();
    }
}

QColor YSClockPlugin::lineColor()
{
    return m_lineColor;
}

void YSClockPlugin::setLineColor(QColor color)
{
    if(m_lineColor != color){
        m_lineColor = color;
        emit lineColorChanged();
        update();
    }
}

QColor YSClockPlugin::textColor()
{
    return m_textColor;
}

void YSClockPlugin::setTextColor(QColor color)
{
    if(m_textColor != color){
        m_textColor = color;
        emit textColorChanged();
        update();
    }
}

QColor YSClockPlugin::background()
{
    return m_background;
}

void YSClockPlugin::setBackground(QColor color)
{
    if(m_background != color){
        m_background =  color;
        emit backgroundChanged();
        update();
    }
}

bool YSClockPlugin::startUpdate()
{
    return m_start;
}

void YSClockPlugin::setStartUpdate(bool start)
{
    if(m_start != start){
        m_start = start;
        emit startUpdateChanged();
        if(m_start && !timer->isActive()){
            timer->start(1000);
            update();
        }else{
            timer->stop();
        }
    }
}

QString YSClockPlugin::ysfamily()
{
    return m_family;
}

void YSClockPlugin::setYsfamily(QString family)
{
    if(m_family != family){
        m_family = family;
        emit ysfamilyChanged();
        update();
    }
}

void YSClockPlugin::setTitle(const QString &title)
{
    if(m_title != title){
        m_title = title;
        update();
    }
}

void YSClockPlugin::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QRect rect(-100, -100, 200, 200);
    painter->setWindow(rect);
    //    painter->fillRect(rect,m_textColor);
    painter->setPen(QPen(m_background));
    painter->setBrush(QBrush(m_background));
    painter->drawEllipse(-100, -100, 200, 200);
    //绘制大刻度
    painter->save(); //save() 与 restore() 必须是一一对应的
    for (int i = 0; i < 60 ; ++i)
    {
        painter->rotate(6);  //rotate()是顺时针旋转坐标轴
        if (i % 5 == 4)
        {
            painter->setPen(QPen(m_lineColor, 3));
            painter->drawLine(0, -85, 0, -100);
        }
        else
        {
            painter->setPen(QPen(m_lineColor, 1));
            painter->drawLine(0, -95, 0, -100);
        }
    }
    painter->restore();

    int s = QTime::currentTime().second();
    int m = QTime::currentTime().minute();
    int h = QTime::currentTime().hour();
    painter->setPen(m_textColor);
    painter->setFont(m_family);
    painter->drawText(-25, 50, QTime::currentTime().toString());
    if(!m_title.isEmpty()){
        painter->drawText(-25, -50, m_title);
    }
    painter->save();
    painter->rotate(((h % 12) +  static_cast<double>(m / 60.0)) * 30);
    painter->setBrush(m_huorColor);
    painter->setPen(m_huorColor);
    painter->drawConvexPolygon(hour, 4);
    painter->restore();

    painter->save();
    painter->rotate(m * 6);
    painter->setBrush(m_minColor);
    painter->setPen(m_minColor);
    painter->drawConvexPolygon(min, 4);
    painter->restore();

    painter->save();
    painter->rotate(s * 6);
    painter->setBrush(m_secColor);
    painter->setPen(m_secColor);
    painter->drawConvexPolygon(sec, 4);
    painter->restore();
}

