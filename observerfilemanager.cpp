#include "observerfilemanager.h"
#include <QFile>
#include <QProcess>
#include <QDir>
#include <QFileInfo>

ObserverFileManager::ObserverFileManager(QObject *parent) : QObject(parent)
{

}

bool ObserverFileManager::isObserverFile(const QString &filePath)
{
    return filePath.split('/').last().contains("LOL_OPGG_Observer") && QFile::exists(filePath);
}

void ObserverFileManager::runProcess(const QString &filePath, std::function<void (int)> exitCallback)
{
    QProcess *process = new QProcess;
    connect(process, QOverload<int>::of(&QProcess::finished),
        [=](int exitCode){ exitCallback(exitCode); process->deleteLater(); });
    process->start(QString("%1").arg(QString(filePath).replace('/','\\')).toStdString().data());
}

void ObserverFileManager::runProcess(const QString &filePath, const QJSValue &exitCallback)
{
    QJSValue *callback = new QJSValue(exitCallback);
    runProcess(filePath, [callback](int exitCode){
        callback->call(QJSValueList() << exitCode);
        delete callback;
    });
}

bool ObserverFileManager::removeFile(const QString &filePath)
{
    return  QFile::remove(filePath);
}
