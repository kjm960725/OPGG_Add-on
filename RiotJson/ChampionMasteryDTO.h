// ChampionMasteryDTO.h
#ifndef CHAMPIONMASTERYDTO_H
#define CHAMPIONMASTERYDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class ChampionMasteryDTO : public JsonObject
{
public:
	// Number of points needed to achieve next level. Zero if player reached maximum champion level for this champion.
	long championPointsUntilNextLevel() const { return long(this->value("championPointsUntilNextLevel").toVariant().toLongLong()); }
	void setChampionPointsUntilNextLevel(long championPointsUntilNextLevel) { this->insert("championPointsUntilNextLevel", qlonglong(championPointsUntilNextLevel)); }
	
	// Is chest granted for this champion or not in current season.
	bool chestGranted() const { return this->value("chestGranted").toBool(); }
	void setChestGranted(bool chestGranted) { this->insert("chestGranted", chestGranted); }
	
	// Champion ID for this entry.
	long championId() const { return long(this->value("championId").toVariant().toLongLong()); }
	void setChampionId(long championId) { this->insert("championId", qlonglong(championId)); }
	
	// Last time this champion was played by this player - in Unix milliseconds time format.
	long lastPlayTime() const { return long(this->value("lastPlayTime").toVariant().toLongLong()); }
	void setLastPlayTime(long lastPlayTime) { this->insert("lastPlayTime", qlonglong(lastPlayTime)); }
	
	// Champion level for specified player and champion combination.
	int championLevel() const { return this->value("championLevel").toInt(); }
	void setChampionLevel(int championLevel) { this->insert("championLevel", championLevel); }
	
	// Summoner ID for this entry. (Encrypted)
	QString summonerId() const { return this->value("summonerId").toString(); }
	void setSummonerId(const QString &summonerId) { this->insert("summonerId", summonerId); }
	
	// Total number of champion points for this player and champion combination - they are used to determine championLevel.
	int championPoints() const { return this->value("championPoints").toInt(); }
	void setChampionPoints(int championPoints) { this->insert("championPoints", championPoints); }
	
	// Number of points earned since current level has been achieved.
	long championPointsSinceLastLevel() const { return long(this->value("championPointsSinceLastLevel").toVariant().toLongLong()); }
	void setChampionPointsSinceLastLevel(long championPointsSinceLastLevel) { this->insert("championPointsSinceLastLevel", qlonglong(championPointsSinceLastLevel)); }
	
	// The token earned for this champion to levelup.
	int tokensEarned() const { return this->value("tokensEarned").toInt(); }
	void setTokensEarned(int tokensEarned) { this->insert("tokensEarned", tokensEarned); }
	
};
}

#endif // CHAMPIONMASTERYDTO - THIS OBJECT CONTAINS SINGLE CHAMPION MASTERY INFORMATION FOR PLAYER AND CHAMPION COMBINATION._H
