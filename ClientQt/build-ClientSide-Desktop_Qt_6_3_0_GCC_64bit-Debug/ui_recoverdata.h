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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecoverData
{
public:
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *recoverykey;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *Confirm;
    QPushButton *back;

    void setupUi(QDialog *RecoverData)
    {
        if (RecoverData->objectName().isEmpty())
            RecoverData->setObjectName(QString::fromUtf8("RecoverData"));
        RecoverData->resize(380, 286);
        verticalLayoutWidget_2 = new QWidget(RecoverData);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 0, 371, 271));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        recoverykey = new QLineEdit(verticalLayoutWidget_2);
        recoverykey->setObjectName(QString::fromUtf8("recoverykey"));

        verticalLayout->addWidget(recoverykey);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        Confirm = new QPushButton(verticalLayoutWidget_2);
        Confirm->setObjectName(QString::fromUtf8("Confirm"));

        horizontalLayout->addWidget(Confirm);

        back = new QPushButton(verticalLayoutWidget_2);
        back->setObjectName(QString::fromUtf8("back"));

        horizontalLayout->addWidget(back);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(RecoverData);

        QMetaObject::connectSlotsByName(RecoverData);
    } // setupUi

    void retranslateUi(QDialog *RecoverData)
    {
        RecoverData->setWindowTitle(QCoreApplication::translate("RecoverData", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("RecoverData", "Enter recovery key:", nullptr));
        Confirm->setText(QCoreApplication::translate("RecoverData", "Confirm", nullptr));
        back->setText(QCoreApplication::translate("RecoverData", "back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecoverData: public Ui_RecoverData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECOVERDATA_H
