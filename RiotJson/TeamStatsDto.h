// -------------------- TeamStatsDto --------------------
#ifndef TEAMSTATSDTO_H
#define TEAMSTATSDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "TeamBansDto.h"
#include "JsonObject.h"

namespace riot {
class TeamStatsDto : public JsonObject
{
public:
    // Number of towers the team destroyed.
    int towerKills() const { return this->value("towerKills").toInt(); }
    void setTowerKills(int towerKills) { this->insert("towerKills", towerKills); }

    // Number of times the team killed Rift Herald.
    int riftHeraldKills() const { return this->value("riftHeraldKills").toInt(); }
    void setRiftHeraldKills(int riftHeraldKills) { this->insert("riftHeraldKills", riftHeraldKills); }

    // Flag indicating whether or not the team scored the first blood.
    bool firstBlood() const { return this->value("firstBlood").toBool(); }
    void setFirstBlood(bool firstBlood) { this->insert("firstBlood", firstBlood); }

    // Number of inhibitors the team destroyed.
    int inhibitorKills() const { return this->value("inhibitorKills").toInt(); }
    void setInhibitorKills(int inhibitorKills) { this->insert("inhibitorKills", inhibitorKills); }

    // If match queueId has a draft, contains banned champion data, otherwise empty.
    QList<TeamBansDto> bans() const {
        QList<TeamBansDto> result;
        auto arr = this->value("bans").toArray();
        for (auto val : arr) result.append(static_cast<TeamBansDto&&>(val.toObject()));
        return result;
    }
    void setBans(const QList<TeamBansDto> &bans) {
        QJsonArray arr;
        for (auto v : bans) arr.append(v);
        this->insert("bans",arr);
    }

    // Flag indicating whether or not the team scored the first Baron kill.
    bool firstBaron() const { return this->value("firstBaron").toBool(); }
    void setFirstBaron(bool firstBaron) { this->insert("firstBaron", firstBaron); }

    // Flag indicating whether or not the team scored the first Dragon kill.
    bool firstDragon() const { return this->value("firstDragon").toBool(); }
    void setFirstDragon(bool firstDragon) { this->insert("firstDragon", firstDragon); }

    // For Dominion matches, specifies the points the team had at game end.
    int dominionVictoryScore() const { return this->value("dominionVictoryScore").toInt(); }
    void setDominionVictoryScore(int dominionVictoryScore) { this->insert("dominionVictoryScore", dominionVictoryScore); }

    // Number of times the team killed Dragon.
    int dragonKills() const { return this->value("dragonKills").toInt(); }
    void setDragonKills(int dragonKills) { this->insert("dragonKills", dragonKills); }

    // Number of times the team killed Baron.
    int baronKills() const { return this->value("baronKills").toInt(); }
    void setBaronKills(int baronKills) { this->insert("baronKills", baronKills); }

    // Flag indicating whether or not the team destroyed the first inhibitor.
    bool firstInhibitor() const { return this->value("firstInhibitor").toBool(); }
    void setFirstInhibitor(bool firstInhibitor) { this->insert("firstInhibitor", firstInhibitor); }

    // Flag indicating whether or not the team destroyed the first tower.
    bool firstTower() const { return this->value("firstTower").toBool(); }
    void setFirstTower(bool firstTower) { this->insert("firstTower", firstTower); }

    // Number of times the team killed Vilemaw.
    int vilemawKills() const { return this->value("vilemawKills").toInt(); }
    void setVilemawKills(int vilemawKills) { this->insert("vilemawKills", vilemawKills); }

    // Flag indicating whether or not the team scored the first Rift Herald kill.
    bool firstRiftHerald() const { return this->value("firstRiftHerald").toBool(); }
    void setFirstRiftHerald(bool firstRiftHerald) { this->insert("firstRiftHerald", firstRiftHerald); }

    // 100 for blue side. 200 for red side.
    int teamId() const { return this->value("teamId").toInt(); }
    void setTeamId(int teamId) { this->insert("teamId", teamId); }

    // String indicating whether or not the team won. There are only two values visibile in public match history. (Legal values: Fail, Win)
    QString win() const { return this->value("win").toString(); }
    void setWin(const QString &win) { this->insert("win", win); }

};
}

#endif // TEAMSTATSDTO_H
