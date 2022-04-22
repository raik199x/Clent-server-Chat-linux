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
    explicit RecoverData(QWidget *parent = nullptr);
    ~RecoverData();

private:
    Ui::RecoverData *ui;
};

#endif // RECOVERDATA_H
