// LobbyEventDTO.h
#ifndef LOBBYEVENTDTO_H
#define LOBBYEVENTDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class LobbyEventDTO : public JsonObject
{
public:
	// Timestamp from the event
	QString timestamp() const { return this->value("timestamp").toString(); }
	void setTimestamp(const QString &timestamp) { this->insert("timestamp", timestamp); }
	
	// The type of event that was triggered
	QString eventType() const { return this->value("eventType").toString(); }
	void setEventType(const QString &eventType) { this->insert("eventType", eventType); }
	
	// The summonerId that triggered the event (Encrypted)
	QString summonerId() const { return this->value("summonerId").toString(); }
	void setSummonerId(const QString &summonerId) { this->insert("summonerId", summonerId); }
	
};
}

#endif // LOBBYEVENTDTO_H
