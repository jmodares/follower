#MAVLINK_CONF = ardupilotmega
#DEFINES += MAVLINK_COMM_NUM_BUFFERS=4

CONFIG += ordered

TEMPLATE = subdirs

SUBDIRS += \
    qgc_cli \
    agent \
