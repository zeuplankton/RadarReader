#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QObject>
class QThread;
class Settings;
class Connector;

class Instrument : public QObject
{
    Q_OBJECT
public:
    explicit Instrument(QObject *parent,
                        Settings& config,
                        Connector& conct,
                        QThread& thread); // Before adding more parameters to the constructor, please remove the default value of parent parameter.
    virtual ~Instrument();
    bool isConnected() const { return m_isConnected; }
    void enableTestMode();
    void initialize();

signals:
    void notifyMainviewmanagerThatInitializationDone(bool value);
    void notifyMainviewmanagerOfStatusUpdate(const QString& message);

public slots:
    void onDistanceChangedFromMainviewmanager(double value);
    void onVelocityChangedFromMainviewmanager(double value);
    void onPowerChangedFromMainviewmanager(bool value);
    void onWorkDoneFromConnector(bool value);
    void onStatusChangedFromConnector(const QString& message);

private:
    bool m_isConnected;
    QThread& m_thread;
    Settings& m_settings;
    bool m_testMode;
    Connector& m_connector;

    void writeRfPower(bool value);
    void writeVelocity(double value);
    void writeDistance(double value);
    void initWithConnector();
    void setDefaultValues();
};

#endif // INSTRUMENT_H
