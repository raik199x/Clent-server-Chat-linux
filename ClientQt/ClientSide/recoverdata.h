#ifndef RECOVERDATA_H
#define RECOVERDATA_H

#include <QDialog>

namespace Ui {
class RecoverData;
}

class RecoverData : public QDialog
{
    Q_OBJECT

public:
    explicit RecoverData(QWidget *parent = nullptr, char *ip = nullptr);
    ~RecoverData();

private slots:
    void on_back_clicked();

    void on_Confirm_clicked();

private:
    char *ip;
    Ui::RecoverData *ui;
};

#endif // RECOVERDATA_H
