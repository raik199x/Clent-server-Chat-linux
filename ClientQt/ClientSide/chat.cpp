#include "chat.h"
#include "ui_chat.h"
#include "mainwindow.h"
#include "qscreen.h"

Chat::Chat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    this->setStyleSheet("color: #00FFFF; background-color: #2F4F4F");

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int x = (screenGeometry.width()-width()) / 2;
    int y = (screenGeometry.height()-height()) / 2;
    move(x, y);
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_LogOut_clicked()
{
    MainWindow *window = new MainWindow;
    window->show();
    close();
}

