#ifndef BINANCE_H
#define BINANCE_H

#include "scraper.h"
#include <QObject>
#include <QVector>
#include <QString>
#include <QJsonObject>
#include <QMap>
#include <QNetworkProxy>

// const QString proxiesPath1 = "/Users/Admin/Desktop/HSE/p2p_fullparsing/p2p_arbitration_app/proxies.txt";

class BinanceAPI : public QObject {
    Q_OBJECT

public:
    explicit BinanceAPI(QObject *parent = nullptr);
    void getCrypto(const QVector<QString> &cryptos);
    void setScraper(Scraper *scraper);

signals:
    void cryptoDataReady(const QString &symbol, const QJsonObject &data);
    void errorOccurred(const QString &error);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    void setNextProxy();
    void loadProxiesFromFile();

    QMap<QString, int> retryCountMap;
    const int maxRetries = 3;
    int pendingRequests;
    Scraper *scraper;
    QNetworkAccessManager *manager;
    QVector<QNetworkProxy> proxyList;
    int currentProxyIndex;
    QString proxiesPath1;
};

#endif // BINANCE_H
