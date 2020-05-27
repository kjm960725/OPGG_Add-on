// TournamentPhaseDto.h
#ifndef TOURNAMENTPHASEDTO_H
#define TOURNAMENTPHASEDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class TournamentPhaseDto : public JsonObject
{
public:
	// id
	int id() const { return this->value("id").toInt(); }
	void setId(int id) { this->insert("id", id); }
	
	// registrationTime
	long registrationTime() const { return long(this->value("registrationTime").toVariant().toLongLong()); }
	void setRegistrationTime(long registrationTime) { this->insert("registrationTime", qlonglong(registrationTime)); }
	
	// startTime
	long startTime() const { return long(this->value("startTime").toVariant().toLongLong()); }
	void setStartTime(long startTime) { this->insert("startTime", qlonglong(startTime)); }
	
	// cancelled
	bool cancelled() const { return this->value("cancelled").toBool(); }
	void setCancelled(bool cancelled) { this->insert("cancelled", cancelled); }
	
};
}

#endif // TOURNAMENTPHASEDTO_H
