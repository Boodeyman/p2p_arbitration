#include "scraper.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QDebug>

Scraper::Scraper(QObject *parent)
    : QObject(parent), currentProxyIndex(0), manager(new QNetworkAccessManager(this)) {
    connect(manager, &QNetworkAccessManager::finished, this, &Scraper::onNetworkReply);
}

void Scraper::setProxyList(const QVector<QString> &proxies) {
    this->proxyList = proxies;
}

void Scraper::testIp() {
    QString url = "https://api.ipify.org?format=json";
    makeRequest(url, [](const QByteArray &data, bool success) {
        if (success) {
            // qDebug() << "Test IP Response data:" << data;
        } else {
            // qDebug() << "Test IP failed.";
        }
    });
}

void Scraper::makeRequest(const QString &url, std::function<void(const QByteArray &, bool)> callback) {
    currentCallback = callback;
    fetchUrl(url);
}

QString Scraper::getNextProxy() {
    if (proxyList.isEmpty()) return QString();
    currentProxyIndex = (currentProxyIndex + 1) % proxyList.size();
    return proxyList.at(currentProxyIndex);
}

void Scraper::fetchUrl(const QString &url, int retryCount) {
    QString proxy = getNextProxy();
    QNetworkRequest request((QUrl(url)));

    if (!proxy.isEmpty()) {
        QNetworkProxy networkProxy;
        networkProxy.setType(QNetworkProxy::HttpProxy);
        QStringList proxyParts = proxy.split(':');
        networkProxy.setHostName(proxyParts[0]);
        networkProxy.setPort(proxyParts[1].toUInt());
        if (proxyParts.size() > 2) {
            networkProxy.setUser(proxyParts[2]);
            networkProxy.setPassword(proxyParts[3]);
        }
        manager->setProxy(networkProxy);
        // qDebug() << "Using proxy:" << proxy;
    } else {
        manager->setProxy(QNetworkProxy::NoProxy);
        // qDebug() << "Using no proxy";
    }

    QNetworkReply *reply = manager->get(request);
    retryCountMap[reply] = retryCount;
}

void Scraper::onNetworkReply(QNetworkReply *reply) {
    QByteArray data = reply->readAll();
    int retryCount = retryCountMap[reply];
    bool success = (reply->error() == QNetworkReply::NoError) && !data.isEmpty();

    if (!success) {
        // qDebug() << "Request failed or returned empty data with proxy" << manager->proxy().hostName() << ":" << reply->errorString();
        if (retryCount < maxRetries) {
            // qDebug() << "Retrying... Attempt:" << retryCount + 1;
            fetchUrl(reply->url().toString(), retryCount + 1);
        } else {
            // qDebug() << "Max retries reached. Giving up.";
            if (currentCallback) {
                currentCallback(data, false);
            }
        }
    } else {
        // qDebug() << "Response data:" << data;
        if (currentCallback) {
            currentCallback(data, true);
        }
    }

    retryCountMap.remove(reply);
    reply->deleteLater();
}
