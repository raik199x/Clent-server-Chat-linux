#include "recoverdata.h"
#include "ui_recoverdata.h"

RecoverData::RecoverData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecoverData)
{
    ui->setupUi(this);
}

RecoverData::~RecoverData()
{
    delete ui;
}
