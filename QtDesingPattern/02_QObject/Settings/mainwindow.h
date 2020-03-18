#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QAction;
class QLabel;
class QMenu;
class QTextEdit;
class QStackedWidget;

/**
 * @brief The MainWindow class
 * Window size/position saved across executions
 * A debug window in the bottom dock area.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event) override;

protected slots:
    virtual void newFile();
    virtual void open();
    virtual bool save();
    virtual bool saveAs();
    virtual void about();
    virtual void documentWasModified();
    virtual QWidget* initialWidget() const;

protected:
    virtual void createActions();
    virtual void createMenus();
    virtual void createEditMenu();
    virtual void createHelpMenu();
    virtual void createFileMenu();
    virtual void createToolBars();
    virtual void createStatusBar();
    virtual void readSettings();
    virtual void writeSettings();
    virtual bool maybeSave();
    virtual void loadFile(const QString& fileName);
    virtual void saveFile(const QString& fileName);
    virtual void setCurrentFile(const QString& fileName);
    QString strippedName(const QString& fullFileName);
    QStackedWidget *m_StackedWidget;
    QTextEdit *m_TextEdit;
    QTextEdit *m_DebugWindow;

    QLabel *m_ModLabel;
    QString m_FileName;

    QMenu *m_FileMenu;
    QMenu *m_EditMenu;
    QMenu *m_HelpMenu;
    QToolBar *m_FileToolBar;
    QToolBar *m_EditToolBar;
    QAction *m_NewAction;
    QAction *m_OpenAction;
    QAction *m_SaveAction;
    QAction *m_SaveAsAction;
    QAction *m_ExitAction;
    QAction *m_CutAction;
    QAction *m_CopyAction;
    QAction *m_PasteAction;
    QAction *m_AboutAction;
    QAction *m_AboutQtAction;
};
#endif // MAINWINDOW_H
