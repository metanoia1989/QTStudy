#include "svgwindow.h"

SvgWindow::SvgWindow(QWidget *parent) : QScrollArea (parent)
{
    svgWidget = new SvgWidget;
    setWidget(svgWidget);
}

// 设置新的文件
void SvgWindow::setFile(QString fileName)
{
    svgWidget->load(fileName);	// 将SVG文件加载到svgWidget中显示
    QSvgRenderer *render = svgWidget->renderer();
    svgWidget->resize(render->defaultSize()); // 使 svgWidget窗体按SVG的默认尺寸显示
}

// 获取窗口的水平和垂直滚动条
void SvgWindow::mousePressEvent(QMouseEvent *event)
{
    mousePressPos = event->pos();
    scrollBarValuesOnMousePress.rx() = horizontalScrollBar()->value();
    scrollBarValuesOnMousePress.ry() = verticalScrollBar()->value();
}

// 通过滚动条的位置设置实现图片拖拽的效果
void SvgWindow::mouseMoveEvent(QMouseEvent *event)
{
    horizontalScrollBar()->setValue(scrollBarValuesOnMousePress.x() -
        event->pos().x() + mousePressPos.x());	// 对水平滚动条的新位置进行设置
    verticalScrollBar()->setValue(scrollBarValuesOnMousePress.y() -
        event->pos().y() + mousePressPos.y());	// 对垂直滚动条的新位置进行设置
    horizontalScrollBar()->update();
    verticalScrollBar()->update();
    event->accept();
}
