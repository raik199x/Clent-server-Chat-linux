#ifndef CHAT_H
#define CHAT_H

#include <QDialog>

namespace Ui {
class Chat;
}

class Chat : public QDialog
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = nullptr);
    explicit Chat(QWidget *parent = nullptr, QString Nickname = "", int *ConnectionDescriptor = nullptr);
    ~Chat();

private slots:
    void on_logout_clicked();

private:
    Ui::Chat *ui;
    int *ConnectionDescriptor;
    QString Nickname;
};

#endif // CHAT_H
