/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *NichnameWrite;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *PasswordWrite;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *RepPaswwordWrite;
    QHBoxLayout *horizontalLayout;
    QPushButton *Confirm;
    QPushButton *Back;

    void setupUi(QDialog *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName(QString::fromUtf8("Register"));
        Register->resize(400, 300);
        verticalLayoutWidget = new QWidget(Register);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 391, 291));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        NichnameWrite = new QLineEdit(verticalLayoutWidget);
        NichnameWrite->setObjectName(QString::fromUtf8("NichnameWrite"));

        horizontalLayout_2->addWidget(NichnameWrite);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        PasswordWrite = new QLineEdit(verticalLayoutWidget);
        PasswordWrite->setObjectName(QString::fromUtf8("PasswordWrite"));

        horizontalLayout_3->addWidget(PasswordWrite);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        RepPaswwordWrite = new QLineEdit(verticalLayoutWidget);
        RepPaswwordWrite->setObjectName(QString::fromUtf8("RepPaswwordWrite"));

        horizontalLayout_4->addWidget(RepPaswwordWrite);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Confirm = new QPushButton(verticalLayoutWidget);
        Confirm->setObjectName(QString::fromUtf8("Confirm"));

        horizontalLayout->addWidget(Confirm);

        Back = new QPushButton(verticalLayoutWidget);
        Back->setObjectName(QString::fromUtf8("Back"));

        horizontalLayout->addWidget(Back);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QDialog *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Register", "Nickname      ", nullptr));
        label_2->setText(QCoreApplication::translate("Register", "Password       ", nullptr));
        label_3->setText(QCoreApplication::translate("Register", "Rep.Password", nullptr));
        Confirm->setText(QCoreApplication::translate("Register", "Confrim", nullptr));
        Back->setText(QCoreApplication::translate("Register", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
