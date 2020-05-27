// CurrentGameInfo.h
#ifndef CURRENTGAMEINFO_H
#define CURRENTGAMEINFO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "BannedChampion.h"
#include "Observer.h"
#include "CurrentGameParticipant.h"
#include "JsonObject.h"

namespace riot {
class CurrentGameInfo : public JsonObject
{
public:
	// The ID of the game
	long gameId() const { return long(this->value("gameId").toVariant().toLongLong()); }
	void setGameId(long gameId) { this->insert("gameId", qlonglong(gameId)); }
	
	// The game type
	QString gameType() const { return this->value("gameType").toString(); }
	void setGameType(const QString &gameType) { this->insert("gameType", gameType); }
	
	// The game start time represented in epoch milliseconds
	long gameStartTime() const { return long(this->value("gameStartTime").toVariant().toLongLong()); }
	void setGameStartTime(long gameStartTime) { this->insert("gameStartTime", qlonglong(gameStartTime)); }
	
	// The ID of the map
	long mapId() const { return long(this->value("mapId").toVariant().toLongLong()); }
	void setMapId(long mapId) { this->insert("mapId", qlonglong(mapId)); }
	
	// The amount of time in seconds that has passed since the game started
	long gameLength() const { return long(this->value("gameLength").toVariant().toLongLong()); }
	void setGameLength(long gameLength) { this->insert("gameLength", qlonglong(gameLength)); }
	
	// The ID of the platform on which the game is being played
	QString platformId() const { return this->value("platformId").toString(); }
	void setPlatformId(const QString &platformId) { this->insert("platformId", platformId); }
	
	// The game mode
	QString gameMode() const { return this->value("gameMode").toString(); }
	void setGameMode(const QString &gameMode) { this->insert("gameMode", gameMode); }
	
	// Banned champion information
	QList<BannedChampion> bannedChampions() const {
		QList<BannedChampion> result;
		auto arr = this->value("bannedChampions").toArray();
		for (auto val : arr) result.append(static_cast<BannedChampion&&>(val.toObject()));
		return result;
	}
	void setBannedChampions(const QList<BannedChampion> &bannedChampions) {
		QJsonArray arr;
		for (auto v : bannedChampions) arr.append(v);
		this->insert("bannedChampions",arr);
	}
	
	// The queue type (queue types are documented on the Game Constants page)
	long gameQueueConfigId() const { return long(this->value("gameQueueConfigId").toVariant().toLongLong()); }
	void setGameQueueConfigId(long gameQueueConfigId) { this->insert("gameQueueConfigId", qlonglong(gameQueueConfigId)); }
	
	// The observer information
	Observer observers() const { return static_cast<Observer&&>(this->value("observers").toObject()); }
	void setObservers(const Observer &observers) { this->insert("observers", observers); }
	
	// The participant information
	QList<CurrentGameParticipant> participants() const {
		QList<CurrentGameParticipant> result;
		auto arr = this->value("participants").toArray();
		for (auto val : arr) result.append(static_cast<CurrentGameParticipant&&>(val.toObject()));
		return result;
	}
	void setParticipants(const QList<CurrentGameParticipant> &participants) {
		QJsonArray arr;
		for (auto v : participants) arr.append(v);
		this->insert("participants",arr);
	}
	
};
}

#endif // CURRENTGAMEINFO_H
