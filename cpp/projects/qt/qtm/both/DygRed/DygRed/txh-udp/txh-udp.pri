
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = txh-udp

include(../build-group.pri)

#TEMPLATE = app

#DEFINES += DEFAULT_KPH_FOLDER=\\\"$$CPP_ROOT_DIR/kph\\\"

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


INCLUDEPATH += $$SRC_PROSET_DIR/DygRed/udpipe
INCLUDEPATH += $$SRC_PROSET_DIR/QRing


INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR
INCLUDEPATH += $$QHYP_SRC_GROUP_DIR
INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

INCLUDEPATH += $$HGDM_SRC_GROUP_DIR/relae-txh
INCLUDEPATH += $$HGDM_SRC_GROUP_DIR


CONFIG += no_keywords


DEFINES += USE_KANS


HEADERS += \
    $$SRC_DIR/txh-udp-sentence.h \
    $$SRC_DIR/txh-udp-corpus.h \


SOURCES += \
    $$SRC_DIR/txh-udp-sentence.cpp \
    $$SRC_DIR/txh-udp-corpus.cpp \



LIBS += -L$$TARGETSDIR -ludpipe -lqring


