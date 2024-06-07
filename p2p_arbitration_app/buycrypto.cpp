#include "buycrypto.h"
#include "ui_buycrypto.h"
#include "stylehelper.h"
#include <QStandardItemModel>
#include <QStandardItem>

buycrypto::buycrypto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::buycrypto)
{
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("QPushButton:hover { color: #eba613; }");
    ui->pushButton_4->setStyleSheet("QPushButton:hover { color: #eba613; }");

    setupCryptoComboBox();

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &buycrypto::on_lineEdit_textChanged);
    connect(ui->cryptoComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &buycrypto::on_cryptoComboBox_currentIndexChanged);

    setupCryptoTable();

    setDarkStyle(this);
}

void buycrypto::setupCryptoComboBox()
{
    QStandardItemModel* model = new QStandardItemModel(this);

    QStringList cryptos = {"BTCUSDT", "ETHUSDT", "XRPUSDT", "ADAUSDT", "DOTUSDT", "BNBUSDT", "SOLUSDT"};
    for (const QString& crypto : cryptos) {
        QStandardItem* item = new QStandardItem;
        item->setText(crypto);
        item->setIcon(QIcon(QString("://icons/icons/%1.png").arg(crypto)));
        model->appendRow(item);
    }

    ui->cryptoComboBox->setModel(model);
    ui->cryptoComboBox->setIconSize(QSize(16, 16));
}

void buycrypto::setupCryptoTable()
{
    ui->cryptoTableWidget->setColumnCount(4);
    QStringList headers = {"Icon", "Symbol Code", "Price", "Change"};
    ui->cryptoTableWidget->setHorizontalHeaderLabels(headers);

    QStringList cryptos = {"BNBUSDT", "BTCUSDT", "ETHUSDT", "NOTUSDT", "SOLUSDT", "DOGEUSDT", "IMXUSDT"};
    for (const QString& crypto : cryptos) {
        ui->cryptoTableWidget->setColumnWidth(0, 40);
        ui->cryptoTableWidget->setColumnWidth(1, 100);
        ui->cryptoTableWidget->setColumnWidth(2, 150);
        ui->cryptoTableWidget->setColumnWidth(3, 70);
        int row = ui->cryptoTableWidget->rowCount();
        ui->cryptoTableWidget->insertRow(row);

        QLabel *iconLabel = new QLabel;
        QPixmap iconPixmap(QString("://icons/icons/%1.png").arg(crypto));
        iconLabel->setPixmap(iconPixmap.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        iconLabel->setAlignment(Qt::AlignCenter);
        ui->cryptoTableWidget->setCellWidget(row, 0, iconLabel);

        QTableWidgetItem *symbolItem = new QTableWidgetItem(crypto);
        symbolItem->setTextAlignment(Qt::AlignCenter);
        ui->cryptoTableWidget->setItem(row, 1, symbolItem);

        QTableWidgetItem *priceItem = new QTableWidgetItem("Loading...");
        priceItem->setTextAlignment(Qt::AlignCenter);
        ui->cryptoTableWidget->setItem(row, 2, priceItem);

        QTableWidgetItem *changeItem = new QTableWidgetItem("Loading...");
        changeItem->setTextAlignment(Qt::AlignCenter);
        ui->cryptoTableWidget->setItem(row, 3, changeItem);
    }

    ui->cryptoTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->cryptoTableWidget->verticalHeader()->setVisible(false);
    ui->cryptoTableWidget->setShowGrid(true);
    ui->cryptoTableWidget->setSortingEnabled(true);
}

void buycrypto::updateCryptoData(const QString &symbol, double price, double change, double volume)
{
    for (int i = 0; i < ui->cryptoTableWidget->rowCount(); ++i) {
        QTableWidgetItem *item = ui->cryptoTableWidget->item(i, 1);
        if (item && item->text() == symbol) {
            ui->cryptoTableWidget->item(i, 2)->setText(QString::number(price, 'f', 2));
            ui->cryptoTableWidget->item(i, 3)->setText(QString::number(change, 'f', 2) + "%");
            QTableWidgetItem *changeItem = ui->cryptoTableWidget->item(i, 3);
            if (change < 0) {
                changeItem->setForeground(QColor(Qt::red));
            } else {
                changeItem->setForeground(QColor(Qt::green));
            }
            break;
        }
    }

    cryptoRates[symbol] = price;
    updateConversion();
}

buycrypto::~buycrypto()
{
    delete ui;
}

void buycrypto::on_pushButton_clicked()
{
    this->hide();
    if (parentWidget()) {
        parentWidget()->show();
    }
}

void buycrypto::changeTheme(int counter)
{
    if (counter % 2 == 0) {
        setDarkStyle(this);
        setDarkStyle(ui->comboBox);
        ui->cryptoComboBox->setStyleSheet(
            "QComboBox {"
            "    background-color: #212327;"
            "    color: #cccccc;"
            "    padding: 5px;"
            "}"
            "QComboBox QAbstractItemView {"
            "    background-color: #212327;"
            "    color: #cccccc;"
            "    selection-background-color: #444444;"
            "    selection-color: #cccccc;"
            "}"
            "QComboBox::drop-down {"
            "    subcontrol-origin: padding;"
            "    subcontrol-position: top right;"
            "    background-color: #212327;"
            "}"
            "QComboBox::down-arrow {"
            "    image: url(:/icons/icons/arrowWhite.png);"
            "    width: 20px;"
            "}"
            );
        ui->pushButton->setStyleSheet(
            "QPushButton {"
            "    color: #ffffff;"
            "}"
            "QPushButton:hover {"
            "    color: #eba613;"
            "}");
        ui->pushButton_4->setStyleSheet(
            "QPushButton {"
            "    color: #ffffff;"
            "}"
            "QPushButton:hover {"
            "    color: #eba613;"
            "}");
        ui->pushButton_2->setStyleSheet(
            "QPushButton {"
            "    background-color: #3e3e3e;"
            "    color: #ffffff;"
            "    border: none;"
            "    padding: 10px 20px;"
            "    border-radius: 5px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #505050;"
            "}"
            "QPushButton:pressed {"
            "    background-color: #2e2e2e;"
            "}"
            );
        ui->pushButton_3->setStyleSheet(
            "QPushButton {"
            "    background-color: #3e3e3e;"
            "    color: #ffffff;"
            "    border: none;"
            "    padding: 10px 20px;"
            "    border-radius: 5px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #505050;"
            "}"
            "QPushButton:pressed {"
            "    background-color: #2e2e2e;"
            "}"
            );


    } else {
        setLightStyle(this);
        setLightStyle(ui->comboBox);
        ui->cryptoComboBox->setStyleSheet(
            "QComboBox {"
            "    background-color: #ffffff;"
            "    color: #404040;"
            "    padding: 10px;"
            "}"
            "QComboBox QAbstractItemView {"
            "    background-color: #ffffff;"
            "    color: #404040;"
            "    selection-background-color: #a6c8ff;"
            "    selection-color: #404040;"
            "}"
            "QComboBox::drop-down {"
            "    subcontrol-origin: padding;"
            "    subcontrol-position: top right;"
            "    background-color: #ffffff;"
            "}"
            "QComboBox::down-arrow {"
            "    image: url(:/icons/icons/arrowBlack.png);"
            "    width: 20px;"
            "}"
            );
        ui->pushButton->setStyleSheet(
            "QPushButton {"
            "    color: #16181c;"
            "}"
            "QPushButton:hover {"
            "    color: #eba613;"
            "}");
        ui->pushButton_4->setStyleSheet(
            "QPushButton {"
            "    color: #16181c;"
            "}"
            "QPushButton:hover {"
            "    color: #eba613;"
            "}");
        ui->pushButton_2->setStyleSheet(
            "QPushButton {"
            "    background-color: #d6d6d6;"
            "    color: #404040;"
            "    border: none;"
            "    padding: 10px 20px;"
            "    border-radius: 5px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #c0c0c0;"
            "}"
            "QPushButton:pressed {"
            "    background-color: #a0a0a0;"
            "}"
            );
        ui->pushButton_3->setStyleSheet(
            "QPushButton {"
            "    background-color: #d6d6d6;"
            "    color: #404040;"
            "    border: none;"
            "    padding: 10px 20px;"
            "    border-radius: 5px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #c0c0c0;"
            "}"
            "QPushButton:pressed {"
            "    background-color: #a0a0a0;"
            "}"
            );
    }
}

void buycrypto::on_lineEdit_textChanged()
{
    updateConversion();
}

void buycrypto::on_cryptoComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    updateConversion();
}

void buycrypto::updateConversion()
{
    QString crypto = ui->cryptoComboBox->currentText();
    double rate = cryptoRates.value(crypto, 0);

    bool ok;
    double amount = ui->lineEdit->text().toDouble(&ok);

    if (ok && rate > 0)
    {
        double convertedAmount = amount / rate;
        ui->lineEdit_2->setText(QString::number(convertedAmount, 'f', 8));
    }
    else
    {
        ui->lineEdit_2->clear();
    }
}


