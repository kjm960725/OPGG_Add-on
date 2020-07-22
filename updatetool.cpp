#include "updatetool.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QTimer>
#include <QStandardPaths>

UpdateTool::UpdateTool(QObject *parent) :
  QObject(parent)
, mUpdateCheckTimer(new QTimer(this))
, mState(UpdateTool::NotRunning)
, mHasUpdate(false)
{
    connect(&mProcess, SIGNAL(started()), this, SLOT(processStarted()));

    connect(&mProcess, QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished)
            , this, &UpdateTool::processFinished);

    connect(&mProcess, SIGNAL(errorOccurred (QProcess::ProcessError))
          , this, SLOT(processError(QProcess::ProcessError)));

    connect(mUpdateCheckTimer, &QTimer::timeout
            , this, &UpdateTool::checkUpdate);

    connect(this, &UpdateTool::hasUpdateChanged, mUpdateCheckTimer, [this](bool hasUpdate){
        if (hasUpdate)
            mUpdateCheckTimer->stop();
    });
}

void UpdateTool::checkUpdate()
{
    QString toolName = "maintenancetool.exe";
    QString path = QDir(qApp->applicationDirPath()).absoluteFilePath(toolName);
    QStringList args;
    if (mProcess.state() == QProcess::NotRunning) {
        args.append("--checkupdates");
        mProcess.start(path, args);
    } else {
        qDebug() << "Already started.";
    }
}

void UpdateTool::startUpdate()
{
    if (!QProcess::startDetached(createUpdateBatFile(), QStringList())) {
        qWarning() << "can not run bat \"update\"";
    }
}

QString UpdateTool::createUpdateBatFile() const
{
    QDir tempDir(QStandardPaths::standardLocations(QStandardPaths::StandardLocation::TempLocation).first() + "/OPGG_Add-on_Temp");
    if (!tempDir.exists())
        tempDir.mkdir(tempDir.absolutePath());

    QFile bat(QString("%1/%2")
              .arg(tempDir.absolutePath())
              .arg("update.bat")
              .replace("\\","/"));

    if (!bat.open(QIODevice::WriteOnly))
        return "";

    QStringList lines;
    lines << "@ECHO OFF"
          << QString("cd %1").arg(QString(qApp->applicationDirPath().replace("/","\\")))
          << QString("TASKKILL /F /IM %1.exe").arg(qApp->applicationName())
          << "start \"\" /W \"maintenancetool.exe\" \"--updater\""
          << QString("start \"\" \"%1\\%2.exe\"").arg(QString(qApp->applicationDirPath().replace("/","\\"))).arg(qApp->applicationName());
    bat.write(lines.join("\r\n").toStdString().data());
    return bat.fileName();
}

UpdateTool::ProcessState UpdateTool::state() const
{
    return mState;
}
void UpdateTool::setState(ProcessState state)
{
    if(mState == state)  return;
    mState = state;
    emit stateChanged(mState);
}

bool UpdateTool::hasUpdate() const
{
    return mHasUpdate;
}
void UpdateTool::setHasUpdate(bool hasUpdate)
{
    if(mHasUpdate == hasUpdate)  return;
    mHasUpdate = hasUpdate;
    emit hasUpdateChanged(mHasUpdate);
}

QString UpdateTool::updateDetails() const
{
    return mUpdateDetails;
}

void UpdateTool::updateCheckTimerStart(int msec)
{
    mUpdateCheckTimer->start(msec);
    checkUpdate();
}

void UpdateTool::setUpdateDetails(const QString &updateDetails)
{
    if(mUpdateDetails == updateDetails) return;
    mUpdateDetails = updateDetails;
    emit updateDetailsChanged(mUpdateDetails);
}

void UpdateTool::processStarted()
{
    setState(UpdateTool::Running);
}

void UpdateTool::processFinished(int exitCode)
{
  if(exitCode == 0){
    QByteArray stdOut = mProcess.readAllStandardOutput();
    QString stdOutStr = QString::fromLocal8Bit(stdOut);
    qDebug() << "UpdateDetected :" << stdOutStr;
    //exitCode= 0 , exitStatus= 0
    //out> "[0] Warning: Could not create lock file 'C:/Program Files (x86)/HelloWorld/lockmyApp15021976.lock': アクセスが拒否されました。
    // (0x00000005)
    //<updates>
    //    <update version="0.3.0-1" name="The root component" size="175748"/>
    //</updates>
    //
    //"
    //err> ""

    QString xmlStr;
    QStringList lines;
    bool enabled = false;
    lines = stdOutStr.split("\n");
    foreach (const QString &line, lines) {
        if(line.startsWith("<updates>")) {
            enabled = true;
            xmlStr.append(line);
        } else if (line.endsWith("</updates>")) {
            xmlStr.append(line);
            break;
        } else if (enabled) {
            xmlStr.append(line);
        }
    }
    if (xmlStr.length() > 0) {
        setUpdateDetails(xmlStr);
        setHasUpdate(true);
    } else {
        setUpdateDetails("");
        setHasUpdate(false);
    }
    setState(UpdateTool::NotRunning);

  }else{
      if (exitCode != 1) {
          QByteArray stdErr = mProcess.readAllStandardError();
          QString stdErrStr = QString::fromLocal8Bit(stdErr);
          qWarning() << "UpdateTool : maintenancetool error :" << exitCode << stdErr << stdErrStr;
      }
      setState(UpdateTool::NotRunning);
  }
}

void UpdateTool::processError(QProcess::ProcessError error)
{
    qDebug() <<  "UpdateTool process error :" << error << mProcess.errorString();
    setState(UpdateTool::NotRunning);
}

