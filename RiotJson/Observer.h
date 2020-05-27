// Observer.h
#ifndef OBSERVER_H
#define OBSERVER_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class Observer : public JsonObject
{
public:
	// Key used to decrypt the spectator grid game data for playback
	QString encryptionKey() const { return this->value("encryptionKey").toString(); }
	void setEncryptionKey(const QString &encryptionKey) { this->insert("encryptionKey", encryptionKey); }
	
};
}

#endif // OBSERVER_H
