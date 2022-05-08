#include "chat.h"
#include "qscreen.h"
#include "ui_chat.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <QMessageBox>
#include <QDebug>
#include <QScrollBar>
#include <QCloseEvent>

Chat::Chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
}

void Chat::RecMessage(){
    char buffer[500] = {'1'};
    //first we make Online users
    while(1){
        recv((*ConnectionDescriptor),buffer,20,0);
        if(buffer[0] == 'D')
            break;
        QString temp;
        for(int i = 3; buffer[i] != '\0';i++)
            temp.append(buffer[i]);
        ui->usersOnline->append(temp);
    }

    while(1){
        recv((*ConnectionDescriptor),buffer,400,0);
        if(buffer[0] == '#')
            break;
        else if(buffer[0] == 'M' && buffer[1] == 'E' && buffer[2] == 'S'){
            QString temp;;
            for(int i = 3; buffer[i] != '\0';i++)
                temp.append(buffer[i]);
            ui->ChatZone->append(temp);
            ui->ChatZone->append("");
            ui->ChatZone->verticalScrollBar()->setValue(ui->ChatZone->verticalScrollBar()->maximum());
        } else if(buffer[0] == 'A' && buffer[1] == 'D' && buffer[2] == 'D'){
            QString temp;
            for(int i = 3; buffer[i] != '\0';i++)
                temp.append(buffer[i]);
            ui->usersOnline->append(temp);
        } else if(buffer[0] == 'D' && buffer[1] == 'I' && buffer[2] == 'S'){
            emit ClearUsersOnline(buffer);
        }
    }

    qDebug() << "Thread closed";
    this->IsDisconnectedFromServer = true;
    emit Disconnected();
    return;
}

void Chat::CleaningUsers(char buffer[500]){
    QString oldOnline = ui->usersOnline->toPlainText(), temp;
    ui->usersOnline->clear();
    oldOnline.append('\n');
    //preparation, checking length of buffer
    int size = 0;
    while(buffer[size+3] != '\0')
        size++;
    //running through users
    for(int i = 0; i < oldOnline.length();i++){
        //if this is end of nickname
        if(oldOnline[i] == '\n'){
            if(size != temp.length()){
                ui->usersOnline->append(temp);
                temp.clear();
                continue;
            }
            bool result = true;
            //we check if this is nickname that need to be deleted
            for(int j = 3; buffer[j] != '\0';j++)
                if(buffer[j] != temp[j-3]){
                    result = false;
                    break;
                }
            if(result == false)
                ui->usersOnline->append(temp);
            temp.clear();
            continue;
        }
        temp.append(oldOnline[i]);
    }
}

Chat::Chat(QWidget *parent,QString Nickname, int *ConnectionDescriptor) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    this->setStyleSheet("color: #00FFFF; background-color: #2F4F4F");

    this->Nickname = Nickname;
    this->ConnectionDescriptor = ConnectionDescriptor;
    this->ListenThread = new std::thread(&Chat::RecMessage, this);
    this->IsDisconnectedFromServer = false;

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int x = (screenGeometry.width()-width()) / 2;
    int y = (screenGeometry.height()-height()) / 2;
    move(x, y);

    ui->SymbolsInLine->setText("0/100");
    ui->userNickname->setText(Nickname);

    connect(this,&Chat::Disconnected,this,&Chat::on_logout_clicked);
    connect(this,&Chat::ClearUsersOnline,this,&Chat::CleaningUsers);
}


Chat::~Chat()
{
    delete ui;
}

void Chat::on_logout_clicked(){
    if(this->IsDisconnectedFromServer == true){
        QMessageBox::warning(this,QObject::tr("Disconnected"), QObject::tr("You were disconnected from server"));
        qDebug() << "Forcefully disconnected";
    }
    close();
}


void Chat::on_Send_clicked()
{
    QString temp = ui->textMessage->toPlainText();
    ui->textMessage->setText("");

    char *buffer = new char[122]; buffer[0] = 'M'; buffer[1] = 'E'; buffer[2] = 'S';
    int i = 3;
    for(; i-3 < this->Nickname.length();i++)
        buffer[i] = Nickname[i-3].toLatin1();
    buffer[i++] = ':';
    for(int j = 0; j < temp.length();j++){
        buffer[i++] = temp[j].toLatin1();
        buffer[i] = '\0';
    }
    send((*ConnectionDescriptor),buffer,122,0);
    delete []buffer;
}

void Chat::closeEvent(QCloseEvent *event){
    if(this->IsDisconnectedFromServer != true){
        char buffer[2] = {'#','\0'};
        send((*ConnectionDescriptor),buffer,3,0);
        this->ListenThread->join();
    }
    ::close((*ConnectionDescriptor));
    delete ConnectionDescriptor;
    event->accept();
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

