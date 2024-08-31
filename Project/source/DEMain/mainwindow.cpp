#include "mainwindow.h"
#include "SARibbonHeaders.h"
#include <QAbstractButton>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QCalendarWidget>
#include <QDebug>
#include <QElapsedTimer>
#include <QFile>
#include <QFileDialog>
#include <QFontComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QStatusBar>
#include <QTextEdit>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QShortcut>
#include <QLineEdit>
#include <QDialogButtonBox>
#include "BindButtonID.h"
#include "DEMainWidget.h"
#include "DERoot.h"
#include "DEPartCollection.h"
#include "DEPart.h"

MainWindow::MainWindow(QWidget* par) : SARibbonMainWindow(par)
{
    InitSARibbon();
    ShowUIWindow(DEUIWelcome);

    setWindowTitle(tr("DialogEditor"));
    setMinimumSize(400, 300);
    resize(1080, 720);
}

void MainWindow::InitSARibbon()
{
    setStatusBar(new QStatusBar());

    SARibbonBar* ribbon = ribbonBar();
    ribbon->setContentsMargins(5, 0, 5, 0);

    createRibbonApplicationButton();

    m_categoryMain = ribbon->addCategoryPage(tr("主页"));
    m_categoryMain->setObjectName(("categoryMain"));
    createCategoryMain(m_categoryMain);

    m_categoryUserDefDlg = ribbon->addCategoryPage(tr("功能"));
    m_categoryUserDefDlg->setObjectName(("categoryUserDefDlg"));
    createCategoryUserDefDlg(m_categoryUserDefDlg);

    setWindowIcon(QIcon(":/Icon/Icon/DE.png"));
    showNormal();
    setRibbonTheme(SARibbonTheme::RibbonThemeOffice2016Blue);
}

void MainWindow::ShowUIWindow(DEUIMode mode)
{
    switch(mode)
    {
    case DEUIWelcome:
    {
        QLabel* label = new QLabel(this);
        label->setStyleSheet("background: rgb(218, 222, 225)");
        label->setPixmap(QPixmap(":/Icon/Icon/Welcome.png"));
        label->setAlignment(Qt::AlignCenter);
        setCentralWidget(label);

        if(m_MainWidget)
        {
            delete m_MainWidget;
            m_MainWidget = nullptr;
        }

        ribbonBar()->showCategory(m_categoryMain);
        ribbonBar()->hideCategory(m_categoryUserDefDlg);
        ribbonBar()->raiseCategory(m_categoryMain);
        break;
    }
    case DEUIEdit:
    {
        m_MainWidget = new DEMainWidget(this);
        setCentralWidget(m_MainWidget);

        ribbonBar()->showCategory(m_categoryUserDefDlg);
        ribbonBar()->hideCategory(m_categoryMain);
        ribbonBar()->raiseCategory(m_categoryUserDefDlg);
        break;
    }
    default:
        break;
    }
}

void MainWindow::createRibbonApplicationButton()
{
    SARibbonBar* ribbon = ribbonBar();
    if (!ribbon) {
        return;
    }
    QAbstractButton* btn = ribbon->applicationButton();
    if (!btn) {
        btn = new SARibbonApplicationButton(this);
        ribbon->setApplicationButton(btn);
    }
    ribbon->applicationButton()->setText(("   文件   "));  // 文字两边留有间距，好看一点

    SARibbonMenu *mMenuApplicationBtn = new SARibbonMenu(this);

    m_ActionFileNew = new QAction(QIcon(":/Icon/Icon/FileNew.png"), tr("新建"), this);
    m_ActionFileNew->setShortcut(tr("Ctrl+N"));
    m_ActionFileNew->setStatusTip(tr("新建文件"));
    m_ActionFileNew->setToolTip("创建一个新的文件");
    bindActionID(m_ActionFileNew, -1, "新建");
    mMenuApplicationBtn->addAction(m_ActionFileNew);
    connect(m_ActionFileNew, &QAction::triggered, this, &MainWindow::FileNew);


    m_ActionFileOpen = new QAction(QIcon(":/Icon/Icon/FileOpen.png"), tr("打开"), this);
    m_ActionFileOpen->setShortcut(tr("Ctrl+O"));
    m_ActionFileOpen->setStatusTip(tr("打开文件"));
    m_ActionFileOpen->setToolTip("打开现有文件");
    bindActionID(m_ActionFileOpen, -1, "打开");
    mMenuApplicationBtn->addAction(m_ActionFileOpen);
    connect(m_ActionFileOpen, &QAction::triggered, this, &MainWindow::FileOpen);

    m_ActionFileSave = new QAction(QIcon(":/Icon/Icon/FileSave.png"), tr("保存"), this);
    m_ActionFileSave->setShortcut(tr("Ctrl+S"));
    m_ActionFileSave->setStatusTip(tr("保存文件"));
    m_ActionFileSave->setToolTip("保存文件到指定目录");
    bindActionID(m_ActionFileSave, -1, "保存");
    mMenuApplicationBtn->addAction(m_ActionFileSave);
    connect(m_ActionFileSave, &QAction::triggered, this, &MainWindow::FileSave);

    m_ActionFileSaveAs = new QAction(QIcon(":/Icon/Icon/FileSaveAs.png"), tr("另存为"), this);
    m_ActionFileSaveAs->setStatusTip(tr("文件另存为"));
    //bindActionID(m_ActionFileSaveAs, -1, "新建");
    mMenuApplicationBtn->addAction(m_ActionFileSaveAs);
    connect(m_ActionFileSaveAs, &QAction::triggered, this, &MainWindow::FileSaveAs);

//        QAction* recentFileAction = nullptr;
//        for(int i = 0; i < 5; i++)
//        {
//            recentFileAction = new QAction(this);
//            recentFileAction->setVisible(false);
////            connect(recentFileAction, &QAction::triggered, this, [=]()
////            {
////                loadFile(recentFileAction->data().toString());
////            });
//            m_recentFileActionList.append(recentFileAction);
//        }

//        QMenu* recentFilesMenu = mMenuApplicationBtn->addMenu(tr("最近打开的文件"));
//        for(int i = 0; i < 5; i++)
//        {
//            recentFilesMenu->addAction(m_recentFileActionList.at(i));
//        }


    mMenuApplicationBtn->addSeparator();

    m_ActionAppSettings = new QAction(QIcon(":/Icon/Icon/FileNew.png"), tr("选项"), this);
    m_ActionAppSettings->setStatusTip(tr("选项设置"));
    m_ActionAppSettings->setToolTip("打开选项设置");
    //bindActionID(m_ActionAppSettings, -1, "新建");
    mMenuApplicationBtn->addAction(m_ActionAppSettings);

    SARibbonApplicationButton* appBtn = qobject_cast< SARibbonApplicationButton* >(btn);
    if (!appBtn) {
        return;
    }
    appBtn->setMenu(mMenuApplicationBtn);
}

void MainWindow::createCategoryMain(SARibbonCategory* page)
{
    SARibbonPannel* pannelFile = page->addPannel(("文件"));

    pannelFile->addLargeAction(m_ActionFileNew);
    pannelFile->addLargeAction(m_ActionFileOpen);
}

void MainWindow::createCategoryUserDefDlg(SARibbonCategory* page)
{
    //文件
    SARibbonPannel* pannelFile = page->addPannel(("文件"));

    QAction* ActionExit = new QAction(QIcon(":/Icon/Icon/Exit.png"), tr("退出"), this);
    ActionExit->setStatusTip(tr("退出对话框样式编辑器"));
    ActionExit->setToolTip("退出对话框样式编辑器");
    bindActionID(ActionExit, -1, "退出");
    connect(ActionExit, &QAction::triggered, this, &MainWindow::ExitDialogEdit);

    pannelFile->addLargeAction(ActionExit);
    pannelFile->addLargeAction(m_ActionFileNew);
    pannelFile->addLargeAction(m_ActionFileOpen);
    pannelFile->addLargeAction(m_ActionFileSave);

    //块操作
    SARibbonPannel* pannelBlock = page->addPannel(("块操作"));

    QAction* ActionBlockDelete = new QAction(QIcon(":/Icon/Icon/DeleteBlock.png"), tr("删除块"), this);
    ActionBlockDelete->setStatusTip(tr("删除此块"));
    ActionBlockDelete->setToolTip("删除此块");
    bindActionID(ActionBlockDelete, -1, "删除块");
    connect(ActionBlockDelete, &QAction::triggered, this, &MainWindow::BlockDelete);

    QAction* ActionBlockMoveUp = new QAction(QIcon(":/Icon/Icon/BlockMoveUp.png"), tr("上移块"), this);
    ActionBlockMoveUp->setStatusTip(tr("将此块向上移动"));
    ActionBlockMoveUp->setToolTip("将此块向上移动");
    bindActionID(ActionBlockMoveUp, -1, "上移块");
    connect(ActionBlockMoveUp, &QAction::triggered, this, &MainWindow::BlockMoveUp);

    QAction* ActionBlockMoveDown = new QAction(QIcon(":/Icon/Icon/BlockMoveDown.png"), tr("下移块"), this);
    ActionBlockMoveDown->setStatusTip(tr("将此块向下移动"));
    ActionBlockMoveDown->setToolTip("将此块向下移动");
    bindActionID(ActionBlockMoveDown, -1, "下移块");
    connect(ActionBlockMoveDown, &QAction::triggered, this, &MainWindow::BlockMoveDown);

    pannelBlock->addLargeAction(ActionBlockDelete);
    pannelBlock->addLargeAction(ActionBlockMoveUp);
    pannelBlock->addLargeAction(ActionBlockMoveDown);
}

void MainWindow::bindActionID(QAction* act, int ID, QString strName)
{
    User* pUser = new User();
    pUser->nID = ID;
    pUser->name = strName;
    act->setUserData(Qt::UserRole, pUser);
}

void MainWindow::closeEvent(QCloseEvent* e)
{
    if(m_MainWidget)
    {
        AutoSave();
        m_MainWidget->Close();
    }

    e->accept();
}

void MainWindow::AutoSave()
{
    DERoot* root = DERoot::GetDERoot();
    DEPart* part = root->GetPartCollection()->GetCurPart();
    if(part)
    {
        if(!part->Saved())
        {
            auto res = QMessageBox::question(this, tr("question"), tr("是否保存"));
            if(res == QMessageBox::Yes)
            {
                FileSave();
            }
        }
    }
}

void MainWindow::FileNew()
{
    AutoSave();

    DERoot* root = DERoot::GetDERoot();
    root->GetPartCollection()->FileNew();
    //界面
    ShowUIWindow(DEUIEdit);
    m_MainWidget->Refresh();
}

void MainWindow::FileOpen()
{
    AutoSave();
    DERoot* root = DERoot::GetDERoot();

    s_curFile = QFileDialog::getOpenFileName(this, tr("打开"), "", tr("xml文件(*.xml)"));
    QFile file(s_curFile);
    if (!file.open(QFileDevice::ReadOnly))
    {
        QMessageBox::information(NULL, "提示", "文件打开失败！");
        return;
    }

    QDomDocument* doc = new QDomDocument;
    // 将doc与file关联起来
    // 这个函数从IO设备dev中读取XML文档，如果内容被成功解析，则返回true;否则返回false。
    if (!doc->setContent(&file))
    {
        QMessageBox::information(NULL, "提示", "操作的文件不是XML文件！");
        file.close();
        return;
    }
    // 关联后可以关闭文件了
    file.close();

    //
    if(doc->documentElement().tagName() != "DEDialog")
    {
        QMessageBox::information(NULL, "提示", "该XML文件不符合本程序标准！");
        return;
    }

    root->GetPartCollection()->FileOpen(doc);
    //界面
    ShowUIWindow(DEUIEdit);
    m_MainWidget->Refresh();
}

void MainWindow::FileSave()
{
    if(s_curFile.isEmpty())
    {
        return FileSaveAs();
    }
    else
    {
        QFile file(s_curFile);
        if (!file.open(QFileDevice::ReadWrite | QFileDevice::Truncate))
        {
            QMessageBox::information(NULL, "提示", "文件打开或创建失败！");
            return;
        }
        file.close();

        DERoot* root = DERoot::GetDERoot();
        root->GetPartCollection()->FileSave(s_curFile);
    }
}

void MainWindow::FileSaveAs()
{
    s_curFile = QFileDialog::getSaveFileName(this, tr("另存为"), "", tr("xml文件(*.xml)"));
    if(s_curFile.isEmpty())
        return;

    return FileSave();
}

void MainWindow::ExitDialogEdit()
{
    AutoSave();

    DERoot* root = DERoot::GetDERoot();
    root->GetPartCollection()->FileDelete();

    //界面
    m_MainWidget->DialogClose();
    ShowUIWindow(DEUIWelcome);
}

void MainWindow::BlockDelete()
{
    if(m_MainWidget)
        m_MainWidget->BlockDelete();
}

void MainWindow::BlockMoveUp()
{
    if(m_MainWidget)
        m_MainWidget->BlockMoveUp();
}

void MainWindow::BlockMoveDown()
{
    if(m_MainWidget)
        m_MainWidget->BlockMoveDown();
}
