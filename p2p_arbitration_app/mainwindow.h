#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QMap>
#include <QTimer>
#include "binance.h"
#include "scraper.h"
#include "hoverbutton.h"

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
    void requestData();  // Slot to request data periodically
    void searchCrypto();
    void onRowSelected();

private:
    Ui::MainWindow *ui;
    BinanceAPI *api;
    Scraper *scraper;
    QTimer *timer;  // Таймер для периодических обновлений
    QTimer *proxyChangeTimer;  // Таймер для смены прокси
    QMap<QString, int> symbolToRowMap;  // Соответствие символов криптовалют строкам

    HoverButton *hoverButton;
    QLineEdit *lineEdit; // Объявляем lineEdit

    void setupTableWidget();
    void setupCryptoRows();
};

#endif // MAINWINDOW_H
