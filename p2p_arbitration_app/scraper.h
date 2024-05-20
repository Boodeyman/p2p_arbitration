#ifndef SCRAPER_H
#define SCRAPER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkProxy>
#include <functional>

class Scraper : public QObject {
    Q_OBJECT

public:
    explicit Scraper(QObject *parent = nullptr);
    void setProxyList(const QVector<QString> &proxies);
    void testIp();
    void makeRequest(const QString &url, std::function<void(const QByteArray &, bool)> callback);

private:
    QVector<QString> proxyList;
    int currentProxyIndex;
    QNetworkAccessManager *manager;
    std::function<void(const QByteArray &, bool)> currentCallback;
    QMap<QNetworkReply*, int> retryCountMap;
    const int maxRetries = 3;

    QString getNextProxy();
    void fetchUrl(const QString &url, int retryCount = 0);

private slots:
    void onNetworkReply(QNetworkReply *reply);
};

#endif // SCRAPER_H
