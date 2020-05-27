// MiniSeriesDTO.h
#ifndef MINISERIESDTO_H
#define MINISERIESDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class MiniSeriesDTO : public JsonObject
{
public:
	// losses
	int losses() const { return this->value("losses").toInt(); }
	void setLosses(int losses) { this->insert("losses", losses); }
	
	// progress
	QString progress() const { return this->value("progress").toString(); }
	void setProgress(const QString &progress) { this->insert("progress", progress); }
	
	// target
	int target() const { return this->value("target").toInt(); }
	void setTarget(int target) { this->insert("target", target); }
	
	// wins
	int wins() const { return this->value("wins").toInt(); }
	void setWins(int wins) { this->insert("wins", wins); }
	
};
}

#endif // MINISERIESDTO_H
