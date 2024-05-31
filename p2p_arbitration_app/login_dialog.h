#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Dialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void handleLogin();
    void handleRegister();

private:
    Ui::Dialog *ui;
    void initializeDatabase();
    QSqlDatabase db;
    QString databasePath;
};

#endif // LOGINDIALOG_H
