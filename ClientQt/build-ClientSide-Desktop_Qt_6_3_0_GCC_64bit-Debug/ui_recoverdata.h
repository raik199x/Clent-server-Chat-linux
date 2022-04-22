/********************************************************************************
** Form generated from reading UI file 'recoverdata.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECOVERDATA_H
#define UI_RECOVERDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_RecoverData
{
public:

    void setupUi(QDialog *RecoverData)
    {
        if (RecoverData->objectName().isEmpty())
            RecoverData->setObjectName(QString::fromUtf8("RecoverData"));
        RecoverData->resize(400, 300);

        retranslateUi(RecoverData);

        QMetaObject::connectSlotsByName(RecoverData);
    } // setupUi

    void retranslateUi(QDialog *RecoverData)
    {
        RecoverData->setWindowTitle(QCoreApplication::translate("RecoverData", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecoverData: public Ui_RecoverData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECOVERDATA_H
