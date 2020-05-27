
// -------------------- ParticipantTimelineDto --------------------
#ifndef PARTICIPANTTIMELINEDTO_H
#define PARTICIPANTTIMELINEDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class ParticipantTimelineDto : public JsonObject
{
public:
    // participantId
    int participantId() const { return this->value("participantId").toInt(); }
    void setParticipantId(int participantId) { this->insert("participantId", participantId); }

    // Creep score difference versus the calculated lane opponent(s) for a specified period.
    QMap<QString, qreal> csDiffPerMinDeltas() const {
        QMap<QString, qreal> result;
        auto object = this->value("csDiffPerMinDeltas").toObject();
        for (auto key : object.keys()) result.insert(key, object.value(key).toDouble());
        return result;
    }
    void setCsDiffPerMinDeltas(const QMap<QString, qreal> csDiffPerMinDeltas) {
        QJsonObject object;
        for (auto key : csDiffPerMinDeltas.keys()) object.insert(key, csDiffPerMinDeltas.value(key));
        this->insert("csDiffPerMinDeltas", object);
    }

    // Damage taken for a specified period.
    QMap<QString, qreal> damageTakenPerMinDeltas() const {
        QMap<QString, qreal> result;
        auto object = this->value("damageTakenPerMinDeltas").toObject();
        for (auto key : object.keys()) result.insert(key, object.value(key).toDouble());
        return result;
    }
    void setDamageTakenPerMinDeltas(const QMap<QString, qreal> damageTakenPerMinDeltas) {
        QJsonObject object;
        for (auto key : damageTakenPerMinDeltas.keys()) object.insert(key, damageTakenPerMinDeltas.value(key));
        this->insert("damageTakenPerMinDeltas", object);
    }

    // Participant's calculated role. (Legal values: DUO, NONE, SOLO, DUO_CARRY, DUO_SUPPORT)
    QString role() const { return this->value("role").toString(); }
    void setRole(const QString &role) { this->insert("role", role); }

    // Damage taken difference versus the calculated lane opponent(s) for a specified period.
    QMap<QString, qreal> damageTakenDiffPerMinDeltas() const {
        QMap<QString, qreal> result;
        auto object = this->value("damageTakenDiffPerMinDeltas").toObject();
        for (auto key : object.keys()) result.insert(key, object.value(key).toDouble());
        return result;
    }
    void setDamageTakenDiffPerMinDeltas(const QMap<QString, qreal> damageTakenDiffPerMinDeltas) {
        QJsonObject object;
        for (auto key : damageTakenDiffPerMinDeltas.keys()) object.insert(key, damageTakenDiffPerMinDeltas.value(key));
        this->insert("damageTakenDiffPerMinDeltas", object);
    }

    // Experience change for a specified period.
    QMap<QString, qreal> xpPerMinDeltas() const {
        QMap<QString, qreal> result;
        auto object = this->value("xpPerMinDeltas").toObject();
        for (auto key : object.keys()) result.insert(key, object.value(key).toDouble());
        return result;
    }
    void setXpPerMinDeltas(const QMap<QString, qreal> xpPerMinDeltas) {
        QJsonObject object;
        for (auto key : xpPerMinDeltas.keys()) object.insert(key, xpPerMinDeltas.value(key));
        this->insert("xpPerMinDeltas", object);
    }

    // Experience difference versus the calculated lane opponent(s) for a specified period.
    QMap<QString, qreal> xpDiffPerMinDeltas() const {
        QMap<QString, qreal> result;
        auto object = this->value("xpDiffPerMinDeltas").toObject();
        for (auto key : object.keys()) result.insert(key, object.value(key).toDouble());
        return result;
    }
    void setXpDiffPerMinDeltas(const QMap<QString, qreal> xpDiffPerMinDeltas) {
        QJsonObject object;
        for (auto key : xpDiffPerMinDeltas.keys()) object.insert(key, xpDiffPerMinDeltas.value(key));
        this->insert("xpDiffPerMinDeltas", object);
    }

    // Participant's calculated lane. MID and BOT are legacy values. (Legal values: MID, MIDDLE, TOP, JUNGLE, BOT, BOTTOM)
    QString lane() const { return this->value("lane").toString(); }
    void setLane(const QString &lane) { this->insert("lane", lane); }

    // Creeps for a specified period.
    QMap<QString, qreal> creepsPerMinDeltas() const {
        QMap<QString, qreal> result;
        auto object = this->value("creepsPerMinDeltas").toObject();
        for (auto key : object.keys()) result.insert(key, object.value(key).toDouble());
        return result;
    }
    void setCreepsPerMinDeltas(const QMap<QString, qreal> creepsPerMinDeltas) {
        QJsonObject object;
        for (auto key : creepsPerMinDeltas.keys()) object.insert(key, creepsPerMinDeltas.value(key));
        this->insert("creepsPerMinDeltas", object);
    }

    // Gold for a specified period.
    QMap<QString, qreal> goldPerMinDeltas() const {
        QMap<QString, qreal> result;
        auto object = this->value("goldPerMinDeltas").toObject();
        for (auto key : object.keys()) result.insert(key, qreal(object.value(key).toDouble()));
        return result;
    }
    void setGoldPerMinDeltas(const QMap<QString, qreal> goldPerMinDeltas) {
        QJsonObject object;
        for (auto key : goldPerMinDeltas.keys()) object.insert(key, goldPerMinDeltas.value(key));
        this->insert("goldPerMinDeltas", object);
    }

};
}

#endif // PARTICIPANTTIMELINEDTO_H
