#include "mainwindow.h"
#include "register.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Color theme
    this->setFixedSize(QSize(550, 300));
    this->setStyleSheet("color: #00FFFF; background-color: #2F4F4F");

    ui->LoginWrite->setPlaceholderText(tr("created by @raik199x"));
    ui->LoginWrite->setStyleSheet("color: #00008B");

    ui->PasswordWrite->setPlaceholderText("****************");
    ui->PasswordWrite->setStyleSheet("color: #00008B");

    setWindowTitle(tr("Logging menu"));
    ui->LoginWrite->setMaxLength(16);
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
    Register *RegWindow = new Register;
    hide();
    RegWindow->setModal(true);
    RegWindow->exec();
    delete RegWindow;
    show();
}


void MainWindow::on_Login_clicked(){
    QString Login = ui->LoginWrite->text();
    //Error handling
    if(Login.isEmpty() == true){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Nickname can't be empty"));
        ui->LoginWrite->setStyleSheet("color: #F08080");
        return;
    } else if (Login.contains(' ') == true){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Nickname can't contain spaces"));
        ui->LoginWrite->setStyleSheet("color: #F08080");
        return;
    }
    qDebug() << Login;
}

