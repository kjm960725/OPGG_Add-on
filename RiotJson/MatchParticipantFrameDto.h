// MatchParticipantFrameDto.h
#ifndef MATCHPARTICIPANTFRAMEDTO_H
#define MATCHPARTICIPANTFRAMEDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "MatchPositionDto.h"
#include "JsonObject.h"

namespace riot {
class MatchParticipantFrameDto : public JsonObject
{
public:
	// participantId
	int participantId() const { return this->value("participantId").toInt(); }
	void setParticipantId(int participantId) { this->insert("participantId", participantId); }
	
	// minionsKilled
	int minionsKilled() const { return this->value("minionsKilled").toInt(); }
	void setMinionsKilled(int minionsKilled) { this->insert("minionsKilled", minionsKilled); }
	
	// teamScore
	int teamScore() const { return this->value("teamScore").toInt(); }
	void setTeamScore(int teamScore) { this->insert("teamScore", teamScore); }
	
	// dominionScore
	int dominionScore() const { return this->value("dominionScore").toInt(); }
	void setDominionScore(int dominionScore) { this->insert("dominionScore", dominionScore); }
	
	// totalGold
	int totalGold() const { return this->value("totalGold").toInt(); }
	void setTotalGold(int totalGold) { this->insert("totalGold", totalGold); }
	
	// level
	int level() const { return this->value("level").toInt(); }
	void setLevel(int level) { this->insert("level", level); }
	
	// xp
	int xp() const { return this->value("xp").toInt(); }
	void setXp(int xp) { this->insert("xp", xp); }
	
	// currentGold
	int currentGold() const { return this->value("currentGold").toInt(); }
	void setCurrentGold(int currentGold) { this->insert("currentGold", currentGold); }
	
	// position
	MatchPositionDto position() const { return static_cast<MatchPositionDto&&>(this->value("position").toObject()); }
	void setPosition(const MatchPositionDto &position) { this->insert("position", position); }
	
	// jungleMinionsKilled
	int jungleMinionsKilled() const { return this->value("jungleMinionsKilled").toInt(); }
	void setJungleMinionsKilled(int jungleMinionsKilled) { this->insert("jungleMinionsKilled", jungleMinionsKilled); }
	
};
}

#endif // MATCHPARTICIPANTFRAMEDTO_H
