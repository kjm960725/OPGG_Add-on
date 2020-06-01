#ifndef DATADRAGON_H
#define DATADRAGON_H

#include <QObject>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariant>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QIODevice>
#include <QNetworkRequest>

// api reference : https://developer.riotgames.com/docs/lol#data-dragon
// this library is support the local based API.
namespace riot {

class DataDragon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString version READ version NOTIFY versionChanged)
    Q_PROPERTY(Language language READ language WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QJsonObject allChampionsInfo READ allChampionsInfo NOTIFY allChampionsInfoChanged)
    Q_PROPERTY(QJsonObject allChampionsDetailInfo READ allChampionsDetailInfo NOTIFY allChampionsDetailInfoChanged)
    Q_PROPERTY(QJsonObject allItemsInfo READ allItemsInfo NOTIFY allItemsInfoChanged)
    Q_PROPERTY(QJsonObject allSummonerSpellsInfo READ allSummonerSpellsInfo NOTIFY allSummonerSpellsInfoChanged)
    Q_PROPERTY(QJsonArray allRunesInfo READ allRunesInfo NOTIFY allRunesInfoChanged)
    Q_PROPERTY(QJsonObject allProfileiconsInfo READ allProfileiconsInfo NOTIFY allProfileiconsInfoChanged)
    Q_PROPERTY(QJsonObject allMissionAssetsInfo READ allMissionAssetsInfo NOTIFY allMissionAssetsInfoChanged)
    Q_PROPERTY(QJsonObject allMapsInfo READ allMapsInfo NOTIFY allMapsInfoChanged)

    Q_PROPERTY(QString getChampionIconDirPath READ getChampionIconDirPath NOTIFY versionChanged)
public:
    enum Language {
        ko_KR = 0, // Korean (Korea) [Default]
        cs_CZ , // Czech (Czech Republic)
        el_GR , // Greek (Greece)
        pl_PL , // Polish (Poland)
        ro_RO , // Romanian (Romania)
        hu_HU , // Hungarian (Hungary)
        en_GB , // English (United Kingdom)
        de_DE , // German (Germany)
        es_ES , // Spanish (Spain)
        it_IT , // Italian (Italy)
        fr_FR , // French (France)
        ja_JP , // Japanese (Japan)
        es_MX , // Spanish (Mexico)
        es_AR , // Spanish (Argentina)
        pt_BR , // Portuguese (Brazil)
        en_US , // English (United States)
        en_AU , // English (Australia)
        ru_RU , // Russian (Russia)
        tr_TR , // Turkish (Turkey)
        ms_MY , // Malay (Malaysia)
        en_PH , // English (Republic of the Philippines)
        en_SG , // English (Singapore)
        th_TH , // Thai (Thailand)
        vn_VN , // Vietnamese (Viet Nam)
        id_ID , // Indonesian (Indonesia)
        zh_MY , // Chinese (Malaysia)
        zh_CN , // Chinese (China)
        zh_TW , // Chinese (Taiwan)
    };
    Q_ENUM(Language)

    // Setting only the flag to use reduces the load time.
    enum UseDataFlag {
        All             = 0x0FFFFFFF , // Default
        Nothing         = 0x00000000 ,
        Champions       = 0x00000001 ,
        ChampionsDetail = 0x00000002 ,
        Items           = 0x00000004 ,
        SummonerSpells  = 0x00000008 ,
        Runes           = 0x00000010 ,
        Profileicons    = 0x00000020 ,
        MissionAssets   = 0x00000040 ,
        Maps            = 0x00000080 ,
    };
    Q_ENUM(UseDataFlag)

    explicit DataDragon(UseDataFlag = All, QObject *parent = nullptr);
    explicit DataDragon(QNetworkAccessManager *client, UseDataFlag = All, QObject *parent = nullptr);
    explicit DataDragon(QNetworkAccessManager *client, Language language, UseDataFlag = All, QObject *parent = nullptr);

    void setClinet(QNetworkAccessManager *clinet);

    void dataDragonVersionCheck(std::function<void(int, QString)>finishedCallback);

    // DataDragon version
    QString version() const;

    // default language
    Language language() const;
    void setLanguage(Language language);

    // get info from member (memory)
    QJsonObject allChampionsInfo() const { return mAllChampionsInfo; }
    QJsonObject allChampionsDetailInfo() const { return mAllChampionsDetailInfo; }
    QJsonObject allItemsInfo() const { return mAllItemsInfo; }
    QJsonObject allSummonerSpellsInfo() const { return mAllSummonerSpellsInfo; }
    QJsonArray allRunesInfo() const { return mAllRunesInfo; }
    QJsonObject allProfileiconsInfo() const { return mAllProfileicnonsInfo; }
    QJsonObject allMissionAssetsInfo() const { return mAllMissionAssetsInfo; }
    QJsonObject allMapsInfo() const { return mAllMapsInfo; }

    Q_INVOKABLE static QString getDataDragonPath();
    Q_INVOKABLE QJsonObject getChampByKey(int key) const;

    // get champion image file path
    QString getChampionIconDirPath() const;
    Q_INVOKABLE QString getChampionIconPath(const QString &championName) const;
    Q_INVOKABLE QString getChampionLoadingImagePath(const QString &championName, int skinNum = 0) const;
    Q_INVOKABLE QString getChampionSplashImagePath(const QString &championName, int skinNum = 0) const;
    Q_INVOKABLE QString getChampionTilesImagePath(const QString &championName, int skinNum = 0) const;

signals:
    void versionChanged();
    void languageChanged();
    void allChampionsInfoChanged();
    void allChampionsDetailInfoChanged();
    void allItemsInfoChanged();
    void allSummonerSpellsInfoChanged();
    void allRunesInfoChanged();
    void allProfileiconsInfoChanged();
    void allMissionAssetsInfoChanged();
    void allMapsInfoChanged();

private:
    QString mVersion;
    void setVersion(const QString &version);

    void getAllChampionsInfo(const QString &version, Language language, std::function<void(const QJsonObject &)>callback) ;
    void getAllChampionsDetailInfo(const QString &version, Language language, std::function<void(const QJsonObject &)>callback);
    void getAllItemsInfo(const QString &version, Language language, std::function<void(const QJsonObject &)>callback);
    void getAllSummonerSpellsInfo(const QString &version, Language language, std::function<void(const QJsonObject &)>callback);
    void getAllRunesInfo(const QString &version, Language language, std::function<void(const QJsonArray &)>callback);
    void getAllProfileiconsInfo(const QString &version, Language language, std::function<void(const QJsonObject &)>callback);
    void getAllMissionAssetsInfo(const QString &version, Language language, std::function<void(const QJsonObject &)>callback);
    void getAllMapsInfo(const QString &version, Language language, std::function<void(const QJsonObject &)>callback);

    UseDataFlag mUseMemberFlag = All;

    QNetworkAccessManager *mClinet = nullptr;

    QJsonObject mAllChampionsDetailInfo;
    void setAllChampionsDetailInfo(const QJsonObject &allChampionsDetailInfo);

    QJsonObject mAllChampionsInfo;
    void setAllChampionsInfo(const QJsonObject &allChampionsInfo);

    QJsonObject mAllItemsInfo;
    void setAllItemsInfo(const QJsonObject &allItemsInfo);

    QJsonObject mAllSummonerSpellsInfo;
    void setAllSummonerSpellsInfo(const QJsonObject &allSummonerSpellsInfo);

    QJsonArray mAllRunesInfo;
    void setAllRunesInfo(const QJsonArray &allRunesInfo);

    QJsonObject mAllProfileicnonsInfo;
    void setAllProfileiconfsInfo(const QJsonObject &allProfileiconfs);

    QJsonObject mAllMissionAssetsInfo;
    void setAllMissionAssetsInfo(const QJsonObject &allMissionAssetsInfo);

    QJsonObject mAllMapsInfo;
    void setAllMapsInfo(const QJsonObject &allMapsInfo);

    static QString getLanguageString(Language language);

    void initDataDragon();

    void getNewestVersion(std::function<void(QString, int, QString)>VersionAndErrAndErrStr) const;
    void getAllVersions(std::function<void(const QJsonArray &, int, QString)>VersionsAndErrAndErrStr) const;




    // ----- 아래 함수는 삭제 예정 -----------

    // donwload DataDragon.tgz
    void getDataDragon(const QString &version, const QString &downlaodPath,
                       std::function<void(int, QString)>errAndErrStr, std::function<void(qreal)>progrecessCallback = nullptr) const;
    void getDataDragon(const QString &version, QIODevice *downlaodDevice,
                       std::function<void(int, QString)>errAndErrStr, std::function<void(qreal)>progrecessCallback = nullptr) const;

    // unzip .tgz file
    void extrackDataDragon(const QString &fileName, std::function<void(bool)>successed) const;
};
}
#endif // DATADRAGON_H
