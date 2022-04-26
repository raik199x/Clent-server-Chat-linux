#include "register.h"
#include "recoveryconfirmation.h"
#include "ui_register.h"
#include <QMessageBox>
#include <arpa/inet.h>
#include <sys/socket.h>

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setStyleSheet("color: #00FFFF; background-color: #2F4F4F");
    setWindowTitle(tr("Register menu"));
    ui->NichnameWrite->setMaxLength(16);
    ui->PasswordWrite->setMaxLength(100);
    ui->RepPaswwordWrite->setMaxLength(100);
}

Register::~Register(){
    delete ui;
}

void Register::on_Back_clicked(){
   close();
}


void Register::on_Confirm_clicked(){
    //error handling
    if(ui->PasswordWrite->text().isEmpty() == true){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Empty password"));
        return;
    } else if (ui->NichnameWrite->text().isEmpty() == true){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Empty nickname"));
        return;
    } else if(ui->PasswordWrite->text() != ui->RepPaswwordWrite->text()){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Passwords are not equal"));
        return;
    } else if(ui->NichnameWrite->text().contains(':') == true || ui->NichnameWrite->text().contains('~') == true){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Nickname contains forbidden symbols '~:'"));
        return;
    } else if(ui->PasswordWrite->text().contains(':') == true || ui->PasswordWrite->text().contains('~') == true){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Passwords contains forbidden symbols '~:"));
        return;
    }
    QString response;

    //asking server for registration
    int RegSocket = -1;
    if((RegSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Client error: cant create socket"));
        return;
    }
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(3002);

    //Convert IPv4 and IPv6 addresses from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &server_adress.sin_addr) <= 0){
         QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Client error: Invalid address/ Address not supported"));
         return;
    }

    if (::connect(RegSocket, (struct sockaddr*)&server_adress, sizeof(server_adress)) < 0) {
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Server error: Client couldnt connect to server"));
        return;
    }
    //preparing message
    char *send_to_server; int bytes = 3 + ui->PasswordWrite->text().size() + ui->NichnameWrite->text().size()+2;
    send_to_server = new char[bytes];
    send_to_server[0] = 'R';
    send_to_server[1] = 'E';
    send_to_server[2] = 'G';
    int i = 3;
    QString Nickname = ui->NichnameWrite->text();
    QString Pass = ui->PasswordWrite->text();
    for(int j = 0; j < ui->NichnameWrite->text().size();j++)
        send_to_server[i++] = Nickname[j].toLatin1();
    send_to_server[i++] = ':';
    for(int j = 0; j < ui->PasswordWrite->text().size();j++)
        send_to_server[i++] = Pass[j].toLatin1();
    send_to_server[i] = '\0';
    send(RegSocket,send_to_server,bytes,0);
    delete []send_to_server;
    send_to_server = new char[202];
    recv(RegSocket,send_to_server,202,0);

    for(int i = 0;send_to_server[i] != '\0';i++)
        response.append(send_to_server[i]);
    if(response == "exist"){
        QMessageBox::warning(this,QObject::tr("Warning"), QObject::tr("User with this nickname is already exist"));
        return;
    } else if (response == "critical"){
        QMessageBox::warning(this,QObject::tr("Warning"), QObject::tr("Server error: get critical response, please try again later or contact the developer"));
        return;
    }
    RecoveryConfirmation *window = new RecoveryConfirmation(nullptr,response);
    window->setModal(true);
    window->exec();
    delete window;
    delete[] send_to_server;
    close();
}

