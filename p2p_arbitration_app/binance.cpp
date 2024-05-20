#include "binance.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>

BinanceAPI::BinanceAPI(QObject *parent) : QObject(parent), manager(new QNetworkAccessManager(this)) {
    connect(manager, &QNetworkAccessManager::finished, this, &BinanceAPI::onReplyFinished);
    this->scraper = nullptr;
}

void BinanceAPI::getCrypto(const QVector<QString> &cryptos) {
    for (const auto &crypto : cryptos) {
        QUrl url(QString("https://www.binance.com/bapi/asset/v2/public/asset-service/product/get-product-by-symbol?symbol=%1").arg(crypto));
        QNetworkRequest request(url);
        manager->get(request)->setProperty("symbol", crypto);  // Set the symbol as a property
    }
}

void BinanceAPI::onReplyFinished(QNetworkReply *reply) {
    QString symbol = reply->property("symbol").toString();  // Retrieve the symbol
    if (reply->error()) {
        emit errorOccurred(reply->errorString());
    } else {
        auto doc = QJsonDocument::fromJson(reply->readAll());
        emit cryptoDataReady(symbol, doc.object());
    }
    reply->deleteLater();
}

void BinanceAPI::setScraper(Scraper *scraper){
    this->scraper = scraper;
}
