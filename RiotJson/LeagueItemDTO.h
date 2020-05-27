// LeagueItemDTO.h
#ifndef LEAGUEITEMDTO_H
#define LEAGUEITEMDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "MiniSeriesDTO.h"
#include "JsonObject.h"

namespace riot {
class LeagueItemDTO : public JsonObject
{
public:
	// freshBlood
	bool freshBlood() const { return this->value("freshBlood").toBool(); }
	void setFreshBlood(bool freshBlood) { this->insert("freshBlood", freshBlood); }
	
	// Winning team on Summoners Rift.
	int wins() const { return this->value("wins").toInt(); }
	void setWins(int wins) { this->insert("wins", wins); }
	
	// summonerName
	QString summonerName() const { return this->value("summonerName").toString(); }
	void setSummonerName(const QString &summonerName) { this->insert("summonerName", summonerName); }
	
	// miniSeries
	MiniSeriesDTO miniSeries() const { return static_cast<MiniSeriesDTO&&>(this->value("miniSeries").toObject()); }
	void setMiniSeries(const MiniSeriesDTO &miniSeries) { this->insert("miniSeries", miniSeries); }
	
	// inactive
	bool inactive() const { return this->value("inactive").toBool(); }
	void setInactive(bool inactive) { this->insert("inactive", inactive); }
	
	// veteran
	bool veteran() const { return this->value("veteran").toBool(); }
	void setVeteran(bool veteran) { this->insert("veteran", veteran); }
	
	// hotStreak
	bool hotStreak() const { return this->value("hotStreak").toBool(); }
	void setHotStreak(bool hotStreak) { this->insert("hotStreak", hotStreak); }
	
	// rank
	QString rank() const { return this->value("rank").toString(); }
	void setRank(const QString &rank) { this->insert("rank", rank); }
	
	// leaguePoints
	int leaguePoints() const { return this->value("leaguePoints").toInt(); }
	void setLeaguePoints(int leaguePoints) { this->insert("leaguePoints", leaguePoints); }
	
	// Losing team on Summoners Rift.
	int losses() const { return this->value("losses").toInt(); }
	void setLosses(int losses) { this->insert("losses", losses); }
	
	// Player's encrypted summonerId.
	QString summonerId() const { return this->value("summonerId").toString(); }
	void setSummonerId(const QString &summonerId) { this->insert("summonerId", summonerId); }
	
};
}

#endif // LEAGUEITEMDTO_H
