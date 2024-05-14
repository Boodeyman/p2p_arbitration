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
    QTimer *timer;  // Timer for periodic updates
    QMap<QString, int> symbolToRowMap;  // Maps cryptocurrency symbols to row indices

    void setupTableWidget();
    void setupCryptoRows();
};

#endif // MAINWINDOW_H
