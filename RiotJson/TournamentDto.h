// TournamentDto.h
#ifndef TOURNAMENTDTO_H
#define TOURNAMENTDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "TournamentPhaseDto.h"
#include "JsonObject.h"

namespace riot {
class TournamentDto : public JsonObject
{
public:
	// id
	int id() const { return this->value("id").toInt(); }
	void setId(int id) { this->insert("id", id); }
	
	// themeId
	int themeId() const { return this->value("themeId").toInt(); }
	void setThemeId(int themeId) { this->insert("themeId", themeId); }
	
	// nameKey
	QString nameKey() const { return this->value("nameKey").toString(); }
	void setNameKey(const QString &nameKey) { this->insert("nameKey", nameKey); }
	
	// nameKeySecondary
	QString nameKeySecondary() const { return this->value("nameKeySecondary").toString(); }
	void setNameKeySecondary(const QString &nameKeySecondary) { this->insert("nameKeySecondary", nameKeySecondary); }
	
	// Tournament phase.
	QList<TournamentPhaseDto> schedule() const {
		QList<TournamentPhaseDto> result;
		auto arr = this->value("schedule").toArray();
		for (auto val : arr) result.append(static_cast<TournamentPhaseDto&&>(val.toObject()));
		return result;
	}
	void setSchedule(const QList<TournamentPhaseDto> &schedule) {
		QJsonArray arr;
		for (auto v : schedule) arr.append(v);
		this->insert("schedule",arr);
	}
	
};
}

#endif // TOURNAMENTDTO_H
