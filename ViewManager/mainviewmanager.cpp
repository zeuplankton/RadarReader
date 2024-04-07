#include "mainviewmanager.h"
#include <QDebug>

MainViewManager::MainViewManager(QObject *parent)
    : QObject{parent}
{

    // Shifted to Startup::wireMainViewManager2Instrument
    // QObject::connect(this, &MainViewManager::powerOnChanged, &MainViewManager::debugPowerOn); // The signatures of the two functions connected here have to be the same.
    // QObject::connect(this, &MainViewManager::velocityChanged, &MainViewManager::debugVelocityChanged); // The signatures of the two functions connected here have to be the same.
    // QObject::connect(this, &MainViewManager::distanceChanged, &MainViewManager::debugDistanceChanged); // The signatures of the two functions connected here have to be the same.

    m_feedbackAreaVisible = true;
    m_feedbackMessage = "System initalizing...";
    m_feedbackOKButtonVisible = false;
    m_instrumentControlsEnabled = false;
}


void MainViewManager::setPowerOn(bool value)
{
    qDebug() << "In C++ setPowerOn method, powerOn: " << m_powerOn;
    if (m_powerOn != value) {
        m_powerOn = value;
        emit powerOnChanged(value);
        qDebug() << "Changing m_powerOn in the C++ setter";
    }
    qDebug() << "In C++ setPowerOn method, powerOn: " << m_powerOn;
}

void MainViewManager::setDistance(double distance)
{
    if (m_distance != distance ) {
        m_distance = distance;
        emit distanceChanged(distance);
    }
}

void MainViewManager::setVelocity(double velocity)
{
    if (m_velocity != velocity) {
        m_velocity = velocity;
        emit velocityChanged(velocity);
    }
}

void MainViewManager::setFeedbackAreaVisibility(bool value)
{
    if (m_feedbackAreaVisible != value) {
        m_feedbackAreaVisible = value;
        emit feedbackAreaVisibilityChanged(value);
    }
}

void MainViewManager::setFeedbackOKButtonVisibility(bool value)
{
    if (m_feedbackOKButtonVisible != value) {
        m_feedbackOKButtonVisible = value;
        emit feedbackOKButtonVisibilityChanged(value);
    }
}

void MainViewManager::enableInstrumentControls(bool value)
{
    if (m_instrumentControlsEnabled != value) {
        m_instrumentControlsEnabled = value;
        emit instrumentControlsAvailabilityChanged(value);
    }
}

void MainViewManager::setFeedbackMessage(QString message)
{
    m_feedbackMessage = message;
    emit feedbackMessageChanged(message);
}

void MainViewManager::setFeedbackProgress(int progress)
{
    m_feedbackProgress = progress;
    emit feedbackProgressChanged(progress);
}



void MainViewManager::initialize(const Settings &config)
{
    m_appName = config.getApplicationName();
    m_powerOn = config.getPowerState();
    m_distance = config.getDistance();
    m_velocity = config.getVelocity();
    m_velocityPreset1 = config.getVelocity1();
    m_velocityPreset2 = config.getVelocity2();
    m_velocityPreset3 = config.getVelocity3();
    m_velocityPreset4 = config.getVelocity4();
    m_distancePreset1 = config.getDistance1();
    m_distancePreset2 = config.getDistance2();
    m_distancePreset3 = config.getDistance3();
    m_distancePreset4 = config.getDistance4();
}

void MainViewManager::onStatusUpdateFromInstrument(const QString& message)
{
    qDebug() << "MainViewManager::onStatusUpdateFromInstrument getting the message {"<< message << "} from Instrument::notifyMainviewmanagerOfStatusUpdate";
    setFeedbackMessage(message);
}

void MainViewManager::onInitializationDoneFromInstrument(bool value)
{
    qDebug() << "MainViewManager::onInitializationDoneFromInstrument getting the connection status {"<< value << "} from Instrument::notifyMainviewmanagerThatInitializationDone";
    if (value) {
        setFeedbackAreaVisibility(!value);
    }
    enableInstrumentControls(value);
    setFeedbackOKButtonVisibility(!value);
}

// void MainViewManager::debugPowerOn(bool value)
// {
//     qDebug() << "powerOnChanged signal triggered";
//     qDebug() << "In debugPowerOn with value " << value;

// }

// void MainViewManager::debugVelocityChanged(double value)
// {
//     qDebug() << "velocityChanged signal triggered";
//     qDebug() << "In debugVelocityChanged with value " << value;
// }

// void MainViewManager::debugDistanceChanged(double value)
// {
//     qDebug() << "distanceChanged signal triggered";
//     qDebug() << "In debugDistanceChanged with value " << value;
// }
