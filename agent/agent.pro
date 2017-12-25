#
# QGroundControl Library
#
include(qgc.pri)

CONFIG += link_prl

TARGET   = agent
TEMPLATE = app

HEADERS = \
    UBConfig.h \
    UBAgent.h \
    UBPacket.h \
    UBNetwork.h \

SOURCES = \
    main.cc \
    UBAgent.cpp \
    UBPacket.cpp \
    UBNetwork.cpp \
