#include "mainwindow.h"
#include "chat.h"
#include "qscreen.h"
#include "recoverdata.h"
#include "register.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

#include <arpa/inet.h>
#include <sys/socket.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Color theme
    this->setFixedSize(QSize(540, 330));
    this->setStyleSheet("color: #00FFFF; background-color: #2F4F4F");

    ui->LoginWrite->setPlaceholderText(tr("created by @raik199x"));
    ui->LoginWrite->setStyleSheet("color: #00008B");

    ui->PasswordWrite->setPlaceholderText("****************");
    ui->PasswordWrite->setStyleSheet("color: #00008B");

    ui->ipWrite->setPlaceholderText(tr("127.0.0.1"));
    ui->ipWrite->setText("127.0.0.1");
    ui->ipWrite->setStyleSheet("color: #00FFFF");

    setWindowTitle(tr("Logging menu"));
    ui->LoginWrite->setMaxLength(16);
    ui->PasswordWrite->setMaxLength(100);

    //placing loggin menu in the center of screen
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int x = (screenGeometry.width()-width()) / 2;
    int y = (screenGeometry.height()-height()) / 2;
    move(x, y);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_LoginWrite_textEdited(const QString &arg1){
    if(arg1.isEmpty() == true)
        ui->LoginWrite->setStyleSheet("color: #00008B");
    else
        ui->LoginWrite->setStyleSheet("color: #00FFFF");
}


void MainWindow::on_PasswordWrite_textEdited(const QString &arg1){
    if(arg1.isEmpty() == true)
        ui->PasswordWrite->setStyleSheet("color: #00008B");
    else
        ui->PasswordWrite->setStyleSheet("color: #00FFFF");

}

void MainWindow::on_Register_clicked(){
    Register *RegWindow = new Register(this,ui->ipWrite->text());
    hide();
    RegWindow->setModal(true);
    RegWindow->exec();
    delete RegWindow;
    show();
}


void MainWindow::on_Login_clicked(){
    //Error handling
    if(ui->LoginWrite->text().isEmpty() == true){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Nickname can't be empty"));
        ui->LoginWrite->setStyleSheet("color: #F08080");
        return;
    } else if (ui->LoginWrite->text().contains(' ') == true){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Nickname can't contain spaces"));
        ui->LoginWrite->setStyleSheet("color: #F08080");
        return;
    } else if (ui->PasswordWrite->text().isEmpty() == true){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Empty password"));
        ui->PasswordWrite->setStyleSheet("color: #F08080");
        return;
    } else if(ui->LoginWrite->text().contains(':') == true || ui->LoginWrite->text().contains('~') == true){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Nickname contains forbidden symbols '~:'"));
        ui->LoginWrite->setStyleSheet("color: #F08080");
        return;
    } else if(ui->PasswordWrite->text().contains(':') == true || ui->PasswordWrite->text().contains('~') == true){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Passwords contains forbidden symbols '~:"));
        ui->PasswordWrite->setStyleSheet("color: #F08080");
        return;
    } else if(ui->ipWrite->text().length() > 20){
        QMessageBox::critical(this,QObject::tr("Warning"), QObject::tr("Only ipv4 supported"));
        ui->ipWrite->setStyleSheet("color: #F08080");
    }

    //asking server for registration
    int *ConnectionDescriptor = new int; (*ConnectionDescriptor) = -1;
    if(((*ConnectionDescriptor) = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Client error: cant create socket"));
        delete ConnectionDescriptor;
        return;
    }
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(3002);

    QString tempIp;
    char *ip = new char[20]; tempIp = ui->ipWrite->text();
    for(int i = 0; i < tempIp.length();i++){
        ip[i] = tempIp[i].toLatin1();
    }
    //Convert IPv4 and IPv6 addresses from text to binary
    if (inet_pton(AF_INET, ip, &server_adress.sin_addr) <= 0){
         QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Client error: Invalid address/ Address not supported"));
         delete ConnectionDescriptor;
         return;
    }
    if (::connect((*ConnectionDescriptor), (struct sockaddr*)&server_adress, sizeof(server_adress)) < 0) {
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Server error: Client couldnt connect to server"));
        delete ConnectionDescriptor;
        return;
    }
    //preparing message
    char *send_to_server = new char[190];
    send_to_server[0] = 'C';
    send_to_server[1] = 'O';
    send_to_server[2] = 'N';
    int i = 3;

    QString Nickname = ui->LoginWrite->text(), Password = ui->PasswordWrite->text();
    for(; i-3 < Nickname.length(); i++)
        send_to_server[i] = Nickname[i-3].toLatin1();
    send_to_server[i++] = ':';
    for(int j = 0; j < Password.length();j++)
        send_to_server[i++] = Password[j].toLatin1();
    send_to_server[i] = '\0';
    send((*ConnectionDescriptor),send_to_server,190,0);
    delete []send_to_server;
    send_to_server = new char[202];
    recv((*ConnectionDescriptor),send_to_server,202,0);

    QString temp;
    for(i = 0; send_to_server[i] != '\0';i++)
        temp.append(send_to_server[i]);
    delete[] send_to_server;
    if(temp == "BAD"){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Wrong login or password"));
        delete ConnectionDescriptor;
        return;
    }

    //if connection accepted - opening chat
    hide();
    Chat *window = new Chat(nullptr,Nickname,ConnectionDescriptor);
    window->setModal(true);
    window->exec();
    show();
    delete window;
}


void MainWindow::on_Recover_clicked(){
    if(ui->ipWrite->text().length() > 20){
        QMessageBox::critical(this,QObject::tr("Warning"), QObject::tr("Only ipv4 supported"));
        ui->ipWrite->setStyleSheet("color: #F08080");
        return;
    }
    char *ip = new char[20];
    QString temp = ui->ipWrite->text();
    for(int i = 0; i < temp.length();i++)
        ip[i] = temp[i].toLatin1();
    RecoverData *window = new RecoverData(this,ip);
    window->setModal(true);
    window->exec();
    delete []ip;
    delete window;
}


void MainWindow::on_ipWrite_textChanged(const QString &arg1){
    if(arg1.isEmpty() == true)
        ui->ipWrite->setStyleSheet("color: #00008B");
    else
        ui->ipWrite->setStyleSheet("color: #00FFFF");
}

