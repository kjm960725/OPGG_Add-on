#include "webscrapforopgg.h"
#include <QTextCodec>
#include <QNetworkAccessManager>
#include <GumboParser>
#include <QNetworkReply>
#include <QJsonObject>
#include "RiotJson/JsonObject.h"
#include <QJsonArray>

WebScrapForOPGG::WebScrapForOPGG(QNetworkAccessManager *client, QJSEngine *jsEngine, QObject *parent)
    : QObject(parent)
    , mClient(client)
    , mJSEngine(jsEngine)
{}

WebScrapForOPGG::WebScrapForOPGG(QNetworkAccessManager *client, QObject *parent)
    : QObject(parent)
    , mClient(client)
{}

WebScrapForOPGG::WebScrapForOPGG(QObject *parent) : QObject(parent) {}

void WebScrapForOPGG::getChampRateByOPGG(const QString &summonerName, const QJSValue &_callback) const
{
    qInfo() << QString("WebScrapForOPGG::getChampRateByOPGG called (arg:%1)").arg(summonerName);
    auto callback = new QJSValue(_callback);
    getHTMLByOPGG(QString("https://www.op.gg/summoner/champions/userName=%1").arg(summonerName)
                  , [this, callback](const QByteArray &html){

        QJsonValue champRate = parseHtmlByChampRate(QGumboDocument::parse(html));

        QJsonObject result;
        result.insert("data", champRate);
        result.insert("success", champRate.type() != QJsonValue::Null);

        if (callback->isCallable())
            callback->call(QJSValueList() << JsonObject::convertToJSValue(mJSEngine,result));

        delete callback;
    });
    /*
     {
         "success":bool,
         "data":[
            {
               "id":string,
               "kda":string,
               "lose":double,
               "most":double,
               "name":string,
               "win":double
            }
         ]
     }
    */
}

void WebScrapForOPGG::getSummonerInfoByOPGG(const QString &summonerName, const QJSValue &_callback) const
{
    qInfo() << QString("WebScrapForOPGG::getSummonerInfoByOPGG called (arg:%1)").arg(summonerName);
    auto callback = new QJSValue(_callback);
    getHTMLByOPGG(QString("https://www.op.gg/summoner/userName=%1").arg(summonerName)
                  , [this, callback](const QByteArray &html){

        QJsonObject result;

        auto doc = QGumboDocument::parse(html);
        QJsonValue summonerInfo = parseHtmlBySummonerInfo(doc);
        QJsonValue playedWith = parseHtmlByPlayedWith(doc);

        if (summonerInfo.type() != QJsonValue::Null && playedWith.type() != QJsonValue::Null) {
            QJsonObject data;
            data.insert("summonerInfo", summonerInfo);
            data.insert("playedWith", playedWith);
            result.insert("data", data);
            result.insert("success", true);

        } else {
            result.insert("data", QJsonValue(QJsonValue::Null));
            result.insert("success", false);
        }

        if (callback->isCallable())
            callback->call(QJSValueList() << JsonObject::convertToJSValue(mJSEngine,result));

        delete callback;
    });
    /*
      {
           "success":bool,
           "data":{
               "summonerInfo":{
                   "name":string,
                   "soloRank":{
                       "tier":string,
                       "point":double,
                       "win":double,
                       "lose":double
                   },
                   "flexRank":{
                       "tier":string,
                       "point":double,
                       "win":double,
                       "lose":double
                   }
               },
               "playedWith":[
                   {
                       "name":string,
                       "win":double,
                       "lose":double
                   }
               ]
           }
      }
     */
}

void WebScrapForOPGG::getHTMLByOPGG(const QString &url, std::function<void (const QByteArray &)> callback) const
{
    auto codec = QTextCodec::codecForLocale();
    auto reply = mClient->get(QNetworkRequest(QUrl(codec->toUnicode(url.toLocal8Bit()))));
    reply->ignoreSslErrors();
    connect(reply, &QNetworkReply::finished, this, [callback, reply](){
        QJsonObject result;
        reply->deleteLater();

        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "WebScrapForOPGG::getHTMLByOPGG network error :" << reply->url() << reply->error() << reply->errorString();
        }

        callback(reply->readAll());
    });
}

QJsonValue WebScrapForOPGG::parseHtmlByChampRate(const QGumboDocument &champHtml)
{
    QJsonValue result;
    try {
        auto root = champHtml.rootNode();

        auto tableBodyNodes = root.getElementsByTagName(HtmlTag::TBODY);
        if (tableBodyNodes.size() < 1) throw 1;

        auto rows = tableBodyNodes.front().getElementsByTagName(HtmlTag::TR);
        if (rows.size() < 1) throw 2;
        QJsonArray array;
        for (uint i = 0; i < rows.size(); ++i)
        {
            auto row = rows.at(i);
            QJsonObject object;
            auto champNameNodes = row.getElementsByClassName("ChampionName");
            if (champNameNodes.size() < 1) throw 3;

            auto rateNodes = row.getElementsByClassName("RatioGraph");
            if (rateNodes.size() < 1) throw 4;

            auto winLoseNodes = rateNodes.front().getElementsByClassName("Text");
            if (winLoseNodes.size() < 1) throw 5;

            auto kdaNodes = row.getElementsByClassName("KDA");
            if (kdaNodes.size() < 1) throw 6;

            auto champHrefNodes = champNameNodes.front().getElementsByTagName(HtmlTag::A);
            if (champHrefNodes.size() < 1) throw 7;

            QStringList href = champHrefNodes.front().getAttribute("href").split('/', Qt::SkipEmptyParts);
            if (href.count() < 2) throw 8;

            object["id"] = href.at(1);
            object["name"] = champNameNodes.front().getAttribute("data-value");
            object["win"] = 0;
            object["lose"] = 0;
            for (auto winLoseNode : winLoseNodes) {
                int num = winLoseNode.innerText().remove(QRegExp("[^0-9]")).toInt();
                if (winLoseNode.classList().contains("Left"))
                    object["win"] = num;
                else if (winLoseNode.classList().contains("Right"))
                    object["lose"] = num;
            }
            object["kda"] = kdaNodes.front().getAttribute("data-value");
            object["most"] = int(i + 1);

            array << object;
        }
        result = array;

    } catch (int exceiption) {
        result = QJsonValue(QJsonValue::Null);
        qWarning() << "WebScrapForOPGG::parseHtmlByChampRate throwed :" << exceiption;
    }
    return result;
}

QJsonValue WebScrapForOPGG::parseHtmlBySummonerInfo(const QGumboDocument &summonerHtml)
{
//    {
//        "name":string,
//        "soloRank":{
//            "tier":string,
//            "point":double,
//            "win":double,
//            "lose":double
//        },
//        "flexRank":{
//            "tier":string,
//            "point":double,
//            "win":double,
//            "lose":double
//        }
//    }
    QJsonValue result;
    try {
        auto root = summonerHtml.rootNode();

        auto sideContent = root.getElementsByClassName("SideContent");
        if (sideContent.size() < 1) throw 1;


        QJsonObject soloRank;

        auto tierRankInfo = root.getElementsByClassName("TierRankInfo");
        if (tierRankInfo.size() < 1) throw 2;

        auto tierRank = root.getElementsByClassName("TierRank");
        if (tierRank.size() < 1) throw 3;

        soloRank.insert("tier", tierRank.front().innerText());


    } catch (int exceiption) {
        result = QJsonValue(QJsonValue::Null);
        qWarning() << "WebScrapForOPGG::parseHtmlBySummonerInfo throwed :" << exceiption;
    }
    return result;
}

QJsonValue WebScrapForOPGG::parseHtmlByPlayedWith(const QGumboDocument &summonerHtml)
{
//    [
//       {
//           "name":string,
//           "win":double,
//           "lose":double
//       }
//    ]
    QJsonValue result;
    try {
        auto root = summonerHtml.rootNode();

        auto sideContent = root.getElementsByClassName("SideContent");
        if (sideContent.size() < 1) throw 1;


    } catch (int exceiption) {
        result = QJsonValue(QJsonValue::Null);
        qWarning() << "WebScrapForOPGG::parseHtmlByPlayedWith throwed :" << exceiption;
    }
    return result;
}

void WebScrapForOPGG::setClient(QNetworkAccessManager *client)
{
    mClient = client;
}

void WebScrapForOPGG::setJSEngine(QJSEngine *jSEngine)
{
    mJSEngine = jSEngine;
}
