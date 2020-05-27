// Service.h
#ifndef SERVICE_H
#define SERVICE_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "Incident.h"
#include "JsonObject.h"

namespace riot {
class Service : public JsonObject
{
public:
	// incidents
	QList<Incident> incidents() const {
		QList<Incident> result;
		auto arr = this->value("incidents").toArray();
		for (auto val : arr) result.append(static_cast<Incident&&>(val.toObject()));
		return result;
	}
	void setIncidents(const QList<Incident> &incidents) {
		QJsonArray arr;
		for (auto v : incidents) arr.append(v);
		this->insert("incidents",arr);
	}
	
	// name
	QString name() const { return this->value("name").toString(); }
	void setName(const QString &name) { this->insert("name", name); }
	
	// slug
	QString slug() const { return this->value("slug").toString(); }
	void setSlug(const QString &slug) { this->insert("slug", slug); }
	
	// status
	QString status() const { return this->value("status").toString(); }
	void setStatus(const QString &status) { this->insert("status", status); }
	
};
}

#endif // SERVICE_H
