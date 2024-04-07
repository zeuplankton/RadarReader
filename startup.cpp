#include "startup.h"
#include "Model/provider.h"
#include <QThread>

const int TIMER_INTERVAL = 250;

Startup::Startup(QObject *parent,  QGuiApplication& app)
    : QObject{parent},
    m_app(app),
    m_engine(*new QQmlApplicationEngine()),
    m_mainViewManager(*new MainViewManager()),
    m_settings(Provider::getSettingsAsSingleton()),
    m_instrument(*new Instrument(this, m_settings, Provider::getConnectorForSingleUse(), *new QThread())),
    m_bootDelay(0),
    m_timer(*new QTimer(this))
{
    m_settings.parseJSONData();
    m_mainViewManager.initialize(m_settings);
    auto rootContext = m_engine.rootContext();
    rootContext->setContextProperty("MainViewManager", &m_mainViewManager);
    const QUrl url(QStringLiteral("qrc:/qt/qml/Main.qml"));
    QObject::connect(
        &m_engine, &QQmlApplicationEngine::objectCreationFailed,
        &m_app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    m_engine.load(url);
    wireMainViewManager2Instrument();
    // m_instrument.initialize();
    wireInstrument2MainViewManager();
    setupBootDelayTimer();

}

void Startup::onTimerFired()
{
    static int counter = 0;
    ++counter;
    float elapsed_time = TIMER_INTERVAL * counter;
    float progress = (elapsed_time/m_bootDelay) * 100.0;
    m_mainViewManager.setFeedbackProgress(progress);
    if (progress > 100) {
        qDebug() << "Startup::onTimerFired, about to initialize instrument";
        m_instrument.initialize();
        m_timer.stop();
    }
}

void Startup::wireMainViewManager2Instrument()
{
    QObject::connect(&m_mainViewManager, &MainViewManager::powerOnChanged,
                     &m_instrument, &Instrument::onPowerChangedFromMainviewmanager);
    QObject::connect(&m_mainViewManager, &MainViewManager::velocityChanged,
                     &m_instrument, &Instrument::onVelocityChangedFromMainviewmanager);
    QObject::connect(&m_mainViewManager, &MainViewManager::distanceChanged,
                     &m_instrument, &Instrument::onDistanceChangedFromMainviewmanager);
}

void Startup::wireInstrument2MainViewManager()
{
    QObject::connect(&m_instrument, &Instrument::notifyMainviewmanagerOfStatusUpdate,
                     &m_mainViewManager, &MainViewManager::onStatusUpdateFromInstrument);
    QObject::connect(&m_instrument, &Instrument::notifyMainviewmanagerThatInitializationDone,
                     &m_mainViewManager, &MainViewManager::onInitializationDoneFromInstrument);
}

void Startup::setupBootDelayTimer()
{
    m_bootDelay = m_settings.getBootDelay();
    bool in_test_mode = m_settings.getTestMode();
    if (in_test_mode) {
        m_bootDelay = 5000;
    }
    m_timer.setInterval(TIMER_INTERVAL);
    QObject::connect(&m_timer, SIGNAL(timeout()), SLOT(onTimerFired()));
    m_timer.start();
}
