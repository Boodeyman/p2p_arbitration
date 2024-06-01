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
const QString proxiesPath = "/Users/kirillzykov/Desktop/p2p_arbitration/p2p_arbitration_app/proxies.txt";
const QString databasePath = "/Users/kirillzykov/Desktop/p2p_arbitration/users.db";
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
    QTimer *hideTimer;  // Таймер для скрытия lineEdit
    QMap<QString, int> symbolToRowMap;
    buycrypto *buycrypto;
    QString formatWithSuffix(double num);


    void setupTableWidget();
    void setupCryptoRows();
    void loadProxiesFromFile();
    void updateTopLosersWidget(QTableWidget* tableWidget, QTableWidget* topLosersWidget);
    void updateTopGainersWidget(QTableWidget* tableWidget, QTableWidget* topGainersWidget);
    void updateTopVolumeWidget(QTableWidget* tableWidget, QTableWidget* topVolumeWidget);

};

#endif // MAINWINDOW_H
