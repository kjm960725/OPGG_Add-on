#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QElapsedTimer>
#include <QFile>
#include <iostream>
#include "riot.h"
#include "lcu.h"
#include "datadragon.h"
#include "challenge.h"
#include <QSslSocket>
#include <QTimer>
#include <QQmlContext>
#include <QtWebEngine>
#include "qmlclipboardadapter.h"
#include <QSslSocket>
#include "webscrapforopgg.h"
//#include "competuser.h"
//#include "competteam.h"
//#include "competmanager.h"
//#include "competmacth.h"
#include "updatetool.h"

#define PROJECT_DIR QString("C:/Users/KJM96/OneDrive/QTProject/OPGG_Add_on")

static QMutex logMutex;
static QString userFolerPath;
void makeUserFolders();
void LogToFile(QtMsgType type, const QMessageLogContext &context, const QString &_msg);
void makeRiotJsonHeaderFromTxt(const QString &filePath, bool echo, bool headerAutoSave = false);
void regQmlModules();
int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("OPGG_Add-on");
    QCoreApplication::setOrganizationName("KJM960725");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QtWebEngine::initialize();
    QGuiApplication app(argc, argv);

    makeUserFolders();
    qInstallMessageHandler(LogToFile);
    regQmlModules();

    QQmlApplicationEngine engine;
    Challenge challenge(&engine);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("supportSsl", QSslSocket::supportsSsl());
    engine.rootContext()->setContextProperty("sslVersion", QSslSocket::sslLibraryVersionString());
    engine.rootContext()->setContextProperty("appDirPath", qApp->applicationDirPath());
    engine.rootContext()->setContextProperty("downloadPath", QString("file:%1").arg(QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).first()));
    engine.rootContext()->setContextProperty("cachePath", QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    engine.rootContext()->setContextProperty("challenge",&challenge);
    engine.rootContext()->setContextProperty("updateTool",challenge.updateTool());
    engine.rootContext()->setContextProperty("lcu",challenge.lcu());
    engine.rootContext()->setContextProperty("riot",challenge.riot());
    engine.rootContext()->setContextProperty("dragon",challenge.dataDragon());
    engine.rootContext()->setContextProperty("opggScrap",challenge.webScrapForOPGG());
    engine.rootContext()->setContextProperty("userFolerPath",userFolerPath);
    engine.rootContext()->setContextProperty("obs", challenge.observerFileManager());

    engine.load(url);

    return app.exec();
}

void regQmlModules()
{
    qmlRegisterType<riot::LCU>("Riot",1,0,"LCU");
    qmlRegisterType<riot::Riot>("Riot",1,0,"Riot");
    qmlRegisterType<riot::DataDragon>("Riot",1,0,"DataDragon");
    qmlRegisterType<Challenge>("Riot",1,0,"Challenge");
    qmlRegisterType<QmlClipboardAdapter>("Clipboard", 1, 0, "Clipboard");
    qmlRegisterType<ObserverFileManager>("Riot", 1, 0, "ObserverFileManager");
    qmlRegisterType<WebScrapForOPGG>("Riot", 1,0, "WebScrapForOPGG");

    qRegisterMetaType<riot::LCU::GameflowState>("GameflowState");
}
void makeUserFolders()
{
    userFolerPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
            + QString("/%1").arg(qApp->applicationName());
    if(!QDir(userFolerPath).exists()) QDir().mkdir(userFolerPath);
}
void LogToFile(QtMsgType type, const QMessageLogContext &context, const QString &_msg)
{
    QMutexLocker lock(&logMutex);
    QString curtime = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    QString curDate = QDateTime::currentDateTime().toString("yyyyMMdd");

    QByteArray localMsg = _msg.toLocal8Bit();
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
        fprintf(stdout, "[Debug]\t%s\t%s\n", curtime.toLocal8Bit().constData() , localMsg.constData());
        fflush(stdout);
        break;
    case QtInfoMsg:
        fprintf(stdout, "[Info]\t%s\t%s\n", curtime.toLocal8Bit().constData(), localMsg.constData());
        fflush(stdout);
        break;
    case QtWarningMsg:
        fprintf(stderr, "[Warning]\t%s\t%s (%s:%u, %s)\n", curtime.toLocal8Bit().constData(), localMsg.constData(), context.file, context.line, function);
        fflush(stderr);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "[Critical]\t%s\t%s (%s:%u, %s)\n", curtime.toLocal8Bit().constData(), localMsg.constData(), context.file, context.line, function);
        fflush(stderr);
        break;
    case QtFatalMsg:
        fprintf(stderr, "[Fatal]\t%s\t%s (%s:%u, %s)\n", curtime.toLocal8Bit().constData(), localMsg.constData(), context.file, context.line, function);
        fflush(stderr);
        break;
    }

//    QString logPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
//            + QString("%1%2_Logs").arg(QDir::separator()).arg(qApp->organizationName());
//    if(!QDir(logPath).exists()) QDir().mkdir(logPath);
//    QFile file(QString("%1%4%2_%3.log")
//               .arg(logPath)
//               .arg(qApp->applicationName())
//               .arg(curDate)
//               .arg(QDir::separator()));
//    if(file.open(QIODevice::Append | QIODevice::Text)) {
//        QTextStream out(&file);
//        QString msg = _msg;
//        msg.replace('\n',"\n\t\t");
//        switch (type) {
//        case QtDebugMsg:
//            out << QString("[Debug]\t%1\t%2\n").arg(curtime).arg(msg);
//            file.flush();
//            break;
//        case QtInfoMsg:

//            out << QString("[Info]\t%1\t%2\n").arg(curtime).arg(msg);
//            file.flush();
//            break;
//        case QtWarningMsg:
//            out << QString("[Warning]\t%1\t%2\n").arg(curtime).arg(msg);
//            file.flush();
//            break;
//        case QtCriticalMsg:
//            out << QString("[Critical]\t%1\t%2\t%3\t%4\n").arg(curtime).arg(msg).arg(context.function).arg(context.line);
//            file.flush();
//            break;
//        case QtFatalMsg:
//            out << QString("[Fatal]\t%1\t%2\n").arg(curtime).arg(msg);
//            file.flush();
//            break;
//        }
//    }
}

void makeRiotJsonHeaderFromTxt(const QString &filePath, bool echo, bool headerAutoSave)
{   // Riot API 문서의 테이블을 엑셀에 복붙후, .txt 포맷으로 저장후 사용.
    auto prt = [echo](const QString &input = QString(), int tapCount = 0, QIODevice *device = nullptr) {
        for (int i = 0; i < tapCount; ++i){
            if (echo) std::cout << "\t";
            if (device != nullptr) device->write("\t");
        }
        if (echo) std::cout << input.toStdString().data() << std::endl;
        if (device != nullptr) device->write(input.toLocal8Bit() + "\n");
    };

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "printRiotJsonHeaderFromTxt - error : 파일 오픈 실패";
        return;
    }

    QStringList functionList;
    QString currentObjectName;
    QStringList otherObjectNamesInfunc;
    int detectedObjectCount = 0;

    while (!file.atEnd()) {
        const QStringList cols = QString(file.readLine()).remove(QRegExp("[\n\"]") ).split('\t',QString::SkipEmptyParts);
        const QString name = cols.count() >= 1 ? cols.at(0) : "";
        const QString dataType = cols.count() >= 2 ? cols.at(1) : "";
        const QString description = cols.count() >= 3 ? cols.at(2) : "";

        if (name.toUpper() == "NAME" && dataType.toUpper().remove(QRegExp("[ ]")) == "DATATYPE" && description.toUpper() == "DESCRIPTION")
            continue;

        bool objectDetected(!name.isEmpty() && dataType.isEmpty());
        bool isValue(!name.isEmpty() && !dataType.isEmpty());

        if (isValue) {
            functionList << QString("// ") + QString(description.isEmpty() ? name : description);

            if (dataType == "long") {
                functionList << QString("long %1() const { return long(this->value(\"%1\").toVariant().toLongLong()); }")
                                .arg(name);
                functionList << QString("void set%2(long %1) { this->insert(\"%1\", qlonglong(%1)); }")
                                .arg(name).arg(QString("%1%2").arg(name.front().toUpper()).arg(name.mid(1)));

            } else if (dataType == "int") {
                functionList << QString("int %1() const { return this->value(\"%1\").toInt(); }")
                                .arg(name);
                functionList << QString("void set%2(int %1) { this->insert(\"%1\", %1); }")
                                .arg(name).arg(QString("%1%2").arg(name.front().toUpper()).arg(name.mid(1)));

            } else if (dataType == "boolean") {
                functionList << QString("bool %1() const { return this->value(\"%1\").toBool(); }")
                                .arg(name);
                functionList << QString("void set%2(bool %1) { this->insert(\"%1\", %1); }")
                                .arg(name).arg(QString("%1%2").arg(name.front().toUpper()).arg(name.mid(1)));

            } else if (dataType == "string") {
                functionList << QString("QString %1() const { return this->value(\"%1\").toString(); }")
                                .arg(name);
                functionList << QString("void set%2(const QString &%1) { this->insert(\"%1\", %1); }")
                                .arg(name).arg(QString("%1%2").arg(name.front().toUpper()).arg(name.mid(1)));

            } else {
                bool isMap(dataType.count() >= 3 ? dataType.left(3).toUpper() == "MAP" : false);
                bool isList(dataType.count() >= 4 ? dataType.left(4).toUpper() == "LIST" : false);
                bool isObject(dataType.front() == dataType.front().toUpper() && !isMap && !isList);

                if (isMap) {
                    const int begin = dataType.indexOf(",") + 1;
                    const int end = dataType.indexOf("]");
                    const QString type = dataType.mid(begin, end - begin).remove(' ');
                    const QString t = type.toLower();

                    if (t == "double" || t == "string" || t == "int" || t == "long" || t == "boolean") {
                        const QString qtType = t == "double" ? "qreal" : t == "string" ? "QString" : t == "boolean" ? "bool" : t;
                        const QString toQtFunc = t == "double" ? "toDouble()" : t == "string" ? "toString()" : t == "int" ? "toInt()" : t == "long" ? "toVariant().toLongLong()" : t == "boolean" ? "toBool()" : "에러";
                        functionList << QString("QMap<QString, %2> %1() const {\n\t\tQMap<QString, %2> result;\n\t\tauto object = this->value(\"%1\").toObject();\n\t\tfor (auto key : object.keys()) result.insert(key, %2(object.value(key).%3));\n\t\treturn result;\n\t}")
                                        .arg(name).arg(qtType).arg(toQtFunc);
                        functionList << QString("void set%2(const QMap<QString, %3> %1) {\n\t\tQJsonObject object;\n\t\tfor (auto key : %1.keys()) object.insert(key, %1.value(key));\n\t\tthis->insert(\"%1\", object);\n\t}")
                                        .arg(name).arg(QString("%1%2").arg(name.front().toUpper()).arg(name.mid(1))).arg(qtType);

                    } else if (type.front() == type.front().toUpper()) {
                        otherObjectNamesInfunc << type;
                        functionList << QString("QMap<QString, %2> %1() const {\n\t\tQMap<QString, %2> result;\n\t\tauto object = this->value(\"%1\").toObject();\n\t\tfor (auto key : object.keys()) result.insert(key, static_cast<%2&&>(object.value(key).toObject()));\n\t\treturn result;\n\t}")
                                        .arg(name).arg(type);
                        functionList << QString("void set%3(const QMap<QString, %2> &%1) {\n\t\tQJsonObject object;\n\t\tfor (auto key : %1.keys()) object.insert(key, %1.value(key));\n\t\tthis->insert(\"%1\", object);\n\t}")
                                        .arg(name).arg(type).arg(QString("%1%2").arg(name.front().toUpper()).arg(name.mid(1)));

                    } else {
                        qWarning() << "정의되지 않은 유형입니다 !" << currentObjectName << cols;
                        return;
                    }


                } else if (isList) {
                    const int begin = dataType.indexOf("[") + 1;
                    const int end = dataType.indexOf("]");
                    const QString type = dataType.mid(begin, end - begin);
                    bool isObjectList = type.front() == type.front().toUpper();

                    if (isObjectList){
                        otherObjectNamesInfunc << type;

                        functionList << QString("QList<%2> %1() const {\n\t\tQList<%2> result;\n\t\tauto arr = this->value(\"%1\").toArray();\n\t\tfor (auto val : arr) result.append(static_cast<%2&&>(val.toObject()));\n\t\treturn result;\n\t}")
                                        .arg(name).arg(type);
                        functionList << QString("void set%3(const QList<%2> &%1) {\n\t\tQJsonArray arr;\n\t\tfor (auto v : %1) arr.append(v);\n\t\tthis->insert(\"%1\",arr);\n\t}")
                                        .arg(name).arg(type).arg(QString("%1%2").arg(name.front().toUpper()).arg(name.mid(1)));
                    } else {
                        if (type == "long") {
                            functionList << QString("QList<%2> %1() const {\n\t\tQList<%2> result;\n\t\tauto arr = this->value(\"%1\").toArray();\n\t\tfor (auto val : arr) result.append(long(val.%3));\n\t\treturn result;\n\t}")
                                            .arg(name).arg("long").arg("toVariant().toLongLong()");
                            functionList << QString("void set%3(const QList<%2> &%1) {\n\t\tQJsonArray arr;\n\t\tfor (auto v : %1) arr.append(qlonglong(v));\n\t\tthis->insert(\"%1\",arr);\n\t}")
                                            .arg(name).arg("long").arg(QString("%1%2").arg(name.front().toUpper()).arg(name.mid(1)));

                        } else if (type == "int") {
                            functionList << QString("QList<%2> %1() const {\n\t\tQList<%2> result;\n\t\tauto arr = this->value(\"%1\").toArray();\n\t\tfor (auto val : arr) result.append(val.%3);\n\t\treturn result;\n\t}")
                                            .arg(name).arg("int").arg("toInt()");
                            functionList << QString("void set%3(const QList<%2> &%1) {\n\t\tQJsonArray arr;\n\t\tfor (auto v : %1) arr.append(v);\n\t\tthis->insert(\"%1\",arr);\n\t}")
                                            .arg(name).arg("int").arg(QString("%1%2").arg(name.front().toUpper()).arg(name.mid(1)));

                        } else if (type == "boolean") {
                            functionList << QString("QList<%2> %1() const {\n\t\tQList<%2> result;\n\t\tauto arr = this->value(\"%1\").toArray();\n\t\tfor (auto val : arr) result.append(val.%3);\n\t\treturn result;\n\t}")
                                            .arg(name).arg("bool").arg("toBool()");
                            functionList << QString("void set%3(const QList<%2> &%1) {\n\t\tQJsonArray arr;\n\t\tfor (auto v : %1) arr.append(v);\n\t\tthis->insert(\"%1\",arr);\n\t}")
                                            .arg(name).arg("bool").arg(QString("%1%2").arg(name.front().toUpper()).arg(name.mid(1)));

                        } else if (type == "string") {
                            functionList << QString("QList<%2> %1() const {\n\t\tQList<%2> result;\n\t\tauto arr = this->value(\"%1\").toArray();\n\t\tfor (auto val : arr) result.append(val.%3);\n\t\treturn result;\n\t}")
                                            .arg(name).arg("QString").arg("toString()");
                            functionList << QString("void set%3(const QList<%2> &%1) {\n\t\tQJsonArray arr;\n\t\tfor (auto v : %1) arr.append(v);\n\t\tthis->insert(\"%1\",arr);\n\t}")
                                            .arg(name).arg("QString").arg(QString("%1%2").arg(name.front().toUpper()).arg(name.mid(1)));

                        } else {
                            qWarning() << "정의되지 않은 유형입니다 !" << currentObjectName << cols;
                            return;
                        }

                    }
                    if ( type == "long") {
                    } else{
                    }

                } else if (isObject) {
                    otherObjectNamesInfunc << dataType;

                    functionList << QString("%2 %1() const { return static_cast<%2&&>(this->value(\"%1\").toObject()); }")
                                    .arg(name).arg(dataType);
                    functionList << QString("void set%3(const %2 &%1) { this->insert(\"%1\", %1); }")
                                    .arg(name).arg(dataType).arg(QString("%1%2").arg(name.front().toUpper()).arg(name.mid(1)));

                } else {
                    qWarning() << "정의되지 않은 유형입니다 !" << currentObjectName << cols;
                    return;

                }
            }

            functionList << QString();
        }

        if (objectDetected || file.atEnd()) {
            if (!currentObjectName.isEmpty()){
                QFile *file = nullptr;
                if (headerAutoSave) {
                    file = new QFile(PROJECT_DIR + QString("/RiotJson/%1.h").arg(currentObjectName));
                    if (!file->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
                        file->deleteLater();
                        file = nullptr;
                        qWarning() << "헤더파일 오픈 실패 :" << currentObjectName;
                    }
                }
                prt(QString("// %1.h").arg(currentObjectName), 0, file);
                prt(QString("#ifndef %1_H").arg(currentObjectName.toUpper()), 0, file);
                prt(QString("#define %1_H").arg(currentObjectName.toUpper()), 0, file);
                prt(QString(), 0, file);
                prt("#include \"JsonObject\"", 0, file);
                prt("#include <QVariant>", 0, file);
                prt("#include <QJsonArray>", 0, file);
                prt("#include <QMap>", 0, file);
                for (auto objName : otherObjectNamesInfunc)
                    prt(QString("#include \"%1.h\"").arg(objName), 0, file);
                prt(QString(), 0, file);
                prt("namespace riot {", 0, file);
                prt(QString("class %1 : public JsonObject").arg(currentObjectName), 0, file);
                prt("{", 0, file);
                prt("public:", 0, file);
                for (auto func : functionList)
                    prt(func,1, file);
                prt("};", 0, file);
                prt("}", 0, file);
                prt("", 0, file);
                prt(QString("#endif // %1_H").arg(currentObjectName.toUpper()), 0, file);

                if (file != nullptr) {
                    file->close();
                    qDebug() << QString("%1.h 파일 저장 성공!").arg(file->fileName());
                }
            }

            currentObjectName = name;
            otherObjectNamesInfunc.clear();
            functionList.clear();
            detectedObjectCount++;

        }
    }
}
