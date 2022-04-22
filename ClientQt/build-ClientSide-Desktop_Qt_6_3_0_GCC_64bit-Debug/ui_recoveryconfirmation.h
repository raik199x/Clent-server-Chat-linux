/********************************************************************************
** Form generated from reading UI file 'recoveryconfirmation.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECOVERYCONFIRMATION_H
#define UI_RECOVERYCONFIRMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_RecoveryConfirmation
{
public:

    void setupUi(QDialog *RecoveryConfirmation)
    {
        if (RecoveryConfirmation->objectName().isEmpty())
            RecoveryConfirmation->setObjectName(QString::fromUtf8("RecoveryConfirmation"));
        RecoveryConfirmation->resize(400, 300);

        retranslateUi(RecoveryConfirmation);

        QMetaObject::connectSlotsByName(RecoveryConfirmation);
    } // setupUi

    void retranslateUi(QDialog *RecoveryConfirmation)
    {
        RecoveryConfirmation->setWindowTitle(QCoreApplication::translate("RecoveryConfirmation", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecoveryConfirmation: public Ui_RecoveryConfirmation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECOVERYCONFIRMATION_H
