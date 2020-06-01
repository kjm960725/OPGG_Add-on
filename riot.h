#ifndef RIOTAPI_H
#define RIOTAPI_H

#include <QJSValue>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include "RiotJson/_RiotJsonInclude.h"
#include <QTimer>


class QJSEngine;
namespace riot {
class Riot : public QObject
{
    Q_OBJECT
public:
    explicit Riot(QObject *parent = nullptr);
    explicit Riot(QNetworkAccessManager* client, const QString &apiKey, QObject *parent = nullptr);

    enum LeagueQueue {
        RankedFlexSR    , // 자유 랭크
        RankedSolo5X5   , // 솔로 랭크
    };
    Q_ENUM(LeagueQueue)

    enum RoutingFlatform {
        BR1  , // br1.api.riotgames.com
        EUN1 , // eun1.api.riotgames.com
        EUW1 , // euw1.api.riotgames.com
        JP1  , // jp1.api.riotgames.com
        KR   , // kr.api.riotgames.com
        LA1  , // la1.api.riotgames.com
        LA2  , // la2.api.riotgames.com
        NA1  , // na1.api.riotgames.com
        OC1  , // oc1.api.riotgames.com
        TR1  , // tr1.api.riotgames.com
        RU   , // ru.api.riotgames.com
    };
    Q_ENUM(RoutingFlatform)

    void setJSEngine(QJSEngine *engine); // QML 사용시 반드시 설정.

    QNetworkAccessManager *client() const;
    void setClient(QNetworkAccessManager *client);

    QString apiKey() const;
    void setApiKey(const QString &apiKey);

    // CHAMPION-MASTERRY-V4__BEGIN
    Q_INVOKABLE void getChampMasteriesAllBySummonerId(const QString &summonerId, RoutingFlatform routing, const QJSValue &jsCallback);
    void getChampMasteriesAllBySummonerId(const QString &summonerId, RoutingFlatform routing, std::function<
                                          void(const QList<ChampionMasteryDTO> &, int, QString)>callback = nullptr);

    Q_INVOKABLE void getChampMasteriesAllBySummonerId(const QString &summonerId, const QString &championId, RoutingFlatform routing, const QJSValue &jsCallback);
    void getChampMasteryBySummonerId(const QString &summonerId, const QString &championId, RoutingFlatform routing, std::function<
                                     void(const ChampionMasteryDTO &, int, QString)>callback = nullptr);

    Q_INVOKABLE void getChampMasteryScoreBySummonerId(const QString &summonerId, RoutingFlatform routing, const QJSValue &jsCallback);
    void getChampMasteryScoreBySummonerId(const QString &summonerId, RoutingFlatform routing, std::function<
                                          void(int, int, QString)>callback = nullptr);


    // CHAMPION-V3
    Q_INVOKABLE void getChampRotations(RoutingFlatform routing, const QJSValue &jsCallback);
    void getChampRotations(RoutingFlatform routing, std::function<
                           void(const ChampionInfo &, int, QString)>callback = nullptr);


    // CLASH-V1
    void getClashAllPlayersBySummonerId(const QString &summonerId, RoutingFlatform routing, std::function<
                                        void(const QList<PlayerDto> &, int, QString)>callback = nullptr);

    void getClashTeamByTeamId(const QString &teamId, RoutingFlatform routing, std::function<
                              void(const TeamDto &, int, QString)>callback = nullptr);

    void getClashAllTournaments(RoutingFlatform routing, std::function<
                                void(const QList<TournamentDto> &, int, QString)>callback = nullptr);

    void getClashTournamentByTeamId(const QString &teamId, RoutingFlatform routing, std::function<
                                    void(const TournamentDto &, int, QString)>callback = nullptr);

    void getClashTournamentByTournamentId(const QString &tournamentId, RoutingFlatform routing, std::function<
                                          void(const TournamentDto &, int, QString)>callback = nullptr);


    // LEAGUE-V4
    Q_INVOKABLE void getLeagueBySummoner(const QString &summonerId, RoutingFlatform routing, const QJSValue &jsCallback);
    void getLeagueBySummoner(const QString &summonerId, RoutingFlatform routing, std::function<
                             void(const QList<LeagueEntryDTO> &, int, QString)>callback = nullptr);



    // SPECTATOR-V4
    Q_INVOKABLE void getCurrentGameInfo(const QString &summonerId, RoutingFlatform routing, const QJSValue &jsCallback);
    void getCurrentGameInfo(const QString &summonerId, RoutingFlatform routing, std::function<
                            void(const CurrentGameInfo &, int, QString)>callback = nullptr);



    // SUMMONER-V4
    Q_INVOKABLE void getSummonerByName(const QString &summonerName, RoutingFlatform routing, const QJSValue &jsCallback);
    void getSummonerByName(const QString &summonerName, RoutingFlatform routing, std::function<
                            void(const SummonerDTO &, int, QString)>callback = nullptr);





signals:
    void rateLimited(int retryAfterSec);


private:
    QJSEngine *mJSEngine = nullptr;
    QTimer *mRetryAfter;
    void get(const QString &path, const QUrlQuery &qurry, RoutingFlatform routing, std::function<
             void(const QByteArray &, int, const QString &)>callback = nullptr);
    QNetworkAccessManager *mClient = nullptr;
    QString mApiKey;

};
}


#endif // RIOTAPI_H
