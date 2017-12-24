#ifndef UBAGENT_H
#define UBAGENT_H

#include <QObject>
#include <QGeoCoordinate>

class QTimer;
class Vehicle;
class UBNetwork;

class UBAgent : public QObject
{
    Q_OBJECT
public:
    explicit UBAgent(QObject *parent = nullptr);

public slots:
    void startAgent();

protected slots:
    void setMAV(Vehicle* mav);

    void vehicleAddedEvent(Vehicle* mav);
    void vehicleRemovedEvent(Vehicle* mav);

    void armedChangedEvent(bool armed);
    void flightModeChangedEvent(QString mode);

    void dataReadyEvent(quint8 srcID, QByteArray data);
    void missionTracker();

protected:
    void stageIdle();
    void stageTakeoff();
    void stageMission();
    void stageLand();

protected:
    enum EMissionStage {
        STAGE_IDLE,
        STAGE_TAKEOFF,
        STAGE_MISSION,
        STAGE_LAND,
    } m_mission_stage;

    struct SMissionData {
        int stage;
        int tick;

        QGeoCoordinate pos;

        void reset() {
            stage = 0;
            tick = 0;
        }
    } m_mission_data;

protected:    
    Vehicle* m_mav;
    UBNetwork* m_net;

    QTimer* m_timer;
};

#endif // UBAGENT_H
