// -------------------- MasteryDto --------------------
#ifndef MASTERYDTO_H
#define MASTERYDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class MasteryDto : public JsonObject
{
public:
    // rank
    int rank() const { return this->value("rank").toInt(); }
    void setRank(int rank) { this->insert("rank", rank); }

    // masteryId
    int masteryId() const { return this->value("masteryId").toInt(); }
    void setMasteryId(int masteryId) { this->insert("masteryId", masteryId); }

};
}

#endif // MASTERYDTO_H
