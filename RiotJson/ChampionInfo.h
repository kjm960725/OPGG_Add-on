// ChampionInfo.h
#ifndef CHAMPIONINFO_H
#define CHAMPIONINFO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class ChampionInfo : public JsonObject
{
public:
	// maxNewPlayerLevel
	int maxNewPlayerLevel() const { return this->value("maxNewPlayerLevel").toInt(); }
	void setMaxNewPlayerLevel(int maxNewPlayerLevel) { this->insert("maxNewPlayerLevel", maxNewPlayerLevel); }
	
	// freeChampionIdsForNewPlayers
	QList<int> freeChampionIdsForNewPlayers() const {
		QList<int> result;
		auto arr = this->value("freeChampionIdsForNewPlayers").toArray();
		for (auto val : arr) result.append(val.toInt());
		return result;
	}
	void setFreeChampionIdsForNewPlayers(const QList<int> &freeChampionIdsForNewPlayers) {
		QJsonArray arr;
		for (auto v : freeChampionIdsForNewPlayers) arr.append(v);
		this->insert("freeChampionIdsForNewPlayers",arr);
	}
	
	// freeChampionIds
	QList<int> freeChampionIds() const {
		QList<int> result;
		auto arr = this->value("freeChampionIds").toArray();
		for (auto val : arr) result.append(val.toInt());
		return result;
	}
	void setFreeChampionIds(const QList<int> &freeChampionIds) {
		QJsonArray arr;
		for (auto v : freeChampionIds) arr.append(v);
		this->insert("freeChampionIds",arr);
	}
	
};
}

#endif // CHAMPIONINFO_H
