#include "svgwidget.h"

SvgWidget::SvgWidget(QWidget *parent) : QSvgWidget (parent)
{
    // 获得本窗体的 QSvgRenderer 对象
    render = renderer();
}

// 响应鼠标的滚轮事件，使SVG图片能够通过鼠标滚轮的滚动进行缩放
void SvgWidget::wheelEvent(QWheelEvent *e)
{
    const double diff = 0.1;	// diff 的值表示每次滚轮滚动一定的值，图片大小改变的比例
    QSize size = render->defaultSize();		// 获取图片显示区的尺寸
    int width = size.width();
    int height = size.height();
    if (e->delta() > 0) {	// 获取滚轮滚动的值
        // 对图片的长、宽值进行处理，放大一定的比例
        width = int(this->width() + this->width()*diff);
        height = int(this->height() + this->height()*diff);
    } else {
        // 对图片的长、宽值进行处理，缩小一定的比例
        width = int(this->width() - this->width()*diff);
        height = int(this->height() - this->height()*diff);
    }
    resize(width, height);	// 对图片进行 resize 操作
}
