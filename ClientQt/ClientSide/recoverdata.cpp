#include "recoverdata.h"
#include "ui_recoverdata.h"
#include <QMessageBox>
#include <QDebug>

#include <arpa/inet.h>
#include <sys/socket.h>

RecoverData::RecoverData(QWidget *parent, char *ip) :
    QDialog(parent),
    ui(new Ui::RecoverData)
{
    ui->setupUi(this);
    this->setStyleSheet("color: #00FFFF; background-color: #2F4F4F");
    setWindowTitle(tr("Recover data"));
    ui->recoverykey->setMaxLength(400);
    ui->textEdit->setReadOnly(true);
    this->ip = ip;
}

RecoverData::~RecoverData()
{
    delete ui;
}

void RecoverData::on_back_clicked(){
    close();
}


void RecoverData::on_Confirm_clicked(){
    if(ui->recoverykey->text().isEmpty() == true){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Recovery key is not written"));
        return;
    } else if (ui->recoverykey->text().contains('~') == true){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Used forbidden symbol '~'"));
        return;
    }
    //preparing request
    QString response;

    //asking server for registration
    int RecSocket = -1;
    if((RecSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Client error: cant create socket"));
        return;
    }
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(3002);

    //Convert IPv4 and IPv6 addresses from text to binary
    if (inet_pton(AF_INET, ip, &server_adress.sin_addr) <= 0){
         QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Client error: Invalid address/ Address not supported"));
         return;
    }

    if (::connect(RecSocket, (struct sockaddr*)&server_adress, sizeof(server_adress)) < 0) {
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Server error: Client couldnt connect to server"));
        return;
    }
    //preparing message
    char *send_to_server;
    send_to_server = new char[205];
    send_to_server[0] = 'R';
    send_to_server[1] = 'E';
    send_to_server[2] = 'C';
    QString RecoveryKey = ui->recoverykey->text();
    for(int i = 3,j = 0;j < RecoveryKey.length();i++,j++)
        send_to_server[i] = RecoveryKey[j].toLatin1();
    send_to_server[206] = '\0';
    send(RecSocket,send_to_server,205,0);
    delete []send_to_server;
    send_to_server = new char[119];
    recv(RecSocket,send_to_server,120,0);

    for(int i = 0;send_to_server[i] != '\0';i++)
        response.append(send_to_server[i]);
    if(response == "critical"){
        ui->textEdit->setText(tr("Server error, please try again letter or contact the developer"));
        return;
    } else if (response == "notexist"){
        ui->textEdit->setText(tr("Not valid recovery key"));
        return;
    }

    QString display;
    display.append("Login: ");
    int i = 0;

    for(i = 0; response[i] != ':';i++)
        display.append(response[i]);
    display.append("\nPassword: ");
    i++;
    for(;i < response.length();i++)
        display.append(response[i]);
    ui->textEdit->setText(display);
}

