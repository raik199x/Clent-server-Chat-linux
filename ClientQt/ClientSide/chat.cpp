#include "chat.h"
#include "qscreen.h"
#include "ui_chat.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <QMessageBox>
#include <QDebug>

Chat::Chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
}

Chat::Chat(QWidget *parent,QString Nickname, int *ConnectionDescriptor) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    this->setStyleSheet("color: #00FFFF; background-color: #2F4F4F");

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int x = (screenGeometry.width()-width()) / 2;
    int y = (screenGeometry.height()-height()) / 2;
    move(x, y);

    this->Nickname = Nickname;
    this->ConnectionDescriptor = ConnectionDescriptor;
}


Chat::~Chat()
{
    delete ui;
}

void Chat::on_logout_clicked(){
    char buffer[2] = {'#','\0'};
    send((*ConnectionDescriptor),buffer,3,0);
    ::close((*ConnectionDescriptor));
    close();
}

