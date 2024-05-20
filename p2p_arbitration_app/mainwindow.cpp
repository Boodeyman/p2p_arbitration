#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "binance.h"
#include "scraper.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), api(new BinanceAPI(this)), scraper(new Scraper(this)) {
    ui->setupUi(this);
    setupTableWidget();
    setupCryptoRows();

    // Set up the scraper and API
    api->setScraper(scraper);

    // Setup and start the data request QTimer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::requestData);
    timer->start(1000);  // Request data every 10 seconds (изменено с 1 секунды на 10 секунд)

    // Setup and start the proxy change QTimer
    proxyChangeTimer = new QTimer(this);
    connect(proxyChangeTimer, &QTimer::timeout, scraper, &Scraper::testIp);
    proxyChangeTimer->start(60000);  // Change proxy every 10 minutes (изменено с 2 минут на 10 минут)

    connect(api, &BinanceAPI::cryptoDataReady, this, &MainWindow::updateCryptoData);
    connect(api, &BinanceAPI::errorOccurred, this, [](const QString &error) {
        qDebug() << "Network error:" << error;
    });

    // Set the proxy list
    QVector<QString> proxies = {
        "196.17.249.47:8000:AYUP1R:wUKVAX",
        "181.177.85.254:9758:rkMEWn:eD09JZ",
        "45.85.162.169:8000:B5WASu:Td2uCw",
        "45.130.126.84:8000:x3mGeU:DFxtuN",
        "186.179.49.5:8000:7PmmyL:GwfamA"
    };
    scraper->setProxyList(proxies);
    scraper->testIp();

    requestData();  // Perform initial data request
}

void MainWindow::requestData() {
    QVector<QString> cryptos = {"BTCUSDT", "ETHUSDT", "SOLUSDT", "BNBUSDT", "XRPUSDT", "ADAUSDT", "DOGEUSDT", "ATOMUSDT", "LTCUSDT", "SHIBUSDT", "AVAXUSDT", "TRXUSDT", "DOTUSDT", "NEARUSDT", "MATICUSDT", "ICPUSDT", "UNIUSDT"};
    api->getCrypto(cryptos);
}

void MainWindow::setupTableWidget() {
    ui->tableWidget->setColumnCount(6);
    QStringList headers = {"", "Name", "Price", "Change", "Volume (USDT)", "Volume (Crypto)"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Set widths for each column, adjust as needed
    ui->tableWidget->setColumnWidth(0, 30);
    ui->tableWidget->setColumnWidth(1, 100);
    ui->tableWidget->setColumnWidth(2, 80);
    ui->tableWidget->setColumnWidth(3, 70);
    ui->tableWidget->setColumnWidth(4, 150);
    ui->tableWidget->setColumnWidth(5, 150);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setShowGrid(true);
}

void MainWindow::setupCryptoRows() {
    QStringList cryptos = {"BTCUSDT", "ETHUSDT", "SOLUSDT", "BNBUSDT", "XRPUSDT", "ADAUSDT", "DOGEUSDT", "ATOMUSDT", "LTCUSDT", "SHIBUSDT", "AVAXUSDT", "TRXUSDT", "DOTUSDT", "NEARUSDT", "MATICUSDT", "ICPUSDT", "UNIUSDT"};
    for (int i = 0; i < cryptos.size(); ++i) {
        symbolToRowMap[cryptos[i]] = i;
        ui->tableWidget->insertRow(i);
    }
}

void MainWindow::updateCryptoData(const QString &symbol, const QJsonObject &data) {
    if (data["success"].toBool()) {
        if (!symbolToRowMap.contains(symbol)) return;  // Only update if we track this symbol
        int row = symbolToRowMap[symbol];

        QJsonObject details = data["data"].toObject();
        QString assetName = details["an"].toString();
        double currentPrice = details["c"].toString().toDouble();
        QString currentPriceFormatted = "$" + QString::number(currentPrice, 'f', 2);
        double changePercent = (currentPrice - details["o"].toString().toDouble()) / details["o"].toString().toDouble() * 100;
        QString changeFormatted = QString::number(changePercent, 'f', 2) + "%";
        double volumeInUSDT = details["v"].toString().toDouble() * currentPrice;
        QString volumeInUSDTFormatted = "$" + QString::number(volumeInUSDT, 'f', 2);
        QString volumeInCryptoFormatted = QString::number(details["v"].toString().toDouble(), 'f', 2);

        // Create and configure QLabel for the icon
        QLabel *iconLabel = new QLabel;
        QPixmap iconPixmap(QString("://icons/icons/%1.png").arg(symbol));  // Assuming icons are named after the symbols
        iconLabel->setPixmap(iconPixmap.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        iconLabel->setAlignment(Qt::AlignCenter);

        // Create items with centered alignment
        QTableWidgetItem *nameItem = new QTableWidgetItem(assetName);
        nameItem->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *priceItem = new QTableWidgetItem(currentPriceFormatted);
        priceItem->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *changeItem = new QTableWidgetItem(changeFormatted);
        changeItem->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *volumeUsdtItem = new QTableWidgetItem(volumeInUSDTFormatted);
        volumeUsdtItem->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *volumeCryptoItem = new QTableWidgetItem(volumeInCryptoFormatted);
        volumeCryptoItem->setTextAlignment(Qt::AlignCenter);

        // Set QLabel and other items in the table
        ui->tableWidget->setCellWidget(row, 0, iconLabel);  // Set QLabel as the cell widget for icons
        ui->tableWidget->setItem(row, 1, nameItem);
        ui->tableWidget->setItem(row, 2, priceItem);
        ui->tableWidget->setItem(row, 3, changeItem);
        ui->tableWidget->setItem(row, 4, volumeUsdtItem);
        ui->tableWidget->setItem(row, 5, volumeCryptoItem);
    } else {
        qDebug() << "Failed to receive valid data for symbol:" << symbol;
    }
}

MainWindow::~MainWindow() {
    delete ui;
}










// #include "mainwindow.h"
// #include "ui_mainwindow.h"
// #include "binance.h"
// #include <QLabel>

// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent), ui(new Ui::MainWindow), api(new BinanceAPI(this)) {
//     ui->setupUi(this);
//     setupTableWidget();
//     setupCryptoRows();

//     // Setup and start the QTimer
//     timer = new QTimer(this);
//     connect(timer, &QTimer::timeout, this, &MainWindow::requestData);
//     timer->start(3000);

//     connect(api, &BinanceAPI::cryptoDataReady, this, &MainWindow::updateCryptoData);
//     connect(api, &BinanceAPI::errorOccurred, this, [](const QString &error) {
//         qDebug() << "Network error:" << error;
//     });

//     requestData();  // Perform initial data request
// }

// void MainWindow::requestData() {
//     QVector<QString> cryptos = {"BTCUSDT", "ETHUSDT", "SOLUSDT", "BNBUSDT", "XRPUSDT", "ADAUSDT", "DOGEUSDT", "ATOMUSDT", "LTCUSDT", "SHIBUSDT"};
//     for (const QString &crypto : cryptos) {
//         QVector<QString> singleCrypto;  // Create a QVector to hold the single crypto symbol
//         singleCrypto.append(crypto);    // Add the current crypto symbol to the vector
//         api->getCrypto(singleCrypto);   // Pass the QVector to getCrypto
//     }
// }


// void MainWindow::setupTableWidget() {
//     ui->tableWidget->setColumnCount(6);  // Increase the number of columns to include icon column
//     QStringList headers = {"", "Name", "Price", "Change", "Volume (USDT)", "Volume (Crypto)"};
//     ui->tableWidget->setHorizontalHeaderLabels(headers);

//     // Set widths for each column, adjust as needed
//     ui->tableWidget->setColumnWidth(0, 30);  // Width for icon column
//     ui->tableWidget->setColumnWidth(1, 100); // Name
//     ui->tableWidget->setColumnWidth(2, 80);  // Price
//     ui->tableWidget->setColumnWidth(3, 70);  // Change
//     ui->tableWidget->setColumnWidth(4, 150); // Volume (USDT)
//     ui->tableWidget->setColumnWidth(5, 150); // Volume (Crypto)

//     ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
//     ui->tableWidget->verticalHeader()->setVisible(false);
//     ui->tableWidget->setShowGrid(true);
// }



// void MainWindow::setupCryptoRows() {
//     QStringList cryptos = {"BTCUSDT", "ETHUSDT", "SOLUSDT", "BNBUSDT", "XRPUSDT", "ADAUSDT", "DOGEUSDT", "ATOMUSDT", "LTCUSDT", "SHIBUSDT"};
//     for (int i = 0; i < cryptos.size(); ++i) {
//         symbolToRowMap[cryptos[i]] = i;
//         ui->tableWidget->insertRow(i);
//     }
// }

// void MainWindow::updateCryptoData(const QString &symbol, const QJsonObject &data) {
//     if (data["success"].toBool()) {
//         if (!symbolToRowMap.contains(symbol)) return;  // Only update if we track this symbol
//         int row = symbolToRowMap[symbol];

//         QJsonObject details = data["data"].toObject();
//         QString assetName = details["an"].toString();
//         double currentPrice = details["c"].toString().toDouble();
//         QString currentPriceFormatted = "$" + QString::number(currentPrice, 'f', 2);
//         double changePercent = (currentPrice - details["o"].toString().toDouble()) / details["o"].toString().toDouble() * 100;
//         QString changeFormatted = QString::number(changePercent, 'f', 2) + "%";
//         double volumeInUSDT = details["v"].toString().toDouble() * currentPrice;
//         QString volumeInUSDTFormatted = "$" + QString::number(volumeInUSDT, 'f', 2);
//         QString volumeInCryptoFormatted = QString::number(details["v"].toString().toDouble(), 'f', 2);

//         // Create and configure QLabel for the icon
//         QLabel *iconLabel = new QLabel;
//         QPixmap iconPixmap(QString("://icons/icons/%1.png").arg(symbol));  // Assuming icons are named after the symbols
//         iconLabel->setPixmap(iconPixmap.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));
//         iconLabel->setAlignment(Qt::AlignCenter);

//         // Create items with centered alignment
//         QTableWidgetItem *nameItem = new QTableWidgetItem(assetName);
//         nameItem->setTextAlignment(Qt::AlignCenter);
//         QTableWidgetItem *priceItem = new QTableWidgetItem(currentPriceFormatted);
//         priceItem->setTextAlignment(Qt::AlignCenter);
//         QTableWidgetItem *changeItem = new QTableWidgetItem(changeFormatted);
//         changeItem->setTextAlignment(Qt::AlignCenter);
//         QTableWidgetItem *volumeUsdtItem = new QTableWidgetItem(volumeInUSDTFormatted);
//         volumeUsdtItem->setTextAlignment(Qt::AlignCenter);
//         QTableWidgetItem *volumeCryptoItem = new QTableWidgetItem(volumeInCryptoFormatted);
//         volumeCryptoItem->setTextAlignment(Qt::AlignCenter);

//         // Set QLabel and other items in the table
//         ui->tableWidget->setCellWidget(row, 0, iconLabel);  // Set QLabel as the cell widget for icons
//         ui->tableWidget->setItem(row, 1, nameItem);
//         ui->tableWidget->setItem(row, 2, priceItem);
//         ui->tableWidget->setItem(row, 3, changeItem);
//         ui->tableWidget->setItem(row, 4, volumeUsdtItem);
//         ui->tableWidget->setItem(row, 5, volumeCryptoItem);
//     } else {
//         qDebug() << "Failed to receive valid data";
//     }
// }



// MainWindow::~MainWindow() {
//     delete ui;
// }
