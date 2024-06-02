#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QMap>
#include <QTimer>
#include <QPushButton>
#include "binance.h"
#include "scraper.h"
#include "buycrypto.h"
#include "ui_mainwindow.h"

extern int counter;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void updateCryptoData(const QString &symbol, const QJsonObject &data);
    void requestData();
    void searchCrypto();
    void onRowSelected();
    void sortByChangeColumn(int column);
    void logout();
    void hideLineEdit();
    void openBuyCrypto();
    void on_themeChange_clicked();

private:
    Ui::MainWindow *ui;
    BinanceAPI *api;
    Scraper *scraper;
    QTimer *timer;
    QTimer *proxyChangeTimer;
    QTimer *hideTimer;
    QMap<QString, int> symbolToRowMap;
    buycrypto *buycrypto;
    QString formatWithSuffix(double num);
    QString proxiesPath;
    QString databasePath;

    void setupTableWidget();
    void setupCryptoRows();
    void loadProxiesFromFile();
    void updateTopLosersWidget(QTableWidget* tableWidget, QTableWidget* topLosersWidget);
    void updateTopGainersWidget(QTableWidget* tableWidget, QTableWidget* topGainersWidget);
    void updateTopVolumeWidget(QTableWidget* tableWidget, QTableWidget* topVolumeWidget);
    void updateBuyCryptoData(const QString &symbol, double price, double change, double volume);
};

#endif // MAINWINDOW_H
