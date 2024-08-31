#pragma once

#include <QString>
#include <QPoint>
#include <QSize>

extern void CalPopWindowAccordBoder(int &x, int &y, QSize popWinSize);
extern void settingWritePos(QString valueName, QPoint point,
                            QPoint parentPoint, bool isWriteRelaValue);
extern QStringList settingReadPos(QString valueName, int &x, int &y);
extern bool DlgGetPos(int &x, int &y);
