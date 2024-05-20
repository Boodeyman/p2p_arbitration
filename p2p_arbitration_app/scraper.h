#ifndef SCRAPER_H
#define SCRAPER_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkProxy>

class Scraper : public QObject {
    Q_OBJECT

public:
    explicit Scraper(QObject *parent = nullptr);
    void setProxyList(const QVector<QString> &proxies);
    void testIp();
    QString makeRequest(const QString &url);



private:
    QVector<QString> proxyList;
    QVector<QString> proxies;
    int currentProxyIndex;
    QNetworkAccessManager *manager;

    QString getRandomProxy();
    QString getNextProxy();
    QString fetchUrl(const QString &url, const QString &proxy);

private slots:
    void onNetworkReply(QNetworkReply *reply);
};

#endif // SCRAPER_H
