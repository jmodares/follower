QGC_DIR = $$PWD/../qgc_cli

#CONFIG += $$fromfile(qgroundcontrol.pro, CONFIG)
include(qgc_cli.pro)

SOURCES = \
HEADERS = \
#FORMS = \
#RESOURCES = \

LIST = $$FORMS
for(ITEM, LIST) : FORMS -= $$ITEM

LIST = $$RESOURCES
for(ITEM, LIST) : RESOURCES -= $$ITEM

LIST = $$INCLUDEPATH
for(ITEM, LIST) : INCLUDEPATH += $$QGC_DIR/$$ITEM

MAVLINKPATH_REL = libs/mavlink/include/mavlink/v2.0
MAVLINKPATH = $$QGC_DIR/$$MAVLINKPATH_REL
MAVLINK_CONF = ardupilotmega
DEFINES += MAVLINK_NO_DATA

INCLUDEPATH += $$MAVLINKPATH
INCLUDEPATH += $$MAVLINKPATH/$$MAVLINK_CONF
DEFINES += $$sprintf('QGC_USE_%1_MESSAGES', $$upper($$MAVLINK_CONF))

DebugBuild {
    QGC_LIB = $$OUT_PWD/../qgc_cli/debug
} else {
    QGC_LIB = $$OUT_PWD/../qgc_cli/release
}

LIBS += -lQGroundControl \
    -L$$QGC_LIB \
    -Wl,-rpath,$$QGC_LIB \

DEPENDPATH += $$QGC_LIB \
