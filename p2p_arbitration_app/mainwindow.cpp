#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "binance.h"
#include "scraper.h"
#include "login_dialog.h"
#include "buycrypto.h"
#include "stylehelper.h"
#include <QLabel>
#include <QMessageBox>
#include <QEvent>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QTimer>
// #include <QApplication>
// #include <QMainWindow>
// #include <QTableWidget>
// #include <QVBoxLayout>
// #include <QHeaderView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    api(new BinanceAPI(this)),
    scraper(new Scraper(this)),
    buycrypto(nullptr)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::openBuyCrypto);

    setupTableWidget();
    setupCryptoRows();

    // Устанавливаем фильтр событий для hoverButton и lineEdit
    ui->hoverButton->installEventFilter(this);
    ui->lineEdit->installEventFilter(this);
    ui->lineEdit->setVisible(false); // Изначально скрываем lineEdit

    // Создаем таймер для скрытия lineEdit
    hideTimer = new QTimer(this);
    hideTimer->setSingleShot(true);
    connect(hideTimer, &QTimer::timeout, this, &MainWindow::hideLineEdit);

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

    loadProxiesFromFile();

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::searchCrypto);
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, &MainWindow::onRowSelected);

    requestData();

    ui->pushButton->setStyleSheet("QPushButton:hover { color: #eba613; }");
    ui->pushButton_2->setStyleSheet("QPushButton:hover { color: #eba613; }");

    setDarkStyle(this);

    connect(ui->logoutButton, &QPushButton::clicked, this, &MainWindow::logout);
}

void MainWindow::logout() {
    this->hide();
    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        this->show();
    } else {
        qApp->quit();
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->hoverButton || watched == ui->lineEdit) {
        if (event->type() == QEvent::Enter) {
            ui->lineEdit->setVisible(true);

            hideTimer->stop();  // Останавливаем таймер, если он запущен
        } else if (event->type() == QEvent::Leave) {
            hideTimer->start(250);  // Запускаем таймер на 0.25 секунду
        }
    } else if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (!ui->hoverButton->rect().contains(mouseEvent->pos()) && !ui->lineEdit->rect().contains(mouseEvent->pos())) {
            ui->lineEdit->setVisible(false);
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::hideLineEdit() {
    if (!ui->lineEdit->hasFocus() && !ui->lineEdit->underMouse()) {  // Проверяем, есть ли фокус на lineEdit или наведение
        ui->lineEdit->setVisible(false);
    }
}

void MainWindow::searchCrypto() {
    QString searchQuery = ui->lineEdit->text().trimmed().toUpper();
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        bool rowMatch = ui->tableWidget->item(i, 1)->text().toUpper().contains(searchQuery);
        ui->tableWidget->setRowHidden(i, !rowMatch);
    }
}

void MainWindow::onRowSelected() {
    auto selection = ui->tableWidget->selectedItems();
    if (!selection.isEmpty()) {
        int row = selection.first()->row();
        QMessageBox::information(this, "Выбранная монета", "Вы выбрали: " + ui->tableWidget->item(row, 1)->text());
    }
}

void MainWindow::requestData() {
    QVector<QString> cryptos = {"BTCUSDT", "ETHUSDT", "SOLUSDT", "BNBUSDT", "XRPUSDT", "ADAUSDT", "DOGEUSDT", "ATOMUSDT", "LTCUSDT", "SHIBUSDT", "AVAXUSDT", "TRXUSDT", "DOTUSDT", "NEARUSDT", "MATICUSDT", "ICPUSDT", "UNIUSDT", "RNDRUSDT", "APTUSDT", "IMXUSDT", "ARUSDT", "XLMUSDT", "WIFUSDT", "FTMUSDT", "OPUSDT", "TAOUSDT", "SUIUSDT", "INJUSDT", "RUNEUSDT", "FLOKIUSDT", "SEIUSDT"};
    api->getCrypto(cryptos);
}


void MainWindow::setupTableWidget() {
    ui->tableWidget->setColumnCount(6);
    QStringList headers = {"", "NAME", "PRICE", "CHANGE", "VOLUME (USDT)", "VOLUME (Crypto)"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Устанавливаем фиксированную ширину для первой колонки
    ui->tableWidget->setColumnWidth(0, 40);

    // Устанавливаем режим изменения размера колонок для других колонок
    for (int i = 1; i < ui->tableWidget->columnCount(); ++i) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    // Оставляем последнюю колонку растягивающейся
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSortingEnabled(true);
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
        QString symbolCode = symbol.left(symbol.indexOf("USDT")).toUpper();
        QString fullName = QString("%1 (%2)").arg(assetName).arg(symbolCode);
        double currentPrice = details["c"].toString().toDouble();
        QString currentPriceFormatted = "$" + QString::number(currentPrice, 'f', 4);
        double changePercent = (currentPrice - details["o"].toString().toDouble()) / details["o"].toString().toDouble() * 100;
        QString changeFormatted = QString::number(changePercent, 'f', 2) + "%";
        double volumeInUSDT = details["v"].toString().toDouble() * currentPrice;
        QString volumeInUSDTFormatted = "$" + QString::number(volumeInUSDT, 'f', 2);
        QString volumeInCryptoFormatted = QString::number(details["v"].toString().toDouble(), 'f', 2);

        QLabel *iconLabel = new QLabel;
        QPixmap iconPixmap(QString("://icons/icons/%1.png").arg(symbol));
        iconLabel->setPixmap(iconPixmap.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        iconLabel->setAlignment(Qt::AlignCenter);

        QTableWidgetItem *nameItem = new QTableWidgetItem(fullName);
        nameItem->setTextAlignment(Qt::AlignCenter);
        nameItem->setFont(QFont("Arial", 14));
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

        updateTopLosersWidget(ui->tableWidget, ui->topLosersWidget);
        updateTopGainersWidget(ui->tableWidget, ui->topGainersWidget);
        updateTopVolumeWidget(ui->tableWidget, ui->topVolumeWidget);


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

void MainWindow::loadProxiesFromFile() {
    QFile file(proxiesPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open proxies.txt file");
        return;
    }
    QTextStream in(&file);
    QVector<QString> proxies;
    while (!in.atEnd()) {
        QString line = in.readLine();
        proxies.append(line);
    }
    file.close();
    scraper->setProxyList(proxies);
    scraper->testIp();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openBuyCrypto()
{
    if (!buycrypto) {
        buycrypto = new class buycrypto(this);
    }
    buycrypto->changeTheme(counter);
    this -> hide();
    buycrypto->exec();
    this -> show();
}



int counter = 0;
void MainWindow::on_themeChange_clicked()
{
    counter ++;
    if (counter % 2 == 0) {
        ui->themeChange->setIcon(QIcon(":/icons/icons/dark.png"));
        ui->hoverButton->setIcon(QIcon(":/icons/icons/hooverDarkStatic.png"));
        ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #16181c; color: #ffffff; }");
        ui->pushButton->setStyleSheet("color: #ffffff");
        ui->pushButton_2->setStyleSheet(
            "QPushButton {"
            "   color: #ffffff;"
            "}"
            "QPushButton:hover {"
            "   color: #eba613;"
            "}"
            );
        setDarkStyle(this);
    }
    else {
        ui->themeChange->setIcon(QIcon(":/icons/icons/light.png"));
        ui->hoverButton->setIcon(QIcon(":/icons/icons/hooverLightStatic.png"));
        ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #f5f5f5; color: #16181c; }");
        ui->pushButton->setStyleSheet("color: #16181c");
        ui->pushButton_2->setStyleSheet(
            "QPushButton {"
            "   color: #16181c;"
            "}"
            "QPushButton:hover {"
            "   color: #eba613;"
            "}"
            );
        setLightStyle(this);
    }
}


QString MainWindow::formatWithSuffix(double num) {
    if (num >= 1'000'000) {
        return QString("$%1M").arg(QString::number(num / 1'000'000, 'f', 2));
    } else if (num >= 1'000) {
        return QString("$%1K").arg(QString::number(num / 1'000, 'f', 2));
    } else {
        return QString("$%1").arg(QString::number(num, 'f', 2));
    }
}


void MainWindow::updateTopLosersWidget(QTableWidget* tableWidget, QTableWidget* topLosersWidget) {
    // Устанавливаем режим изменения размера всех столбцов в режим QHeaderView::Stretch
    topLosersWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Остальной код без изменений
    ui->topLosersWidget->setColumnWidth(0, 40);
    ui->topLosersWidget->setColumnWidth(1, 50);
    ui->topLosersWidget->setColumnWidth(2, 70);
    ui->topLosersWidget->setColumnWidth(3, 70);
    topLosersWidget->clearContents();
    topLosersWidget->setRowCount(0);
    topLosersWidget->setColumnCount(4);
    topLosersWidget->setHorizontalHeaderLabels(QStringList() << "Icon" << "Symbol Code" << "Price" << "Change");
    QList<QPair<double, int>> changes;
    int rowCount = tableWidget->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QTableWidgetItem* changeItem = tableWidget->item(i, 3);
        if (changeItem) {
            double change = changeItem->text().remove('%').toDouble();
            changes.append(qMakePair(change, i));
        }
    }
    std::sort(changes.begin(), changes.end(), [](const QPair<double, int>& a, const QPair<double, int>& b) {
        return a.first < b.first;
    });
    int displayCount = qMin(changes.size(), 3);
    for (int i = 0; i < displayCount; ++i) {
        int newRow = topLosersWidget->rowCount();
        topLosersWidget->insertRow(newRow);
        QLabel* iconLabel = qobject_cast<QLabel*>(tableWidget->cellWidget(changes[i].second, 0));
        if (iconLabel && !iconLabel->pixmap().isNull()) {
            QLabel* newIconLabel = new QLabel;
            newIconLabel->setPixmap(iconLabel->pixmap().copy());
            newIconLabel->setAlignment(Qt::AlignCenter);
            topLosersWidget->setCellWidget(newRow, 0, newIconLabel);
        } else {
            topLosersWidget->setCellWidget(newRow, 0, new QLabel("No icon"));
        }
        QString symbolFull = tableWidget->item(changes[i].second, 1)->text();
        QString symbolCode = symbolFull.section('(', 1, 1).section(')', 0, 0);
        QTableWidgetItem* symbolCodeItem = new QTableWidgetItem(symbolCode);
        symbolCodeItem->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem* priceItem = tableWidget->item(changes[i].second, 2)->clone();
        QTableWidgetItem* changeItem = tableWidget->item(changes[i].second, 3)->clone();
        changeItem->setForeground(tableWidget->item(changes[i].second, 3)->foreground());
        topLosersWidget->setItem(newRow, 1, symbolCodeItem);
        topLosersWidget->setItem(newRow, 2, priceItem);
        topLosersWidget->setItem(newRow, 3, changeItem);
    }
}

void MainWindow::updateTopGainersWidget(QTableWidget* tableWidget, QTableWidget* topGainersWidget) {
    // Устанавливаем режим изменения размера всех столбцов в режим QHeaderView::Stretch
    topGainersWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Остальной код без изменений
    ui->topGainersWidget->setColumnWidth(0, 40);
    ui->topGainersWidget->setColumnWidth(1, 50);
    ui->topGainersWidget->setColumnWidth(2, 70);
    ui->topGainersWidget->setColumnWidth(3, 70);
    topGainersWidget->clearContents();
    topGainersWidget->setRowCount(0);
    topGainersWidget->setColumnCount(4);
    topGainersWidget->setHorizontalHeaderLabels(QStringList() << "Icon" << "Symbol Code" << "Price" << "Change");
    QList<QPair<double, int>> changes;
    int rowCount = tableWidget->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QTableWidgetItem* changeItem = tableWidget->item(i, 3);
        if (changeItem) {
            double change = changeItem->text().remove('%').toDouble();
            changes.append(qMakePair(change, i));
        }
    }
    std::sort(changes.begin(), changes.end(), [](const QPair<double, int>& a, const QPair<double, int>& b) {
        return a.first > b.first;
    });
    int displayCount = qMin(changes.size(), 3);
    for (int i = 0; i < displayCount; ++i) {
        int newRow = topGainersWidget->rowCount();
        topGainersWidget->insertRow(newRow);
        QLabel* iconLabel = qobject_cast<QLabel*>(tableWidget->cellWidget(changes[i].second, 0));
        if (iconLabel && !iconLabel->pixmap().isNull()) {
            QLabel* newIconLabel = new QLabel;
            newIconLabel->setPixmap(iconLabel->pixmap().copy());
            newIconLabel->setAlignment(Qt::AlignCenter);
            topGainersWidget->setCellWidget(newRow, 0, newIconLabel);
        } else {
            topGainersWidget->setCellWidget(newRow, 0, new QLabel("No icon"));
        }
        QString symbolFull = tableWidget->item(changes[i].second, 1)->text();
        QString symbolCode = symbolFull.section('(', 1, 1).section(')', 0, 0);
        QTableWidgetItem* symbolCodeItem = new QTableWidgetItem(symbolCode);
        symbolCodeItem->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem* priceItem = tableWidget->item(changes[i].second, 2)->clone();
        QTableWidgetItem* changeItem = tableWidget->item(changes[i].second, 3)->clone();
        changeItem->setForeground(tableWidget->item(changes[i].second, 3)->foreground());
        topGainersWidget->setItem(newRow, 1, symbolCodeItem);
        topGainersWidget->setItem(newRow, 2, priceItem);
        topGainersWidget->setItem(newRow, 3, changeItem);
    }
}

void MainWindow::updateTopVolumeWidget(QTableWidget* tableWidget, QTableWidget* topVolumeWidget) {
    // Устанавливаем режим изменения размера всех столбцов в режим QHeaderView::Stretch
    topVolumeWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Остальной код без изменений
    ui->topVolumeWidget->setColumnWidth(0, 40);
    ui->topVolumeWidget->setColumnWidth(1, 50);
    ui->topVolumeWidget->setColumnWidth(2, 70);
    ui->topVolumeWidget->setColumnWidth(3, 70);
    topVolumeWidget->clearContents();
    topVolumeWidget->setRowCount(0);
    topVolumeWidget->setColumnCount(4);
    topVolumeWidget->setHorizontalHeaderLabels(QStringList() << "Top Volume");
    QList<QPair<double, int>> volumes;
    int rowCount = tableWidget->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QTableWidgetItem* volumeItem = tableWidget->item(i, 4);
        if (volumeItem) {
            QString volumeText = volumeItem->text();
            volumeText.remove('$');
            double volume = volumeText.toDouble();
            volumes.append(qMakePair(volume, i));
        }
    }
    std::sort(volumes.begin(), volumes.end(), [](const QPair<double, int>& a, const QPair<double, int>& b) {
        return a.first > b.first;
    });
    int displayCount = qMin(volumes.size(), 3);
    for (int i = 0; i < displayCount; ++i) {
        int newRow = topVolumeWidget->rowCount();
        topVolumeWidget->insertRow(newRow);
        QLabel* iconLabel = qobject_cast<QLabel*>(tableWidget->cellWidget(volumes[i].second, 0));
        if (iconLabel && !iconLabel->pixmap().isNull()) {
            QLabel* newIconLabel = new QLabel;
            newIconLabel->setPixmap(iconLabel->pixmap().copy());
            newIconLabel->setAlignment(Qt::AlignCenter);
            topVolumeWidget->setCellWidget(newRow, 0, newIconLabel);
        } else {
            topVolumeWidget->setCellWidget(newRow, 0, new QLabel("No icon"));
        }
        QString symbolFull = tableWidget->item(volumes[i].second, 1)->text();
        QString symbolCode = symbolFull.section('(', 1, 1).section(')', 0, 0);
        QTableWidgetItem* symbolCodeItem = new QTableWidgetItem(symbolCode);
        symbolCodeItem->setTextAlignment(Qt::AlignCenter);
        double price = tableWidget->item(volumes[i].second, 2)->text().remove('$').toDouble();
        QString priceFormatted = formatWithSuffix(price);
        QTableWidgetItem* priceItem = new QTableWidgetItem(priceFormatted);
        priceItem->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem* changeItem = tableWidget->item(volumes[i].second, 3)->clone();
        topVolumeWidget->setItem(newRow, 1, symbolCodeItem);
        topVolumeWidget->setItem(newRow, 2, priceItem);
        topVolumeWidget->setItem(newRow, 3, changeItem);
    }
}
