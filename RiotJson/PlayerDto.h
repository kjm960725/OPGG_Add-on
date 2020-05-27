// PlayerDto.h
#ifndef PLAYERDTO_H
#define PLAYERDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class PlayerDto : public JsonObject
{
public:
	// summonerId
	QString summonerId() const { return this->value("summonerId").toString(); }
	void setSummonerId(const QString &summonerId) { this->insert("summonerId", summonerId); }
	
	// (Legal values: UNSELECTED, FILL, TOP, JUNGLE, MIDDLE, BOTTOM, UTILITY)
	QString position() const { return this->value("position").toString(); }
	void setPosition(const QString &position) { this->insert("position", position); }
	
	// (Legal values: CAPTAIN, MEMBER)
	QString role() const { return this->value("role").toString(); }
	void setRole(const QString &role) { this->insert("role", role); }
	
};
}

#endif // PLAYERDTO_H
