// -------------------- RuneDto --------------------
#ifndef RUNEDTO_H
#define RUNEDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class RuneDto : public JsonObject
{
public:
    // runeId
    int runeId() const { return this->value("runeId").toInt(); }
    void setRuneId(int runeId) { this->insert("runeId", runeId); }

    // rank
    int rank() const { return this->value("rank").toInt(); }
    void setRank(int rank) { this->insert("rank", rank); }

};
}

#endif // RUNEDTO_H
