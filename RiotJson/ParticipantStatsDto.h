// -------------------- ParticipantStatsDto --------------------
#ifndef PARTICIPANTSTATSDTO_H
#define PARTICIPANTSTATSDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "JsonObject.h"

namespace riot {
class ParticipantStatsDto : public JsonObject
{
public:
    // item0
    int item0() const { return this->value("item0").toInt(); }
    void setItem0(int item0) { this->insert("item0", item0); }

    // item2
    int item2() const { return this->value("item2").toInt(); }
    void setItem2(int item2) { this->insert("item2", item2); }

    // totalUnitsHealed
    int totalUnitsHealed() const { return this->value("totalUnitsHealed").toInt(); }
    void setTotalUnitsHealed(int totalUnitsHealed) { this->insert("totalUnitsHealed", totalUnitsHealed); }

    // item1
    int item1() const { return this->value("item1").toInt(); }
    void setItem1(int item1) { this->insert("item1", item1); }

    // largestMultiKill
    int largestMultiKill() const { return this->value("largestMultiKill").toInt(); }
    void setLargestMultiKill(int largestMultiKill) { this->insert("largestMultiKill", largestMultiKill); }

    // goldEarned
    int goldEarned() const { return this->value("goldEarned").toInt(); }
    void setGoldEarned(int goldEarned) { this->insert("goldEarned", goldEarned); }

    // firstInhibitorKill
    bool firstInhibitorKill() const { return this->value("firstInhibitorKill").toBool(); }
    void setFirstInhibitorKill(bool firstInhibitorKill) { this->insert("firstInhibitorKill", firstInhibitorKill); }

    // physicalDamageTaken
    long physicalDamageTaken() const { return long(this->value("physicalDamageTaken").toVariant().toLongLong()); }
    void setPhysicalDamageTaken(long physicalDamageTaken) { this->insert("physicalDamageTaken", qlonglong(physicalDamageTaken)); }

    // nodeNeutralizeAssist
    int nodeNeutralizeAssist() const { return this->value("nodeNeutralizeAssist").toInt(); }
    void setNodeNeutralizeAssist(int nodeNeutralizeAssist) { this->insert("nodeNeutralizeAssist", nodeNeutralizeAssist); }

    // totalPlayerScore
    int totalPlayerScore() const { return this->value("totalPlayerScore").toInt(); }
    void setTotalPlayerScore(int totalPlayerScore) { this->insert("totalPlayerScore", totalPlayerScore); }

    // champLevel
    int champLevel() const { return this->value("champLevel").toInt(); }
    void setChampLevel(int champLevel) { this->insert("champLevel", champLevel); }

    // damageDealtToObjectives
    long damageDealtToObjectives() const { return long(this->value("damageDealtToObjectives").toVariant().toLongLong()); }
    void setDamageDealtToObjectives(long damageDealtToObjectives) { this->insert("damageDealtToObjectives", qlonglong(damageDealtToObjectives)); }

    // totalDamageTaken
    long totalDamageTaken() const { return long(this->value("totalDamageTaken").toVariant().toLongLong()); }
    void setTotalDamageTaken(long totalDamageTaken) { this->insert("totalDamageTaken", qlonglong(totalDamageTaken)); }

    // neutralMinionsKilled
    int neutralMinionsKilled() const { return this->value("neutralMinionsKilled").toInt(); }
    void setNeutralMinionsKilled(int neutralMinionsKilled) { this->insert("neutralMinionsKilled", neutralMinionsKilled); }

    // deaths
    int deaths() const { return this->value("deaths").toInt(); }
    void setDeaths(int deaths) { this->insert("deaths", deaths); }

    // tripleKills
    int tripleKills() const { return this->value("tripleKills").toInt(); }
    void setTripleKills(int tripleKills) { this->insert("tripleKills", tripleKills); }

    // magicDamageDealtToChampions
    long magicDamageDealtToChampions() const { return long(this->value("magicDamageDealtToChampions").toVariant().toLongLong()); }
    void setMagicDamageDealtToChampions(long magicDamageDealtToChampions) { this->insert("magicDamageDealtToChampions", qlonglong(magicDamageDealtToChampions)); }

    // wardsKilled
    int wardsKilled() const { return this->value("wardsKilled").toInt(); }
    void setWardsKilled(int wardsKilled) { this->insert("wardsKilled", wardsKilled); }

    // pentaKills
    int pentaKills() const { return this->value("pentaKills").toInt(); }
    void setPentaKills(int pentaKills) { this->insert("pentaKills", pentaKills); }

    // damageSelfMitigated
    long damageSelfMitigated() const { return long(this->value("damageSelfMitigated").toVariant().toLongLong()); }
    void setDamageSelfMitigated(long damageSelfMitigated) { this->insert("damageSelfMitigated", qlonglong(damageSelfMitigated)); }

    // largestCriticalStrike
    int largestCriticalStrike() const { return this->value("largestCriticalStrike").toInt(); }
    void setLargestCriticalStrike(int largestCriticalStrike) { this->insert("largestCriticalStrike", largestCriticalStrike); }

    // nodeNeutralize
    int nodeNeutralize() const { return this->value("nodeNeutralize").toInt(); }
    void setNodeNeutralize(int nodeNeutralize) { this->insert("nodeNeutralize", nodeNeutralize); }

    // totalTimeCrowdControlDealt
    int totalTimeCrowdControlDealt() const { return this->value("totalTimeCrowdControlDealt").toInt(); }
    void setTotalTimeCrowdControlDealt(int totalTimeCrowdControlDealt) { this->insert("totalTimeCrowdControlDealt", totalTimeCrowdControlDealt); }

    // firstTowerKill
    bool firstTowerKill() const { return this->value("firstTowerKill").toBool(); }
    void setFirstTowerKill(bool firstTowerKill) { this->insert("firstTowerKill", firstTowerKill); }

    // magicDamageDealt
    long magicDamageDealt() const { return long(this->value("magicDamageDealt").toVariant().toLongLong()); }
    void setMagicDamageDealt(long magicDamageDealt) { this->insert("magicDamageDealt", qlonglong(magicDamageDealt)); }

    // totalScoreRank
    int totalScoreRank() const { return this->value("totalScoreRank").toInt(); }
    void setTotalScoreRank(int totalScoreRank) { this->insert("totalScoreRank", totalScoreRank); }

    // nodeCapture
    int nodeCapture() const { return this->value("nodeCapture").toInt(); }
    void setNodeCapture(int nodeCapture) { this->insert("nodeCapture", nodeCapture); }

    // wardsPlaced
    int wardsPlaced() const { return this->value("wardsPlaced").toInt(); }
    void setWardsPlaced(int wardsPlaced) { this->insert("wardsPlaced", wardsPlaced); }

    // totalDamageDealt
    long totalDamageDealt() const { return long(this->value("totalDamageDealt").toVariant().toLongLong()); }
    void setTotalDamageDealt(long totalDamageDealt) { this->insert("totalDamageDealt", qlonglong(totalDamageDealt)); }

    // timeCCingOthers
    long timeCCingOthers() const { return long(this->value("timeCCingOthers").toVariant().toLongLong()); }
    void setTimeCCingOthers(long timeCCingOthers) { this->insert("timeCCingOthers", qlonglong(timeCCingOthers)); }

    // magicalDamageTaken
    long magicalDamageTaken() const { return long(this->value("magicalDamageTaken").toVariant().toLongLong()); }
    void setMagicalDamageTaken(long magicalDamageTaken) { this->insert("magicalDamageTaken", qlonglong(magicalDamageTaken)); }

    // largestKillingSpree
    int largestKillingSpree() const { return this->value("largestKillingSpree").toInt(); }
    void setLargestKillingSpree(int largestKillingSpree) { this->insert("largestKillingSpree", largestKillingSpree); }

    // totalDamageDealtToChampions
    long totalDamageDealtToChampions() const { return long(this->value("totalDamageDealtToChampions").toVariant().toLongLong()); }
    void setTotalDamageDealtToChampions(long totalDamageDealtToChampions) { this->insert("totalDamageDealtToChampions", qlonglong(totalDamageDealtToChampions)); }

    // physicalDamageDealtToChampions
    long physicalDamageDealtToChampions() const { return long(this->value("physicalDamageDealtToChampions").toVariant().toLongLong()); }
    void setPhysicalDamageDealtToChampions(long physicalDamageDealtToChampions) { this->insert("physicalDamageDealtToChampions", qlonglong(physicalDamageDealtToChampions)); }

    // neutralMinionsKilledTeamJungle
    int neutralMinionsKilledTeamJungle() const { return this->value("neutralMinionsKilledTeamJungle").toInt(); }
    void setNeutralMinionsKilledTeamJungle(int neutralMinionsKilledTeamJungle) { this->insert("neutralMinionsKilledTeamJungle", neutralMinionsKilledTeamJungle); }

    // totalMinionsKilled
    int totalMinionsKilled() const { return this->value("totalMinionsKilled").toInt(); }
    void setTotalMinionsKilled(int totalMinionsKilled) { this->insert("totalMinionsKilled", totalMinionsKilled); }

    // firstInhibitorAssist
    bool firstInhibitorAssist() const { return this->value("firstInhibitorAssist").toBool(); }
    void setFirstInhibitorAssist(bool firstInhibitorAssist) { this->insert("firstInhibitorAssist", firstInhibitorAssist); }

    // visionWardsBoughtInGame
    int visionWardsBoughtInGame() const { return this->value("visionWardsBoughtInGame").toInt(); }
    void setVisionWardsBoughtInGame(int visionWardsBoughtInGame) { this->insert("visionWardsBoughtInGame", visionWardsBoughtInGame); }

    // objectivePlayerScore
    int objectivePlayerScore() const { return this->value("objectivePlayerScore").toInt(); }
    void setObjectivePlayerScore(int objectivePlayerScore) { this->insert("objectivePlayerScore", objectivePlayerScore); }

    // kills
    int kills() const { return this->value("kills").toInt(); }
    void setKills(int kills) { this->insert("kills", kills); }

    // firstTowerAssist
    bool firstTowerAssist() const { return this->value("firstTowerAssist").toBool(); }
    void setFirstTowerAssist(bool firstTowerAssist) { this->insert("firstTowerAssist", firstTowerAssist); }

    // combatPlayerScore
    int combatPlayerScore() const { return this->value("combatPlayerScore").toInt(); }
    void setCombatPlayerScore(int combatPlayerScore) { this->insert("combatPlayerScore", combatPlayerScore); }

    // inhibitorKills
    int inhibitorKills() const { return this->value("inhibitorKills").toInt(); }
    void setInhibitorKills(int inhibitorKills) { this->insert("inhibitorKills", inhibitorKills); }

    // turretKills
    int turretKills() const { return this->value("turretKills").toInt(); }
    void setTurretKills(int turretKills) { this->insert("turretKills", turretKills); }

    // participantId
    int participantId() const { return this->value("participantId").toInt(); }
    void setParticipantId(int participantId) { this->insert("participantId", participantId); }

    // trueDamageTaken
    long trueDamageTaken() const { return long(this->value("trueDamageTaken").toVariant().toLongLong()); }
    void setTrueDamageTaken(long trueDamageTaken) { this->insert("trueDamageTaken", qlonglong(trueDamageTaken)); }

    // firstBloodAssist
    bool firstBloodAssist() const { return this->value("firstBloodAssist").toBool(); }
    void setFirstBloodAssist(bool firstBloodAssist) { this->insert("firstBloodAssist", firstBloodAssist); }

    // nodeCaptureAssist
    int nodeCaptureAssist() const { return this->value("nodeCaptureAssist").toInt(); }
    void setNodeCaptureAssist(int nodeCaptureAssist) { this->insert("nodeCaptureAssist", nodeCaptureAssist); }

    // assists
    int assists() const { return this->value("assists").toInt(); }
    void setAssists(int assists) { this->insert("assists", assists); }

    // teamObjective
    int teamObjective() const { return this->value("teamObjective").toInt(); }
    void setTeamObjective(int teamObjective) { this->insert("teamObjective", teamObjective); }

    // altarsNeutralized
    int altarsNeutralized() const { return this->value("altarsNeutralized").toInt(); }
    void setAltarsNeutralized(int altarsNeutralized) { this->insert("altarsNeutralized", altarsNeutralized); }

    // goldSpent
    int goldSpent() const { return this->value("goldSpent").toInt(); }
    void setGoldSpent(int goldSpent) { this->insert("goldSpent", goldSpent); }

    // damageDealtToTurrets
    long damageDealtToTurrets() const { return long(this->value("damageDealtToTurrets").toVariant().toLongLong()); }
    void setDamageDealtToTurrets(long damageDealtToTurrets) { this->insert("damageDealtToTurrets", qlonglong(damageDealtToTurrets)); }

    // altarsCaptured
    int altarsCaptured() const { return this->value("altarsCaptured").toInt(); }
    void setAltarsCaptured(int altarsCaptured) { this->insert("altarsCaptured", altarsCaptured); }

    // win
    bool win() const { return this->value("win").toBool(); }
    void setWin(bool win) { this->insert("win", win); }

    // totalHeal
    long totalHeal() const { return long(this->value("totalHeal").toVariant().toLongLong()); }
    void setTotalHeal(long totalHeal) { this->insert("totalHeal", qlonglong(totalHeal)); }

    // unrealKills
    int unrealKills() const { return this->value("unrealKills").toInt(); }
    void setUnrealKills(int unrealKills) { this->insert("unrealKills", unrealKills); }

    // visionScore
    long visionScore() const { return long(this->value("visionScore").toVariant().toLongLong()); }
    void setVisionScore(long visionScore) { this->insert("visionScore", qlonglong(visionScore)); }

    // physicalDamageDealt
    long physicalDamageDealt() const { return long(this->value("physicalDamageDealt").toVariant().toLongLong()); }
    void setPhysicalDamageDealt(long physicalDamageDealt) { this->insert("physicalDamageDealt", qlonglong(physicalDamageDealt)); }

    // firstBloodKill
    bool firstBloodKill() const { return this->value("firstBloodKill").toBool(); }
    void setFirstBloodKill(bool firstBloodKill) { this->insert("firstBloodKill", firstBloodKill); }

    // longestTimeSpentLiving
    int longestTimeSpentLiving() const { return this->value("longestTimeSpentLiving").toInt(); }
    void setLongestTimeSpentLiving(int longestTimeSpentLiving) { this->insert("longestTimeSpentLiving", longestTimeSpentLiving); }

    // killingSprees
    int killingSprees() const { return this->value("killingSprees").toInt(); }
    void setKillingSprees(int killingSprees) { this->insert("killingSprees", killingSprees); }

    // sightWardsBoughtInGame
    int sightWardsBoughtInGame() const { return this->value("sightWardsBoughtInGame").toInt(); }
    void setSightWardsBoughtInGame(int sightWardsBoughtInGame) { this->insert("sightWardsBoughtInGame", sightWardsBoughtInGame); }

    // trueDamageDealtToChampions
    long trueDamageDealtToChampions() const { return long(this->value("trueDamageDealtToChampions").toVariant().toLongLong()); }
    void setTrueDamageDealtToChampions(long trueDamageDealtToChampions) { this->insert("trueDamageDealtToChampions", qlonglong(trueDamageDealtToChampions)); }

    // neutralMinionsKilledEnemyJungle
    int neutralMinionsKilledEnemyJungle() const { return this->value("neutralMinionsKilledEnemyJungle").toInt(); }
    void setNeutralMinionsKilledEnemyJungle(int neutralMinionsKilledEnemyJungle) { this->insert("neutralMinionsKilledEnemyJungle", neutralMinionsKilledEnemyJungle); }

    // doubleKills
    int doubleKills() const { return this->value("doubleKills").toInt(); }
    void setDoubleKills(int doubleKills) { this->insert("doubleKills", doubleKills); }

    // trueDamageDealt
    long trueDamageDealt() const { return long(this->value("trueDamageDealt").toVariant().toLongLong()); }
    void setTrueDamageDealt(long trueDamageDealt) { this->insert("trueDamageDealt", qlonglong(trueDamageDealt)); }

    // quadraKills
    int quadraKills() const { return this->value("quadraKills").toInt(); }
    void setQuadraKills(int quadraKills) { this->insert("quadraKills", quadraKills); }

    // item4
    int item4() const { return this->value("item4").toInt(); }
    void setItem4(int item4) { this->insert("item4", item4); }

    // item3
    int item3() const { return this->value("item3").toInt(); }
    void setItem3(int item3) { this->insert("item3", item3); }

    // item6
    int item6() const { return this->value("item6").toInt(); }
    void setItem6(int item6) { this->insert("item6", item6); }

    // item5
    int item5() const { return this->value("item5").toInt(); }
    void setItem5(int item5) { this->insert("item5", item5); }

    // playerScore0
    int playerScore0() const { return this->value("playerScore0").toInt(); }
    void setPlayerScore0(int playerScore0) { this->insert("playerScore0", playerScore0); }

    // playerScore1
    int playerScore1() const { return this->value("playerScore1").toInt(); }
    void setPlayerScore1(int playerScore1) { this->insert("playerScore1", playerScore1); }

    // playerScore2
    int playerScore2() const { return this->value("playerScore2").toInt(); }
    void setPlayerScore2(int playerScore2) { this->insert("playerScore2", playerScore2); }

    // playerScore3
    int playerScore3() const { return this->value("playerScore3").toInt(); }
    void setPlayerScore3(int playerScore3) { this->insert("playerScore3", playerScore3); }

    // playerScore4
    int playerScore4() const { return this->value("playerScore4").toInt(); }
    void setPlayerScore4(int playerScore4) { this->insert("playerScore4", playerScore4); }

    // playerScore5
    int playerScore5() const { return this->value("playerScore5").toInt(); }
    void setPlayerScore5(int playerScore5) { this->insert("playerScore5", playerScore5); }

    // playerScore6
    int playerScore6() const { return this->value("playerScore6").toInt(); }
    void setPlayerScore6(int playerScore6) { this->insert("playerScore6", playerScore6); }

    // playerScore7
    int playerScore7() const { return this->value("playerScore7").toInt(); }
    void setPlayerScore7(int playerScore7) { this->insert("playerScore7", playerScore7); }

    // playerScore8
    int playerScore8() const { return this->value("playerScore8").toInt(); }
    void setPlayerScore8(int playerScore8) { this->insert("playerScore8", playerScore8); }

    // playerScore9
    int playerScore9() const { return this->value("playerScore9").toInt(); }
    void setPlayerScore9(int playerScore9) { this->insert("playerScore9", playerScore9); }

    // Primary path keystone rune.
    int perk0() const { return this->value("perk0").toInt(); }
    void setPerk0(int perk0) { this->insert("perk0", perk0); }

    // Post game rune stats.
    int perk0Var1() const { return this->value("perk0Var1").toInt(); }
    void setPerk0Var1(int perk0Var1) { this->insert("perk0Var1", perk0Var1); }

    // Post game rune stats.
    int perk0Var2() const { return this->value("perk0Var2").toInt(); }
    void setPerk0Var2(int perk0Var2) { this->insert("perk0Var2", perk0Var2); }

    // Post game rune stats.
    int perk0Var3() const { return this->value("perk0Var3").toInt(); }
    void setPerk0Var3(int perk0Var3) { this->insert("perk0Var3", perk0Var3); }

    // Primary path rune.
    int perk1() const { return this->value("perk1").toInt(); }
    void setPerk1(int perk1) { this->insert("perk1", perk1); }

    // Post game rune stats.
    int perk1Var1() const { return this->value("perk1Var1").toInt(); }
    void setPerk1Var1(int perk1Var1) { this->insert("perk1Var1", perk1Var1); }

    // Post game rune stats.
    int perk1Var2() const { return this->value("perk1Var2").toInt(); }
    void setPerk1Var2(int perk1Var2) { this->insert("perk1Var2", perk1Var2); }

    // Post game rune stats.
    int perk1Var3() const { return this->value("perk1Var3").toInt(); }
    void setPerk1Var3(int perk1Var3) { this->insert("perk1Var3", perk1Var3); }

    // Primary path rune.
    int perk2() const { return this->value("perk2").toInt(); }
    void setPerk2(int perk2) { this->insert("perk2", perk2); }

    // Post game rune stats.
    int perk2Var1() const { return this->value("perk2Var1").toInt(); }
    void setPerk2Var1(int perk2Var1) { this->insert("perk2Var1", perk2Var1); }

    // Post game rune stats.
    int perk2Var2() const { return this->value("perk2Var2").toInt(); }
    void setPerk2Var2(int perk2Var2) { this->insert("perk2Var2", perk2Var2); }

    // Post game rune stats.
    int perk2Var3() const { return this->value("perk2Var3").toInt(); }
    void setPerk2Var3(int perk2Var3) { this->insert("perk2Var3", perk2Var3); }

    // Primary path rune.
    int perk3() const { return this->value("perk3").toInt(); }
    void setPerk3(int perk3) { this->insert("perk3", perk3); }

    // Post game rune stats.
    int perk3Var1() const { return this->value("perk3Var1").toInt(); }
    void setPerk3Var1(int perk3Var1) { this->insert("perk3Var1", perk3Var1); }

    // Post game rune stats.
    int perk3Var2() const { return this->value("perk3Var2").toInt(); }
    void setPerk3Var2(int perk3Var2) { this->insert("perk3Var2", perk3Var2); }

    // Post game rune stats.
    int perk3Var3() const { return this->value("perk3Var3").toInt(); }
    void setPerk3Var3(int perk3Var3) { this->insert("perk3Var3", perk3Var3); }

    // Secondary path rune.
    int perk4() const { return this->value("perk4").toInt(); }
    void setPerk4(int perk4) { this->insert("perk4", perk4); }

    // Post game rune stats.
    int perk4Var1() const { return this->value("perk4Var1").toInt(); }
    void setPerk4Var1(int perk4Var1) { this->insert("perk4Var1", perk4Var1); }

    // Post game rune stats.
    int perk4Var2() const { return this->value("perk4Var2").toInt(); }
    void setPerk4Var2(int perk4Var2) { this->insert("perk4Var2", perk4Var2); }

    // Post game rune stats.
    int perk4Var3() const { return this->value("perk4Var3").toInt(); }
    void setPerk4Var3(int perk4Var3) { this->insert("perk4Var3", perk4Var3); }

    // Secondary path rune.
    int perk5() const { return this->value("perk5").toInt(); }
    void setPerk5(int perk5) { this->insert("perk5", perk5); }

    // Post game rune stats.
    int perk5Var1() const { return this->value("perk5Var1").toInt(); }
    void setPerk5Var1(int perk5Var1) { this->insert("perk5Var1", perk5Var1); }

    // Post game rune stats.
    int perk5Var2() const { return this->value("perk5Var2").toInt(); }
    void setPerk5Var2(int perk5Var2) { this->insert("perk5Var2", perk5Var2); }

    // Post game rune stats.
    int perk5Var3() const { return this->value("perk5Var3").toInt(); }
    void setPerk5Var3(int perk5Var3) { this->insert("perk5Var3", perk5Var3); }

    // Primary rune path
    int perkPrimaryStyle() const { return this->value("perkPrimaryStyle").toInt(); }
    void setPerkPrimaryStyle(int perkPrimaryStyle) { this->insert("perkPrimaryStyle", perkPrimaryStyle); }

    // Secondary rune path
    int perkSubStyle() const { return this->value("perkSubStyle").toInt(); }
    void setPerkSubStyle(int perkSubStyle) { this->insert("perkSubStyle", perkSubStyle); }

};
}

#endif // PARTICIPANTSTATSDTO_H
