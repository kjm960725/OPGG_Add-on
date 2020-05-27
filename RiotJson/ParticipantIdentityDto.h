// -------------------- ParticipantIdentityDto --------------------
#ifndef PARTICIPANTIDENTITYDTO_H
#define PARTICIPANTIDENTITYDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "PlayerDto.h"
#include "JsonObject.h"

namespace riot {
class ParticipantIdentityDto : public JsonObject
{
public:
    // participantId
    int participantId() const { return this->value("participantId").toInt(); }
    void setParticipantId(int participantId) { this->insert("participantId", participantId); }

    // Player information not included in the response for custom matches. Custom matches are considered private unless a tournament code was used to create the match.
    PlayerDto player() const { return static_cast<PlayerDto&&>(this->value("player").toObject()); }
    void setPlayer(const PlayerDto &player) { this->insert("player", player); }

};
}

#endif // PARTICIPANTIDENTITYDTO_H
