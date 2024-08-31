QT       += core gui widgets

TEMPLATE = lib
TARGET = DEUIBlock
DEFINES += DEUIBLOCK_LIBRARY

CONFIG += c++14

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
    DEBlockAngularDimension.cpp \
    DEBlockBasicBase.cpp \
    DEBlockCommon.cpp \
    DEBlockDimension.cpp \
    DEBlockDouble.cpp \
    DEBlockEnumeration.cpp \
    DEBlockGroup.cpp \
    DEBlockInt.cpp \
    DEBlockLabel.cpp \
    DEBlockLayoutBase.cpp \
    DEBlockLinearDimension.cpp \
    DEBlockNumBase.cpp \
    DEBlockObject.cpp \
    DEBlockRadiusDimension.cpp \
    DEBlockSelectBase.cpp \
    DEBlockToggle.cpp \
    DECtrlLineEdit.cpp

HEADERS += \
    ../../include/DEUIBlock/DEBlockAngularDimension.h \
    ../../include/DEUIBlock/DEBlockBasicBase.h \
    ../../include/DEUIBlock/DEBlockCommon.h \
    ../../include/DEUIBlock/DEBlockDimension.h \
    ../../include/DEUIBlock/DEBlockDouble.h \
    ../../include/DEUIBlock/DEBlockEnumeration.h \
    ../../include/DEUIBlock/DEBlockGroup.h \
    ../../include/DEUIBlock/DEBlockInt.h \
    ../../include/DEUIBlock/DEBlockLabel.h \
    ../../include/DEUIBlock/DEBlockLayoutBase.h \
    ../../include/DEUIBlock/DEBlockLinearDimension.h \
    ../../include/DEUIBlock/DEBlockNumBase.h \
    ../../include/DEUIBlock/DEBlockObject.h \
    ../../include/DEUIBlock/DEBlockRadiusDimension.h \
    ../../include/DEUIBlock/DEBlockSelectBase.h \
    ../../include/DEUIBlock/DEBlockToggle.h \
    ../../include/DEUIBlock/DEUIBlock_global.h \
    DECtrlLineEdit.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += ../../include
INCLUDEPATH += ../../include/DEPart
INCLUDEPATH += ../../include/DEUIBlock
LIBS += -lDERoot -lDEPart

include(../OutputDir.pri)

RESOURCES += \
    DEBlock.qrc
