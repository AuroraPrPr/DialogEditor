#include "mainwindow.h"
#include "SARibbonBar.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QTranslator>
#include <QSettings>

//QTranslator *g_trans = NULL;
//QTranslator *g_transSys = NULL;

int main(int argc, char *argv[])
{
    // 以下是针对高分屏的设置，有高分屏需求都需要按照下面进行设置
    SARibbonBar::initHighDpi();

    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_DontUseNativeMenuBar);
    app.setOrganizationName(QStringLiteral("Developer Machines"));
    QFont f = app.font();
    f.setFamily(u8"微软雅黑");
    app.setFont(f);

    //Q_INIT_RESOURCE(DialogEditor);
    QCoreApplication::setApplicationName("DialogEditor");
    QCoreApplication::setOrganizationName("None");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription("个人项目");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open");
    parser.process(app);

//    //加载注册表中的语言
//    g_trans = new QTranslator;
//    g_transSys = new QTranslator;

//    QString curLang = readSetting();
//    if(curLang == "EN")
//    {
//        g_trans->load("Project_en.qm");
//        g_transSys->load("qt_en.qm");
//    }
//    else
//    {
//        g_trans->load("Project_cn.qm");
//        g_transSys->load("qt_zh_CN.qm");
//    }
//    app.installTranslator(g_trans);
//    app.installTranslator(g_transSys);

    MainWindow w;
    w.show();
    return app.exec();
}
