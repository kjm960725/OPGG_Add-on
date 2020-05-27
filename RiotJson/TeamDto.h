// TeamDto.h
#ifndef TEAMDTO_H
#define TEAMDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "PlayerDto.h"
#include "JsonObject.h"

namespace riot {
class TeamDto : public JsonObject
{
public:
	// id
	QString id() const { return this->value("id").toString(); }
	void setId(const QString &id) { this->insert("id", id); }
	
	// tournamentId
	int tournamentId() const { return this->value("tournamentId").toInt(); }
	void setTournamentId(int tournamentId) { this->insert("tournamentId", tournamentId); }
	
	// name
	QString name() const { return this->value("name").toString(); }
	void setName(const QString &name) { this->insert("name", name); }
	
	// iconId
	int iconId() const { return this->value("iconId").toInt(); }
	void setIconId(int iconId) { this->insert("iconId", iconId); }
	
	// tier
	int tier() const { return this->value("tier").toInt(); }
	void setTier(int tier) { this->insert("tier", tier); }
	
	// Summoner ID of the team captain.
	QString captain() const { return this->value("captain").toString(); }
	void setCaptain(const QString &captain) { this->insert("captain", captain); }
	
	// abbreviation
	QString abbreviation() const { return this->value("abbreviation").toString(); }
	void setAbbreviation(const QString &abbreviation) { this->insert("abbreviation", abbreviation); }
	
	// Team members.
	QList<PlayerDto> players() const {
		QList<PlayerDto> result;
		auto arr = this->value("players").toArray();
		for (auto val : arr) result.append(static_cast<PlayerDto&&>(val.toObject()));
		return result;
	}
	void setPlayers(const QList<PlayerDto> &players) {
		QJsonArray arr;
		for (auto v : players) arr.append(v);
		this->insert("players",arr);
	}
	
};
}

#endif // TEAMDTO_H
