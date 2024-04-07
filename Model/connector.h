#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>
#include "Model/settings.h"

class Connector : public QObject
{
    Q_OBJECT
public:
    explicit Connector(QObject *parent, Settings& config);


signals:
    void notifyInstrumentThatWorkDone(bool value);  // passing the bool value (connection succeeded or not) to Instrument::onConnectorWorkDone
    void notifyInstrumentOfStatusChange(const QString& message); // passing the connection status change message to Instrument::onConnectorStatusChange

public slots:
    void onStartFromThread();

private:
    Settings& m_settings;

    void doWork();
};

#endif // CONNECTOR_H
