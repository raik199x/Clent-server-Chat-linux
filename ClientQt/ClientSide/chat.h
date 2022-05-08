#ifndef CHAT_H
#define CHAT_H

#include <thread>
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
    void RecMessage();
    ~Chat();

private slots:
    void on_logout_clicked();

    void on_Send_clicked();

    void on_textMessage_textChanged();

    void CleaningUsers(char *buffer);
private:
    Ui::Chat *ui;
    int *ConnectionDescriptor;
    QString Nickname;
    std::thread *ListenThread;
    bool IsDisconnectedFromServer;
    void closeEvent(QCloseEvent *event);
signals:
    void Disconnected();
    void ClearUsersOnline(char *buffer);
};

#endif // CHAT_H
