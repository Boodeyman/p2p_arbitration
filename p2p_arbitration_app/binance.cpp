#include "binance.h"
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkProxy>

BinanceAPI::BinanceAPI(QObject *parent) : QObject(parent), scraper(nullptr), currentProxyIndex(0) {
    manager = new QNetworkAccessManager(this);

    // Инициализируем список прокси-серверов
    QNetworkProxy proxy1;
    proxy1.setType(QNetworkProxy::HttpProxy);
    proxy1.setHostName("196.17.249.47");
    proxy1.setPort(8000);
    proxy1.setUser("AYUP1R");
    proxy1.setPassword("wUKVAX");
    proxyList.append(proxy1);

    QNetworkProxy proxy2;
    proxy2.setType(QNetworkProxy::HttpProxy);
    proxy2.setHostName("196.17.67.75");
    proxy2.setPort(8000);
    proxy2.setUser("yzbLcj");
    proxy2.setPassword("sn5tVm");
    proxyList.append(proxy2);

    QNetworkProxy proxy3;
    proxy3.setType(QNetworkProxy::HttpProxy);
    proxy3.setHostName("45.130.126.84");
    proxy3.setPort(8000);
    proxy3.setUser("x3mGeU");
    proxy3.setPassword("DFxtuN");
    proxyList.append(proxy3);

    QNetworkProxy proxy4;
    proxy4.setType(QNetworkProxy::HttpProxy);
    proxy4.setHostName("181.177.85.254");
    proxy4.setPort(9758);
    proxy4.setUser("rkMEWn");
    proxy4.setPassword("eD09JZ");
    proxyList.append(proxy4);

    QNetworkProxy proxy5;
    proxy5.setType(QNetworkProxy::HttpProxy);
    proxy5.setHostName("186.179.49.5");
    proxy5.setPort(8000);
    proxy5.setUser("7PmmyL");
    proxy5.setPassword("GwfamA");
    proxyList.append(proxy5);

    QNetworkProxy proxy6;
    proxy6.setType(QNetworkProxy::HttpProxy);
    proxy6.setHostName("45.85.162.169");
    proxy6.setPort(8000);
    proxy6.setUser("B5WASu");
    proxy6.setPassword("Td2uCw");
    proxyList.append(proxy6);

    QNetworkProxy proxy7;
    proxy7.setType(QNetworkProxy::HttpProxy);
    proxy7.setHostName("168.181.52.14");
    proxy7.setPort(8000);
    proxy7.setUser("PhE4fP");
    proxy7.setPassword("nz05nG");
    proxyList.append(proxy7);

    QNetworkProxy proxy8;
    proxy8.setType(QNetworkProxy::HttpProxy);
    proxy8.setHostName("200.10.36.42");
    proxy8.setPort(8000);
    proxy8.setUser("PhE4fP");
    proxy8.setPassword("nz05nG");
    proxyList.append(proxy8);

    QNetworkProxy proxy9;
    proxy9.setType(QNetworkProxy::HttpProxy);
    proxy9.setHostName("138.219.72.122");
    proxy9.setPort(8000);
    proxy9.setUser("PhE4fP");
    proxy9.setPassword("nz05nG");
    proxyList.append(proxy9);

    QNetworkProxy proxy10;
    proxy10.setType(QNetworkProxy::HttpProxy);
    proxy10.setHostName("138.219.72.205");
    proxy10.setPort(8000);
    proxy10.setUser("PhE4fP");
    proxy10.setPassword("nz05nG");
    proxyList.append(proxy10);

    setNextProxy();

    connect(manager, &QNetworkAccessManager::finished, this, &BinanceAPI::onReplyFinished);
}

void BinanceAPI::setNextProxy() {
    if (proxyList.isEmpty()) {
        emit errorOccurred("Proxy list is empty");
        return;
    }
    currentProxyIndex = (currentProxyIndex + 1) % proxyList.size();
    manager->setProxy(proxyList[currentProxyIndex]);
    // qDebug() << "Using proxy:" << proxyList[currentProxyIndex].hostName() << ":" << proxyList[currentProxyIndex].port();
}

void BinanceAPI::getCrypto(const QVector<QString> &cryptos) {
    if (!scraper) {
        emit errorOccurred("Scraper not set");
        return;
    }

    pendingRequests = cryptos.size(); // Initialize pending requests counter

    for (const auto &crypto : cryptos) {
        retryCountMap[crypto] = 0; // Initialize retry count for each crypto symbol
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
        // qDebug() << "Request failed for symbol:" << symbol << "with error:" << reply->errorString();
        if (retryCountMap[symbol] < maxRetries) {
            retryCountMap[symbol]++;
            // qDebug() << "Retrying request for symbol:" << symbol << "Attempt:" << retryCountMap[symbol];
            setNextProxy(); // Переключаемся на следующий прокси
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
            // qDebug() << "Received empty data for symbol:" << symbol << "Retrying... Attempt:" << retryCountMap[symbol];
            setNextProxy(); // Переключаемся на следующий прокси
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
            // qDebug() << "Received invalid data for symbol:" << symbol << "Retrying... Attempt:" << retryCountMap[symbol];
            setNextProxy(); // Переключаемся на следующий прокси
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
