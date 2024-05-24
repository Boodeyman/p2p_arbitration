#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "binance.h"
#include "scraper.h"
#include "hoverbutton.h"
#include <QLabel>
#include <QMessageBox>
#include <QEvent>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), api(new BinanceAPI(this)), scraper(new Scraper(this)) {
    ui->setupUi(this);
    setupTableWidget();
    setupCryptoRows();

    hoverButton = new HoverButton(ui->hoverButton, ui->lineEdit, this);
    ui->verticalLayout->addWidget(hoverButton);

    this->installEventFilter(this);

    api->setScraper(scraper);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::requestData);
    timer->start(2000);

    proxyChangeTimer = new QTimer(this);
    connect(proxyChangeTimer, &QTimer::timeout, scraper, &Scraper::testIp);
    proxyChangeTimer->start(90000);

    connect(api, &BinanceAPI::cryptoDataReady, this, &MainWindow::updateCryptoData);
    connect(api, &BinanceAPI::errorOccurred, this, [](const QString &error) {
        // Handle error
    });

    QVector<QString> proxies = {
        "196.17.249.47:8000:AYUP1R:wUKVAX",
        "196.17.67.75:8000:yzbLcj:sn5tVm",
        "45.130.126.84:8000:x3mGeU:DFxtuN",
        "181.177.85.254:9758:rkMEWn:eD09JZ",
        "186.179.49.5:8000:7PmmyL:GwfamA",
        "45.85.162.169:8000:B5WASu:Td2uCw",
        "138.219.72.205:8000:PhE4fP:nz05nG",
        "138.219.72.122:8000:PhE4fP:nz05nG",
        "200.10.36.42:8000:PhE4fP:nз05nG",
        "168.181.52.14:8000:PhE4fP:nз05nG"
    };
    scraper->setProxyList(proxies);
    scraper->testIp();

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::searchCrypto);
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, &MainWindow::onRowSelected);

    requestData();

    ui->pushButton->setStyleSheet(
        "QPushButton:hover { color: yellow; }"
        );
    ui->pushButton_2->setStyleSheet(
        "QPushButton:hover { color: yellow; }"
        );
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (!hoverButton->rect().contains(mouseEvent->pos())) {
            ui->lineEdit->setVisible(false);
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::searchCrypto() {
    QString searchQuery = ui->lineEdit->text().trimmed().toUpper();
    bool found = false;

    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        bool rowMatch = false;
        QTableWidgetItem *item = ui->tableWidget->item(i, 1);

        if (item->text().toUpper().contains(searchQuery)) {
            rowMatch = true;
        }

        ui->tableWidget->setRowHidden(i, !rowMatch);
    }
}

void MainWindow::onRowSelected() {
    QList<QTableWidgetItem*> selection = ui->tableWidget->selectedItems();
    if (!selection.isEmpty()) {
        QTableWidgetItem* item = selection.first();
        int row = item->row();
        QMessageBox::information(this, "Выбранная монета", "Вы выбрали: " + ui->tableWidget->item(row, 1)->text());
    }
}

void MainWindow::requestData() {
    QVector<QString> cryptos = {"BTCUSDT", "ETHUSDT", "SOLUSDT", "BNBUSDT", "XRPUSDT", "ADAUSDT", "DOGEUSDT", "ATOMUSDT", "LTCUSDT", "SHIBUSDT", "AVAXUSDT", "TRXUSDT", "DOTUSDT", "NEARUSDT", "MATICUSDT", "ICPUSDT", "UNIUSDT", "RNDRUSDT", "APTUSDT", "IMXUSDT", "ARUSDT", "XLMUSDT", "WIFUSDT", "FTMUSDT", "OPUSDT", "TAOUSDT", "SUIUSDT", "INJUSDT", "RUNEUSDT", "FLOKIUSDT", "SEIUSDT"};
    api->getCrypto(cryptos);
}

void MainWindow::setupTableWidget() {
    ui->tableWidget->setColumnCount(6);
    QStringList headers = {"", "Name", "Price", "Change", "Volume (USDT)", "Volume (Crypto)"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    ui->tableWidget->setColumnWidth(0, 30);
    ui->tableWidget->setColumnWidth(1, 100);
    ui->tableWidget->setColumnWidth(2, 80);
    ui->tableWidget->setColumnWidth(3, 70);
    ui->tableWidget->setColumnWidth(4, 150);
    ui->tableWidget->setColumnWidth(5, 150);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setShowGrid(true);

    // Enable sorting
    ui->tableWidget->setSortingEnabled(true);

    // Connect the header click signal to the sorting slot
    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::sortByChangeColumn);
}

void MainWindow::setupCryptoRows() {
    QStringList cryptos = {"BTCUSDT", "ETHUSDT", "SOLUSDT", "BNBUSDT", "XRPUSDT", "ADAUSDT", "DOGEUSDT", "ATOMUSDT", "LTCUSDT", "SHIBUSDT", "AVAXUSDT", "TRXUSDT", "DOTUSDT", "NEARUSDT", "MATICUSDT", "ICPUSDT", "UNIUSDT", "RNDRUSDT", "APTUSDT", "IMXUSDT", "ARUSDT", "XLMUSDT", "WIFUSDT", "FTMUSDT", "OPUSDT", "TAOUSDT", "SUIUSDT", "INJUSDT", "RUNEUSDT", "FLOKIUSDT", "SEIUSDT"};
    for (int i = 0; i < cryptos.size(); ++i) {
        symbolToRowMap[cryptos[i]] = i;
        ui->tableWidget->insertRow(i);
    }
}

void MainWindow::updateCryptoData(const QString &symbol, const QJsonObject &data) {
    if (data["success"].toBool()) {
        if (!symbolToRowMap.contains(symbol)) return;
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

        QLabel *iconLabel = new QLabel;
        QPixmap iconPixmap(QString("://icons/icons/%1.png").arg(symbol));
        iconLabel->setPixmap(iconPixmap.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        iconLabel->setAlignment(Qt::AlignCenter);

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

        if (changePercent < 0) {
            changeItem->setForeground(QColor(Qt::red));
        } else {
            changeItem->setForeground(QColor(Qt::green));
        }

        ui->tableWidget->setCellWidget(row, 0, iconLabel);
        ui->tableWidget->setItem(row, 1, nameItem);
        ui->tableWidget->setItem(row, 2, priceItem);
        ui->tableWidget->setItem(row, 3, changeItem);
        ui->tableWidget->setItem(row, 4, volumeUsdtItem);
        ui->tableWidget->setItem(row, 5, volumeCryptoItem);
    } else {
        // Handle error
    }
}

void MainWindow::sortByChangeColumn(int column) {
    if (column == 3) {
        static bool ascending = true;
        ui->tableWidget->sortByColumn(column, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
        ascending = !ascending;
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
