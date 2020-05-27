// Translation.h
#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class Translation : public JsonObject
{
public:
	// updated_at
	QString updated_at() const { return this->value("updated_at").toString(); }
	void setUpdated_at(const QString &updated_at) { this->insert("updated_at", updated_at); }
	
	// locale
	QString locale() const { return this->value("locale").toString(); }
	void setLocale(const QString &locale) { this->insert("locale", locale); }
	
	// content
	QString content() const { return this->value("content").toString(); }
	void setContent(const QString &content) { this->insert("content", content); }
	
};
}

#endif // TRANSLATION_H
