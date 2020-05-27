#include "challenge.h"
#include <QUrlQuery>
#include "lcu.h"
#include "datadragon.h"
#include "riot.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <QElapsedTimer>
using namespace riot;

Challenge::Challenge(QObject *parent) : QObject(parent)
{
    init();
}

Challenge::Challenge(QJSEngine *engine, QObject *parent) : QObject(parent)
{
    init();
    mRiot->setJSEngine(engine);
    mLCU->setJSEngine(engine);
    mJSEngine = engine;
}

QString Challenge::readFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Challenge::readFile error : open file failed" << file.error() << file.errorString();
        return QString();
    }
    return file.readAll();
}

void Challenge::init()
{
    mClient = new QNetworkAccessManager(this);
    mRiot = new Riot(mClient, "{API-KEY}", this);
    mDataDragon = new DataDragon(mClient, DataDragon::ko_KR, DataDragon::All, this);
    mLCU = new LCU(mClient, this);
    mObserverFileManager = new ObserverFileManager(this);

    currentGameflowStateUpdate();
    currentSummonerUpdate();

    connect(mLCU, &LCU::connected, [=](){ qInfo() << "League cleint connected"; });
    connect(mLCU, &LCU::disconnected, [=](){ qInfo() << "League cleint disconnected"; });

    mDataDragon->dataDragonVersionCheck([=](int err, QString errStr){err = 0; errStr = "";});

    mLCU->start();
}

QNetworkAccessManager *Challenge::client() const
{
    return mClient;
}

Riot *Challenge::riot() const
{
    return mRiot;
}

LCU *Challenge::lcu() const
{
    return mLCU;
}

DataDragon *Challenge::dataDragon() const
{
    return mDataDragon;
}

LCU::GameflowState Challenge::currentGameflowState() const
{
    return mCurrentGameflowState;
}

void Challenge::currentGameflowStateUpdate()
{
    if (mLCU->isConnected()) {
        mLCU->getGameflowState([this](LCU::GameflowState state, int err, QString errStr){
            if (err == 0) {
                setCurrentGameflowState(state);

            } else {
                qWarning() << "Challenge::currentGameflowStateUpdate - lcu client error :" << err << errStr.toStdString().data();
            }
        });
    } else {
        setCurrentGameflowState(LCU::None);
    }
    QTimer::singleShot(1500, this, &Challenge::currentGameflowStateUpdate);
}

void Challenge::currentSummonerUpdate()
{
    if (mLCU->isConnected()) {
        mLCU->getCurrentSummoner([this](const QJsonObject &summoner, int err, QString errStr){
            if (err == 0) {
                QString name = summoner["displayName"].toString();
                setCurrentSummoner(summoner);

            } else {
                qWarning() << "Challenge::currentSummonerUpdate - lcu client error :" << err << errStr.toStdString().data();
            }
        });
    } else {
        setCurrentSummoner(QJsonObject());
    }
    QTimer::singleShot(3000, this, &Challenge::currentSummonerUpdate);
}

void Challenge::setCurrentGameflowState(const LCU::GameflowState &currentGameflowState)
{
    if (mCurrentGameflowState != currentGameflowState) {
        mCurrentGameflowState = currentGameflowState;
        qInfo() << "currentGameflowStateChanged :" << currentGameflowState;
        emit currentGameflowStateChanged();
    }
}

QJsonObject Challenge::currentSummoner() const
{
    return mCurrentSummoner;
}

void Challenge::setCurrentSummoner(const QJsonObject &currentSummoner)
{
    if (mCurrentSummoner != currentSummoner) {
        mCurrentSummoner = currentSummoner;
        qInfo() << "currentSummonerName :" << currentSummoner;
        emit currentSummonerChanged();
    }
}

ObserverFileManager *Challenge::observerFileManager() const
{
    return mObserverFileManager;
}
