#ifndef LCU_H
#define LCU_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QThread>
#include <QMutex>
#include <QJsonArray>
#include <QJsonObject>
#include <QJSEngine>

namespace riot {
class LCU : public QThread
{
    Q_OBJECT
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY isConnectedChanged)
    Q_PROPERTY(ConnectionError error READ error NOTIFY errorChanged)
public:
    explicit LCU(QObject *parent = nullptr);
    explicit LCU(QNetworkAccessManager *client, QObject *parent = nullptr);
    virtual ~LCU() override;

    enum ConnectionError {
        NoError,
        NotRunningLeagueClient,
        LackOfAuthority,
        NotFoundLockfile,
        LockfileOpenFailed,
        LockfileParseError
    };
    Q_ENUM(ConnectionError)

    enum GameflowState {
        None,
        Lobby,
        Matchmaking,
        ReadyCheck,
        ChampSelect,
        InProgress,
        Reconnect,
        WaitingForStats,
        EndOfGame,
        PreEndOfGame,
    };
    Q_ENUM(GameflowState)

    void setJSEngine(QJSEngine *jSEngine); // QML 에서 호출시 사용
    QJSValue convertToJSValue(const QJsonValue &val) const;

    QString lcuPort() const;
    QString lcuPassword() const;

    bool isConnected() const;
    ConnectionError error() const;

    QNetworkAccessManager *client() const;
    void setClient(QNetworkAccessManager *client);

    // 픽창의 픽(밴픽) 현황 상태값
    void getChampSelectSession(std::function<void(const QJsonObject &, int, QString)>sessionAndErrAndErrStr);
    Q_INVOKABLE void getChampSelectSession(const QJSValue &js);

    // LCU의 accountId와 summonorId는 RiotAPI와는 전혀 별개의 값이다. (RiotAPI는 Hash로 암호화된 데이터로 예상)
    void getCurrentSummoner(std::function<void(const QJsonObject &, int, QString)>summonerAndErrAndErrStr);

    void getSummonersByIds(const QList<int> &summonerIds, std::function<void(const QJsonArray &, int, QString)>summonersAndErrAndErrStr);
    Q_INVOKABLE void getSummonersByIds(const QList<int> &ids, const QJSValue &js);

    // 현재 실행중인 LeagueClient의 국가 코드
    void getClientRegion(std::function<void(const QJsonObject &, int, QString)>regionAndErrAndErrStr);
    Q_INVOKABLE void getClientRegion(const QJSValue &callback);

    // 현재 로비(큐 잡기 직전)의 상태
    void getLobby(std::function<void(const QJsonObject &, int, QString)>lobbyAndErrAndErrStr);

    // 큐 잡는 화면 상태값 or 제어
    void getMatchSearch(std::function<void(const QJsonObject &, int, QString)>matchmakingAndErrAndErrStr);
//    void postMatchReadyDecline(std::function<void(int, QString)>errAndErrStr); //POST /lol-matchmaking/v1/ready-check/accept
//    void postMatchReadyAccept(std::function<void(int, QString)>errAndErrStr); //POST /lol-matchmaking/v1/ready-check/decline


    // 현재 진행중인 게임 상태값
    void getGameflowState(std::function<void(GameflowState, int, QString)>stateAndErrAndErrStr);
    void getGameSession(std::function<void(const QJsonObject &, int, QString)>sessionAndErrAndErrStr);
    Q_INVOKABLE void getGameSession(const QJSValue &js);


    // 룬 페이지 제어
    void getPerksAllPages(std::function<void(const QJsonArray &, int, QString)>pagesAndErrAndErrStr);
    void postPerksPage(const QJsonObject &page, std::function<void(const QJsonObject &,int, QString)>pageErrAndErrStr);
    void putPerkPage(int id, const QJsonObject &page, std::function<void(int,QString)>errAndErrStr);
    void getPerkInventory(std::function<void(int, int, QString)>inventoryCountAndErrAndErrStr);
    void delPerkPage(int id, std::function<void(int,QString)>errAndErrStr);

    // OP.GG 전용
    Q_INVOKABLE void putPerkPage(const QJsonObject &page, const QJSValue &js);


signals:
    void errorChanged();
    void connected();
    void disconnected();
    void isConnectedChanged();
    void errorOccurred();

private:
    void get(const QString &path, std::function<void(const QByteArray &, int, QString)>callback) const;
    void put(const QString &path, const QJsonDocument &body, std::function<void(const QByteArray &, int, QString)>callback) const;
    void post(const QString &path, const QJsonDocument &body, std::function<void(const QByteArray &, int, QString)>callback) const;
    void del(const QString &path, std::function<void(const QByteArray &, int, QString)>callback) const;

    void run() override;
    bool mThreadQuit = false;

    static void dealay(int msec);
    static QByteArray getProcessCommandLine(const QString &name);
    static QByteArray createAuthorizationHeader(const QString &password);
    static bool isRunningProcessByWMIC(const QByteArray &data);
    static QMap<QString,QString> parseCommandLineByWMIC(const QByteArray &data);

    mutable QMutex mMutex;
    void setConnected(bool isConnected, const QString &port, const QString &password, ConnectionError error);
    QNetworkAccessManager *mClient = nullptr;
    ConnectionError mError = NoError;
    bool mIsConnected = false;

    QString mLCUPort;
    QString mLCUPassword;

    QJSEngine *mJSEngine = nullptr;

    template <typename T>
    static QJsonArray listToArr(const QList<T> &list)
    {
        QJsonArray result;
        for (auto val : list) result.append(val);
        return result;
    }

    template <typename T>
    static QList<T> arrToList(const QJsonArray &arr)
    {
        QList<T> result;
        for (auto val : arr) result.append(static_cast<T>(val.toObject()));
        return result;
    }
};
}

#endif // LCU_H
