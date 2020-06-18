#ifndef UPDATETOOL_H
#define UPDATETOOL_H

#include <QObject>
#include <QProcess>

class QTimer;
class UpdateTool : public QObject
{
    Q_OBJECT
    Q_ENUMS(ProcessState)
    Q_ENUMS(StartMode)
    Q_PROPERTY(ProcessState state READ state NOTIFY stateChanged)
    Q_PROPERTY(bool hasUpdate READ hasUpdate NOTIFY hasUpdateChanged)
    Q_PROPERTY(QString updateDetails READ updateDetails NOTIFY updateDetailsChanged)

  public:
    explicit UpdateTool(QObject *parent = nullptr);

    enum ProcessState {
      NotRunning,
      Running
    };
    enum StartMode {
      CheckUpdate,
      Update
    };

    ProcessState state() const;
    bool hasUpdate() const;
    QString updateDetails() const;

  signals:
    void stateChanged(ProcessState state);
    void hasUpdateChanged(bool hasUpdate);
    void updateDetailsChanged(const QString &updateDetails);

  public slots:
    void updateCheckTimerStart(int msec);
    void checkUpdate();
    void startUpdate();

  private slots:
    QString createUpdateBatFile() const;
    void setHasUpdate(bool hasUpdate);
    void setUpdateDetails(const QString &updateDetails);
    void processStarted();
    void processFinished(int exitCode);
    void processError(QProcess::ProcessError error);

  private:
    QTimer *mUpdateCheckTimer;
    ProcessState mState;
    bool mHasUpdate;
    QString mUpdateDetails;
    QProcess mProcess;

    void setState(ProcessState state);
};

#endif // UPDATETOOL_H
