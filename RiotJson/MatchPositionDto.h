// MatchPositionDto.h
#ifndef MATCHPOSITIONDTO_H
#define MATCHPOSITIONDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class MatchPositionDto : public JsonObject
{
public:
	// x
	int x() const { return this->value("x").toInt(); }
	void setX(int x) { this->insert("x", x); }
	
	// y
	int y() const { return this->value("y").toInt(); }
	void setY(int y) { this->insert("y", y); }
	
};
}

#endif // MATCHPOSITIONDTO_H
