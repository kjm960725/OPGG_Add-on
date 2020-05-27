// LeagueListDTO.h
#ifndef LEAGUELISTDTO_H
#define LEAGUELISTDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "LeagueItemDTO.h"
#include "JsonObject.h"

namespace riot {
class LeagueListDTO : public JsonObject
{
public:
	// leagueId
	QString leagueId() const { return this->value("leagueId").toString(); }
	void setLeagueId(const QString &leagueId) { this->insert("leagueId", leagueId); }
	
	// entries
	QList<LeagueItemDTO> entries() const {
		QList<LeagueItemDTO> result;
		auto arr = this->value("entries").toArray();
		for (auto val : arr) result.append(static_cast<LeagueItemDTO&&>(val.toObject()));
		return result;
	}
	void setEntries(const QList<LeagueItemDTO> &entries) {
		QJsonArray arr;
		for (auto v : entries) arr.append(v);
		this->insert("entries",arr);
	}
	
	// tier
	QString tier() const { return this->value("tier").toString(); }
	void setTier(const QString &tier) { this->insert("tier", tier); }
	
	// name
	QString name() const { return this->value("name").toString(); }
	void setName(const QString &name) { this->insert("name", name); }
	
	// queue
	QString queue() const { return this->value("queue").toString(); }
	void setQueue(const QString &queue) { this->insert("queue", queue); }
	
};
}

#endif // LEAGUELISTDTO_H
