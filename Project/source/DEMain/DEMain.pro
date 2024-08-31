QT       += core gui xml widgets

CONFIG += c++14

##_HAS_STD_BYTE = 0 避免使用C++17时 报错error C2872 : "byte":不明确的符号
#DEFINES += _HAS_STD_BYTE = 0
#TARGET = K3DUIMgr
#DEFINES += K3DUIMGR_LIBRARY

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DEBlockTree.cpp \
    DEDialogTree.cpp \
    DEMainWidget.cpp \
    DEPropTree.cpp \
    DETreeTable.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BindButtonID.h \
    DEBlockTree.h \
    DEDelegate.h \
    DEDialogTree.h \
    DEMainWidget.h \
    DEPropTree.h \
    DETreeTable.h \
    SARibbonHeaders.h \
    mainwindow.h

RESOURCES += \
    DEMain.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += ../../include
INCLUDEPATH += ../../include/DERoot
INCLUDEPATH += ../../include/DEPart
INCLUDEPATH += ../../include/DEUIBlock
LIBS += -lDERoot -lDEPart -lDEUIBlock

include($$PWD/../../../Licensed/SARibbon/importSARibbonBarLib.pri)
include(../OutputDir.pri)

RC_FILE += logo.rc
