#ifndef BINANCE_H
#define BINANCE_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QJsonObject>

class QNetworkAccessManager;
class QNetworkReply;

class BinanceAPI : public QObject {
    Q_OBJECT

public:
    explicit BinanceAPI(QObject *parent = nullptr);
    void getCrypto(const QVector<QString> &cryptos);  // Updated to handle a list of symbols

signals:
    void cryptoDataReady(const QString &symbol, const QJsonObject &data);
    void errorOccurred(const QString &error);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
};

#endif // BINANCE_H

