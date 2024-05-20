#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QMap>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class BinanceAPI;
class Scraper;  // Добавьте это объявление

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateCryptoData(const QString &symbol, const QJsonObject &data);
    void requestData();  // Slot to request data periodically

private:
    Ui::MainWindow *ui;
    BinanceAPI *api;
    Scraper *scraper;  // Добавьте это объявление
    QTimer *timer;  // Timer for periodic updates
    QTimer *proxyChangeTimer;  // Timer for changing proxies
    QMap<QString, int> symbolToRowMap;  // Maps cryptocurrency symbols to row indices

    void setupTableWidget();
    void setupCryptoRows();
};

#endif // MAINWINDOW_H
