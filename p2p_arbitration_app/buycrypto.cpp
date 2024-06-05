#include "buycrypto.h"
#include "ui_buycrypto.h"
#include "stylehelper.h"
buycrypto::buycrypto(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::buycrypto)
{
    ui->setupUi(this);
    setDarkStyle(this);
    ui->homeButton->setStyleSheet(
        "QPushButton {"
        "   color: #ffffff;"
        "}"
        "QPushButton:hover {"
        "   color: #eba613;"
        "}"
    );
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


void buycrypto::changeTheme(int counter)
{
    if (counter % 2 == 0) {
        setDarkStyle(this);
        ui->homeButton->setIcon(QIcon(":/icons/icons/homeWhite.png"));
        ui->homeButton->setStyleSheet(
            "QPushButton {"
            "   color: #ffffff;"
            "}"
            "QPushButton:hover {"
            "   color: #eba613;"
            "}"
        );
    }
    else {
        setLightStyle(this);
        ui->homeButton->setIcon(QIcon(":/icons/icons/homeBlack.png"));
        ui->homeButton->setStyleSheet(
            "QPushButton {"
            "   color: #16181c;"
            "}"
            "QPushButton:hover {"
            "   color: #eba613;"
            "}"
        );
    }
}
