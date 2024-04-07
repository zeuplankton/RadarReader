#ifndef STARTUP_H
#define STARTUP_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "ViewManager/mainviewmanager.h"
#include <QQmlContext>
#include "Model/settings.h"
#include "Model/instrument.h"
#include <QGuiApplication>

#include <QTimer>


class Startup : public QObject
{
    Q_OBJECT
public:
    explicit Startup(QObject *parent,  QGuiApplication& app);

signals:

private slots:
    void onTimerFired();

private:
    QGuiApplication& m_app;
    QQmlApplicationEngine& m_engine;
    MainViewManager& m_mainViewManager;
    Settings& m_settings;
    Instrument& m_instrument;
    int m_bootDelay;
    QTimer& m_timer;

    void wireMainViewManager2Instrument();
    void wireInstrument2MainViewManager();
    void setupBootDelayTimer();

};

#endif // STARTUP_H
