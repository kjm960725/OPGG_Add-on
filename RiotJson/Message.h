// Message.h
#ifndef MESSAGE_H
#define MESSAGE_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "Translation.h"
#include "JsonObject.h"

namespace riot {
class Message : public JsonObject
{
public:
	// severity
	QString severity() const { return this->value("severity").toString(); }
	void setSeverity(const QString &severity) { this->insert("severity", severity); }
	
	// updated_at
	QString updated_at() const { return this->value("updated_at").toString(); }
	void setUpdated_at(const QString &updated_at) { this->insert("updated_at", updated_at); }
	
	// author
	QString author() const { return this->value("author").toString(); }
	void setAuthor(const QString &author) { this->insert("author", author); }
	
	// translations
	QList<Translation> translations() const {
		QList<Translation> result;
		auto arr = this->value("translations").toArray();
		for (auto val : arr) result.append(static_cast<Translation&&>(val.toObject()));
		return result;
	}
	void setTranslations(const QList<Translation> &translations) {
		QJsonArray arr;
		for (auto v : translations) arr.append(v);
		this->insert("translations",arr);
	}
	
	// created_at
	QString created_at() const { return this->value("created_at").toString(); }
	void setCreated_at(const QString &created_at) { this->insert("created_at", created_at); }
	
	// id
	QString id() const { return this->value("id").toString(); }
	void setId(const QString &id) { this->insert("id", id); }
	
	// content
	QString content() const { return this->value("content").toString(); }
	void setContent(const QString &content) { this->insert("content", content); }
	
};
}

#endif // MESSAGE_H
