#include "challenge.h"
#include <QUrlQuery>
#include <QTextCodec>
#include "lcu.h"
#include "datadragon.h"
#include "riot.h"
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

void Challenge::getChampRateByOPGG(const QString &summonerName, const QJSValue &_callback) const
{
    qInfo() << QString("Challenge::getChampRateByOPGG called (arg:%1)").arg(summonerName);
    auto codec = QTextCodec::codecForLocale();
    auto callback = new QJSValue(_callback);
    QString url = QString("https://www.op.gg/summoner/champions/userName=%1")
            .arg(codec->toUnicode(summonerName.toLocal8Bit()));
    auto reply = mClient->get(QNetworkRequest(QUrl(url)));
    reply->ignoreSslErrors();
    connect(reply, &QNetworkReply::finished, this, [this, callback, reply](){
        QJsonObject result;
        reply->deleteLater();

        try {
            if (reply->error() != QNetworkReply::NoError) {
                qWarning() << "Challenge::getChampRateByOPGG network error :" << reply->error() << reply->errorString();
                throw 0;
            }

            auto doc = QGumboDocument::parse(reply->readAll());
            auto root = doc.rootNode();

            auto tableBodyNodes = root.getElementsByTagName(HtmlTag::TBODY);
            if (tableBodyNodes.size() < 1) throw 1;

            auto rows = tableBodyNodes.front().getElementsByTagName(HtmlTag::TR);
            if (rows.size() < 1) throw 2;
            QJsonArray array;
            for (uint i = 0; i < rows.size(); ++i)
            {
                auto row = rows.at(i);
                QJsonObject object;
                auto champNameNodes = row.getElementsByClassName("ChampionName");
                if (champNameNodes.size() < 1) throw 3;

                auto rateNodes = row.getElementsByClassName("RatioGraph");
                if (rateNodes.size() < 1) throw 4;

                auto winLoseNodes = rateNodes.front().getElementsByClassName("Text");
                if (winLoseNodes.size() < 1) throw 5;

                auto kdaNodes = row.getElementsByClassName("KDA");
                if (kdaNodes.size() < 1) throw 6;

                auto champHrefNodes = champNameNodes.front().getElementsByTagName(HtmlTag::A);
                if (champHrefNodes.size() < 1) throw 7;

                QStringList href = champHrefNodes.front().getAttribute("href").split("/",QString::SkipEmptyParts);
                if (href.count() < 2) throw 8;

                object["id"] = href.at(1);
                object["name"] = champNameNodes.front().getAttribute("data-value");
                object["win"] = 0;
                object["lose"] = 0;
                for (auto winLoseNode : winLoseNodes) {
                    int num = winLoseNode.innerText().remove(QRegExp("[^0-9]")).toInt();
                    if (winLoseNode.classList().contains("Left"))
                        object["win"] = num;
                    else if (winLoseNode.classList().contains("Right"))
                        object["lose"] = num;
                }
                object["kda"] = kdaNodes.front().getAttribute("data-value");
                object["most"] = int(i + 1);

                array << object;
            }
            result["data"] = array;
            result["success"] = true;

        } catch (int exceiption) {
            result["data"] = QJsonValue(QJsonValue::Null);
            result["success"] = false;
            qDebug() << "Challenge::getChampRateByOPGG throwed :" << exceiption;
        }

        if (callback->isCallable())
            callback->call(QJSValueList() << JsonObject::convertToJSValue(mJSEngine,result));
        delete callback;
    });
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
