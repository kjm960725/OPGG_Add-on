#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <QObject>
#include <QJsonObject>
#include <QJSEngine>


#include "lcu.h"
#include "riot.h"
#include "datadragon.h"
#include "updatetool.h"
#include "observerfilemanager.h"

using namespace riot;

class WebScrapForOPGG;
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
    Q_INVOKABLE static bool clearWebCache();
    Q_INVOKABLE static bool clearWebCookie();
    Q_INVOKABLE static QPoint getMousePos();
    Q_INVOKABLE static void restartAdministrator();

    QNetworkAccessManager *client() const;
    UpdateTool *updateTool() const;
    Riot *riot() const;
    LCU *lcu() const;
    DataDragon *dataDragon() const;
    ObserverFileManager *observerFileManager() const;
    WebScrapForOPGG *webScrapForOPGG() const;

    LCU::GameflowState currentGameflowState() const;
    QJsonObject currentSummoner() const;

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

    WebScrapForOPGG *mWebScrapForOPGG;
    UpdateTool *mUpdateTool;
    QJSEngine *mJSEngine;
    QNetworkAccessManager *mClient;
    Riot *mRiot;
    LCU *mLCU;
    DataDragon *mDataDragon;
    ObserverFileManager *mObserverFileManager;
};

#endif // CHALLENGE_H
