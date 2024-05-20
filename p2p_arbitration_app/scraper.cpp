#include "scraper.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QDebug>
#include <QTimer>
#include <random>

Scraper::Scraper(QObject *parent)
    : QObject(parent), currentProxyIndex(0), manager(new QNetworkAccessManager(this)) {
    connect(manager, &QNetworkAccessManager::finished, this, &Scraper::onNetworkReply);
}

void Scraper::setProxyList(const QVector<QString> &proxies) {
    this->proxies = proxies;
}

void Scraper::testIp() {
    QString url = "https://api.ipify.org?format=json";
    QString proxy = getNextProxy();
    fetchUrl(url, proxy);
}

QString Scraper::makeRequest(const QString &url) {
    QString proxy = getNextProxy();
    return fetchUrl(url, proxy);
}

QString Scraper::getRandomProxy() {
    if (proxies.isEmpty()) return QString();
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, proxies.size() - 1);
    return proxies.at(dist(rng));
}

QString Scraper::getNextProxy() {
    if (proxies.isEmpty()) return QString();
    currentProxyIndex = (currentProxyIndex + 1) % proxies.size();
    return proxies.at(currentProxyIndex);
}

QString Scraper::fetchUrl(const QString &url, const QString &proxy) {
    QNetworkRequest request((QUrl(url)));
    if (!proxy.isEmpty()) {
        QNetworkProxy networkProxy;
        networkProxy.setType(QNetworkProxy::Socks5Proxy);
        QStringList proxyParts = proxy.split(':');
        networkProxy.setHostName(proxyParts[0]);
        networkProxy.setPort(proxyParts[1].toUInt());
        networkProxy.setUser(proxyParts[2]);
        networkProxy.setPassword(proxyParts[3]);
        manager->setProxy(networkProxy);
        qDebug() << "New proxy: " << proxy;
    } else {
        manager->setProxy(QNetworkProxy::NoProxy);
        qDebug() << "New proxy: null";
    }
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onNetworkReply(reply);
    });
    return QString();
}

void Scraper::onNetworkReply(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Request failed with proxy" << manager->proxy().hostName() << ":" << reply->errorString();
    } else {
        qDebug() << "HTML Content fetched:" << reply->readAll();
    }
    reply->deleteLater();
}
