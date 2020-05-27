// MatchEventDto.h
#ifndef MATCHEVENTDTO_H
#define MATCHEVENTDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "MatchPositionDto.h"
#include "JsonObject.h"

namespace riot {
class MatchEventDto : public JsonObject
{
public:
	// laneType
	QString laneType() const { return this->value("laneType").toString(); }
	void setLaneType(const QString &laneType) { this->insert("laneType", laneType); }
	
	// skillSlot
	int skillSlot() const { return this->value("skillSlot").toInt(); }
	void setSkillSlot(int skillSlot) { this->insert("skillSlot", skillSlot); }
	
	// ascendedType
	QString ascendedType() const { return this->value("ascendedType").toString(); }
	void setAscendedType(const QString &ascendedType) { this->insert("ascendedType", ascendedType); }
	
	// creatorId
	int creatorId() const { return this->value("creatorId").toInt(); }
	void setCreatorId(int creatorId) { this->insert("creatorId", creatorId); }
	
	// afterId
	int afterId() const { return this->value("afterId").toInt(); }
	void setAfterId(int afterId) { this->insert("afterId", afterId); }
	
	// eventType
	QString eventType() const { return this->value("eventType").toString(); }
	void setEventType(const QString &eventType) { this->insert("eventType", eventType); }
	
	// (Legal values: CHAMPION_KILL, WARD_PLACED, WARD_KILL, BUILDING_KILL, ELITE_MONSTER_KILL, ITEM_PURCHASED, ITEM_SOLD, ITEM_DESTROYED, ITEM_UNDO, SKILL_LEVEL_UP, ASCENDED_EVENT, CAPTURE_POINT, PORO_KING_SUMMON)
	QString type() const { return this->value("type").toString(); }
	void setType(const QString &type) { this->insert("type", type); }
	
	// levelUpType
	QString levelUpType() const { return this->value("levelUpType").toString(); }
	void setLevelUpType(const QString &levelUpType) { this->insert("levelUpType", levelUpType); }
	
	// wardType
	QString wardType() const { return this->value("wardType").toString(); }
	void setWardType(const QString &wardType) { this->insert("wardType", wardType); }
	
	// participantId
	int participantId() const { return this->value("participantId").toInt(); }
	void setParticipantId(int participantId) { this->insert("participantId", participantId); }
	
	// towerType
	QString towerType() const { return this->value("towerType").toString(); }
	void setTowerType(const QString &towerType) { this->insert("towerType", towerType); }
	
	// itemId
	int itemId() const { return this->value("itemId").toInt(); }
	void setItemId(int itemId) { this->insert("itemId", itemId); }
	
	// beforeId
	int beforeId() const { return this->value("beforeId").toInt(); }
	void setBeforeId(int beforeId) { this->insert("beforeId", beforeId); }
	
	// pointCaptured
	QString pointCaptured() const { return this->value("pointCaptured").toString(); }
	void setPointCaptured(const QString &pointCaptured) { this->insert("pointCaptured", pointCaptured); }
	
	// monsterType
	QString monsterType() const { return this->value("monsterType").toString(); }
	void setMonsterType(const QString &monsterType) { this->insert("monsterType", monsterType); }
	
	// monsterSubType
	QString monsterSubType() const { return this->value("monsterSubType").toString(); }
	void setMonsterSubType(const QString &monsterSubType) { this->insert("monsterSubType", monsterSubType); }
	
	// teamId
	int teamId() const { return this->value("teamId").toInt(); }
	void setTeamId(int teamId) { this->insert("teamId", teamId); }
	
	// position
	MatchPositionDto position() const { return static_cast<MatchPositionDto&&>(this->value("position").toObject()); }
	void setPosition(const MatchPositionDto &position) { this->insert("position", position); }
	
	// killerId
	int killerId() const { return this->value("killerId").toInt(); }
	void setKillerId(int killerId) { this->insert("killerId", killerId); }
	
	// timestamp
	long timestamp() const { return long(this->value("timestamp").toVariant().toLongLong()); }
	void setTimestamp(long timestamp) { this->insert("timestamp", qlonglong(timestamp)); }
	
	// assistingParticipantIds
	QList<int> assistingParticipantIds() const {
		QList<int> result;
		auto arr = this->value("assistingParticipantIds").toArray();
		for (auto val : arr) result.append(val.toInt());
		return result;
	}
	void setAssistingParticipantIds(const QList<int> &assistingParticipantIds) {
		QJsonArray arr;
		for (auto v : assistingParticipantIds) arr.append(v);
		this->insert("assistingParticipantIds",arr);
	}
	
	// buildingType
	QString buildingType() const { return this->value("buildingType").toString(); }
	void setBuildingType(const QString &buildingType) { this->insert("buildingType", buildingType); }
	
	// victimId
	int victimId() const { return this->value("victimId").toInt(); }
	void setVictimId(int victimId) { this->insert("victimId", victimId); }
	
};
}

#endif // MATCHEVENTDTO_H
