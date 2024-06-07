#include "binance.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>
#include <QCoreApplication>

BinanceAPI::BinanceAPI(QObject *parent) : QObject(parent), scraper(nullptr), currentProxyIndex(0) {
    manager = new QNetworkAccessManager(this);

    QString basePath = QCoreApplication::applicationDirPath();
    proxiesPath1 = basePath + "/../Resources/proxies.txt";

    loadProxiesFromFile();
    setNextProxy();
    connect(manager, &QNetworkAccessManager::finished, this, &BinanceAPI::onReplyFinished);
}

void BinanceAPI::loadProxiesFromFile() {
    QFile file(proxiesPath1);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open proxies.txt file. Error:" << file.errorString();
        emit errorOccurred("Failed to open proxies.txt file");
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() != 5) {
            qDebug() << "Invalid line format:" << line;
            continue;
        }

        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName(fields[1]);
        proxy.setPort(static_cast<quint16>(fields[2].toInt()));
        proxy.setUser(fields[3]);
        proxy.setPassword(fields[4]);
        proxyList.append(proxy);
    }
    file.close();
}

void BinanceAPI::setNextProxy() {
    if (proxyList.isEmpty()) {
        emit errorOccurred("Proxy list is empty");
        return;
    }
    currentProxyIndex = (currentProxyIndex + 1) % proxyList.size();
    manager->setProxy(proxyList[currentProxyIndex]);
    qDebug() << "Using proxy:" << proxyList[currentProxyIndex].hostName() << ":" << proxyList[currentProxyIndex].port();
}

void BinanceAPI::getCrypto(const QVector<QString> &cryptos) {
    if (!scraper) {
        emit errorOccurred("Scraper not set");
        return;
    }

    pendingRequests = cryptos.size();

    for (const auto &crypto : cryptos) {
        retryCountMap[crypto] = 0;
        QString url = QString("https://www.binance.com/bapi/asset/v2/public/asset-service/product/get-product-by-symbol?symbol=%1").arg(crypto);
        QNetworkRequest request((QUrl(url)));
        request.setAttribute(QNetworkRequest::User, crypto);
        manager->get(request);
    }
}


void BinanceAPI::onReplyFinished(QNetworkReply *reply) {
    QString symbol = reply->request().attribute(QNetworkRequest::User).toString();
    QByteArray data = reply->readAll();

    if (reply->error() != QNetworkReply::NoError) {
        if (retryCountMap[symbol] < maxRetries) {
            retryCountMap[symbol]++;
            setNextProxy();
            QString url = QString("https://www.binance.com/bapi/asset/v2/public/asset-service/product/get-product-by-symbol?symbol=%1").arg(symbol);
            QNetworkRequest request((QUrl(url)));
            request.setAttribute(QNetworkRequest::User, symbol);
            manager->get(request);
        } else {
            emit errorOccurred("Failed to fetch data for symbol: " + symbol + " after " + QString::number(maxRetries) + " attempts");
        }
        reply->deleteLater();
        return;
    }

    if (data.isEmpty()) {
        if (retryCountMap[symbol] < maxRetries) {
            retryCountMap[symbol]++;
            setNextProxy();
            QString url = QString("https://www.binance.com/bapi/asset/v2/public/asset-service/product/get-product-by-symbol?symbol=%1").arg(symbol);
            QNetworkRequest request((QUrl(url)));
            request.setAttribute(QNetworkRequest::User, symbol);
            manager->get(request);
        } else {
            emit errorOccurred("Received empty data for symbol: " + symbol + " after " + QString::number(maxRetries) + " attempts");
        }
        reply->deleteLater();
        return;
    }

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        emit errorOccurred("Failed to parse JSON for symbol: " + symbol + " Error: " + parseError.errorString());
        reply->deleteLater();
        return;
    }

    QJsonObject jsonObject = doc.object();
    if (jsonObject.isEmpty() || !jsonObject.contains("data")) {
        if (retryCountMap[symbol] < maxRetries) {
            retryCountMap[symbol]++;
            setNextProxy();
            QString url = QString("https://www.binance.com/bapi/asset/v2/public/asset-service/product/get-product-by-symbol?symbol=%1").arg(symbol);
            QNetworkRequest request((QUrl(url)));
            request.setAttribute(QNetworkRequest::User, symbol);
            manager->get(request);
        } else {
            emit errorOccurred("Received invalid data for symbol: " + symbol + " after " + QString::number(maxRetries) + " attempts");
        }
        reply->deleteLater();
        return;
    }

    emit cryptoDataReady(symbol, jsonObject);
    reply->deleteLater();
}

void BinanceAPI::setScraper(Scraper *scraper) {
    this->scraper = scraper;
}


