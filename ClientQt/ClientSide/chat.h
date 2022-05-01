#ifndef CHAT_H
#define CHAT_H

#include <QMainWindow>

namespace Ui {
class Chat;
}

class Chat : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = nullptr);
    ~Chat();

private slots:
    void on_LogOut_clicked();

private:
    Ui::Chat *ui;
};

#endif // CHAT_H
