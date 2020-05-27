#ifndef SUMMONERDTO_H
#define SUMMONERDTO_H

#include <QJsonObject>
#include <QVariant>
#include "JsonObject.h"

namespace riot {
class SummonerDTO : public JsonObject
{
public:
    // Encrypted account ID. Max length 56 characters.
    QString accountId() const { return this->value("accountId").toString(); }
    void setAaccountId(const QString &accountId) { this->insert("accountId", accountId); }

    // ID of the summoner icon associated with the summoner.
    int profileIconId() const { return this->value("profileIconId").toInt(); }
    void setProfileIconId(int profileIconId) { this->insert("profileIconId", profileIconId); }

    // Date summoner was last modified specified as epoch milliseconds. The following events will update this timestamp: profile icon change, playing the tutorial or advanced tutorial, finishing a game, summoner name change
    long revisionDate() const { return long(this->value("revisionDate").toVariant().toLongLong()); }
    void setRevisionDate(long revisionDate) { this->insert("revisionDate", qlonglong(revisionDate)); }

    // Summoner name.
    QString name() const { return this->value("name").toString(); }
    void setName(const QString &accountId) { this->insert("name", accountId); }

    // Encrypted summoner ID. Max length 63 characters.
    QString id() const { return this->value("id").toString(); }
    void setId(const QString &id) { this->insert("id", id); }

    // Encrypted PUUID. Exact length of 78 characters.
    QString puuid() const { return this->value("puuid").toString(); }
    void setPuuid(const QString &puuid) { this->insert("puuid", puuid); }

    // Summoner level associated with the summoner.
    long summonerLevel() const { return long(this->value("summonerLevel").toVariant().toLongLong()); }
    void setSummonerLevel(long summonerLevel) { this->insert("summonerLevel", qlonglong(summonerLevel)); }
};
}
#endif // SUMMONERDTO_H
