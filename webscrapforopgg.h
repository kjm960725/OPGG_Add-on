#ifndef WEBSCRAPFOROPGG_H
#define WEBSCRAPFOROPGG_H

#include <QObject>
#include <QJSValue>
#include <GumboParser>

class QJSEngine;
class QNetworkAccessManager;
class WebScrapForOPGG : public QObject
{
    Q_OBJECT
public:
    explicit WebScrapForOPGG(QNetworkAccessManager *client, QJSEngine *jsEngine, QObject *parent = nullptr);
    explicit WebScrapForOPGG(QNetworkAccessManager *client, QObject *parent = nullptr);
    explicit WebScrapForOPGG(QObject *parent = nullptr);

    void setJSEngine(QJSEngine *jSEngine);
    void setClient(QNetworkAccessManager *client);

    Q_INVOKABLE void getChampRateByOPGG(const QString &summonerName, const QJSValue &callback) const;
    Q_INVOKABLE void getSummonerInfoByOPGG(const QString &summonerName, const QJSValue &callback) const;


private:
    void getHTMLByOPGG(const QString &url, std::function<void(const QByteArray &)>callback) const;
    static QJsonValue parseHtmlByChampRate(const QGumboDocument &champHtml);
    static QJsonValue parseHtmlBySummonerInfo(const QGumboDocument &summonerHtml);
    static QJsonValue parseHtmlByPlayedWith(const QGumboDocument &summonerHtml);

    QNetworkAccessManager *mClient = nullptr;
    QJSEngine *mJSEngine = nullptr;
};

#endif // WEBSCRAPFOROPGG_H
