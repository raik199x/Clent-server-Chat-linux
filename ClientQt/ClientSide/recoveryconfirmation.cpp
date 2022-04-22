#include "recoveryconfirmation.h"
#include "ui_recoveryconfirmation.h"

RecoveryConfirmation::RecoveryConfirmation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecoveryConfirmation)
{
    ui->setupUi(this);
}

RecoveryConfirmation::~RecoveryConfirmation()
{
    delete ui;
}
