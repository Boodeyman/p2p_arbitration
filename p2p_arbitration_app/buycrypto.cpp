#include "buycrypto.h"
#include "ui_buycrypto.h"
#include "stylehelper.h"
buycrypto::buycrypto(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::buycrypto)
{
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("QPushButton:hover { color: #eba613; }");
    ui->pushButton_4->setStyleSheet("QPushButton:hover { color: #eba613; }");
    // В файле buycrypto.cpp в конструкторе
    ui->cryptoComboBox->addItems({"BTCUSDT", "ETHUSDT", "XRPUSDT", "ADAUSDT", "DOTUSDT"}); // Примеры символов

    setDarkStyle(this);
}

buycrypto::~buycrypto()
{
    delete ui;
}




void buycrypto::on_pushButton_clicked()
{
    this->hide();
    // Показываем MainWindow (родительский виджет)
    if (parentWidget()) {
        parentWidget()->show();
    }
}


void buycrypto::changeTheme(int counter)
{
    if (counter % 2 == 0) {
        setDarkStyle(this);
        ui->pushButton->setStyleSheet("color: #ffffff");
        ui->pushButton->setStyleSheet("QPushButton:hover { color: #eba613; }");
        ui->pushButton_4->setStyleSheet("QPushButton:hover { color: #eba613; }");
    }
    else {
        setLightStyle(this);
        ui->pushButton->setStyleSheet("color: #16181c");
        ui->pushButton->setStyleSheet("QPushButton:hover { color: #eba613; }");
        ui->pushButton_4->setStyleSheet("QPushButton:hover { color: #eba613; }");
    }
}
