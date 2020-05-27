// LeagueEntryDTO.h
#ifndef LEAGUEENTRYDTO_H
#define LEAGUEENTRYDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "MiniSeriesDTO.h"
#include "JsonObject.h"

namespace riot {
class LeagueEntryDTO : public JsonObject
{
public:
	// leagueId
	QString leagueId() const { return this->value("leagueId").toString(); }
	void setLeagueId(const QString &leagueId) { this->insert("leagueId", leagueId); }
	
	// Player's summonerId (Encrypted)
	QString summonerId() const { return this->value("summonerId").toString(); }
	void setSummonerId(const QString &summonerId) { this->insert("summonerId", summonerId); }
	
	// summonerName
	QString summonerName() const { return this->value("summonerName").toString(); }
	void setSummonerName(const QString &summonerName) { this->insert("summonerName", summonerName); }
	
	// queueType
	QString queueType() const { return this->value("queueType").toString(); }
	void setQueueType(const QString &queueType) { this->insert("queueType", queueType); }
	
	// tier
	QString tier() const { return this->value("tier").toString(); }
	void setTier(const QString &tier) { this->insert("tier", tier); }
	
	// rank
	QString rank() const { return this->value("rank").toString(); }
	void setRank(const QString &rank) { this->insert("rank", rank); }
	
	// leaguePoints
	int leaguePoints() const { return this->value("leaguePoints").toInt(); }
	void setLeaguePoints(int leaguePoints) { this->insert("leaguePoints", leaguePoints); }
	
	// Winning team on Summoners Rift. First placement in Teamfight Tactics.
	int wins() const { return this->value("wins").toInt(); }
	void setWins(int wins) { this->insert("wins", wins); }
	
	// Losing team on Summoners Rift. Second through eighth placement in Teamfight Tactics.
	int losses() const { return this->value("losses").toInt(); }
	void setLosses(int losses) { this->insert("losses", losses); }
	
	// hotStreak
	bool hotStreak() const { return this->value("hotStreak").toBool(); }
	void setHotStreak(bool hotStreak) { this->insert("hotStreak", hotStreak); }
	
	// veteran
	bool veteran() const { return this->value("veteran").toBool(); }
	void setVeteran(bool veteran) { this->insert("veteran", veteran); }
	
	// freshBlood
	bool freshBlood() const { return this->value("freshBlood").toBool(); }
	void setFreshBlood(bool freshBlood) { this->insert("freshBlood", freshBlood); }
	
	// inactive
	bool inactive() const { return this->value("inactive").toBool(); }
	void setInactive(bool inactive) { this->insert("inactive", inactive); }
	
	// miniSeries
	MiniSeriesDTO miniSeries() const { return static_cast<MiniSeriesDTO&&>(this->value("miniSeries").toObject()); }
	void setMiniSeries(const MiniSeriesDTO &miniSeries) { this->insert("miniSeries", miniSeries); }
	
};
}

#endif // LEAGUEENTRYDTO_H
