#include "dialoglogin.h"
#include "ui_dialoglogin.h"

#include <QMouseEvent>
#include <QSettings>
#include <QMessageBox>
#include <QByteArray>
#include <QCryptographicHash>
#include <QDebug>

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);

    ui->editPwd->setEchoMode(QLineEdit::Password);	// 密码输入模式
    this->setAttribute(Qt::WA_DeleteOnClose);	// 关闭时删除
    // 设置为 SplashScreen，窗口无边框，不在任务栏显示
    this->setWindowFlags(Qt::SplashScreen);
    // 无边框，但是在任务栏显示对话框标题
//    this->setWindowFlags(Qt::FramelessWindowHint);
    readSettings(); // 读取存储的用户名和密码
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

// 读取存储的用户名和密码，密码是经过加载的
void DialogLogin::readSettings()
{
    QString organization = "WWB-Qt"; // 用于注册表
    QString appName = "SplashLogin";	// HKEY_CURRENT_USER/Software/WWB-Qt/SplashLogin
    QSettings settings(organization, appName);	// 创建

    bool saved = settings.value("saved", false).toBool(); // 读取saved键的值
    m_user = settings.value("Username", "user").toString(); // 读取 Username 键的值，默认为user
    QString defaultPwd = encrypt("12345"); // 默认密码为12345的加密数据
    m_pwd = settings.value("PWD", defaultPwd).toString(); // 读取 PWD 键的值

    if (saved) {
        ui->editUser->setText(m_user);
    }
    ui->chkBoxSave->setChecked(saved);
}

// 保存用户名，密码等设置
void DialogLogin::writeSettings()
{
    QString organization = "WWB-Qt"; // 用于注册表
    QString appName = "SplashLogin";	// HKEY_CURRENT_USER/Software/WWB-Qt/SplashLogin
    QSettings settings(organization, appName);	// 创建
    settings.setValue("Username", m_user);	// 用户名
    settings.setValue("PWD", m_pwd);	// 加密后的密码
    settings.setValue("saved", ui->chkBoxSave->isChecked());
}

// 字符串MD5算法加密
QString DialogLogin::encrypt(const QString &str)
{
    QByteArray btArray;
    btArray.append(str);	// 加入原始字符串
    QCryptographicHash hash(QCryptographicHash::Md5);	// Md5加密算法
    hash.addData(btArray);	// 添加数据到加密哈希值

    QByteArray resultArray= hash.result(); 	// 返回最终的哈希值
    QString md5= resultArray.toHex();	// 转换为16进制字符串

    return md5;
}

// 鼠标按键被按下
void DialogLogin::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_moving = true;
        // 记录下鼠标相对于窗口的位置
        // event->globalPost()鼠标按下时，鼠标相对于整个屏幕位置
        // pos() this->pos() 鼠标按下时，窗口相对于整个屏幕位置
        m_lastPos = event->globalPos() - pos();
    }
    return QDialog::mousePressEvent(event);
}

// 鼠标按下左键移动时
void DialogLogin::mouseMoveEvent(QMouseEvent *event)
{
    // (event->buttons() && Qt::LeftButton) 按下左键
    // 鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标
    // 然后 move 到底这个坐标，怎么获取坐标？
    // 通过事件 event->globalPos() 知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
    if (m_moving && (event->buttons() && Qt::LeftButton)
            && (event->globalPos()-m_lastPos).manhattanLength() > QApplication::startDragDistance()) {
        move(event->globalPos()-m_lastPos);
        m_lastPos = event->globalPos() - pos();
    }
    return QDialog::mouseMoveEvent(event);
}

// 鼠标按键释放
void DialogLogin::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_moving = false;	// 停止移动
}

// 点击确认按钮
void DialogLogin::on_btnOk_clicked()
{
    QString user = ui->editUser->text().trimmed(); // 用户名
    QString pwd = ui->editPwd->text().trimmed(); // 密码
    QString encrptPWD = encrypt(pwd);	// 密码加密

    qDebug() << "当前密码：" << encrptPWD << "， 正确密码：" << m_pwd;

    if ((user == m_user) && (encrptPWD == m_pwd)) {
        writeSettings();	// 保存设置
        this->accept();	// 对话框 accept() 关闭对话框
    } else {
        m_tryCount++; // 错误次数
        if (m_tryCount > 3) {
            QMessageBox::critical(this, "错误", "输入错误次数太多，强行退出");
            this->reject(); // 退出
        } else {
            QMessageBox::warning(this, "错误提示", "用户名或密码错误");
        }
    }
}
