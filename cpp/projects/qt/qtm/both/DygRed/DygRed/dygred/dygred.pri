
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = dygred

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


CONFIG += no_keywords


DEFINES += USE_KANS


HEADERS += \
    $$SRC_DIR/dygred-sentence.h \
    $$SRC_DIR/dygred-corpus.h \
    $$SRC_DIR/dygred-word-pos.h \
    $$SRC_DIR/dygred-deprel-callbacks.h \
    $$SRC_DIR/dygred-word-group.h \
    $$SRC_DIR/dygred-word-pair.h \


SOURCES += \
    $$SRC_DIR/dygred-sentence.cpp \
    $$SRC_DIR/dygred-corpus.cpp \
    $$SRC_DIR/dygred-word-pos.cpp \
    $$SRC_DIR/dygred-deprel-callbacks.cpp \
    $$SRC_DIR/dygred-word-group.cpp \
    $$SRC_DIR/dygred-word-pair.cpp \

SOURCES += \
    $$SRC_DIR/_cbs/_groups/_det.cpp \
    $$SRC_DIR/_cbs/_groups/_advmod.cpp \
    $$SRC_DIR/_cbs/_groups/_amod.cpp \
    $$SRC_DIR/_cbs/_groups/_nsubj.cpp \
    $$SRC_DIR/_cbs/_groups/_root.cpp \
    $$SRC_DIR/_cbs/_claims/_det.cpp \
    $$SRC_DIR/_cbs/_claims/_advmod.cpp \
    $$SRC_DIR/_cbs/_claims/_amod.cpp \
    $$SRC_DIR/_cbs/_claims/_nsubj.cpp \
    $$SRC_DIR/_cbs/_claims/_root.cpp \



LIBS += -L$$TARGETSDIR -ludpipe -lqring


