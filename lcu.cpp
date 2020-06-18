#include "lcu.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QCommandLineParser>
#include <QTimer>
#include <QDir>
#include <QFile>
#include <QEventLoop>
using namespace riot;

LCU::LCU(QObject *parent) : QThread(parent)
{

}

LCU::LCU(QNetworkAccessManager *client, QObject *parent)
    : QThread(parent)
    , mClient(client)
{

}

LCU::~LCU()
{
    mThreadQuit = true;
    this->quit();
    this->wait(10000);
    if (this->isFinished()) {
        qInfo() << "LCU finish successfuly";
    } else {
        qWarning() << "LCU finish failed";
    }
}

QJSValue LCU::convertToJSValue(const QJsonValue &val) const
{
    if (mJSEngine == nullptr) {
        qWarning() << "JSEngine을 먼저 설정해야합니다.";
        return QJSValue();
    }
    if (val.isBool())
    {
        return QJSValue(val.toBool());
    }
    else if (val.isString())
    {
        return QJSValue(val.toString());
    }
    else if (val.isDouble())
    {
        return QJSValue(val.toDouble());
    }
    else if (val.isNull())
    {
        return QJSValue(QJSValue::NullValue);
    }
    else if (val.isUndefined())
    {
        return QJSValue(QJSValue::UndefinedValue);
    }
    else if (val.isObject())
    {
        QJsonObject obj = val.toObject();
        if (obj.isEmpty())
            return QJSValue(QJSValue::NullValue);
        QJSValue newobj = mJSEngine->newObject();
        for (auto itor = obj.begin(); itor != obj.end(); itor++)
        {
            QString key = itor.key();
            QJsonValue value = itor.value();
            QJSValue convertedValue = convertToJSValue(value);
            newobj.setProperty(key, convertedValue);
        }
        return newobj;
    }
    else if (val.isArray())
    {
        QJsonArray arr = val.toArray();
        if (arr.isEmpty())
            return QJSValue(QJSValue::NullValue);
        QJSValue newobj = mJSEngine->newArray(uint(arr.size()));
        for (int i = 0; i < arr.size(); i++)
        {
            QJsonValue value = arr[i];
            QJSValue convertedValue = convertToJSValue(value);
            newobj.setProperty(quint32(i), convertedValue);
        }
        return newobj;
    }
    return QJSValue(QJSValue::UndefinedValue);
}

QNetworkAccessManager *LCU::client() const
{
    return mClient;
}

void LCU::setClient(QNetworkAccessManager *client)
{
    mClient = client;
}

void LCU::getChampSelectSession(std::function<void (const QJsonObject &, int, QString)> sessionAndErrAndErrStr)
{
    get("/lol-champ-select/v1/session",[sessionAndErrAndErrStr](const QByteArray &read, int err, QString errStr){
        QJsonObject session = QJsonDocument::fromJson(read).object();
        sessionAndErrAndErrStr(session, session.isEmpty() ? err : 0, session.isEmpty() ? errStr : "");
    });
}

void LCU::getChampSelectSession(const QJSValue &js)
{
    QJSValue *callback = new QJSValue(js);
    getChampSelectSession([this,callback](const QJsonObject &obj, int err, QString errStr){
        callback->call(QJSValueList() << convertToJSValue(obj) << err << errStr);
        delete callback;
    });
}

void LCU::getCurrentSummoner(std::function<void (const QJsonObject &, int, QString)> summonerAndErrAndErrStr)
{
    get("/lol-summoner/v1/current-summoner",[summonerAndErrAndErrStr](const QByteArray &read, int err, QString errStr){
        QJsonObject summoner = QJsonDocument::fromJson(read).object();
        summonerAndErrAndErrStr(summoner, summoner.isEmpty() ? err : 0, summoner.isEmpty() ? errStr : "");
    });
    //    {
    //      "accountId": 0,
    //      "displayName": "string",
    //      "internalName": "string",
    //      "percentCompleteForNextLevel": 0,
    //      "profileIconId": 0,
    //      "puuid": "string",
    //      "rerollPoints": {
    //        "currentPoints": 0,
    //        "maxRolls": 0,
    //        "numberOfRolls": 0,
    //        "pointsCostToRoll": 0,
    //        "pointsToReroll": 0
    //      },
    //      "summonerId": 0,
    //      "summonerLevel": 0,
    //      "xpSinceLastLevel": 0,
    //      "xpUntilNextLevel": 0
    //    }
}

void LCU::getSummonersByIds(const QList<int> &summonerIds, std::function<void(const QJsonArray &, int, QString)>summonersAndErrAndErrStr)
{
    QJsonArray arr = listToArr(summonerIds);
    QByteArray ids = QJsonDocument(arr).toJson(QJsonDocument::Compact);
    QString url = QString("/lol-summoner/v2/summoner-names?ids=%1").arg(QString(ids));
    get(url, [summonersAndErrAndErrStr](const QByteArray &read, int err, QString errStr){
        QJsonArray summoner = QJsonDocument::fromJson(read).array();
        summonersAndErrAndErrStr(summoner, summoner.isEmpty() ? err : 0, summoner.isEmpty() ? errStr : "");
    });
}

void LCU::getSummonersByIds(const QList<int> &ids, const QJSValue &js)
{
    QJSValue *callback = new QJSValue(js);
    getSummonersByIds(ids, [this,callback](const QJsonArray &arr, int err, QString errStr){
        callback->call(QJSValueList() << convertToJSValue(arr) << err << errStr);
        delete callback;
    });
}

void LCU::getClientRegion(std::function<void (const QJsonObject &, int, QString)> regionAndErrAndErrStr)
{
    get("/riotclient/region-locale",[regionAndErrAndErrStr](const QByteArray &read, int err, QString errStr){
        QJsonObject region = QJsonDocument::fromJson(read).object();
        regionAndErrAndErrStr(region, region.isEmpty() ? err : 0, region.isEmpty() ? errStr : "");
    });
    //{
    //   "locale": "string",
    //   "region": "string",
    //   "webLanguage": "string",
    //   "webRegion": "string"
    //}
}

void LCU::getClientRegion(const QJSValue &_callback)
{
    QJSValue *callback = new QJSValue(_callback);
    getClientRegion([this,callback](const QJsonObject &obj, int err, QString errStr){
        callback->call(QJSValueList() << convertToJSValue(obj) << err << errStr);
        delete callback;
    });
}

void LCU::getLobby(std::function<void (const QJsonObject &, int, QString)> lobbyAndErrAndErrStr)
{
    get("/lol-lobby/v2/lobby",[lobbyAndErrAndErrStr](const QByteArray &read, int err, QString errStr){
        QJsonObject lobby = QJsonDocument::fromJson(read).object();
        lobbyAndErrAndErrStr(lobby, lobby.isEmpty() ? err : 0, lobby.isEmpty() ? errStr : "");
    });
//    {
//      "canStartActivity": true,
//      "chatRoomId": "string",
//      "chatRoomKey": "string",
//      "gameConfig": {
//        "allowablePremadeSizes": [
//          0
//        ],
//        "customLobbyName": "string",
//        "customMutatorName": "string",
//        "customRewardsDisabledReasons": [
//          "string"
//        ],
//        "customSpectatorPolicy": "NotAllowed",
//        "customSpectators": [
//          {
//            "allowedChangeActivity": true,
//            "allowedInviteOthers": true,
//            "allowedKickOthers": true,
//            "allowedStartActivity": true,
//            "allowedToggleInvite": true,
//            "autoFillEligible": true,
//            "autoFillProtectedForPromos": true,
//            "autoFillProtectedForSoloing": true,
//            "autoFillProtectedForStreaking": true,
//            "botChampionId": 0,
//            "botDifficulty": "NONE",
//            "botId": "string",
//            "firstPositionPreference": "string",
//            "isBot": true,
//            "isLeader": true,
//            "isSpectator": true,
//            "puuid": "string",
//            "ready": true,
//            "secondPositionPreference": "string",
//            "showGhostedBanner": true,
//            "summonerIconId": 0,
//            "summonerId": 0,
//            "summonerInternalName": "string",
//            "summonerLevel": 0,
//            "summonerName": "string",
//            "teamId": 0
//          }
//        ],
//        "customTeam100": [
//          {
//            "allowedChangeActivity": true,
//            "allowedInviteOthers": true,
//            "allowedKickOthers": true,
//            "allowedStartActivity": true,
//            "allowedToggleInvite": true,
//            "autoFillEligible": true,
//            "autoFillProtectedForPromos": true,
//            "autoFillProtectedForSoloing": true,
//            "autoFillProtectedForStreaking": true,
//            "botChampionId": 0,
//            "botDifficulty": "NONE",
//            "botId": "string",
//            "firstPositionPreference": "string",
//            "isBot": true,
//            "isLeader": true,
//            "isSpectator": true,
//            "puuid": "string",
//            "ready": true,
//            "secondPositionPreference": "string",
//            "showGhostedBanner": true,
//            "summonerIconId": 0,
//            "summonerId": 0,
//            "summonerInternalName": "string",
//            "summonerLevel": 0,
//            "summonerName": "string",
//            "teamId": 0
//          }
//        ],
//        "customTeam200": [
//          {
//            "allowedChangeActivity": true,
//            "allowedInviteOthers": true,
//            "allowedKickOthers": true,
//            "allowedStartActivity": true,
//            "allowedToggleInvite": true,
//            "autoFillEligible": true,
//            "autoFillProtectedForPromos": true,
//            "autoFillProtectedForSoloing": true,
//            "autoFillProtectedForStreaking": true,
//            "botChampionId": 0,
//            "botDifficulty": "NONE",
//            "botId": "string",
//            "firstPositionPreference": "string",
//            "isBot": true,
//            "isLeader": true,
//            "isSpectator": true,
//            "puuid": "string",
//            "ready": true,
//            "secondPositionPreference": "string",
//            "showGhostedBanner": true,
//            "summonerIconId": 0,
//            "summonerId": 0,
//            "summonerInternalName": "string",
//            "summonerLevel": 0,
//            "summonerName": "string",
//            "teamId": 0
//          }
//        ],
//        "gameMode": "string",
//        "isCustom": true,
//        "isLobbyFull": true,
//        "isTeamBuilderManaged": true,
//        "mapId": 0,
//        "maxHumanPlayers": 0,
//        "maxLobbySize": 0,
//        "maxTeamSize": 0,
//        "pickType": "string",
//        "premadeSizeAllowed": true,
//        "queueId": 0,
//        "showPositionSelector": true
//      },
//      "invitations": [
//        {
//          "invitationId": "string",
//          "state": "Requested",
//          "timestamp": "string",
//          "toSummonerId": 0,
//          "toSummonerName": "string"
//        }
//      ],
//      "localMember": {
//        "allowedChangeActivity": true,
//        "allowedInviteOthers": true,
//        "allowedKickOthers": true,
//        "allowedStartActivity": true,
//        "allowedToggleInvite": true,
//        "autoFillEligible": true,
//        "autoFillProtectedForPromos": true,
//        "autoFillProtectedForSoloing": true,
//        "autoFillProtectedForStreaking": true,
//        "botChampionId": 0,
//        "botDifficulty": "NONE",
//        "botId": "string",
//        "firstPositionPreference": "string",
//        "isBot": true,
//        "isLeader": true,
//        "isSpectator": true,
//        "puuid": "string",
//        "ready": true,
//        "secondPositionPreference": "string",
//        "showGhostedBanner": true,
//        "summonerIconId": 0,
//        "summonerId": 0,
//        "summonerInternalName": "string",
//        "summonerLevel": 0,
//        "summonerName": "string",
//        "teamId": 0
//      },
//      "members": [
//        {
//          "allowedChangeActivity": true,
//          "allowedInviteOthers": true,
//          "allowedKickOthers": true,
//          "allowedStartActivity": true,
//          "allowedToggleInvite": true,
//          "autoFillEligible": true,
//          "autoFillProtectedForPromos": true,
//          "autoFillProtectedForSoloing": true,
//          "autoFillProtectedForStreaking": true,
//          "botChampionId": 0,
//          "botDifficulty": "NONE",
//          "botId": "string",
//          "firstPositionPreference": "string",
//          "isBot": true,
//          "isLeader": true,
//          "isSpectator": true,
//          "puuid": "string",
//          "ready": true,
//          "secondPositionPreference": "string",
//          "showGhostedBanner": true,
//          "summonerIconId": 0,
//          "summonerId": 0,
//          "summonerInternalName": "string",
//          "summonerLevel": 0,
//          "summonerName": "string",
//          "teamId": 0
//        }
//      ],
//      "partyId": "string",
//      "partyType": "string",
//      "restrictions": [
//        {
//          "expiredTimestamp": 0,
//          "restrictionArgs": {},
//          "restrictionCode": "QueueDisabled",
//          "summonerIds": [
//            0
//          ],
//          "summonerIdsString": "string"
//        }
//      ]
    //    }
}

void LCU::getMatchSearch(std::function<void (const QJsonObject &, int, QString)> searchAndErrAndErrStr)
{
    get("/lol-matchmaking/v1/search",[searchAndErrAndErrStr](const QByteArray &read, int err, QString errStr){
        QJsonObject search = QJsonDocument::fromJson(read).object();
        searchAndErrAndErrStr(search, search.isEmpty() ? err : 0, search.isEmpty() ? errStr : "");
    });
//    {
//      "dodgeData": {
//        "dodgerId": 0,
//        "state": "Invalid"
//      },
//      "errors": [
//        {
//          "errorType": "string",
//          "id": 0,
//          "message": "string",
//          "penalizedSummonerId": 0,
//          "penaltyTimeRemaining": 0
//        }
//      ],
//      "estimatedQueueTime": 0,
//      "isCurrentlyInQueue": true,
//      "lobbyId": "string",
//      "lowPriorityData": {
//        "bustedLeaverAccessToken": "string",
//        "penalizedSummonerIds": [
//          0
//        ],
//        "penaltyTime": 0,
//        "penaltyTimeRemaining": 0,
//        "reason": "string"
//      },
//      "queueId": 0,
//      "readyCheck": {
//        "declinerIds": [
//          0
//        ],
//        "dodgeWarning": "None",
//        "playerResponse": "None",
//        "state": "Invalid",
//        "suppressUx": true,
//        "timer": 0
//      },
//      "searchState": "Invalid",
//      "timeInQueue": 0
    //    }
}

void LCU::getGameflowState(std::function<void (GameflowState, int, QString)> stateAndErrAndErrStr)
{
    get("/lol-gameflow/v1/gameflow-phase",[stateAndErrAndErrStr](const QByteArray &read, int err, QString errStr){
        QString str = QString(read).toLower().remove(QRegExp("[^a-z]"));
        LCU::GameflowState state = None;
        if      (str == "lobby")           state = Lobby;
        else if (str == "matchmaking")     state = Matchmaking;
        else if (str == "readycheck")      state = ReadyCheck;
        else if (str == "champselect")     state = ChampSelect;
        else if (str == "inprogress")      state = InProgress;
        else if (str == "reconnect")       state = Reconnect;
        else if (str == "waitingforstats") state = WaitingForStats;
        else if (str == "endofgame")       state = EndOfGame;
        else if (str == "preendofgame")    state = PreEndOfGame;
        else if (str == "none")            state = None;
        else {
            qWarning() << "LCU::getGameflowState - undefined state :" << read;
        }
        stateAndErrAndErrStr(state, read.isEmpty() ? err : 0, read.isEmpty() ? errStr : "");
    });
}

void LCU::getGameSession(std::function<void (const QJsonObject &, int, QString)> sessionAndErrAndErrStr)
{
    get("/lol-gameflow/v1/session",[sessionAndErrAndErrStr](const QByteArray &read, int err, QString errStr){
        QJsonObject session = QJsonDocument::fromJson(read).object();
        sessionAndErrAndErrStr(session, session.isEmpty() ? err : 0, session.isEmpty() ? errStr : "");
    });
}

void LCU::getGameSession(const QJSValue &js)
{
    QJSValue *callback = new QJSValue(js);
    getGameSession([this,callback](const QJsonObject &obj, int err, QString errStr){
        callback->call(QJSValueList() << convertToJSValue(obj) << err << errStr);
        delete callback;
    });
}

void LCU::getPerksAllPages(std::function<void (const QJsonArray &, int, QString)> pagesAndErrAndErrStr)
{
    get("/lol-perks/v1/pages",[pagesAndErrAndErrStr](const QByteArray &read, int err, QString errStr){
        QJsonArray json = QJsonDocument::fromJson(read).array();
        pagesAndErrAndErrStr(json, json.isEmpty() ? err : 0, json.isEmpty() ? errStr : "");
    });
}

void LCU::postPerksPage(const QJsonObject &page, std::function<void (const QJsonObject &, int, QString)> pageErrAndErrStr)
{
    post("/lol-perks/v1/pages",QJsonDocument(page),[pageErrAndErrStr](const QByteArray &read, int err, QString errStr){
        QJsonObject json = QJsonDocument::fromJson(read).object();
        pageErrAndErrStr(json, json.isEmpty() ? err : 0, json.isEmpty() ? errStr : "");
    });
}

void LCU::putPerkPage(int id, const QJsonObject &page, std::function<void (int, QString)> errAndErrStr)
{
    put(QString("/lol-perks/v1/pages/%1").arg(QString::number(id)),QJsonDocument(page),[errAndErrStr](const QByteArray &read, int err, QString errStr){
        read.isEmpty();
        errAndErrStr(err,errStr);
    });
}

void LCU::getPerkInventory(std::function<void (int, int, QString)> inventoryCountAndErrAndErrStr)
{
    get("/lol-perks/v1/inventory",[inventoryCountAndErrAndErrStr](const QByteArray &read, int err, QString errStr){
        QJsonObject json = QJsonDocument::fromJson(read).object();
        inventoryCountAndErrAndErrStr(json.value("ownedPageCount").toInt(), json.isEmpty() ? err : 0, json.isEmpty() ? errStr : "");
    });
}

void LCU::delPerkPage(int id, std::function<void (int, QString)> errAndErrStr)
{
    del(QString("/lol-perks/v1/pages/%1").arg(QString::number(id)),[errAndErrStr](const QByteArray &read, int err, QString errStr){
        read.isEmpty();
        errAndErrStr( err,errStr);
    });
}

void LCU::putPerkPage(const QJsonObject &page, const QJSValue &js)
{
    QJSValue *callback = new QJSValue(js);
    getPerksAllPages([this,callback,page](const QJsonArray &arr, int err, QString errStr){
        if (err != 0) {
            callback->call(QJSValueList() << err << errStr);
            delete callback;
            return;
        }
        for (auto val : arr) {
            auto obj = val.toObject();
            int id = obj.value("id").toInt();
            QString name = obj.value("name").toString();
            if (name.toLower().contains("op.gg")) {
                delPerkPage(id, [this,page,callback](int err, QString errStr){
                    if (err != 0) {
                        callback->call(QJSValueList() << err << errStr);
                        delete callback;
                        return;
                    }
                    postPerksPage(page,[callback](const QJsonObject &obj, int err, QString errStr){
                        obj.isEmpty();
                        callback->call(QJSValueList() << err << errStr);
                        delete callback;
                    });
                });
                return;
            }
        }

        getPerkInventory([this,callback,page,arr](int count, int err, QString errStr){
            if (err != 0) {
                callback->call(QJSValueList() << err << errStr);
                delete callback;
                return;
            }
            int curPageCount = 0;
            for (auto val : arr)
                if (val.toObject().value("isDeletable").toBool()) curPageCount++;
            if(curPageCount >= count) {
                callback->call(QJSValueList() << 110 << QString(("Perk pages is full")));
                delete callback;
                return;
            }
            postPerksPage(page,[callback](const QJsonObject &obj, int err, QString errStr){
                obj.isEmpty();
                callback->call(QJSValueList() << err << errStr);
                delete callback;
            });
        });
    });
}

void LCU::run()
{
    while (!mThreadQuit)
    {
        try {
            QString installPath = getLCUPathFromProcess();
            if (installPath.isNull())
                throw NotRunningLeagueClient;

            QDir dir(installPath);
            QStringList dirEntry = dir.entryList(QDir::Files);
            if (!dirEntry.contains("lockfile"))
                throw NotFoundLockfile;

            QFile lockFile(installPath + QDir::separator() + "lockfile");
            if (!lockFile.open(QIODevice::ReadOnly | QIODevice::Text))
                throw LockfileOpenFailed;

            QStringList args = QString(lockFile.readAll()).split(':');
            if (args.count() < 5)
                throw LockfileParseError;

            setConnected(true, args.at(2), args.at(3), NoError);

        } catch (ConnectionError error) {
            setConnected(false, "", "", error);
        }
        dealay(1000);
    }
}

void LCU::get(const QString &path, std::function<void (const QByteArray &, int, QString)> callback) const
{
    QNetworkRequest request(QUrl(QString("https://127.0.0.1:%1%2").arg(lcuPort()).arg(path)));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("Authorization", createAuthorizationHeader(lcuPassword()));
    QNetworkReply *re = mClient->get(request);
    re->ignoreSslErrors();

    connect(re, &QNetworkReply::finished, [re,callback](){
        if (re->error() == QNetworkReply::ContentNotFoundError) {
            callback(QByteArray(), 0, QString());
        } else {
            callback(re->readAll(), re->error(), re->errorString());
        }
        re->deleteLater();
    });
}

void LCU::put(const QString &path, const QJsonDocument &body, std::function<void (const QByteArray &, int, QString)> callback) const
{
    QNetworkRequest request(QUrl(QString("https://127.0.0.1:%1%2").arg(lcuPort()).arg(path)));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("Authorization", createAuthorizationHeader(lcuPassword()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *re = mClient->put(request,body.toJson(QJsonDocument::Compact));
    re->ignoreSslErrors();

    connect(re, &QNetworkReply::finished, [re,callback](){
        re->deleteLater();
        if (re->error() == QNetworkReply::ContentNotFoundError) {
            callback(QByteArray(), 0, QString());
        } else {
            callback(re->readAll(), re->error(), re->errorString());
        }
    });
}

void LCU::post(const QString &path, const QJsonDocument &body, std::function<void (const QByteArray &, int, QString)> callback) const
{
    QNetworkRequest request(QUrl(QString("https://127.0.0.1:%1%2").arg(lcuPort()).arg(path)));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("Authorization", createAuthorizationHeader(lcuPassword()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *re = mClient->post(request,body.toJson(QJsonDocument::Compact));
    re->ignoreSslErrors();

    connect(re, &QNetworkReply::finished, [re,callback](){
        re->deleteLater();
        if (re->error() == QNetworkReply::ContentNotFoundError) {
            callback(QByteArray(), 0, QString());
        } else {
            callback(re->readAll(), re->error(), re->errorString());
        }
    });
}

void LCU::del(const QString &path, std::function<void (const QByteArray &, int, QString)> callback) const
{
    QNetworkRequest request(QUrl(QString("https://127.0.0.1:%1%2").arg(lcuPort()).arg(path)));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("Authorization", createAuthorizationHeader(lcuPassword()));

    QNetworkReply *re = mClient->deleteResource(request);
    re->ignoreSslErrors();

    connect(re, &QNetworkReply::finished, [re,callback](){
        re->deleteLater();
        if (re->error() == QNetworkReply::ContentNotFoundError) {
            callback(QByteArray(), 0, QString());
        } else {
            callback(re->readAll(), re->error(), re->errorString());
        }
    });
}

void LCU::dealay(int msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, &QEventLoop::quit);
    loop.exec();
}

QString LCU::getLCUPathFromProcess()
{
    QProcess process;
    process.start("wmic.exe /OUTPUT:STDOUT PROCESS WHERE name='LeagueClientUx.exe' GET CommandLine");
    process.waitForFinished();

    const QByteArray read = process.readAllStandardOutput();
    QProcess::ExitStatus exitStatus = process.exitStatus();
    int exitCode = process.exitCode();

    if (exitStatus == QProcess::CrashExit) {
        qWarning() << "LCU::getLCUPathFromProcess - wmic crash" << exitCode;
        return QString();
    }

    const QStringList args = QString(read).remove(QRegExp("[\r\n\"]")).split(" --");

    QString installPath;
    const QString findOption = "install-directory=";
    for (auto arg : args) {
        if (arg.contains(findOption)) {
            installPath = QString(arg).remove(findOption).replace("\\","/");
            break;
        }
    }
    return installPath;
}

QByteArray LCU::createAuthorizationHeader(const QString &password)
{
    QString credentials = QString("riot:%2").arg(password);
    QString credentialsBase64 = credentials.toLocal8Bit().toBase64();
    return QString("Basic %1").arg(credentialsBase64).toLocal8Bit();
}

LCU::ConnectionError LCU::error() const
{
    QMutexLocker locker(&mMutex);
    return mError;
}

void LCU::setConnected(bool isConnected, const QString &port, const QString &password, ConnectionError error)
{
    QMutexLocker locker(&mMutex);
    mLCUPort = port;
    mLCUPassword = password;
    if (error != mError) {
        mError = error;
        if (error != NoError)
            QMetaObject::invokeMethod(this, [this](){emit errorOccurred();}, Qt::QueuedConnection);
    }
    if (mIsConnected != isConnected) {
        mIsConnected = isConnected;
        if (isConnected)
            QMetaObject::invokeMethod(this, [this](){emit connected();}, Qt::QueuedConnection);
        else
            QMetaObject::invokeMethod(this, [this](){emit disconnect();}, Qt::QueuedConnection);
        QMetaObject::invokeMethod(this, [this](){emit isConnectedChanged();}, Qt::QueuedConnection);
    }
}

void LCU::setJSEngine(QJSEngine *jSEngine)
{
    mJSEngine = jSEngine;
}

QString LCU::lcuPassword() const
{
    QMutexLocker locker(&mMutex);
    return mLCUPassword;
}

QString LCU::lcuPort() const
{
    QMutexLocker locker(&mMutex);
    return mLCUPort;
}

bool LCU::isConnected() const
{
    QMutexLocker locker(&mMutex);
    return mIsConnected;
}
