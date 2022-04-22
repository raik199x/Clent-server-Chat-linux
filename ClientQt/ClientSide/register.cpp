#include "register.h"
#include "recoveryconfirmation.h"
#include "ui_register.h"
#include <QMessageBox>

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setStyleSheet("color: #00FFFF; background-color: #2F4F4F");
    setWindowTitle(tr("Register menu"));
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
    }
    RecoveryConfirmation *window = new RecoveryConfirmation;
    window->setModal(true);
    window->exec();
    delete window;
    close();
}

