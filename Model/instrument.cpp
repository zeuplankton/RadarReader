#include "instrument.h"
#include "utils.h"
#include <QDebug>
#include <QThread>
#include "Model/connector.h"
#include "Model/settings.h"

Instrument::Instrument(QObject *parent,
                       Settings& config,
                       Connector& conct,
                       QThread& thread)
    : QObject{parent},
    m_isConnected(false),
    m_thread(thread),
    m_settings(config),
    m_connector(conct)
{}

Instrument::~Instrument()
{
    Utils::DestructorMsg(this);
}

void Instrument::enableTestMode()
{
    m_isConnected = false;
    qDebug() << "Running in the test mode. Instrument is not being controlled.";
}

void Instrument::initialize()
{
    qDebug() << "Instrument::initialize";
    // Fake making a TCP connection
    // QThread::msleep(5000);
    initWithConnector();
}


// public slots

void Instrument::onDistanceChangedFromMainviewmanager(double value)
{
    writeDistance(value);
}

void Instrument::onVelocityChangedFromMainviewmanager(double value)
{
    writeVelocity(value);
}

void Instrument::onPowerChangedFromMainviewmanager(bool value)
{
    writeRfPower(value);
}

void Instrument::onWorkDoneFromConnector(bool value)
{
    qDebug() << "Instrument::onWorkDoneFromConnector getting the connection status {"<< value << "} from Connector::notifyInstrumentThatWorkDone";
    m_isConnected = value;
    // If connection successful, set default values.
    if (m_isConnected) { setDefaultValues(); }
    qDebug() << "Passing the status {"<< value << "} to MainViewManager::onInitializationDoneFromInstrument via signal Instrument::notifyMainviewmanagerThatInitializationDone";
    emit notifyMainviewmanagerThatInitializationDone(value);
    m_thread.quit();
    m_thread.wait();
    qDebug() << "Instrument::onWorkDoneFromConnector, Connection has completed.";
}

void Instrument::onStatusChangedFromConnector(const QString &message)
{
    qDebug() << "Instrument::onStatusChangedFromConnector getting the message {"<< message << "} from Connector::notifyInstrumentOfStatusChange";
    qDebug() << "Passing the message {"<< message << "} to MainViewManager::onStatusUpdateFromInstrument via signal Instrument::notifyMainviewmanagerOfStatusUpdate";
    emit notifyMainviewmanagerOfStatusUpdate(message);
}


// private methods

void Instrument::writeRfPower(bool value)
{
    if (m_isConnected) {
        qDebug() << "Writing to remote: PowerOn: " << value;
    } else {
        qDebug() << "Writing to console: PowerOn: " << value;
    }
}

void Instrument::writeVelocity(double value)
{
    if (m_isConnected) {
        qDebug() << "Writing to remote: Velocity: " << value;
    } else {
        qDebug() << "Writing to console: Velocity: " << value;
    }
}

void Instrument::writeDistance(double value)
{
    if (m_isConnected) {
        qDebug() << "Writing to remote: Distance: " << value;
    } else {
        qDebug() << "Writing to console: Distance: " << value;
    }
}

void Instrument::initWithConnector()
{
    qDebug() << "Instrument::initWithConnector. Kicking start the connector in a new thread, which would retrieve information of connnection status (true or false) and connection status message, passing back the Instrument";
    m_connector.moveToThread(&m_thread);
    QObject::connect(&m_thread, &QThread::started,
                     &m_connector, &Connector::onStartFromThread);
    QObject::connect(&m_connector, &Connector::notifyInstrumentThatWorkDone,
                     this, &Instrument::onWorkDoneFromConnector);
    QObject::connect(&m_connector, &Connector::notifyInstrumentOfStatusChange,
                     this, &Instrument::onStatusChangedFromConnector);
    m_thread.start();
}

void Instrument::setDefaultValues()
{
    qDebug() << "Instrument::setDefaultValues";
    writeRfPower(m_settings.getPowerState());
    writeDistance(m_settings.getDistance());
    writeVelocity(m_settings.getVelocity());
}



