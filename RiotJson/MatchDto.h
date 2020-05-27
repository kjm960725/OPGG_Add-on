
// -------------------- MatchDto --------------------
#ifndef MATCHDTO_H
#define MATCHDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "ParticipantIdentityDto.h"
#include "TeamStatsDto.h"
#include "ParticipantDto.h"
#include "JsonObject.h"

namespace riot {
class MatchDto : public JsonObject
{
public:
    // gameId
    long gameId() const { return long(this->value("gameId").toVariant().toLongLong()); }
    void setGameId(long gameId) { this->insert("gameId", qlonglong(gameId)); }

    // Participant identity information.
    QList<ParticipantIdentityDto> participantIdentities() const {
        QList<ParticipantIdentityDto> result;
        auto arr = this->value("participantIdentities").toArray();
        for (auto val : arr) result.append(static_cast<ParticipantIdentityDto&&>(val.toObject()));
        return result;
    }
    void setParticipantIdentities(const QList<ParticipantIdentityDto> &participantIdentities) {
        QJsonArray arr;
        for (auto v : participantIdentities) arr.append(v);
        this->insert("participantIdentities",arr);
    }

    // Please refer to the Game Constants documentation.
    int queueId() const { return this->value("queueId").toInt(); }
    void setQueueId(int queueId) { this->insert("queueId", queueId); }

    // Please refer to the Game Constants documentation.
    QString gameType() const { return this->value("gameType").toString(); }
    void setGameType(const QString &gameType) { this->insert("gameType", gameType); }

    // Match duration in seconds.
    long gameDuration() const { return long(this->value("gameDuration").toVariant().toLongLong()); }
    void setGameDuration(long gameDuration) { this->insert("gameDuration", qlonglong(gameDuration)); }

    // Team information.
    QList<TeamStatsDto> teams() const {
        QList<TeamStatsDto> result;
        auto arr = this->value("teams").toArray();
        for (auto val : arr) result.append(static_cast<TeamStatsDto&&>(val.toObject()));
        return result;
    }
    void setTeams(const QList<TeamStatsDto> &teams) {
        QJsonArray arr;
        for (auto v : teams) arr.append(v);
        this->insert("teams",arr);
    }

    // Platform where the match was played.
    QString platformId() const { return this->value("platformId").toString(); }
    void setPlatformId(const QString &platformId) { this->insert("platformId", platformId); }

    // Designates the timestamp when champion select ended and the loading screen appeared, NOT when the game timer was at 0:00.
    long gameCreation() const { return long(this->value("gameCreation").toVariant().toLongLong()); }
    void setGameCreation(long gameCreation) { this->insert("gameCreation", qlonglong(gameCreation)); }

    // Please refer to the Game Constants documentation.
    int seasonId() const { return this->value("seasonId").toInt(); }
    void setSeasonId(int seasonId) { this->insert("seasonId", seasonId); }

    // The major.minor version typically indicates the patch the match was played on.
    QString gameVersion() const { return this->value("gameVersion").toString(); }
    void setGameVersion(const QString &gameVersion) { this->insert("gameVersion", gameVersion); }

    // Please refer to the Game Constants documentation.
    int mapId() const { return this->value("mapId").toInt(); }
    void setMapId(int mapId) { this->insert("mapId", mapId); }

    // Please refer to the Game Constants documentation.
    QString gameMode() const { return this->value("gameMode").toString(); }
    void setGameMode(const QString &gameMode) { this->insert("gameMode", gameMode); }

    // Participant information.
    QList<ParticipantDto> participants() const {
        QList<ParticipantDto> result;
        auto arr = this->value("participants").toArray();
        for (auto val : arr) result.append(static_cast<ParticipantDto&&>(val.toObject()));
        return result;
    }
    void setParticipants(const QList<ParticipantDto> &participants) {
        QJsonArray arr;
        for (auto v : participants) arr.append(v);
        this->insert("participants",arr);
    }

};
}

#endif // MATCHDTO_H
