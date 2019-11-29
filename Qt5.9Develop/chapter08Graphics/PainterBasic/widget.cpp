#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setPalette(QPalette(Qt::white));	// 设置窗口为白色背景
    setAutoFillBackground(true);
    this->resize(400, 400);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    // 1. 基本绘图1，绘制一个填充矩形
//    myDrawFilledRect();

    // 2. 用材质图片填充一个矩形
//    myDrawTextureRect();

    // 3. 渐变填充
//    myDrawGradient();

    // 4. 绘制基本图形
    myDrawShape();
}



// 基本绘图1，绘制一个填充矩形
void Widget::myDrawFilledRect()
{
    // 基本绘图
    QPainter painter(this);	// 创建QPainter对象
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    int W = this->width(); // 绘图区宽度
    int H = this->height(); // 绘图区高度
    QRect rect(W/4, H/4, W/2, H/2);	// 中间区域矩形框

    // 设置画笔
    QPen pen;
    pen.setWidth(10);	// 线宽
    pen.setColor(Qt::red);	// 划线颜色
    // Qt::NoPen, Qt::SolidLine, Qt::DashLine, Qt::DotLine, Qt::DashDotLine, Qt::DashDotDotLine, Qt::CustomDashLine
    pen.setStyle(Qt::SolidLine);	// 线的类型，实线、虚线等
    // Qt::FlatCap, Qt::SquareCap, Qt::RoundCap
    pen.setCapStyle(Qt::FlatCap);	// 线端点样式
    // Qt::MiterJoin, Qt::BevelJoin, Qt::RoundJoin, Qt::SvgMiterJoin
    pen.setJoinStyle(Qt::BevelJoin);	// 线的连接点样式
    painter.setPen(pen);


    // 设置画刷
//    QPixmap texturePixmap(":images/images/texture.jpg");
    QBrush brush;
    brush.setColor(Qt::yellow);	// 画刷颜色
    brush.setStyle(Qt::HorPattern);	// 画刷填充样式
//    brush.setStyle(Qt::TexturePattern);	// 画刷填充样式 材质填充 需要设置材质图片
//    brush.setTexture(texturePixmap);	// 设置材质图片
    painter.setBrush(brush);
    // Qt::NoBrush,Qt::SolidPattern,Qt::Dense1Pattern,Qt::Dense2Pattern,..,Qt::Dense7Pattern,Qt::HorPattern
    // Qt::VerPattern, Qt::CrossPattern, Qt::BDiagPattern,Qt::FDiagPattern,Qt::DiagCrossPattern,
    // Qt::LinearGradientPattern,Qt::ConicalGradientPattern,Qt::RadialGradientPattern
    // Qt::TexturePattern

    // 绘图
    painter.drawRect(rect);	// 只填充定义的渐变区域
//    painter.drawRect(this->rect());	// 填充更大区域，会有延展效果
}


// 用材质图片填充一个矩形
void Widget::myDrawTextureRect()
{
    QPainter painter(this);	// 创建QPainter对象
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    int W = this->width(); // 绘图区宽度
    int H = this->height(); // 绘图区高度
    QRect rect(W/4, H/4, W/2, H/2);	// 中间区域矩形框

    // 设置画笔
    QPen pen;
    pen.setWidth(3);	// 线宽
    pen.setColor(Qt::red);	// 划线颜色
    pen.setStyle(Qt::SolidLine);	// 线的类型，实线、虚线等
    pen.setCapStyle(Qt::FlatCap);	// 线端点样式
    pen.setJoinStyle(Qt::BevelJoin);	// 线的连接点样式
    painter.setPen(pen);

    // 设置画刷
    QPixmap texturePixmap(":images/images/texture.jpg");
    QBrush brush;
    brush.setStyle(Qt::TexturePattern);	// 画刷填充样式 材质填充 需要设置材质图片
    brush.setTexture(texturePixmap);	// 设置材质图片
    painter.setBrush(brush);

    // 绘图
    painter.drawRect(rect);	// 只填充定义的渐变区域
}


// 渐变填充
void Widget::myDrawGradient()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    int W = this->width(); // 绘图区宽度
    int H = this->height(); // 绘图区高度
    QRect rect(W/4, H/4, W/2, H/2);	// 中间区域矩形框

    // 线性渐变
//    QLinearGradient linearGrad(rect.left(), rect.top(), rect.right(), rect.top());	// 从右到左
//    QLinearGradient linearGrad(rect.left(), rect.top(), rect.right(), rect.bottom());	// 对角线
//    linearGrad.setColorAt(0, Qt::white);	// 起点颜色
//    linearGrad.setColorAt(0.5, Qt::yellow);	// 起点颜色
//    linearGrad.setColorAt(1, Qt::black);	// 终点颜色
//    linearGrad.setSpread(QGradient::ReflectSpread); // 展布模式
//    painter.setBrush(linearGrad);

    // 径向渐变
//    QRadialGradient radialGrad(W/2, H/2, qMax(W/8, H/8), W/2, H/2);
//    radialGrad.setColorAt(0, Qt::white);
//    radialGrad.setColorAt(0, Qt::green);
//    radialGrad.setColorAt(1, Qt::blue);
//    radialGrad.setSpread(QGradient::ReflectSpread);
//    painter.setBrush(radialGrad);

    // 圆锥型渐变
    QConicalGradient coniGrad(W/2, H/2, 45);
    coniGrad.setColorAt(0, Qt::yellow);
    coniGrad.setColorAt(0.5, Qt::blue);
    coniGrad.setColorAt(1, Qt::green);
    painter.setBrush(coniGrad);

    // 绘图
    painter.drawRect(this->rect());	// 填充更大区域，会有延展效果

}

// 绘制基本图形
void Widget::myDrawShape()
{
   QPainter    painter(this);//创建QPainter对象
   painter.setRenderHint(QPainter::Antialiasing);
   painter.setRenderHint(QPainter::TextAntialiasing);

   int W=this->width(); //绘图区宽度
   int H=this->height(); //绘图区高度

//设置画笔
   QPen    pen;
   pen.setWidth(3); //线宽
   pen.setColor(Qt::black); //划线颜色

   //Qt::NoPen,Qt::SolidLine, Qt::DashLine, Qt::DotLine,Qt::DashDotLine,Qt::DashDotDotLine,Qt::CustomDashLine
   pen.setStyle(Qt::SolidLine);//线的类型，实线、虚线等

   //Qt::FlatCap, Qt::SquareCap,Qt::RoundCap
   pen.setCapStyle(Qt::FlatCap);//线端点样式

   //Qt::MiterJoin,Qt::BevelJoin,Qt::RoundJoin,Qt::SvgMiterJoin
   pen.setJoinStyle(Qt::BevelJoin);//线的连接点样式
   painter.setPen(pen);

//1. drawArc() 弧线
//   QRect   rect(W/4,H/4,W/2,H/2);
//   int startAngle = 90 * 16; //起始90°
//   int spanAngle = 90 * 16;   //旋转90°
//   painter.drawArc(rect, startAngle, spanAngle);

//2. drawChord() 弧形
//   QRect   rect(W/4,H/4,W/2,H/2);
//   int startAngle = 90 * 16; //起始90°
//   int spanAngle = 90 * 16;   //旋转90°
//   painter.drawChord(rect, startAngle, spanAngle);

//3.drawConvexPolygon() 多边形
//   QPoint points[4]={
//      QPoint(5*W/12,H/4),
////      QPoint(7*W/12,H/4),
//      QPoint(3*W/4,5*H/12),
////      QPoint(3*W/4,7*H/12),
////      QPoint(7*W/12,3*H/4),
//      QPoint(5*W/12,3*H/4),
////      QPoint(W/4,7*H/12),
//      QPoint(W/4,5*H/12),
////      QPoint(5*W/12,H/4)
//   };
//   painter.drawConvexPolygon(points, 4);


//4. drawEllipse 椭圆
//   QRect   rect(W/4,H/4,W/2,H/2);
//   painter.drawEllipse(rect);

//5. drawImage 图片
//   QRect   rect(W/4,H/4,W/2,H/2);
//   QImage  image(":images/images/qt.jpg");
//   painter.drawImage(rect, image);

//6.  drawLine 线
//   QLine   Line(W/4,H/4,W/2,H/2);
//   painter.drawLine(Line);

//7.  drawLines 多条线
//   QRect   rect(W/4,H/4,W/2,H/2);

//   QVector<QLine> Lines;
//   Lines.append(QLine(rect.topLeft(),rect.bottomRight()));
//   Lines.append(QLine(rect.topRight(),rect.bottomLeft()));
//   Lines.append(QLine(rect.topLeft(),rect.bottomLeft()));
//   Lines.append(QLine(rect.topRight(),rect.bottomRight()));

//   painter.drawLines(Lines);

// 8.QPainterPath 路径
//   QRect   rect(W/4,H/4,W/2,H/2);
//   QPainterPath  path;
//   path.addEllipse(rect);
//   path.addRect(rect);
//   painter.drawPath(path);

//9.drawPie 扇形
//   QRect   rect(W/4,H/4,W/2,H/2);
//   int startAngle = 40 * 16;//起始40°
//   int spanAngle = 120 * 16;//旋转120°
//   painter.drawPie(rect, startAngle, spanAngle);

//10. drawPixmap 渲染资源图片
//   QRect   rect(W/4,H/4,W/2,H/2);
//   QPixmap   pixmap(":images/images/qt.jpg");
//   painter.drawPixmap(rect, pixmap);

//11. drawPolygon 多边形
//   QPoint points[]={
//      QPoint(5*W/12,H/4),
//      QPoint(3*W/4,5*H/12),
//      QPoint(5*W/12,3*H/4),
//      QPoint(2*W/4,5*H/12),
//   };
//   painter.drawPolygon(points, 4);

//12.drawPolyline
//   QPoint points[]={
//      QPoint(5*W/12,H/4),
//      QPoint(3*W/4,5*H/12),
//      QPoint(5*W/12,3*H/4),
//      QPoint(2*W/4,5*H/12)
//   };
//   painter.drawPolyline(points, 4);

//13.drawRect
//   QRect   rect(W/4,H/4,W/2,H/2);
//   painter.drawRect(rect);

//14.drawRect
//   QRect   rect(W/4,H/4,W/2,H/2);
//   painter.drawRoundedRect(rect,20,20);

//14.drawRect
//   QRect   rect(W/4,H/4,W/2,H/2);
//   QFont   font;
//   font.setPointSize(30);
//   font.setBold(true);
//   painter.setFont(font);
//   painter.drawText (rect,"Hello,Qt");

//.  eraseRect
//   QRect   rect(W/4,H/4,W/2,H/2);
//   painter.eraseRect(rect);

//15. fillRect
//   QRect   rect(W/4,H/4,W/2,H/2);
//   painter.fillRect (rect,Qt::green);

//16.   fillPath
//   QRect  rect(W/4,H/4,W/2,H/2);
//   QPainterPath  path;
//   path.addEllipse(rect);
//   path.addRect(rect);
//   painter.fillPath(path,Qt::red);

//17.drawPoint
//     painter.drawPoint(QPoint(W/2,H/2));

//18. drawPoints
     QPoint points[]={
        QPoint(5*W/12,H/4),
        QPoint(3*W/4,5*H/12),
        QPoint(2*W/4,5*H/12)
     };
     painter.drawPoints(points, 3);
}
