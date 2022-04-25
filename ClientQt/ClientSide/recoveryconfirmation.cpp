#include "recoveryconfirmation.h"
#include "ui_recoveryconfirmation.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

RecoveryConfirmation::RecoveryConfirmation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecoveryConfirmation)
{
    ui->setupUi(this);
    setWindowTitle(tr("Recovery info"));
    setStyleSheet("color: #00FFFF; background-color: #2F4F4F");
    ui->textEdit->setReadOnly(true);

    ui->RecoveryKey->setReadOnly(true);
    ui->RecoveryKey->setText("Test text");
}

RecoveryConfirmation::RecoveryConfirmation(QWidget *parent, QString info) :
    QDialog(parent),
    ui(new Ui::RecoveryConfirmation)
{
    ui->setupUi(this);
    setWindowTitle(tr("Recovery info"));
    setStyleSheet("color: #00FFFF; background-color: #2F4F4F");
    ui->textEdit->setReadOnly(true);

    ui->RecoveryKey->setReadOnly(true);
    ui->RecoveryKey->setText(info);
}

RecoveryConfirmation::~RecoveryConfirmation()
{
    delete ui;
}

void RecoveryConfirmation::on_pushButton_2_clicked(){
    close();
}


void RecoveryConfirmation::on_pushButton_clicked(){
    QString Path = QFileDialog::getExistingDirectory(this,"Choose Folder");
    if(Path.isEmpty() == true)
        return;
    QFile File(Path+"/ChatRecoveryKey.txt");
    if(!File.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::critical(this,QObject::tr("Error"), QObject::tr("Couldn't create file"));
        return;
    }
    QTextStream out(&File);
    out << ui->RecoveryKey->text();
    File.close();
    QMessageBox::information(this,QObject::tr("info"), QObject::tr("File successfuly saved"));
}

