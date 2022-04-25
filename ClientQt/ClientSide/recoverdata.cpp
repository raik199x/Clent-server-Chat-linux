#include "recoverdata.h"
#include "ui_recoverdata.h"

RecoverData::RecoverData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecoverData)
{
    ui->setupUi(this);
    this->setStyleSheet("color: #00FFFF; background-color: #2F4F4F");
    setWindowTitle(tr("Recover data"));
}

RecoverData::~RecoverData()
{
    delete ui;
}

void RecoverData::on_back_clicked(){
    close();
}

