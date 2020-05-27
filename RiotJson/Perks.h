// Perks.h
#ifndef PERKS_H
#define PERKS_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class Perks : public JsonObject
{
public:
	// IDs of the perks/runes assigned.
	QList<long> perkIds() const {
		QList<long> result;
		auto arr = this->value("perkIds").toArray();
		for (auto val : arr) result.append(long(val.toVariant().toLongLong()));
		return result;
	}
	void setPerkIds(const QList<long> &perkIds) {
		QJsonArray arr;
        for (auto v : perkIds) arr.append(qlonglong(v));
		this->insert("perkIds",arr);
	}
	
	// Primary runes path
	long perkStyle() const { return long(this->value("perkStyle").toVariant().toLongLong()); }
	void setPerkStyle(long perkStyle) { this->insert("perkStyle", qlonglong(perkStyle)); }
	
	// Secondary runes path
	long perkSubStyle() const { return long(this->value("perkSubStyle").toVariant().toLongLong()); }
	void setPerkSubStyle(long perkSubStyle) { this->insert("perkSubStyle", qlonglong(perkSubStyle)); }
	
};
}

#endif // PERKS_H
