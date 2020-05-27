// LobbyEventDTOWrapper.h
#ifndef LOBBYEVENTDTOWRAPPER_H
#define LOBBYEVENTDTOWRAPPER_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "LobbyEventDTO.h"
#include "JsonObject.h"

namespace riot {
class LobbyEventDTOWrapper : public JsonObject
{
public:
	// eventList
    QList<LobbyEventDTO> eventList() const {
        QList<LobbyEventDTO> result;
        auto arr = this->value("eventList").toArray();
        for (auto val : arr) result.append(static_cast<LobbyEventDTO&&>(val.toObject()));
        return result;
    }
    void setEventList(const QList<LobbyEventDTO> &eventList) {
        QJsonArray arr;
        for (auto v : eventList) arr.append(v);
        this->insert("eventList",arr);
    }

};
}

#endif // LOBBYEVENTDTOWRAPPER_H
