#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <QObject>
#include <QJsonObject>
#include <QJSEngine>


#include "lcu.h"
#include "riot.h"
#include "datadragon.h"
#include "observerfilemanager.h"

using namespace riot;

class QNetworkAccessManager;
class Challenge : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentGameflowState READ currentGameflowState NOTIFY currentGameflowStateChanged)
    Q_PROPERTY(QJsonObject currentSummoner READ currentSummoner NOTIFY currentSummonerChanged)
public:
    explicit Challenge(QObject *parent = nullptr);
    explicit Challenge(QJSEngine *engine, QObject *parent = nullptr);

    Q_INVOKABLE static QString readFile(const QString &path);

    QNetworkAccessManager *client() const;
    Riot *riot() const;
    LCU *lcu() const;
    DataDragon *dataDragon() const;
    ObserverFileManager *observerFileManager() const;

    LCU::GameflowState currentGameflowState() const;
    QJsonObject currentSummoner() const;

    Q_INVOKABLE void getChampRateByOPGG(const QString &summonerName, const QJSValue &callback) const;



signals:
    void currentGameflowStateChanged();
    void currentSummonerChanged();

private slots:
    void currentGameflowStateUpdate();
    void currentSummonerUpdate();

private:
    void init();

    LCU::GameflowState mCurrentGameflowState = LCU::None;
    void setCurrentGameflowState(const LCU::GameflowState &currentGameflowState);

    QJsonObject mCurrentSummoner;
    void setCurrentSummoner(const QJsonObject &currentSummoner);

    QJSEngine *mJSEngine;
    QNetworkAccessManager *mClient;
    Riot *mRiot;
    LCU *mLCU;
    DataDragon *mDataDragon;
    ObserverFileManager *mObserverFileManager;
};

#endif // CHALLENGE_H
