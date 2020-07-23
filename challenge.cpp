#include "challenge.h"
#include <QCoreApplication>
#include <QCursor>
#include "webscrapforopgg.h"
#include <QDir>
#include <QUrlQuery>
#include <QStandardPaths>
#include <QTextCodec>
#include "lcu.h"
#include "datadragon.h"
#include "riot.h"
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <QElapsedTimer>
#include <iostream>
#include <GumboParser>
using namespace riot;

Challenge::Challenge(QObject *parent) : QObject(parent)
{
    init();
}

Challenge::Challenge(QJSEngine *engine, QObject *parent) : QObject(parent)
{
    init();
    mJSEngine = engine;
    mRiot->setJSEngine(engine);
    mLCU->setJSEngine(engine);
    mWebScrapForOPGG->setJSEngine(engine);
}

QString Challenge::readFile(const QString &path)
{
    QString result;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Challenge::readFile error : open file failed" << file.error() << file.errorString();
    }
    result = file.readAll();
    return result;
}

bool Challenge::clearWebCache()
{
    QString path = QString("%1/%2")
            .arg(QStandardPaths::writableLocation(QStandardPaths::CacheLocation)).arg("cache")
            .replace("/","\\");
    QDir dir(path);
    return dir.removeRecursively();
}

bool Challenge::clearWebCookie()
{
    QString path = QString("%1/%2")
            .arg(QStandardPaths::writableLocation(QStandardPaths::DataLocation)).arg("QtWebEngine")
            .replace("\\","/");
    QDir dir(path);
    return dir.removeRecursively();
}

QPoint Challenge::getMousePos()
{
    return QCursor::pos();
}

void Challenge::restartAdministrator()
{
    QProcess::startDetached(QString("powershell -Command \"Start-Process '%1' -Verb runAs\"").arg(qApp->applicationFilePath().replace("/","\\")));
    qApp->quit();
}

void Challenge::init()
{
    mUpdateTool = new UpdateTool(this);
    mClient = new QNetworkAccessManager(this);
    mRiot = new Riot(mClient, "{API-KEY}", this);
    mDataDragon = new DataDragon(mClient, DataDragon::ko_KR, DataDragon::All, this);
    mLCU = new LCU(mClient, this);
    mObserverFileManager = new ObserverFileManager(this);
    mWebScrapForOPGG = new WebScrapForOPGG(mClient, this);

    currentGameflowStateUpdate();
    currentSummonerUpdate();

    connect(mLCU, &LCU::connected, [=](){ qInfo() << "League cleint connected"; });
    connect(mLCU, &LCU::disconnected, [=](){ qInfo() << "League cleint disconnected"; });

    mLCU->start();
    mUpdateTool->updateCheckTimerStart(60000);
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

WebScrapForOPGG *Challenge::webScrapForOPGG() const
{
    return mWebScrapForOPGG;
}

UpdateTool *Challenge::updateTool() const
{
    return mUpdateTool;
}

ObserverFileManager *Challenge::observerFileManager() const
{
    return mObserverFileManager;
}
