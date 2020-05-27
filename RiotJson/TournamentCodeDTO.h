// TournamentCodeDTO.h
#ifndef TOURNAMENTCODEDTO_H
#define TOURNAMENTCODEDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include <QSet>
#include "JsonObject.h"

namespace riot {
class TournamentCodeDTO : public JsonObject
{
public:
	// The tournament code.
	QString code() const { return this->value("code").toString(); }
	void setCode(const QString &code) { this->insert("code", code); }
	
	// The spectator mode for the tournament code game.
	QString spectators() const { return this->value("spectators").toString(); }
	void setSpectators(const QString &spectators) { this->insert("spectators", spectators); }
	
	// The lobby name for the tournament code game.
	QString lobbyName() const { return this->value("lobbyName").toString(); }
	void setLobbyName(const QString &lobbyName) { this->insert("lobbyName", lobbyName); }
	
	// The metadata for tournament code.
	QString metaData() const { return this->value("metaData").toString(); }
	void setMetaData(const QString &metaData) { this->insert("metaData", metaData); }
	
	// The password for the tournament code game.
	QString password() const { return this->value("password").toString(); }
	void setPassword(const QString &password) { this->insert("password", password); }
	
	// The team size for the tournament code game.
	int teamSize() const { return this->value("teamSize").toInt(); }
	void setTeamSize(int teamSize) { this->insert("teamSize", teamSize); }
	
	// The provider's ID.
	int providerId() const { return this->value("providerId").toInt(); }
	void setProviderId(int providerId) { this->insert("providerId", providerId); }
	
	// The pick mode for tournament code game.
	QString pickType() const { return this->value("pickType").toString(); }
	void setPickType(const QString &pickType) { this->insert("pickType", pickType); }
	
	// The tournament's ID.
	int tournamentId() const { return this->value("tournamentId").toInt(); }
	void setTournamentId(int tournamentId) { this->insert("tournamentId", tournamentId); }
	
	// The tournament code's ID.
	int id() const { return this->value("id").toInt(); }
	void setId(int id) { this->insert("id", id); }
	
	// The tournament code's region. (Legal values: BR, EUNE, EUW, JP, LAN, LAS, NA, OCE, PBE, RU, TR)
	QString region() const { return this->value("region").toString(); }
	void setRegion(const QString &region) { this->insert("region", region); }
	
	// The game map for the tournament code game
	QString map() const { return this->value("map").toString(); }
	void setMap(const QString &map) { this->insert("map", map); }
	
	// The summonerIds of the participants (Encrypted)
    QSet<QString> participants() const {
        QSet<QString> result;
        auto arr = this->value("participants").toArray();
        for (auto val : arr) result.insert(val.toString());
        return result;
    }
    void setParticipants(const QSet<QString> &participants) {
        QJsonArray arr;
        for (auto val : participants) arr.append(val);
        this->insert("participants", arr);
    }
	
};
}

#endif // TOURNAMENTCODEDTO_H
