// LeaderboardDto.h
#ifndef LEADERBOARDDTO_H
#define LEADERBOARDDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "PlayerDto.h"
#include "JsonObject.h"

namespace riot {
class LeaderboardDto : public JsonObject
{
public:
	// A list of players in Master tier.
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

#endif // LEADERBOARDDTO_H
