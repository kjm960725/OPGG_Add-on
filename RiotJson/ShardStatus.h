// ShardStatus.h
#ifndef SHARDSTATUS_H
#define SHARDSTATUS_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "Service.h"
#include "JsonObject.h"

namespace riot {
class ShardStatus : public JsonObject
{
public:
	// locales
	QList<QString> locales() const {
		QList<QString> result;
		auto arr = this->value("locales").toArray();
		for (auto val : arr) result.append(val.toString());
		return result;
	}
    void setLocales(const QList<QString> &locales) {
		QJsonArray arr;
		for (auto v : locales) arr.append(v);
		this->insert("locales",arr);
	}
	
	// hostname
	QString hostname() const { return this->value("hostname").toString(); }
	void setHostname(const QString &hostname) { this->insert("hostname", hostname); }
	
	// name
	QString name() const { return this->value("name").toString(); }
	void setName(const QString &name) { this->insert("name", name); }
	
	// services
	QList<Service> services() const {
		QList<Service> result;
		auto arr = this->value("services").toArray();
		for (auto val : arr) result.append(static_cast<Service&&>(val.toObject()));
		return result;
	}
	void setServices(const QList<Service> &services) {
		QJsonArray arr;
		for (auto v : services) arr.append(v);
		this->insert("services",arr);
	}
	
	// slug
	QString slug() const { return this->value("slug").toString(); }
	void setSlug(const QString &slug) { this->insert("slug", slug); }
	
	// region_tag
	QString region_tag() const { return this->value("region_tag").toString(); }
	void setRegion_tag(const QString &region_tag) { this->insert("region_tag", region_tag); }
	
};
}

#endif // SHARDSTATUS_H
