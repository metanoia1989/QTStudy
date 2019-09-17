#ifndef EXTENSIONDLG_H
#define EXTENSIONDLG_H

#include <QDialog>

class ExtensionDlg : public QDialog
{
    Q_OBJECT

public:
    ExtensionDlg(QWidget *parent = nullptr);
    ~ExtensionDlg();

private:
    void createBaseInfo(); // 实现基本对话窗体的部分
    void createDetailInfo();	// 实现扩展窗体部分
    QWidget *baseWidget;	// 基本对话窗体部分
    QWidget *detailWidget;	// 扩展窗体部分

private slots:
    void showDetailInfo();
};

#endif // EXTENSIONDLG_H
