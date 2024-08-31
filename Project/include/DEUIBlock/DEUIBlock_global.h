#ifndef DEUIBLOCK_GLOBAL_H
#define DEUIBLOCK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DEUIBLOCK_LIBRARY)
#  define DEUIBLOCK_EXPORT Q_DECL_EXPORT
#else
#  define DEUIBLOCK_EXPORT Q_DECL_IMPORT
#endif

#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QActionGroup>
#include <QListView>
#include <QRadioButton>
#include <QMenu>
#include <QEvent>
#include <QCheckBox>
#include <QLineEdit>
#include <QMouseEvent>
#include <QSpinBox>
#include <QDoubleSpinBox>

typedef void(*CallBack1)(void *pFun);
typedef void(*CallBack2)(void *pFun, void *pData);

#define BlockHeight 32
#define IconSize 32
#define SIconSize 24

#endif // DEUIBLOCK_GLOBAL_H
