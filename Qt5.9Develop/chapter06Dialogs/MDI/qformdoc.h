#ifndef QFORMDOC_H
#define QFORMDOC_H

#include <QWidget>

namespace Ui {
class QFormDoc;
}

class QFormDoc : public QWidget
{
    Q_OBJECT

public:
    explicit QFormDoc(QWidget *parent = nullptr);
    ~QFormDoc();

    // 以下接口函数方便在主窗口中调用，实现对MDI子窗口的操作
    void loadFromFile(QString& aFileName);	// 打开文件
    QString currentFileName();	// 返回当前文件名
    bool isFileOpened();	// 文件已经打开

    void setEditFont();	// 设置字体
    void textCut();		// cut
    void textCopy();		// copy
    void textPaste();		// paste

private:
    QString mCurrentFile;	// 当前文件
    bool mFileOpened = false;	// 文件已打开

    Ui::QFormDoc *ui;
};

#endif // QFORMDOC_H
