#ifndef BUYCRYPTO_H
#define BUYCRYPTO_H

#include <QDialog>
#include <QObject>
#include <QMap>
#include <QComboBox>

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
    void updateCryptoData(const QString &symbol, double price, double change, double volume);

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_textChanged();
    void on_cryptoComboBox_currentIndexChanged(int index);

private:
    Ui::buycrypto *ui;
    QMap<QString, double> cryptoRates;
    void setupCryptoTable();
    void setupCryptoComboBox();
    void updateConversion();
};

#endif // BUYCRYPTO_H
