// Incident.h
#ifndef INCIDENT_H
#define INCIDENT_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "Message.h"
#include "JsonObject.h"

namespace riot {
class Incident : public JsonObject
{
public:
	// active
	bool active() const { return this->value("active").toBool(); }
	void setActive(bool active) { this->insert("active", active); }
	
	// created_at
	QString created_at() const { return this->value("created_at").toString(); }
	void setCreated_at(const QString &created_at) { this->insert("created_at", created_at); }
	
	// id
	long id() const { return long(this->value("id").toVariant().toLongLong()); }
	void setId(long id) { this->insert("id", qlonglong(id)); }
	
	// updates
	QList<Message> updates() const {
		QList<Message> result;
		auto arr = this->value("updates").toArray();
		for (auto val : arr) result.append(static_cast<Message&&>(val.toObject()));
		return result;
	}
	void setUpdates(const QList<Message> &updates) {
		QJsonArray arr;
		for (auto v : updates) arr.append(v);
		this->insert("updates",arr);
	}
	
};
}

#endif // INCIDENT_H
