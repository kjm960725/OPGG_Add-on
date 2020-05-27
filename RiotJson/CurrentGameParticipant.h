// CurrentGameParticipant.h
#ifndef CURRENTGAMEPARTICIPANT_H
#define CURRENTGAMEPARTICIPANT_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "Perks.h"
#include "GameCustomizationObject.h"
#include "JsonObject.h"

namespace riot {
class CurrentGameParticipant : public JsonObject
{
public:
	// The ID of the champion played by this participant
	long championId() const { return long(this->value("championId").toVariant().toLongLong()); }
	void setChampionId(long championId) { this->insert("championId", qlonglong(championId)); }
	
	// Perks/Runes Reforged Information
	Perks perks() const { return static_cast<Perks&&>(this->value("perks").toObject()); }
	void setPerks(const Perks &perks) { this->insert("perks", perks); }
	
	// The ID of the profile icon used by this participant
	long profileIconId() const { return long(this->value("profileIconId").toVariant().toLongLong()); }
	void setProfileIconId(long profileIconId) { this->insert("profileIconId", qlonglong(profileIconId)); }
	
	// Flag indicating whether or not this participant is a bot
	bool bot() const { return this->value("bot").toBool(); }
	void setBot(bool bot) { this->insert("bot", bot); }
	
	// The team ID of this participant, indicating the participant's team
	long teamId() const { return long(this->value("teamId").toVariant().toLongLong()); }
	void setTeamId(long teamId) { this->insert("teamId", qlonglong(teamId)); }
	
	// The summoner name of this participant
	QString summonerName() const { return this->value("summonerName").toString(); }
	void setSummonerName(const QString &summonerName) { this->insert("summonerName", summonerName); }
	
	// The encrypted summoner ID of this participant
	QString summonerId() const { return this->value("summonerId").toString(); }
	void setSummonerId(const QString &summonerId) { this->insert("summonerId", summonerId); }
	
	// The ID of the first summoner spell used by this participant
	long spell1Id() const { return long(this->value("spell1Id").toVariant().toLongLong()); }
	void setSpell1Id(long spell1Id) { this->insert("spell1Id", qlonglong(spell1Id)); }
	
	// The ID of the second summoner spell used by this participant
	long spell2Id() const { return long(this->value("spell2Id").toVariant().toLongLong()); }
	void setSpell2Id(long spell2Id) { this->insert("spell2Id", qlonglong(spell2Id)); }
	
	// List of Game Customizations
	QList<GameCustomizationObject> gameCustomizationObjects() const {
		QList<GameCustomizationObject> result;
		auto arr = this->value("gameCustomizationObjects").toArray();
		for (auto val : arr) result.append(static_cast<GameCustomizationObject&&>(val.toObject()));
		return result;
	}
	void setGameCustomizationObjects(const QList<GameCustomizationObject> &gameCustomizationObjects) {
		QJsonArray arr;
		for (auto v : gameCustomizationObjects) arr.append(v);
		this->insert("gameCustomizationObjects",arr);
	}
	
};
}

#endif // CURRENTGAMEPARTICIPANT_H
