#include "riot.h"
#include <QJSEngine>
#include <QQmlApplicationEngine>
#include <QUrlQuery>
#include <QVariant>
#include <QJsonArray>
#include <QMetaEnum>
#include <QJsonDocument>

using namespace riot;

Riot::Riot(QObject *parent)
    : QObject(parent)
    , mRetryAfter(new QTimer(this))
{
    connect(mRetryAfter, &QTimer::timeout, mRetryAfter, &QTimer::stop);
}

Riot::Riot(QNetworkAccessManager *client, const QString &apiKey, QObject *parent)
    : QObject(parent)
    , mRetryAfter(new QTimer(this))
    , mClient(client)
    , mApiKey(apiKey)
{
    connect(mRetryAfter, &QTimer::timeout, mRetryAfter, &QTimer::stop);
}

QNetworkAccessManager *Riot::client() const
{
    return mClient;
}

void Riot::setClient(QNetworkAccessManager *client)
{
    mClient = client;
}

QString Riot::apiKey() const
{
    return mApiKey;
}

void Riot::setApiKey(const QString &apiKey)
{
    mApiKey = apiKey;
}

void Riot::getChampMasteriesAllBySummonerId(const QString &summonerId, Riot::RoutingFlatform routing, const QJSValue &jsCallback)
{
    QJSValue *js = new QJSValue(jsCallback);
    this->get(QString("/lol/champion-mastery/v4/champion-masteries/by-summoner/%1").arg(summonerId),QUrlQuery(),routing,[this,js](const QByteArray &json, int err, const QString &errStr){
        js->call(QJSValueList() << JsonObject::convertToJSValue(mJSEngine, QJsonDocument::fromJson(json).array()) << err << errStr);
        delete js;
    });
}

void Riot::getChampMasteriesAllBySummonerId(const QString &summonerId, Riot::RoutingFlatform routing, std::function<void (const QList<ChampionMasteryDTO> &, int, QString)> callback)
{
    this->get(QString("/lol/champion-mastery/v4/champion-masteries/by-summoner/%1").arg(summonerId),QUrlQuery(),routing,[callback](const QByteArray &json, int err, const QString &errStr){
        QList<ChampionMasteryDTO>result;
        auto arr = QJsonDocument::fromJson(json).array();
        for (auto val : arr) {
            result.append(static_cast<ChampionMasteryDTO&&>(val.toObject()));
        }
        callback(result, err, errStr);
    });
}

void Riot::getChampMasteriesAllBySummonerId(const QString &summonerId, const QString &championId, Riot::RoutingFlatform routing, const QJSValue &jsCallback)
{
    QJSValue *js = new QJSValue(jsCallback);
    this->get(QString("/lol/champion-mastery/v4/champion-masteries/by-summoner/%1/by-champion/%2").arg(summonerId).arg(championId),QUrlQuery(),routing,[this,js](const QByteArray &json, int err, const QString &errStr){
        js->call(QJSValueList() << JsonObject::convertToJSValue(mJSEngine, QJsonDocument::fromJson(json).object()) << err << errStr);
        delete js;
    });
}

void Riot::getChampMasteryBySummonerId(const QString &summonerId, const QString &championId, Riot::RoutingFlatform routing, std::function<void (const ChampionMasteryDTO &, int, QString)> callback)
{
    this->get(QString("/lol/champion-mastery/v4/champion-masteries/by-summoner/%1/by-champion/%2").arg(summonerId).arg(championId),QUrlQuery(),routing,[callback](const QByteArray &json, int err, const QString &errStr){
        callback(static_cast<ChampionMasteryDTO&&>(QJsonDocument::fromJson(json).object()), err, errStr);
    });
}

void Riot::getChampMasteryScoreBySummonerId(const QString &summonerId, Riot::RoutingFlatform routing, const QJSValue &jsCallback)
{
    QJSValue *js = new QJSValue(jsCallback);
    this->get(QString("/lol/champion-mastery/v4/scores/by-summoner/%1").arg(summonerId),QUrlQuery(),routing,[js](const QByteArray &data, int err, const QString &errStr){
        js->call(QJSValueList() << QString(data).toInt() << err << errStr);
        delete js;
    });
}

void Riot::getChampMasteryScoreBySummonerId(const QString &summonerId, Riot::RoutingFlatform routing, std::function<void (int, int, QString)> callback)
{
    this->get(QString("/lol/champion-mastery/v4/scores/by-summoner/%1").arg(summonerId),QUrlQuery(),routing,[callback](const QByteArray &data, int err, const QString &errStr){
        callback(QString(data).toInt(), err, errStr);
    });
}

void Riot::getChampRotations(Riot::RoutingFlatform routing, const QJSValue &jsCallback)
{
    QJSValue *js = new QJSValue(jsCallback);
    this->get(QString("/lol/platform/v3/champion-rotations"),QUrlQuery(),routing,[this,js](const QByteArray &json, int err, const QString &errStr){
        js->call(QJSValueList() << JsonObject::convertToJSValue(mJSEngine, QJsonDocument::fromJson(json).object()) << err << errStr);
        delete js;
    });
}

void Riot::getChampRotations(Riot::RoutingFlatform routing, std::function<void (const ChampionInfo &, int, QString)> callback)
{
    this->get(QString("/lol/platform/v3/champion-rotations"),QUrlQuery(),routing,[callback](const QByteArray &json, int err, const QString &errStr){
        callback(static_cast<ChampionInfo&&>(QJsonDocument::fromJson(json).object()), err, errStr);
    });
}

void Riot::getClashAllPlayersBySummonerId(const QString &summonerId, Riot::RoutingFlatform routing, std::function<void (const QList<PlayerDto> &, int, QString)> callback)
{
    this->get(QString("/lol/clash/v1/players/by-summoner/%1").arg(summonerId),QUrlQuery(),routing,[callback](const QByteArray &json, int err, const QString &errStr){
        QList<PlayerDto>result;
        auto arr = QJsonDocument::fromJson(json).array();
        for (auto val : arr) {
            result.append(static_cast<PlayerDto&&>(val.toObject()));
        }
        callback(result, err, errStr);
    });
}

void Riot::getClashTeamByTeamId(const QString &teamId, Riot::RoutingFlatform routing, std::function<void (const TeamDto &, int, QString)> callback)
{
    this->get(QString("/lol/clash/v1/teams/%1").arg(teamId),QUrlQuery(),routing,[callback](const QByteArray &json, int err, const QString &errStr){
        callback(static_cast<TeamDto&&>(QJsonDocument::fromJson(json).object()), err, errStr);
    });
}

void Riot::getClashAllTournaments(Riot::RoutingFlatform routing, std::function<void (const QList<TournamentDto> &, int, QString)> callback)
{
    this->get(QString("/lol/clash/v1/tournaments"),QUrlQuery(),routing,[callback](const QByteArray &json, int err, const QString &errStr){
        QList<TournamentDto>result;
        auto arr = QJsonDocument::fromJson(json).array();
        for (auto val : arr) {
            result.append(static_cast<TournamentDto&&>(val.toObject()));
        }
        callback(result, err, errStr);
    });
}

void Riot::getClashTournamentByTeamId(const QString &teamId, Riot::RoutingFlatform routing, std::function<void (const TournamentDto &, int, QString)> callback)
{
    this->get(QString("/lol/clash/v1/tournaments/by-team/%1").arg(teamId),QUrlQuery(),routing,[callback](const QByteArray &json, int err, const QString &errStr){
        callback(static_cast<TournamentDto&&>(QJsonDocument::fromJson(json).object()), err, errStr);
    });
}

void Riot::getClashTournamentByTournamentId(const QString &tournamentId, Riot::RoutingFlatform routing, std::function<void (const TournamentDto &, int, QString)> callback)
{
    this->get(QString("/lol/clash/v1/tournaments/%1").arg(tournamentId),QUrlQuery(),routing,[callback](const QByteArray &json, int err, const QString &errStr){
        callback(static_cast<TournamentDto&&>(QJsonDocument::fromJson(json).object()), err, errStr);
    });
}

void Riot::getCurrentGameInfo(const QString &summonerId, Riot::RoutingFlatform routing, const QJSValue &jsCallback)
{
    QJSValue *js = new QJSValue(jsCallback);
    this->get(QString("/lol/spectator/v4/active-games/by-summoner/%1").arg(summonerId),QUrlQuery(),routing,[this,js](const QByteArray &json, int err, const QString &errStr){
        js->call(QJSValueList() << JsonObject::convertToJSValue(mJSEngine, QJsonDocument::fromJson(json).object()) << err << errStr);
        delete js;
    });
}

void Riot::getCurrentGameInfo(const QString &summonerId, RoutingFlatform routing, std::function<void (const CurrentGameInfo &, int, QString)>callback)
{
    this->get(QString("/lol/spectator/v4/active-games/by-summoner/%1").arg(summonerId),QUrlQuery(),routing,[callback](const QByteArray &json, int err, const QString &errStr){
        callback(static_cast<CurrentGameInfo&&>(QJsonDocument::fromJson(json).object()), err, errStr);
    });
}

void Riot::getSummonerByName(const QString &summonerName, Riot::RoutingFlatform routing, const QJSValue &jsCallback)
{
    QJSValue *js = new QJSValue(jsCallback);
    this->get(QString("/lol/summoner/v4/summoners/by-name/%1").arg(summonerName),QUrlQuery(),routing,[this,js](const QByteArray &json, int err, const QString &errStr){
        js->call(QJSValueList() << JsonObject::convertToJSValue(mJSEngine, QJsonDocument::fromJson(json).object()) << err << errStr);
        delete js;
    });
}
void Riot::getSummonerByName(const QString &summonerName, RoutingFlatform routing, std::function<void (const SummonerDTO &, int, QString)> callback)
{
    this->get(QString("/lol/summoner/v4/summoners/by-name/%1").arg(summonerName),QUrlQuery(),routing,[callback](const QByteArray &json, int err, const QString &errStr){
        callback(static_cast<SummonerDTO&&>(QJsonDocument::fromJson(json).object()), err, errStr);
    });
}

void Riot::setJSEngine(QJSEngine *engine)
{
    mJSEngine = engine;
}

void Riot::getLeagueBySummoner(const QString &summonerId, Riot::RoutingFlatform routing, const QJSValue &jsCallback)
{
    QJSValue *js = new QJSValue(jsCallback);
    this->get(QString("/lol/league/v4/entries/by-summoner/%1").arg(summonerId),QUrlQuery(),routing,[this,js](const QByteArray &json, int err, const QString &errStr){
        js->call(QJSValueList() << JsonObject::convertToJSValue(mJSEngine, QJsonDocument::fromJson(json).array()) << err << errStr);
        delete js;
    });
}

void Riot::getLeagueBySummoner(const QString &summonerId, RoutingFlatform routing, std::function<void (const QList<LeagueEntryDTO> &, int, QString)> callback)
{
    this->get(QString("/lol/league/v4/entries/by-summoner/%1").arg(summonerId),QUrlQuery(),routing,[callback](const QByteArray &json, int err, const QString &errStr){
        QList<LeagueEntryDTO>result;
        auto arr = QJsonDocument::fromJson(json).array();
        for (auto val : arr) {
            result.append(static_cast<LeagueEntryDTO&&>(val.toObject()));
        }
        callback(result, err, errStr);
    });
}


void Riot::get(const QString &path, const QUrlQuery &qurry, RoutingFlatform routing , std::function<void (const QByteArray &, int, const QString &)> callback)
{
    std::function<void(int,bool)> reateLimitFunction = [this, callback](int sec, bool initTimer) {
        qWarning() << "Riot - APIError : rate limited - retry after" << sec;
        callback(QByteArray(), 429, tr("%1 초 후 다시 시도해주세요. (사유 : Riot API 속도제한)")
                 .arg(QString::number(sec)));
        if (initTimer) {
            mRetryAfter->start(sec * 1000);
            emit rateLimited(sec);
        }
    };

    if (mRetryAfter->isActive()) { // Rate limited
        reateLimitFunction((mRetryAfter->remainingTime() + 1000)  / 1000 , false);
        return;
    }

    QUrl url;
    url.setScheme("https");

    auto metaEnum = QMetaEnum::fromType<Riot::RoutingFlatform>();
    url.setHost(QString("%1.api.riotgames.com")
                .arg(QString(metaEnum.key(routing)).toLower()));
    url.setPath(path);
    url.setQuery(qurry);

    QNetworkRequest request(url);
    request.setRawHeader("X-Riot-Token", mApiKey.toUtf8());
    QNetworkReply *re = mClient->get(request);
    connect(re, &QNetworkReply::finished, this, [callback, re, path, reateLimitFunction](){
        re->deleteLater();
        int retryAfter = QString(re->rawHeader("Retry-After")).toInt();
        if (retryAfter > 0) { // Rate limited exception
            reateLimitFunction(retryAfter, true);
            return;
        }

        QByteArray buffer = re->readAll();
        QJsonDocument json = QJsonDocument::fromJson(buffer);
        if (json.object().contains("status")) {
            QJsonObject status = json.object().value("status").toObject();
            if (status.value("status_code").toInt() == 404) {
                callback(QByteArray(), 0, QString());
            } else {
                qWarning() << "Riot - APIError :" << status << re->request().url() << re->rawHeaderPairs();
                callback(QByteArray(), status.value("status_code").toInt(), QString("RiotAPIError(%1)").arg(status.value("message").toString()));
            }

        } else if (re->error() != QNetworkReply::NoError) {
            qWarning() << "Riot - NetworkError :" << json << re->error() << re->errorString();
            callback(QByteArray(), re->error(), QString("NetworkError(%1)").arg(re->errorString()));

        } else {
            callback(buffer, 0, "");
        }
    });
}
