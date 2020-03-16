#ifndef LIFEWIDGET_H
#define LIFEWIDGET_H

#include <QWidget>
#include <QImage>

class LifeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LifeWidget(QWidget *parent = nullptr);
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent *event) override;

public slots:
    void setImage(const QImage& image);

private:
    QImage m_image;
    QSize m_size;
};

#endif // LIFEWIDGET_H
