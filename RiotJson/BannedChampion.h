// BannedChampion.h
#ifndef BANNEDCHAMPION_H
#define BANNEDCHAMPION_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class BannedChampion : public JsonObject
{
public:
	// The turn during which the champion was banned
	int pickTurn() const { return this->value("pickTurn").toInt(); }
	void setPickTurn(int pickTurn) { this->insert("pickTurn", pickTurn); }
	
	// The ID of the banned champion
	long championId() const { return long(this->value("championId").toVariant().toLongLong()); }
	void setChampionId(long championId) { this->insert("championId", qlonglong(championId)); }
	
	// The ID of the team that banned the champion
	long teamId() const { return long(this->value("teamId").toVariant().toLongLong()); }
	void setTeamId(long teamId) { this->insert("teamId", qlonglong(teamId)); }
	
};
}

#endif // BANNEDCHAMPION_H
