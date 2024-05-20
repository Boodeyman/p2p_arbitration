#ifndef BINANCE_H
#define BINANCE_H

#include "scraper.h"
#include <QObject>
#include <QVector>
#include <QString>
#include <QJsonObject>
#include <QMap>
#include <QNetworkProxy>

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

    QMap<QString, int> retryCountMap;
    const int maxRetries = 3;
    int pendingRequests;
    Scraper *scraper;
    QNetworkAccessManager *manager;
    QVector<QNetworkProxy> proxyList;
    int currentProxyIndex;
};

#endif // BINANCE_H
