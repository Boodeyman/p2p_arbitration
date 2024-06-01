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
        ui->logoutButton->setIcon(QIcon(":/icons/icons/logoutWhite.png"));
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
        setDarkStyle(this);
        setDarkStyle(ui->tableWidget);
        setDarkStyle(ui->comboBox);
        setDarkStyle(ui->comboBox_2);
    }
    else {
        ui->themeChange->setIcon(QIcon(":/icons/icons/light.png"));
        ui->hoverButton->setIcon(QIcon(":/icons/icons/hooverLightStatic.png"));
        ui->logoutButton->setIcon(QIcon(":/icons/icons/logoutBlack.png"));
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
        setLightStyle(ui->tableWidget);
        setLightStyle(ui->comboBox);
        setLightStyle(ui->comboBox_2);
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

    ui->topLosersWidget->setColumnWidth(0, 40);
    ui->topLosersWidget->setColumnWidth(1, 50);
    ui->topLosersWidget->setColumnWidth(2, 70);
    ui->topLosersWidget->setColumnWidth(3, 70);

    // Очистка текущих данных в topLosersWidget
    topLosersWidget->clearContents();
    topLosersWidget->setRowCount(0);

    // Настройка заголовков столбцов
    topLosersWidget->setColumnCount(4);
    topLosersWidget->setHorizontalHeaderLabels(QStringList() << "Icon" << "Symbol Code" << "Price" << "Change");

    // Собираем данные для сортировки
    QList<QPair<double, int>> changes;
    int rowCount = tableWidget->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QTableWidgetItem* changeItem = tableWidget->item(i, 3); // Предполагаем, что столбец изменения цены — это четвертый столбец
        if (changeItem) {
            double change = changeItem->text().remove('%').toDouble();
            changes.append(qMakePair(change, i));
        }
    }

    // Сортировка данных по убыванию
    std::sort(changes.begin(), changes.end(), [](const QPair<double, int>& a, const QPair<double, int>& b) {
        return a.first < b.first;  // Сортировка по убыванию
    });

    // Ограничиваем количество отображаемых элементов до трех
    int displayCount = qMin(changes.size(), 3);

    // Заполняем topLosersWidget отсортированными данными
    for (int i = 0; i < displayCount; ++i) {
        int newRow = topLosersWidget->rowCount();
        topLosersWidget->insertRow(newRow);

        // Копирование иконки из tableWidget
        QLabel* iconLabel = qobject_cast<QLabel*>(tableWidget->cellWidget(changes[i].second, 0)); // Первый столбец предположительно содержит иконку
        if (iconLabel && !iconLabel->pixmap().isNull()) {
            QLabel* newIconLabel = new QLabel;
            newIconLabel->setPixmap(iconLabel->pixmap().copy());  // Копирование QPixmap
            newIconLabel->setAlignment(Qt::AlignCenter);
            topLosersWidget->setCellWidget(newRow, 0, newIconLabel);
        } else {
            // Устанавливаем пустую ячейку или текст "No icon"
            topLosersWidget->setCellWidget(newRow, 0, new QLabel("No icon"));
        }

        // Копирование символа, цены, изменения
        QString symbolFull = tableWidget->item(changes[i].second, 1)->text();
        QString symbolCode = symbolFull.section('(', 1, 1).section(')', 0, 0); // Извлечение кода символа из полного имени

        QTableWidgetItem* symbolCodeItem = new QTableWidgetItem(symbolCode);
        symbolCodeItem->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem* priceItem = tableWidget->item(changes[i].second, 2)->clone(); // Третий столбец - цена
        QTableWidgetItem* changeItem = tableWidget->item(changes[i].second, 3)->clone(); // Четвертый столбец - изменение

        // Копирование формата (цвет текста) для изменения
        changeItem->setForeground(tableWidget->item(changes[i].second, 3)->foreground());

        topLosersWidget->setItem(newRow, 1, symbolCodeItem);
        topLosersWidget->setItem(newRow, 2, priceItem);
        topLosersWidget->setItem(newRow, 3, changeItem);
    }
}


void MainWindow::updateTopGainersWidget(QTableWidget* tableWidget, QTableWidget* topGainersWidget) {

    ui->topGainersWidget->setColumnWidth(0, 40);
    ui->topGainersWidget->setColumnWidth(1, 50);
    ui->topGainersWidget->setColumnWidth(2, 70);
    ui->topGainersWidget->setColumnWidth(3, 70);

    // Очистка текущих данных в topLosersWidget
    topGainersWidget->clearContents();
    topGainersWidget->setRowCount(0);

    // Настройка заголовков столбцов
    topGainersWidget->setColumnCount(4);
    topGainersWidget->setHorizontalHeaderLabels(QStringList() << "Icon" << "Symbol Code" << "Price" << "Change");

    // Собираем данные для сортировки
    QList<QPair<double, int>> changes;
    int rowCount = tableWidget->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QTableWidgetItem* changeItem = tableWidget->item(i, 3); // Предполагаем, что столбец изменения цены — это четвертый столбец
        if (changeItem) {
            double change = changeItem->text().remove('%').toDouble();
            changes.append(qMakePair(change, i));
        }
    }

    // Сортировка данных по убыванию
    std::sort(changes.begin(), changes.end(), [](const QPair<double, int>& a, const QPair<double, int>& b) {
        return a.first > b.first;  // Сортировка по убыванию
    });

    // Ограничиваем количество отображаемых элементов до трех
    int displayCount = qMin(changes.size(), 3);

    // Заполняем topLosersWidget отсортированными данными
    for (int i = 0; i < displayCount; ++i) {
        int newRow = topGainersWidget->rowCount();
        topGainersWidget->insertRow(newRow);

        // Копирование иконки из tableWidget
        QLabel* iconLabel = qobject_cast<QLabel*>(tableWidget->cellWidget(changes[i].second, 0)); // Первый столбец предположительно содержит иконку
        if (iconLabel && !iconLabel->pixmap().isNull()) {
            QLabel* newIconLabel = new QLabel;
            newIconLabel->setPixmap(iconLabel->pixmap().copy());  // Копирование QPixmap
            newIconLabel->setAlignment(Qt::AlignCenter);
            topGainersWidget->setCellWidget(newRow, 0, newIconLabel);
        } else {
            // Устанавливаем пустую ячейку или текст "No icon"
            topGainersWidget->setCellWidget(newRow, 0, new QLabel("No icon"));
        }

        // Копирование символа, цены, изменения
        QString symbolFull = tableWidget->item(changes[i].second, 1)->text();
        QString symbolCode = symbolFull.section('(', 1, 1).section(')', 0, 0); // Извлечение кода символа из полного имени

        QTableWidgetItem* symbolCodeItem = new QTableWidgetItem(symbolCode);
        symbolCodeItem->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem* priceItem = tableWidget->item(changes[i].second, 2)->clone(); // Третий столбец - цена
        QTableWidgetItem* changeItem = tableWidget->item(changes[i].second, 3)->clone(); // Четвертый столбец - изменение

        // Копирование формата (цвет текста) для изменения
        changeItem->setForeground(tableWidget->item(changes[i].second, 3)->foreground());

        topGainersWidget->setItem(newRow, 1, symbolCodeItem);
        topGainersWidget->setItem(newRow, 2, priceItem);
        topGainersWidget->setItem(newRow, 3, changeItem);
    }
}

void MainWindow::updateTopVolumeWidget(QTableWidget* tableWidget, QTableWidget* topVolumeWidget) {
    ui->topVolumeWidget->setColumnWidth(0, 40);
    ui->topVolumeWidget->setColumnWidth(1, 50);
    ui->topVolumeWidget->setColumnWidth(2, 70);
    ui->topVolumeWidget->setColumnWidth(3, 70);

    // Очистка текущих данных в topVolumeWidget
    topVolumeWidget->clearContents();
    topVolumeWidget->setRowCount(0);

    // Настройка заголовков столбцов
    topVolumeWidget->setColumnCount(4);
    topVolumeWidget->setHorizontalHeaderLabels(QStringList() << "Top Volume");

    // Собираем данные для сортировки
    QList<QPair<double, int>> volumes;
    int rowCount = tableWidget->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QTableWidgetItem* volumeItem = tableWidget->item(i, 4); // Предполагаем, что столбец объема в USDT — это пятый столбец
        if (volumeItem) {
            QString volumeText = volumeItem->text();
            volumeText.remove('$'); // Удаление знака доллара
            double volume = volumeText.toDouble();
            volumes.append(qMakePair(volume, i));
        }
    }

    // Сортировка данных по убыванию объема
    std::sort(volumes.begin(), volumes.end(), [](const QPair<double, int>& a, const QPair<double, int>& b) {
        return a.first > b.first;  // Сортировка по убыванию
    });

    // Ограничиваем количество отображаемых элементов до трех
    int displayCount = qMin(volumes.size(), 3);

    // Заполняем topVolumeWidget отсортированными данными
    for (int i = 0; i < displayCount; ++i) {
        int newRow = topVolumeWidget->rowCount();
        topVolumeWidget->insertRow(newRow);

        // Копирование иконки из tableWidget
        QLabel* iconLabel = qobject_cast<QLabel*>(tableWidget->cellWidget(volumes[i].second, 0)); // Первый столбец предположительно содержит иконку
        if (iconLabel && !iconLabel->pixmap().isNull()) {
            QLabel* newIconLabel = new QLabel;
            newIconLabel->setPixmap(iconLabel->pixmap().copy());  // Копирование QPixmap
            newIconLabel->setAlignment(Qt::AlignCenter);
            topVolumeWidget->setCellWidget(newRow, 0, newIconLabel);
        } else {
            // Устанавливаем пустую ячейку или текст "No icon"
            topVolumeWidget->setCellWidget(newRow, 0, new QLabel("No icon"));
        }

        // Копирование символа, цены, изменения
        QString symbolFull = tableWidget->item(volumes[i].second, 1)->text();
        QString symbolCode = symbolFull.section('(', 1, 1).section(')', 0, 0); // Извлечение кода символа из полного имени

        QTableWidgetItem* symbolCodeItem = new QTableWidgetItem(symbolCode);
        symbolCodeItem->setTextAlignment(Qt::AlignCenter);

        // Форматирование цены и объема
        double price = tableWidget->item(volumes[i].second, 2)->text().remove('$').toDouble();
        QString priceFormatted = formatWithSuffix(price);
        QTableWidgetItem* priceItem = new QTableWidgetItem(priceFormatted);
        priceItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem* changeItem = tableWidget->item(volumes[i].second, 3)->clone(); // Четвертый столбец - изменение



        topVolumeWidget->setItem(newRow, 1, symbolCodeItem);
        topVolumeWidget->setItem(newRow, 2, priceItem);
        topVolumeWidget->setItem(newRow, 3, changeItem);
    }
}
