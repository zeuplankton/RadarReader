#ifndef MAINVIEWMANAGER_H
#define MAINVIEWMANAGER_H

#include <QObject>
#include "Model/settings.h"

class MainViewManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString appName READ appName CONSTANT)
    Q_PROPERTY(QString appNameVer READ appNameVer CONSTANT)

    Q_PROPERTY(bool powerOn READ powerOn WRITE setPowerOn NOTIFY powerOnChanged FINAL)
    Q_PROPERTY(double distance READ distance WRITE setDistance NOTIFY distanceChanged FINAL)
    Q_PROPERTY(double velocity READ velocity WRITE setVelocity NOTIFY velocityChanged FINAL)
    Q_PROPERTY(double distancePreset1 READ distancePreset1 CONSTANT)
    Q_PROPERTY(double velocityPreset1 READ velocityPreset1 CONSTANT)
    Q_PROPERTY(double distancePreset2 READ distancePreset2 CONSTANT)
    Q_PROPERTY(double velocityPreset2 READ velocityPreset2 CONSTANT)
    Q_PROPERTY(double distancePreset3 READ distancePreset3 CONSTANT)
    Q_PROPERTY(double velocityPreset3 READ velocityPreset3 CONSTANT)
    Q_PROPERTY(double distancePreset4 READ distancePreset4 CONSTANT)
    Q_PROPERTY(double velocityPreset4 READ velocityPreset4 CONSTANT)


    Q_PROPERTY(bool feedbackAreaVisible READ feedbackAreaVisible WRITE setFeedbackAreaVisibility NOTIFY feedbackAreaVisibilityChanged FINAL)
    Q_PROPERTY(bool feedbackOKButtonVisible READ feedbackOKButtonVisible WRITE setFeedbackOKButtonVisibility NOTIFY feedbackOKButtonVisibilityChanged FINAL)
    Q_PROPERTY(bool instrumentControlsEnabled READ instrumentControlsEnabled WRITE enableInstrumentControls NOTIFY instrumentControlsAvailabilityChanged FINAL)
    Q_PROPERTY(QString feedbackMessage READ feedbackMessage WRITE setFeedbackMessage NOTIFY feedbackMessageChanged FINAL)
    Q_PROPERTY(int feedbackProgress READ feedbackProgress WRITE setFeedbackProgress NOTIFY feedbackProgressChanged FINAL)

public:
    explicit MainViewManager(QObject *parent = nullptr);
    QString appName() const { return m_appName; }
    QString appNameVer() const { return m_appName + " " + PROJECT_VERSION; }

    bool powerOn() const { return m_powerOn; }
    Q_INVOKABLE void setPowerOn(bool value);  // For a function to be called from QML, it has to be Q_INVOKABLE

    double distance() const { return m_distance; }
    Q_INVOKABLE void setDistance(double distance);

    double velocity() const { return m_velocity; }
    Q_INVOKABLE void setVelocity(double velocity);

    double distancePreset1() const { return m_distancePreset1; }
    double velocityPreset1() const { return m_velocityPreset1; }
    double distancePreset2() const { return m_distancePreset2; }
    double velocityPreset2() const { return m_velocityPreset2; }
    double distancePreset3() const { return m_distancePreset3; }
    double velocityPreset3() const { return m_velocityPreset3; }
    double distancePreset4() const { return m_distancePreset4; }
    double velocityPreset4() const { return m_velocityPreset4; }

    bool feedbackAreaVisible() const { return m_feedbackAreaVisible; }
    Q_INVOKABLE void setFeedbackAreaVisibility(bool value);

    bool feedbackOKButtonVisible() const { return m_feedbackOKButtonVisible; }
    Q_INVOKABLE void setFeedbackOKButtonVisibility(bool value);

    bool instrumentControlsEnabled() const { return m_instrumentControlsEnabled; }
    Q_INVOKABLE void enableInstrumentControls(bool value);

    QString feedbackMessage() const { return m_feedbackMessage; }
    Q_INVOKABLE void setFeedbackMessage(QString message);

    int feedbackProgress() const { return m_feedbackProgress; }
    Q_INVOKABLE void setFeedbackProgress(int progress);


    void initialize(const Settings& config);

signals:
    void powerOnChanged(bool value);
    void distanceChanged(double distance);
    void velocityChanged(double velocity);
    void feedbackAreaVisibilityChanged(bool value);
    void feedbackOKButtonVisibilityChanged(bool value);
    void instrumentControlsAvailabilityChanged(bool value);
    void feedbackMessageChanged(QString message);
    void feedbackProgressChanged(int progress);

public slots:
    void onStatusUpdateFromInstrument(const QString& message);
    void onInitializationDoneFromInstrument(bool value);

private slots:
    // void debugPowerOn(bool value);
    // void debugVelocityChanged(double value);
    // void debugDistanceChanged(double value);

private:
    QString m_appName;    
    bool m_powerOn;
    double m_distance;
    double m_velocity;
    double m_distancePreset1;
    double m_velocityPreset1;
    double m_distancePreset2;
    double m_velocityPreset2;
    double m_distancePreset3;
    double m_velocityPreset3;
    double m_distancePreset4;
    double m_velocityPreset4;

    bool m_feedbackAreaVisible;
    bool m_feedbackOKButtonVisible;
    bool m_instrumentControlsEnabled;
    QString m_feedbackMessage;
    int m_feedbackProgress;
};

#endif // MAINVIEWMANAGER_H
