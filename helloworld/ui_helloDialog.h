/********************************************************************************
** Form generated from reading UI file 'helloDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLODIALOG_H
#define UI_HELLODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_helloDialog
{
public:

    void setupUi(QDialog *helloDialog)
    {
        if (helloDialog->objectName().isEmpty())
            helloDialog->setObjectName(QString::fromUtf8("helloDialog"));
        helloDialog->resize(400, 300);

        retranslateUi(helloDialog);

        QMetaObject::connectSlotsByName(helloDialog);
    } // setupUi

    void retranslateUi(QDialog *helloDialog)
    {
        helloDialog->setWindowTitle(QApplication::translate("helloDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class helloDialog: public Ui_helloDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLODIALOG_H
