/********************************************************************************
** Form generated from reading UI file 'chat.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_H
#define UI_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chat
{
public:
    QWidget *centralwidget;
    QLabel *YourNickname;
    QScrollArea *ClientChat;
    QWidget *scrollAreaWidgetContents;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QScrollArea *UsersOnline;
    QWidget *scrollAreaWidgetContents_2;
    QPlainTextEdit *WriteMessage;
    QPushButton *SendMessage;
    QPushButton *LogOut;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Chat)
    {
        if (Chat->objectName().isEmpty())
            Chat->setObjectName(QString::fromUtf8("Chat"));
        Chat->resize(800, 600);
        centralwidget = new QWidget(Chat);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        YourNickname = new QLabel(centralwidget);
        YourNickname->setObjectName(QString::fromUtf8("YourNickname"));
        YourNickname->setGeometry(QRect(410, 20, 151, 16));
        ClientChat = new QScrollArea(centralwidget);
        ClientChat->setObjectName(QString::fromUtf8("ClientChat"));
        ClientChat->setGeometry(QRect(10, 80, 551, 371));
        ClientChat->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 549, 369));
        ClientChat->setWidget(scrollAreaWidgetContents);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(580, 10, 201, 71));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        UsersOnline = new QScrollArea(centralwidget);
        UsersOnline->setObjectName(QString::fromUtf8("UsersOnline"));
        UsersOnline->setGeometry(QRect(580, 80, 201, 371));
        UsersOnline->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 199, 369));
        UsersOnline->setWidget(scrollAreaWidgetContents_2);
        WriteMessage = new QPlainTextEdit(centralwidget);
        WriteMessage->setObjectName(QString::fromUtf8("WriteMessage"));
        WriteMessage->setGeometry(QRect(10, 470, 551, 70));
        SendMessage = new QPushButton(centralwidget);
        SendMessage->setObjectName(QString::fromUtf8("SendMessage"));
        SendMessage->setGeometry(QRect(580, 470, 201, 71));
        LogOut = new QPushButton(centralwidget);
        LogOut->setObjectName(QString::fromUtf8("LogOut"));
        LogOut->setGeometry(QRect(20, 20, 80, 22));
        Chat->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Chat);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 19));
        Chat->setMenuBar(menubar);
        statusbar = new QStatusBar(Chat);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Chat->setStatusBar(statusbar);

        retranslateUi(Chat);

        QMetaObject::connectSlotsByName(Chat);
    } // setupUi

    void retranslateUi(QMainWindow *Chat)
    {
        Chat->setWindowTitle(QCoreApplication::translate("Chat", "MainWindow", nullptr));
        YourNickname->setText(QCoreApplication::translate("Chat", "NNNNNNNNNNNNNNNN", nullptr));
        label_2->setText(QString());
        label_3->setText(QCoreApplication::translate("Chat", "Users online", nullptr));
        SendMessage->setText(QCoreApplication::translate("Chat", "Send", nullptr));
        LogOut->setText(QCoreApplication::translate("Chat", "LogOut", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Chat: public Ui_Chat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_H
