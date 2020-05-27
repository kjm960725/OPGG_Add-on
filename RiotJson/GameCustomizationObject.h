// GameCustomizationObject.h
#ifndef GAMECUSTOMIZATIONOBJECT_H
#define GAMECUSTOMIZATIONOBJECT_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class GameCustomizationObject : public JsonObject
{
public:
	// Category identifier for Game Customization
	QString category() const { return this->value("category").toString(); }
	void setCategory(const QString &category) { this->insert("category", category); }
	
	// Game Customization content
	QString content() const { return this->value("content").toString(); }
	void setContent(const QString &content) { this->insert("content", content); }
	
};
}

#endif // GAMECUSTOMIZATIONOBJECT_H
