/********************************************************************************
** Form generated from reading UI file 'DEDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEDIALOG_H
#define UI_DEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_DEDialog
{
public:

    void setupUi(QDialog *DEDialog)
    {
        if (DEDialog->objectName().isEmpty())
            DEDialog->setObjectName(QString::fromUtf8("DEDialog"));
        DEDialog->resize(350, 300);

        retranslateUi(DEDialog);

        QMetaObject::connectSlotsByName(DEDialog);
    } // setupUi

    void retranslateUi(QDialog *DEDialog)
    {
        DEDialog->setWindowTitle(QCoreApplication::translate("DEDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DEDialog: public Ui_DEDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEDIALOG_H
