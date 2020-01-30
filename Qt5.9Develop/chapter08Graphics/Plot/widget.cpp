#include "widget.h"
#include "ui_widget.h"

#include <QtMath>
#include <QPainter>
#include <QFontMetrics>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_margins.setLeft(80);
    m_margins.setTop(50);
    m_margins.setRight(50);
    m_margins.setBottom(50);
//    m_margins = new QMargins(50, 50, 50, 50);

    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);

    iniData();
}

Widget::~Widget()
{
    delete ui;
}

// 生成实际数据
void Widget::iniData()
{
    qreal t = 0;
    qreal w = 4;

    for (int i = 0; i < m_count; i++) {
        m_dataF.append(QPointF(t, qSin(w*t)));
        t += m_intv;
    }
}

// 准备画点的数据
void Widget::preparePoints(QRect &windRect)
{
    m_points.clear();
    int xPos, yPos;
    qreal x, y;
    for (int i =0; i < m_count; i++) {
        x = m_dataF[i].x();
        y = m_dataF[i].y();
        xPos = m_xRatio * (x - m_xmin);
        xPos += m_margins.left();

        yPos = m_yRatio * (y - m_ymin);
        yPos = windRect.height() - m_margins.bottom() - yPos;

        m_points.append(QPoint(xPos, yPos));
    }
}

// 绘制网格底图
void Widget::drawGrid(QPainter &p, QRect &windRect)
{
    QRect rect(windRect.left() + m_margins.left(),
               windRect.top() + m_margins.top(),
               windRect.width() - m_margins.left() - m_margins.right(),
               windRect.height() - m_margins.top() - m_margins.bottom());

    if (!rect.isValid()) {
        return;
    }

    QPen penDot(Qt::DotLine);
    penDot.setColor(Qt::gray);
    QPen penSolid(Qt::SolidLine);
    penSolid.setColor(Qt::black);

    p.setPen(penSolid);
    p.drawRect(rect.adjusted(0, 0, -1, -1));

    int Xpos;
    qreal Xvalue;
    QString xlab;
    QFontMetrics textSize(this->font());
    QRect textRect;
    for (int i = 0; i < m_XTicks; i++) {
        Xpos = rect.left() + i * m_xRatio;
        Xvalue = m_xmin + i * m_xspan / m_XTicks;
        p.setPen(penDot);
        p.drawLine(Xpos, rect.top(), Xpos, rect.bottom());
        p.setPen(penSolid);
        p.drawLine(Xpos, rect.top(), Xpos, rect.bottom() + 5);

        xlab = QString::asprintf("%.1f", Xvalue);
        textRect = textSize.boundingRect(xlab);	// 得到字符串的rect
        p.drawText(Xpos - textRect.width() / 2,
                   rect.bottom() + 5 + textRect.height(),
                   xlab);

    }
    xlab = "time(sec)";
    textRect = textSize.boundingRect(xlab);	// 得到字符串的rect
    p.drawText(rect.left()+(rect.width()-textRect.width())/2,
               windRect.bottom()-textRect.height()/2,
               xlab);

    xlab = "曲线绘图";
    textRect = textSize.boundingRect(xlab);	// 得到字符串的rect
    p.drawText(rect.left()+(rect.width()-textRect.width())/2,
               (m_margins.top()-textRect.height())/2 + textRect.height(),
               xlab);

    int Ypos;
    qreal Yvalue;
    QString ylab;
    QFontMetrics teytSize(this->font());
    QRect teytRect;
    for (int i = 0; i < m_YTicks; i++) {
        Ypos = rect.bottom() - i * m_yRatio;
        Yvalue = m_ymin + i * m_yspan / m_YTicks;
        p.setPen(penDot);
        p.drawLine(rect.left(), Ypos, rect.right(), Ypos);
        p.setPen(penSolid);
        p.drawLine(rect.left() - 5, Ypos, rect.left(), Ypos);

        ylab = QString::asprintf("%.1f", Yvalue);
        teytRect = teytSize.boundingRect(ylab);	// 得到字符串的rect
        p.drawText(rect.left() - 10 - teytRect.width(),
                   Ypos + textRect.height() / 2,
                   ylab);

    }
    ylab = "函数值";
    teytRect = teytSize.boundingRect(ylab);	// 得到字符串的rect
    p.save();
    p.translate(0, windRect.height()/2);	// 平移到左侧中心
    p.rotate(-90);	// 逆时针旋转90度，变成正北为X轴，正东为Y轴
    p.drawText(-textRect.width()/2,
               (m_margins.left()-textRect.height())/2,
               ylab);
    p.restore();
}

// 绘制曲线
void Widget::drawCurve(QPainter &p, QRect &winRect)
{
    QPolygon curve(m_points.count());

    for (int i = 0; i < m_points.count(); i++) {
        curve.setPoint(i, m_points[i].x(), m_points[i].y());
    }

    QPen penSolid(Qt::SolidLine);
    penSolid.setColor(Qt::blue);
    penSolid.setWidth(2);
    p.setPen(penSolid);
    p.drawPolyline(curve);
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);

    int W = this->width();
    int H = this->height();

    QRect WindRect(0, 0, W, H);

    m_xRatio = (W - m_margins.left() - m_margins.right()) / m_xspan;
    m_yRatio = (H - m_margins.top() - m_margins.bottom()) / m_yspan;

    drawGrid(p, WindRect);
    preparePoints(WindRect);
    drawCurve(p, WindRect);
}