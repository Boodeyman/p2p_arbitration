#ifndef BUYCRYPTO_H
#define BUYCRYPTO_H

#include <QDialog>
#include <QObject>

class MainWindow;

namespace Ui {
class buycrypto;
}

class buycrypto : public QDialog
{
    Q_OBJECT

public:
    explicit buycrypto(QWidget *parent = nullptr);
    ~buycrypto();
    void changeTheme(int counter);

private slots:
    void on_pushButton_clicked();

private:
    Ui::buycrypto *ui;
};

#endif // BUYCRYPTO_H
