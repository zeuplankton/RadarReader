#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QStringListModel>
#include <QJsonParseError>
#include <QJsonObject>
#include <QFile>
#include <QDir>

#include <QDebug>

typedef std::pair<QJsonObject, QJsonParseError> JsonObjErrPair;

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr, QString filename = "");
    void parseJSONData(); //
    QString getApplicationName() const { return m_applicationName; }
    QString getAppShortName() const { return m_appShortName; }
    QString getHostName() const { return m_hostName; }
    quint16 getPortNumber() const { return m_portNumber; }
    int getWaitMs() const { return m_waitMs; }
    int getReadWaitMs() const { return m_readWaitMs; }
    double getVelocity() const { return m_velocity; }
    double getDistance() const { return m_distance; }
    double getRadarFreqGhz() const { return m_radarFreqGhz; }
    int getRxIfAttnDb() const { return m_RxIfAttnDb; }
    int getTxIfAttnDb() const { return m_TxIfAttnDb; }
    bool getPowerState() const { return m_powerState; }

    bool getTestMode() const { return m_testMode; }
    int getBootDelay() const { return m_bootDelay; }

    double getDistance1() const { return m_distance1; }
    double getDistance2() const { return m_distance2; }
    double getDistance3() const { return m_distance3; }
    double getDistance4() const { return m_distance4; }

    double getVelocity1() const { return m_velocity1; }
    double getVelocity2() const { return m_velocity2; }
    double getVelocity3() const { return m_velocity3; }
    double getVelocity4() const { return m_velocity4; }

    QStringListModel& getCommandAsModel() const { return m_modelCommands; }
    QStringList getCommandAsStringList() const { return m_modelCommands.stringList(); }

signals:
    void notifyFailure(QString message);

private:
    QString m_filename;
    QStringListModel& m_modelCommands;

    QString m_applicationName;
    QString m_appShortName;
    QString m_hostName;
    quint16 m_portNumber;
    int m_waitMs;
    int m_readWaitMs;
    double m_velocity;
    double m_distance;
    double m_radarFreqGhz;
    int m_RxIfAttnDb;
    int m_TxIfAttnDb;
    bool m_powerState;
    bool m_testMode;
    int m_bootDelay;

    double m_distance1;
    double m_distance2;
    double m_distance3;
    double m_distance4;

    double m_velocity1;
    double m_velocity2;
    double m_velocity3;
    double m_velocity4;



    QString readJSONFile();
    QString readJSONFromInternalResource();
    QDir openConfigDirectory();
    void writeDefaultsToStdConfigFile(QFile &stdConfigFile, const QString &settings);

    JsonObjErrPair getJsonObject(const QString &rawJson);
    void showJsonParseError(QJsonParseError jsonParseError);




};

#endif // SETTINGS_H
