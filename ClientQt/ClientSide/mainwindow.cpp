#include "mainwindow.h"
#include "chat.h"
#include "qscreen.h"
#include "recoverdata.h"
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
    Register *RegWindow = new Register;
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
    }
    Chat *window = new Chat;
    window->show();
    close();
}


void MainWindow::on_Recover_clicked(){
    RecoverData *window = new RecoverData;
    window->setModal(true);
    window->exec();
    delete window;
}

