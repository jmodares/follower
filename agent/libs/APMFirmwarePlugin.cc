/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


/// @file
///     @author Don Gagne <don@thegagnes.com>

#include "APMFirmwarePlugin.h"
#include "APMAutoPilotPlugin.h"
#include "QGCMAVLink.h"
#include "QGCApplication.h"
#include "APMFlightModesComponentController.h"
#include "APMAirframeComponentController.h"
#include "APMSensorsComponentController.h"

#include <QTcpSocket>

#include "UBConfig.h"

void APMFirmwarePlugin::initializeVehicle(Vehicle* vehicle)
{
    vehicle->setFirmwarePluginInstanceData(new APMFirmwarePluginInstanceData);

    if (vehicle->isOfflineEditingVehicle()) {
        switch (vehicle->vehicleType()) {
        case MAV_TYPE_QUADROTOR:
        case MAV_TYPE_HEXAROTOR:
        case MAV_TYPE_OCTOROTOR:
        case MAV_TYPE_TRICOPTER:
        case MAV_TYPE_COAXIAL:
        case MAV_TYPE_HELICOPTER:
            vehicle->setFirmwareVersion(3, 4, 0);
            break;
        case MAV_TYPE_FIXED_WING:
            vehicle->setFirmwareVersion(3, 5, 0);
            break;
        case MAV_TYPE_GROUND_ROVER:
        case MAV_TYPE_SURFACE_BOAT:
            vehicle->setFirmwareVersion(3, 0, 0);
            break;
        case MAV_TYPE_SUBMARINE:
            vehicle->setFirmwareVersion(3, 4, 0);
            break;
        default:
            // No version set
            break;
        }
    } else {
        // Streams are not started automatically on APM stack
//        vehicle->requestDataStream(MAV_DATA_STREAM_RAW_SENSORS,     2);
//        vehicle->requestDataStream(MAV_DATA_STREAM_EXTENDED_STATUS, 2);
//        vehicle->requestDataStream(MAV_DATA_STREAM_RC_CHANNELS,     2);
//        vehicle->requestDataStream(MAV_DATA_STREAM_POSITION,        3);
//        vehicle->requestDataStream(MAV_DATA_STREAM_EXTRA1,          10);
//        vehicle->requestDataStream(MAV_DATA_STREAM_EXTRA2,          10);
//        vehicle->requestDataStream(MAV_DATA_STREAM_EXTRA3,          3);

        vehicle->requestDataStream(MAV_DATA_STREAM_RAW_SENSORS,     MAV_DATA_STREAM_RAW_SENSORS_RATE);
        vehicle->requestDataStream(MAV_DATA_STREAM_EXTENDED_STATUS, MAV_DATA_STREAM_EXTENDED_STATUS_RATE);
        vehicle->requestDataStream(MAV_DATA_STREAM_RC_CHANNELS,     MAV_DATA_STREAM_RC_CHANNELS_RATE);
        vehicle->requestDataStream(MAV_DATA_STREAM_POSITION,        MAV_DATA_STREAM_POSITION_RATE);
        vehicle->requestDataStream(MAV_DATA_STREAM_EXTRA1,          MAV_DATA_STREAM_EXTRA1_RATE);
        vehicle->requestDataStream(MAV_DATA_STREAM_EXTRA2,          MAV_DATA_STREAM_EXTRA2_RATE);
        vehicle->requestDataStream(MAV_DATA_STREAM_EXTRA3,          MAV_DATA_STREAM_EXTRA3_RATE);
    }
}
