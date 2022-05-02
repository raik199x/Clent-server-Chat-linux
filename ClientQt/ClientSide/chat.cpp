#include "chat.h"
#include "qscreen.h"
#include "ui_chat.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <QMessageBox>
#include <QDebug>
#include <QScrollBar>

Chat::Chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
}

void Chat::RecMessage(){
    char buffer[1000] = {'1'};
    while(1){
        ui->ChatZone->verticalScrollBar()->setValue(ui->ChatZone->verticalScrollBar()->maximum());
        recv((*ConnectionDescriptor),buffer,1000,0);
        if(buffer[0] == '#')
            break;
        QString temp;;
        for(int i = 3; buffer[i] != '\0';i++)
            temp.append(buffer[i]);
        ui->ChatZone->append(temp);
        ui->ChatZone->append("");
    }
    qDebug() << "Thread closed";
    this->IsDisconnectedFromServer = true;
    emit Disconnected();
    return;
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

    ui->SymbolsInLine->setText("0/100");
    ui->userNickname->setText(Nickname);

    this->Nickname = Nickname;
    this->ConnectionDescriptor = ConnectionDescriptor;
    this->ListenThread = new std::thread(&Chat::RecMessage, this);
    this->IsDisconnectedFromServer = false;

    connect(this,&Chat::Disconnected,this,&Chat::on_logout_clicked);
}


Chat::~Chat()
{
    delete ui;
}

void Chat::on_logout_clicked(){
    if(this->IsDisconnectedFromServer == true){
        QMessageBox::warning(this,QObject::tr("Disconnected"), QObject::tr("You were disconnected from server"));
        ::close((*ConnectionDescriptor));
        delete ConnectionDescriptor;
        qDebug() << "Forcefully disconnected";
        close();
    }
    char buffer[2] = {'#','\0'};
    send((*ConnectionDescriptor),buffer,3,0);
    this->ListenThread->join();
    ::close((*ConnectionDescriptor));
    close();
}


void Chat::on_Send_clicked()
{
    QString temp = ui->textMessage->toPlainText();
    ui->textMessage->setText("");

    char *buffer = new char[105]; buffer[0] = 'M'; buffer[1] = 'E'; buffer[2] = 'S';
    for(int i = 3; i-3 < temp.length();i++){
        buffer[i] = temp[i-3].toLatin1();
        buffer[i+1] = '\0';
    }
    send((*ConnectionDescriptor),buffer,105,0);
    delete []buffer;
}


void Chat::on_textMessage_textChanged()
{
    QString temp = ui->textMessage->toPlainText();
    if(temp.length() >= 101){
        temp = temp.chopped(1);
        ui->textMessage->setText(temp);
    }
    temp = QString::number(temp.length()) + "/100";
    ui->SymbolsInLine->setText(temp);
}

