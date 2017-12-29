#include "UBAgent.h"
#include "UBNetwork.h"

#include "UBConfig.h"

#include <QTimer>
#include <QCommandLineParser>

#include "Vehicle.h"
#include "TCPLink.h"
#include "MissionManager.h"
#include "QGCApplication.h"

UBAgent::UBAgent(QObject *parent) : QObject(parent),
    m_mav(nullptr)
{
    m_net = new UBNetwork;
    connect(m_net, SIGNAL(dataReady(quint8, QByteArray)), this, SLOT(dataReadyEvent(quint8, QByteArray)));

    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(missionTracker()));

    startAgent();
}

void UBAgent::startAgent() {
    QCommandLineParser parser;
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);

    parser.addOptions({
        {{"I", "instance"}, "Set instance (ID) of the agent", "id"},
    });

//    parser.process(*QCoreApplication::instance());
    parser.parse(QCoreApplication::arguments());

    quint8 id = parser.value("I").toUInt();
    LinkConfiguration* link = nullptr;
    if (id) {
        quint32 port = 10 * id + STL_PORT + 3;
        TCPConfiguration* tcp = new TCPConfiguration(tr("TCP Port %1").arg(port));

        tcp->setAddress(QHostAddress::LocalHost);
        tcp->setPort(port);
        tcp->setDynamic();
        tcp->setAutoConnect();

        link = tcp;
    } else {
        SerialConfiguration* serial = new SerialConfiguration("Serial Port");

        serial->setBaud(BAUD_RATE);
        serial->setPortName(SERIAL_PORT);
        serial->setDynamic();
        serial->setAutoConnect();

        link = serial;
    }

    LinkManager* linkManager = qgcApp()->toolbox()->linkManager();
    linkManager->addConfiguration(link);
    linkManager->linkConfigurationsChanged();

    connect(qgcApp()->toolbox()->multiVehicleManager(), SIGNAL(vehicleAdded(Vehicle*)), this, SLOT(vehicleAddedEvent(Vehicle*)));
    connect(qgcApp()->toolbox()->multiVehicleManager(), SIGNAL(vehicleRemoved(Vehicle*)), this, SLOT(vehicleRemovedEvent(Vehicle*)));

    m_net->connectToHost(QHostAddress::LocalHost, 10 * id + NET_PORT);
    m_timer->start(MISSION_TRACK_RATE);
}

void UBAgent::setMAV(Vehicle* mav) {
    if (m_mav) {
        disconnect(m_mav, SIGNAL(armedChanged(bool)), this, SLOT(armedChangedEvent(bool)));
        disconnect(m_mav, SIGNAL(flightModeChanged(QString)), this, SLOT(flightModeChangedEvent(QString)));
    }

    m_mav = mav;

    if (m_mav) {
        connect(m_mav, SIGNAL(armedChanged(bool)), this, SLOT(armedChangedEvent(bool)));
        connect(m_mav, SIGNAL(flightModeChanged(QString)), this, SLOT(flightModeChangedEvent(QString)));
    }
}

void UBAgent::vehicleAddedEvent(Vehicle* mav) {
    if (!mav || m_mav == mav) {
        return;
    }

    setMAV(mav);
    m_net->setID(mav->id());

    m_mission_data.reset();
    m_mission_stage = STAGE_MISSION;

    qInfo() << "New MAV connected with ID: " << m_mav->id();
}

void UBAgent::vehicleRemovedEvent(Vehicle* mav) {
    if (!mav || m_mav != mav) {
        return;
    }

    setMAV(nullptr);
    m_net->setID(0);

    m_mission_data.reset();
    m_mission_stage = STAGE_IDLE;

    qInfo() << "MAV disconnected with ID: " << mav->id();
}

void UBAgent::armedChangedEvent(bool armed) {
    Q_UNUSED(armed);
}

void UBAgent::flightModeChangedEvent(QString mode) {
    qInfo() << mode;
}

void UBAgent::dataReadyEvent(quint8 srcID, QByteArray data) {
    if(srcID != m_mav->id() - 1) {
        return;
    }

    m_mission_data.pos = QGeoCoordinate(data.mid(0, 25).toDouble(), data.mid(0 + 25, 25).toDouble(), data.mid(0 + 25 + 25).toDouble());

    m_mission_data.tick = 0;
    m_mission_data.stage = 1;
}

void UBAgent::missionTracker() {
    switch (m_mission_stage) {
    case STAGE_IDLE:
        stageIdle();
        break;
    case STAGE_TAKEOFF:
        stageTakeoff();
        break;
    case STAGE_MISSION:
        stageMission();
        break;
    case STAGE_LAND:
        stageLand();
        break;
    default:
        break;
    }
}

void UBAgent::stageIdle() {
}

void UBAgent::stageTakeoff() {
}

void UBAgent::stageLand() {
}

void UBAgent::stageMission() {
//    if (!m_mav->guidedMode()) {
//        return;
//    }

    QByteArray lat = QByteArray::number(m_mav->coordinate().latitude(), 'g', 25);
    lat = lat.rightJustified(25, '0', true);

    QByteArray lon = QByteArray::number(m_mav->coordinate().longitude(), 'g', 25);
    lon = lon.rightJustified(25, '0', true);

    QByteArray alt = QByteArray::number(m_mav->altitudeRelative()->rawValue().toDouble(), 'g', 10);
    alt = alt.rightJustified(10, '0', true);

    m_net->sendData(m_mav->id() + 1, lat + lon + alt);

    if (!m_mission_data.stage) {
        return;
    }

    m_mission_data.tick++;
    if (m_mission_data.tick > (10 * 1000 / MISSION_TRACK_RATE)) {
        m_mission_data.reset();
        return;
    }

    QGeoCoordinate pos = m_mav->coordinate();
    pos.setAltitude(m_mav->altitudeRelative()->rawValue().toDouble());

    if (m_mission_data.pos.distanceTo(pos) < 10) {
        return;
    }

    if (m_mission_data.pos.altitude() < POINT_ZONE) {
        if (m_mav->armed()) {
            m_mav->guidedModeLand();
        }

        return;
    }

    if (pos.altitude() < POINT_ZONE) {
        m_mav->guidedModeTakeoff();
        return;
    }

    QGeoCoordinate _pos = m_mission_data.pos.atDistanceAndAzimuth(10, m_mission_data.pos.azimuthTo(pos));
    _pos.setAltitude(m_mission_data.pos.altitude());

    if (pos.distanceTo(_pos) < POINT_ZONE) {
        return;
    }

//    m_mav->guidedModeGotoLocation(_pos);
    m_mav->missionManager()->writeArduPilotGuidedMissionItem(_pos, false);
}
