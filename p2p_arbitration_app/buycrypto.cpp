#include "buycrypto.h"
#include "ui_buycrypto.h"
#include "stylehelper.h"
buycrypto::buycrypto(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::buycrypto)
{
    ui->setupUi(this);
    setDarkStyle(this);
    ui->homeButton->setStyleSheet("QPushButton:hover { color: #eba613; }");
}

buycrypto::~buycrypto()
{
    delete ui;
}




void buycrypto::on_homeButton_clicked()
{
    this->hide();

    // Показываем MainWindow (родительский виджет)
    if (parentWidget()) {
        parentWidget()->show();
    }
}
