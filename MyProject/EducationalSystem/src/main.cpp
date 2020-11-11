#include "informationlist.h"
#include "logindialog.h"
#include "utils/WizWin32Helper.h"
#include "utils/sqlite.h"
#include "utils/cache.h"
#include "utils/global.h"
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>

int main(int argc, char *argv[])
{
    // 仅Windows平台可以使用

    // 暂时先采用UI缩放+字体缩小的方案来适配Windows高分屏
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    // 配置字体
    QFont appFont = WizCreateWindowsUIFont(app);
    QApplication::setFont(appFont);

    // tooltip 样式
    app.setStyle(QStyleFactory::create("fusion"));
    app.setStyleSheet("QToolTip { \
                     font: 12px; \
                     color:#000000; \
                     padding:0px 1px; \
                     background-color: #F8F8F8; \
                     border:0px;}");


    Sqlite *sqlite = new Sqlite("sqlite.db");
    Cache *cache = new Cache(sqlite);
    Global::setCache(cache);

    bool bFallback = true;


//    ESUserSettings userSettings(strAccountFolderName);

//    bool bAutoLogin = userSettings.autoLogin();
//    QString strPassword = userSettings.password();
//    QString strUsername = userSettings.username();

//    if (bAutoLogin && !strPassword.isEmpty()) {
//        // 当勾选自动登录且密码不为空时，自动登录
//        bFallback = false;
//    }

    // 手动登录
    if (bFallback) {
        LoginDialog loginDialog;
        if (loginDialog.exec() != QDialog::Accepted)
            return 0;
    }
    
    // 登录数据库管理
//    WizDatabaseManager dbMgr(strAccountFolderName);
//    if (!dbMgr.openAll()) {
//        QMessageBox::critical(NULL, "", QObject::tr("Can not open database"));
//        return 0;
//    }

//    qDebug() << "set user id for token ; " << strUsername;
//    ESToken::setUsername(strUsername);
//    ESToken::setPasswd(strPassword);

//    dbMgr.db().setPassword(strPassword);
//    dbMgr.db().updateInvalidData();
     

    InformationList w;
    w.show();

    return app.exec();
}
