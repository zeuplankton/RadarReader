#include "connector.h"
#include <QThread>

Connector::Connector(QObject *parent, Settings& config)
    : QObject{parent},
    m_settings(config)
{}

void Connector::onStartFromThread()
{ // executed when QThread::started
    doWork();
}

void Connector::doWork()
{
    emit notifyInstrumentOfStatusChange("Connecting in Connector::doWork");
    auto hostname = m_settings.getHostName().toLocal8Bit();
    char* charStr = hostname.data();
    QThread::msleep(m_settings.getBootDelay());
    //bool result = Connect(charStr);
    bool result = true;  // fake connection is successful or not
    if (result) {
        emit notifyInstrumentOfStatusChange("Connected in Connector::doWork");
        QThread::msleep(1000); // Displaying the Connected message before phasing out the feedback area
        emit notifyInstrumentThatWorkDone(true);
    } else {
        emit notifyInstrumentOfStatusChange("Unable to connect to instrument at address " + hostname + ".\n" + "Instrument not functioning properly.");
        emit notifyInstrumentThatWorkDone(false);
    }
}
