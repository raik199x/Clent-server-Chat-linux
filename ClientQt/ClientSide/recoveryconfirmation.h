#ifndef RECOVERYCONFIRMATION_H
#define RECOVERYCONFIRMATION_H

#include <QDialog>

namespace Ui {
class RecoveryConfirmation;
}

class RecoveryConfirmation : public QDialog
{
    Q_OBJECT

public:
    explicit RecoveryConfirmation(QWidget *parent = nullptr);
    ~RecoveryConfirmation();

private:
    Ui::RecoveryConfirmation *ui;
};

#endif // RECOVERYCONFIRMATION_H
