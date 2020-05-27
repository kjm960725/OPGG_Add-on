// -------------------- TeamBansDto --------------------
#ifndef TEAMBANSDTO_H
#define TEAMBANSDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class TeamBansDto : public JsonObject
{
public:
    // Banned championId.
    int championId() const { return this->value("championId").toInt(); }
    void setChampionId(int championId) { this->insert("championId", championId); }

    // Turn during which the champion was banned.
    int pickTurn() const { return this->value("pickTurn").toInt(); }
    void setPickTurn(int pickTurn) { this->insert("pickTurn", pickTurn); }

};
}

#endif // TEAMBANSDTO_H
