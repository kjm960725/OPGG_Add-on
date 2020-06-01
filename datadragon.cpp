#include "datadragon.h"
#include <QMetaEnum>
#include <QTimer>
#include <QDir>
#include <QNetworkReply>
#include <QSettings>
#include <QGuiApplication>
#include <QProcess>
#include <QFile>
#include <QStandardPaths>
#include <QNetworkAccessManager>

using namespace riot;

DataDragon::DataDragon(UseDataFlag flag, QObject *parent)
    : QObject(parent)
    , mUseMemberFlag(flag)
{
    dataDragonVersionCheck([=](int err, QString errStr){err = 0; errStr = "";});
}

DataDragon::DataDragon(QNetworkAccessManager *client, UseDataFlag flag, QObject *parent)
    : QObject(parent)
    , mUseMemberFlag(flag)
    , mClinet(client)
{
    dataDragonVersionCheck([=](int err, QString errStr){err = 0; errStr = "";});
}

DataDragon::DataDragon(QNetworkAccessManager *client, DataDragon::Language language, UseDataFlag flag, QObject *parent)
    : QObject(parent)
    , mUseMemberFlag(flag)
    , mClinet(client)
{
    setLanguage(language);
    dataDragonVersionCheck([=](int err, QString errStr){err = 0; errStr = "";});
}

void DataDragon::dataDragonVersionCheck(std::function<void(int, QString)>finishedCallback)
{
    getNewestVersion([this, finishedCallback](QString version, int err, QString errStr){
        if (err != 0) {
            qWarning() << "DataDragon::dataDragonVersionCheck failed  (retry after 2sec) :" << err << errStr;
            QTimer::singleShot(2000, this,[this, finishedCallback](){dataDragonVersionCheck(finishedCallback);});
            return;
        }
        qInfo() << QString("DataDragon::dataDragonVersionCheck - version:%1").arg(version).toStdString().data();
        this->setVersion(version);
        finishedCallback(0, "");
    });
}

QString DataDragon::getLanguageString(DataDragon::Language language)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<DataDragon::Language>();
    QString str = metaEnum.key(language);
    str[0] = str.at(0).toLower();
    return str;
}

void DataDragon::getAllChampionsInfo(const QString &version, DataDragon::Language language, std::function<void(const QJsonObject &)>callback)
{
    QNetworkRequest request(QUrl(getDataDragonPath() + QString("/%1/data/%2/champion.json")
                                 .arg(version).arg(getLanguageString(language))));
    auto *re = mClinet->get(request);
    connect(re, &QNetworkReply::finished, [this,version,language,re,callback](){
        if (re->error() != QNetworkReply::NoError) {
            qWarning() << "DataDragon::getAllChampionsInfo - network reqeust error (retry after 5sec) - "  << re->error() << re->errorString();
            QTimer::singleShot(5000, [this,version,language,callback](){ this->getAllChampionsInfo(version, language, callback); });
            return;
        }
        callback(QJsonDocument::fromJson(re->readAll()).object().value("data").toObject());
    });
}

void DataDragon::getAllChampionsDetailInfo(const QString &version, DataDragon::Language language, std::function<void(const QJsonObject &)>callback)
{
    QNetworkRequest request(QUrl(getDataDragonPath() + QString("/%1/data/%2/championFull.json")
                                 .arg(version).arg(getLanguageString(language))));
    auto *re = mClinet->get(request);
    connect(re, &QNetworkReply::finished, [re,callback,this,version,language](){
        if (re->error() != QNetworkReply::NoError) {
            qWarning() << "DataDragon::getAllChampionsDetailInfo - network reqeust error (retry after 5sec) - "  << re->error() << re->errorString();
            QTimer::singleShot(5000, [this,version,language,callback](){ this->getAllChampionsDetailInfo(version, language, callback); });
            return;
        }
        callback(QJsonDocument::fromJson(re->readAll()).object().value("data").toObject());
    });
}

void DataDragon::getAllItemsInfo(const QString &version, DataDragon::Language language, std::function<void(const QJsonObject &)>callback)
{
    QNetworkRequest request(QUrl(getDataDragonPath() + QString("/%1/data/%2/item.json")
                                 .arg(version).arg(getLanguageString(language))));
    auto *re = mClinet->get(request);
    connect(re, &QNetworkReply::finished, [re,callback,this,language,version](){
        if (re->error() != QNetworkReply::NoError) {
            qWarning() << "DataDragon::getAllItemsInfo - network reqeust error (retry after 5sec) - "  << re->error() << re->errorString();
            QTimer::singleShot(5000, [this,version,language,callback](){ this->getAllItemsInfo(version, language, callback); });
            return;
        }
        callback(QJsonDocument::fromJson(re->readAll()).object().value("data").toObject());
    });
}

void DataDragon::getAllSummonerSpellsInfo(const QString &version, DataDragon::Language language, std::function<void(const QJsonObject &)>callback)
{
    QNetworkRequest request(QUrl(getDataDragonPath() + QString("/%1/data/%2/summoner.json")
                                 .arg(version).arg(getLanguageString(language))));
    auto *re = mClinet->get(request);
    connect(re, &QNetworkReply::finished, [re,callback,this,language,version](){
        if (re->error() != QNetworkReply::NoError) {
            qWarning() << "DataDragon::getAllSummonerSpellsInfo - network reqeust error (retry after 5sec) - "  << re->error() << re->errorString();
            QTimer::singleShot(5000, [this,version,language,callback](){ this->getAllSummonerSpellsInfo(version, language, callback); });
            return;
        }
        callback(QJsonDocument::fromJson(re->readAll()).object().value("data").toObject());
    });
}

void DataDragon::getAllRunesInfo(const QString &version, DataDragon::Language language, std::function<void(const QJsonArray &)>callback)
{
    QNetworkRequest request(QUrl(getDataDragonPath() + QString("/%1/data/%2/runesReforged.json")
                                 .arg(version).arg(getLanguageString(language))));
    auto *re = mClinet->get(request);
    connect(re, &QNetworkReply::finished, [re,callback,this,language,version](){
        if (re->error() != QNetworkReply::NoError) {
            qWarning() << "DataDragon::getAllRunesInfo - network reqeust error (retry after 5sec) - "  << re->error() << re->errorString();
            QTimer::singleShot(5000, [this,version,language,callback](){ this->getAllRunesInfo(version, language, callback); });
            return;
        }
        callback(QJsonDocument::fromJson(re->readAll()).array());
    });
}

void DataDragon::getAllProfileiconsInfo(const QString &version, DataDragon::Language language, std::function<void(const QJsonObject &)>callback)
{
    QNetworkRequest request(QUrl(getDataDragonPath() + QString("/%1/data/%2/profileicon.json")
                                 .arg(version).arg(getLanguageString(language))));
    auto *re = mClinet->get(request);
    connect(re, &QNetworkReply::finished, [re,callback,this,language,version](){
        if (re->error() != QNetworkReply::NoError) {
            qWarning() << "DataDragon::getAllProfileiconsInfo - network reqeust error (retry after 5sec) - "  << re->error() << re->errorString();
            QTimer::singleShot(5000, [this,version,language,callback](){ this->getAllProfileiconsInfo(version, language, callback); });
            return;
        }
        callback(QJsonDocument::fromJson(re->readAll()).object().value("data").toObject());
    });
}

void DataDragon::getAllMissionAssetsInfo(const QString &version, DataDragon::Language language, std::function<void(const QJsonObject &)>callback)
{
    QNetworkRequest request(QUrl(getDataDragonPath() + QString("/%1/data/%2/mission-assets.json")
                                 .arg(version).arg(getLanguageString(language))));
    auto *re = mClinet->get(request);
    connect(re, &QNetworkReply::finished, [re,callback,this,language,version](){
        if (re->error() != QNetworkReply::NoError) {
            qWarning() << "DataDragon::getAllMissionAssetsInfo - network reqeust error (retry after 5sec) - "  << re->error() << re->errorString();
            QTimer::singleShot(5000, [this,version,language,callback](){ this->getAllMissionAssetsInfo(version, language, callback); });
            return;
        }
        callback(QJsonDocument::fromJson(re->readAll()).object().value("data").toObject());
    });
}

void DataDragon::getAllMapsInfo(const QString &version, DataDragon::Language language, std::function<void(const QJsonObject &)>callback)
{
    QNetworkRequest request(QUrl(getDataDragonPath() + QString("/%1/data/%2/map.json")
                                 .arg(version).arg(getLanguageString(language))));
    auto *re = mClinet->get(request);
    connect(re, &QNetworkReply::finished, [re,callback,this,language,version](){
        if (re->error() != QNetworkReply::NoError) {
            qWarning() << "DataDragon::getAllMapsInfo - network reqeust error (retry after 5sec) - "  << re->error() << re->errorString();
            QTimer::singleShot(5000, [this,version,language,callback](){ this->getAllMapsInfo(version, language, callback); });
            return;
        }
        callback(QJsonDocument::fromJson(re->readAll()).object().value("data").toObject());
    });
}

void DataDragon::setAllChampionsDetailInfo(const QJsonObject &allChampionsInfo)
{
    if (mAllChampionsDetailInfo != allChampionsInfo) {
        mAllChampionsDetailInfo = allChampionsInfo;
        emit allChampionsDetailInfoChanged();
    }
}

void DataDragon::setAllChampionsInfo(const QJsonObject &allChampionsInfo)
{
    if (mAllChampionsInfo != allChampionsInfo) {
        mAllChampionsInfo = allChampionsInfo;
        emit allChampionsInfoChanged();
    }
}

void DataDragon::setAllItemsInfo(const QJsonObject &allItemsInfo)
{
    if (mAllItemsInfo != allItemsInfo) {
        mAllItemsInfo = allItemsInfo;
        emit allItemsInfoChanged();
    }
}

void DataDragon::setAllSummonerSpellsInfo(const QJsonObject &allSummonerSpellsInfo)
{
    if (mAllSummonerSpellsInfo != allSummonerSpellsInfo) {
        mAllSummonerSpellsInfo = allSummonerSpellsInfo;
        emit allSummonerSpellsInfoChanged();
    }
}

void DataDragon::setAllRunesInfo(const QJsonArray &allRunesInfo)
{
    if (mAllRunesInfo != allRunesInfo) {
        mAllRunesInfo = allRunesInfo;
        emit allRunesInfoChanged();
    }
}

void DataDragon::setAllProfileiconfsInfo(const QJsonObject &allProfileiconfs)
{
    if (mAllProfileicnonsInfo != allProfileiconfs) {
        mAllProfileicnonsInfo = allProfileiconfs;
        emit allProfileiconsInfoChanged();
    }
}

void DataDragon::setAllMissionAssetsInfo(const QJsonObject &allMissionAssetsInfo)
{
    if (mAllMissionAssetsInfo != allMissionAssetsInfo) {
        mAllMissionAssetsInfo = allMissionAssetsInfo;
        emit allMissionAssetsInfoChanged();
    }
}

void DataDragon::setAllMapsInfo(const QJsonObject &allMapsInfo)
{
    if (mAllMapsInfo != allMapsInfo) {
        mAllMapsInfo = allMapsInfo;
        emit allMapsInfoChanged();
    }
}

QString DataDragon::getChampionIconPath(const QString &championName) const
{
    return getDataDragonPath() + QString("/%1/img/champion/%2.png")
            .arg(this->version()).arg(championName);
}

QString DataDragon::getChampionLoadingImagePath(const QString &championName, int skinNum) const
{
    return getDataDragonPath() + QString("/img/champion/loading/%1_%2.jpg")
            .arg(championName).arg(QString::number(skinNum));
}

QString DataDragon::getChampionSplashImagePath(const QString &championName, int skinNum) const
{
    return getDataDragonPath() + QString("/img/champion/splash/%1_%2.jpg")
            .arg(championName).arg(QString::number(skinNum));
}

QString DataDragon::getChampionTilesImagePath(const QString &championName, int skinNum) const
{
    return getDataDragonPath() + QString("/img/champion/tiles/%1_%2.jpg")
            .arg(championName).arg(QString::number(skinNum));
}

QString DataDragon::getDataDragonPath()
{
    return "http://ddragon.leagueoflegends.com/cdn";
}

void DataDragon::initDataDragon()
{
    const QString curVersion = this->version();
    const Language lang = this->language();

    if (curVersion.isEmpty()) {
        dataDragonVersionCheck([=](int err, QString errStr){err = 0; errStr = "";});
        return;
    }

    if (mUseMemberFlag == (mUseMemberFlag | Champions))
        getAllChampionsInfo(curVersion, lang, [this](const QJsonObject &json){
            this->setAllChampionsInfo(json);
        });
    else this->setAllChampionsInfo(QJsonObject());

    if (mUseMemberFlag == (mUseMemberFlag | ChampionsDetail))
        getAllChampionsDetailInfo(curVersion, lang, [this](const QJsonObject &json){
            this->setAllChampionsDetailInfo(json);
        });
    else this->setAllChampionsDetailInfo(QJsonObject());

    if (mUseMemberFlag == (mUseMemberFlag | Items))
        getAllItemsInfo(curVersion, lang, [this](const QJsonObject &json){
            this->setAllItemsInfo(json);
        });
    else this->setAllItemsInfo(QJsonObject());

    if (mUseMemberFlag == (mUseMemberFlag | Runes))
        getAllRunesInfo(curVersion, lang, [this](const QJsonArray &json){
            this->setAllRunesInfo(json);
        });
    else this->setAllRunesInfo(QJsonArray());

    if (mUseMemberFlag == (mUseMemberFlag | SummonerSpells))
        getAllSummonerSpellsInfo(curVersion, lang, [this](const QJsonObject &json){
            this->setAllSummonerSpellsInfo(json);
        });
    else this->setAllSummonerSpellsInfo(QJsonObject());

    if (mUseMemberFlag == (mUseMemberFlag | Profileicons))
        getAllProfileiconsInfo(curVersion, lang, [this](const QJsonObject &json){
            this->setAllProfileiconfsInfo(json);
        });
    else this->setAllProfileiconfsInfo(QJsonObject());

    if (mUseMemberFlag == (mUseMemberFlag | MissionAssets))
        getAllMissionAssetsInfo(curVersion, lang, [this](const QJsonObject &json){
            this->setAllMissionAssetsInfo(json);
        });
    else this->setAllMissionAssetsInfo(QJsonObject());

    if (mUseMemberFlag == (mUseMemberFlag | Maps))
        getAllMapsInfo(curVersion, lang, [this](const QJsonObject &json){
            this->setAllMapsInfo(json);
        });
    else this->setAllMapsInfo(QJsonObject());
}

void DataDragon::setClinet(QNetworkAccessManager *clinet)
{
    mClinet = clinet;
}

QString DataDragon::version() const
{
    return mVersion;
}

void DataDragon::setVersion(const QString &version)
{
    if (mVersion != version){
        mVersion = version;
        emit this->versionChanged();
        initDataDragon();
    }
}

void DataDragon::getNewestVersion(std::function<void (QString, int, QString)> versionAndErrAndErrStr) const
{
    getAllVersions([versionAndErrAndErrStr](const QJsonArray &arr, int err, QString errStr){
        versionAndErrAndErrStr(err ? "" : arr.first().toString(), err, errStr);
    });
}

void DataDragon::getAllVersions(std::function<void (const QJsonArray &, int, QString)> VersionsAndErrAndErrStr) const
{
    QNetworkReply *re = mClinet->get(QNetworkRequest(QUrl("https://ddragon.leagueoflegends.com/api/versions.json")));
    connect(re, &QNetworkReply::finished, [re, VersionsAndErrAndErrStr](){
        re->deleteLater();
        QJsonArray versions = QJsonDocument::fromJson(re->readAll()).array();
        if (versions.isEmpty()) {
            if (re->error() == QNetworkReply::NoError) {
                VersionsAndErrAndErrStr(QJsonArray(), 100, "UndefindedError");
            } else {
                VersionsAndErrAndErrStr(QJsonArray(), re->error(), re->errorString());
            }
            return;
        }
        VersionsAndErrAndErrStr(versions, 0, QString());
    });
}

DataDragon::Language DataDragon::language() const
{
    QSettings settings;
    return DataDragon::Language(settings.value("DataDragon/language").toInt());
}

void DataDragon::setLanguage(DataDragon::Language language)
{
    QSettings settings;
    if (this->language() != language){
        settings.setValue("DataDragon/language", int(language));
        emit this->languageChanged();
        initDataDragon();
    }
}

QJsonObject DataDragon::getChampByKey(int key) const
{
    auto keys = mAllChampionsInfo.keys();
    for (auto id : keys)
        if (key == mAllChampionsInfo.value(id).toObject().value("key").toInt())
            return mAllChampionsInfo.value(id).toObject();
    return QJsonObject();
}

QString DataDragon::getChampionIconDirPath() const
{
    return getDataDragonPath() + QString("/%1/img/champion")
            .arg(this->version());
}


void DataDragon::getDataDragon(const QString &version, const QString &downlaodPath,
                               std::function<void (int, QString)> errAndErrStr, std::function<void(qreal)>progrecessCallback) const
{
    QFile *file = new QFile(downlaodPath);
    this->getDataDragon(version, file, [errAndErrStr,file](int err, QString errStr){
        errAndErrStr(err, errStr);
        file->deleteLater();
    },progrecessCallback);
}

void DataDragon::getDataDragon(const QString &version, QIODevice *downlaodDevice,
                               std::function<void (int, QString)> errAndErrStr, std::function<void(qreal)>progrecessCallback) const
{
    QString url = QString("https://ddragon.leagueoflegends.com/cdn/dragontail-%1.tgz").arg(version);

    if (downlaodDevice->isOpen()) downlaodDevice->close();
    if (!downlaodDevice->open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        errAndErrStr(100, "cannot open the I/O device");
        return;
    }

    QNetworkReply *re = mClinet->get(QNetworkRequest(QUrl(url)));

    connect(re, &QNetworkReply::readyRead,  [re, progrecessCallback, downlaodDevice, errAndErrStr](){
        downlaodDevice->write(re->readAll());
        if (progrecessCallback != nullptr) progrecessCallback(qreal(downlaodDevice->size()) / re->header(QNetworkRequest::ContentLengthHeader).toReal());
    });

    connect(re, &QNetworkReply::finished, [re, downlaodDevice, errAndErrStr](){
        re->deleteLater();
        if (re->error() != QNetworkReply::NoError) {
            errAndErrStr(re->error(), re->errorString());
            return;
        }
        downlaodDevice->close();
        errAndErrStr(0, QString());
    });
}

void DataDragon::extrackDataDragon(const QString &fileName, std::function<void (bool)> successed) const
{
    const QString workingPath = getDataDragonPath();
    if(!QDir(workingPath).exists()) QDir().mkdir(workingPath);
    QProcess *process = new QProcess;
    process->setWorkingDirectory(workingPath);
    process->start(QString("tar -xf \"%1\"").arg(QString(fileName).replace('/','\\')));
    connect(process, QOverload<int>::of(&QProcess::finished),
        [successed, process](int exitCode)
    {
        successed(exitCode == 0 ? true : false);
        process->deleteLater();
    });
}
