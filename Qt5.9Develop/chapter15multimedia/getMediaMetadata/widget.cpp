#include "widget.h"
#include <QPushButton>
#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include <QCoreApplication>
#include <QTextCodec>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_player = new QMediaPlayer(this);
    QPushButton *btn = new QPushButton("点击选择媒体文件", this);

    connect(m_player, &QMediaPlayer::mediaStatusChanged, this,
            &Widget::onMediaStatusChanged);
    connect(btn, &QPushButton::clicked, this, &Widget::selectMediaFile);
}

Widget::~Widget()
{
}


// 选择媒体文件
void Widget::selectMediaFile()
{
    QString cur = QCoreApplication::applicationDirPath();
    QString file = QFileDialog::getOpenFileName(this,"选择", "选择音频文件", "Audio files (*.mp3)");
    m_player->setMedia(QUrl::fromLocalFile(file));
}

void Widget::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia) {
        getMetaData();
    }
}

// 获取媒体文件元数据
void Widget::getMetaData()
{
    QStringList metadatalist = m_player->availableMetaData();

    foreach (QString metaDataType, metadatalist) {
        auto byteArray = m_player->metaData(metaDataType).toByteArray();
        QTextCodec *codec = QTextCodec::codecForUtfText(byteArray, QTextCodec::codecForName("System"));
        const QString &text = codec->toUnicode(byteArray);
        qDebug() << "Type of metadata: " + metaDataType;
        qDebug() << text;
        qDebug() << "---------------";
    }
    qDebug() << " ";
}
