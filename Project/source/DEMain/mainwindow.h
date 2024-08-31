#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "SARibbonMainWindow.h"
class SARibbonCategory;
class SARibbonContextCategory;
class SARibbonCustomizeWidget;
class SARibbonActionsManager;
class SARibbonQuickAccessBar;
class SARibbonButtonGroupWidget;
class SARibbonPannel;
class QCloseEvent;
class QLabel;
class DEMainWidget;

enum DEUIMode
{
    DEUIWelcome,
    DEUIEdit
};

class MainWindow : public SARibbonMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* par = nullptr);

    void ShowUIWindow(DEUIMode mode);

private:
    //初始化Ribbon
    void InitSARibbon();
    // 创建ribbon-application菜单示例
    void createRibbonApplicationButton();
    // 创建main菜单示例
    void createCategoryMain(SARibbonCategory* page);
    void createCategoryUserDefDlg(SARibbonCategory* page);
private:
    void AutoSave();
    void bindActionID(QAction* act, int ID, QString strName);

protected:
    void closeEvent(QCloseEvent* e) override;
public slots:
    void FileNew();
    void FileOpen();
    void FileSave();
    void FileSaveAs();

    void ExitDialogEdit();
    void BlockDelete();
    void BlockMoveUp();
    void BlockMoveDown();

private:
    QLabel* m_wWelCome = nullptr;
    DEMainWidget* m_MainWidget = nullptr;
private:
    SARibbonCategory* m_categoryMain;
    SARibbonCategory* m_categoryUserDefDlg;
private:
    QAction* m_ActionFileNew;
    QAction* m_ActionFileOpen;
    QAction* m_ActionFileSave;
    QAction* m_ActionFileSaveAs;
    QList<QAction*> m_recentFileActionList;
    QAction* m_ActionAppSettings;

    bool mHasApplyCustomizeXmlFile { false };  /// 程序启动后是否应用上次修改

private:
    QString s_curFile;
};

#endif  // MAINWINDOW_H
