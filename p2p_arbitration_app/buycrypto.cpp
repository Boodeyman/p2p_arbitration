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

    setupCryptoComboBox(); // Инициализация комбобокса с иконками криптовалют

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &buycrypto::on_lineEdit_textChanged);
    connect(ui->cryptoComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &buycrypto::on_cryptoComboBox_currentIndexChanged);

    setupCryptoTable(); // Инициализация таблицы криптовалют

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
    // Обновление данных в таблице
    for (int i = 0; i < ui->cryptoTableWidget->rowCount(); ++i) {
        QTableWidgetItem *item = ui->cryptoTableWidget->item(i, 1); // Столбец с символами криптовалют
        if (item && item->text() == symbol) {
            ui->cryptoTableWidget->item(i, 2)->setText(QString::number(price, 'f', 2));
            ui->cryptoTableWidget->item(i, 3)->setText(QString::number(change, 'f', 2) + "%");
            // Обновление цвета текста для изменения
            QTableWidgetItem *changeItem = ui->cryptoTableWidget->item(i, 3);
            if (change < 0) {
                changeItem->setForeground(QColor(Qt::red));
            } else {
                changeItem->setForeground(QColor(Qt::green));
            }
            break;
        }
    }

    // Обновление курса криптовалюты для конверсии
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
        ui->pushButton->setStyleSheet(        "QPushButton {"
                                      "    color: #ffffff;"
                                      "}"
                                      "QPushButton:hover {"
                                      "    color: #eba613;"
                                      "}");
        ui->pushButton_4->setStyleSheet(        "QPushButton {"
                                        "    color: #ffffff;"
                                        "}"
                                        "QPushButton:hover {"
                                        "    color: #eba613;"
                                        "}");
    } else {
        setLightStyle(this);
        ui->pushButton->setStyleSheet(        "QPushButton {"
                                      "    color: #16181c;"
                                      "}"
                                      "QPushButton:hover {"
                                      "    color: #eba613;"
                                      "}");
        ui->pushButton_4->setStyleSheet(        "QPushButton {"
                                        "    color: #16181c;"
                                        "}"
                                        "QPushButton:hover {"
                                        "    color: #eba613;"
                                        "}");
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
