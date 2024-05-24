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
    void requestData();
    void searchCrypto();
    void onRowSelected();
    void sortByChangeColumn(int column); // New slot for sorting

private:
    Ui::MainWindow *ui;
    BinanceAPI *api;
    Scraper *scraper;
    QTimer *timer;
    QTimer *proxyChangeTimer;
    QMap<QString, int> symbolToRowMap;

    HoverButton *hoverButton;
    QLineEdit *lineEdit;

    void setupTableWidget();
    void setupCryptoRows();
};

#endif // MAINWINDOW_H
