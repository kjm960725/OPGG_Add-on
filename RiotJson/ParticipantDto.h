// -------------------- ParticipantDto --------------------
#ifndef PARTICIPANTDTO_H
#define PARTICIPANTDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "RuneDto.h"
#include "ParticipantStatsDto.h"
#include "ParticipantTimelineDto.h"
#include "MasteryDto.h"
#include "JsonObject.h"

namespace riot {
class ParticipantDto : public JsonObject
{
public:
    // participantId
    int participantId() const { return this->value("participantId").toInt(); }
    void setParticipantId(int participantId) { this->insert("participantId", participantId); }

    // championId
    int championId() const { return this->value("championId").toInt(); }
    void setChampionId(int championId) { this->insert("championId", championId); }

    // List of legacy Rune information. Not included for matches played with Runes Reforged.
    QList<RuneDto> runes() const {
        QList<RuneDto> result;
        auto arr = this->value("runes").toArray();
        for (auto val : arr) result.append(static_cast<RuneDto&&>(val.toObject()));
        return result;
    }
    void setRunes(const QList<RuneDto> &runes) {
        QJsonArray arr;
        for (auto v : runes) arr.append(v);
        this->insert("runes",arr);
    }

    // Participant statistics.
    ParticipantStatsDto stats() const { return static_cast<ParticipantStatsDto&&>(this->value("stats").toObject()); }
    void setStats(const ParticipantStatsDto &stats) { this->insert("stats", stats); }

    // 100 for blue side. 200 for red side.
    int teamId() const { return this->value("teamId").toInt(); }
    void setTeamId(int teamId) { this->insert("teamId", teamId); }

    // Participant timeline data.
    ParticipantTimelineDto timeline() const { return static_cast<ParticipantTimelineDto&&>(this->value("timeline").toObject()); }
    void setTimeline(const ParticipantTimelineDto &timeline) { this->insert("timeline", timeline); }

    // First Summoner Spell id.
    int spell1Id() const { return this->value("spell1Id").toInt(); }
    void setSpell1Id(int spell1Id) { this->insert("spell1Id", spell1Id); }

    // Second Summoner Spell id.
    int spell2Id() const { return this->value("spell2Id").toInt(); }
    void setSpell2Id(int spell2Id) { this->insert("spell2Id", spell2Id); }

    // Highest ranked tier achieved for the previous season in a specific subset of queueIds, if any, otherwise null. Used to display border in game loading screen. Please refer to the Ranked Info documentation. (Legal values: CHALLENGER, MASTER, DIAMOND, PLATINUM, GOLD, SILVER, BRONZE, UNRANKED)
    QString highestAchievedSeasonTier() const { return this->value("highestAchievedSeasonTier").toString(); }
    void setHighestAchievedSeasonTier(const QString &highestAchievedSeasonTier) { this->insert("highestAchievedSeasonTier", highestAchievedSeasonTier); }

    // List of legacy Mastery information. Not included for matches played with Runes Reforged.
    QList<MasteryDto> masteries() const {
        QList<MasteryDto> result;
        auto arr = this->value("masteries").toArray();
        for (auto val : arr) result.append(static_cast<MasteryDto&&>(val.toObject()));
        return result;
    }
    void setMasteries(const QList<MasteryDto> &masteries) {
        QJsonArray arr;
        for (auto v : masteries) arr.append(v);
        this->insert("masteries",arr);
    }

};
}

#endif // PARTICIPANTDTO_H
