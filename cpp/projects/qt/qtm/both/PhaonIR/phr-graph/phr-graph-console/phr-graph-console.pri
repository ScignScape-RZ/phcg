
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = phr-graph-console

include(../build-group.pri)

TEMPLATE = app

DEFINES += DEFAULT_KPH_FOLDER=\\\"$$CPP_ROOT_DIR/kph\\\"
DEFINES += DEFAULT_PHR_FOLDER=\\\"$$CPP_ROOT_DIR/phr\\\"
DEFINES += DEFAULT_PHR_GEN_FOLDER=\\\"$$CPP_ROOT_DIR/phr/gen\\\"

DEFINES += USE_RZNS
DEFINES += CAON_DEBUG

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_GROUP_DIR/phr-graph-core


#INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR
#INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR
#INCLUDEPATH += $$QHYP_SRC_GROUP_DIR
#INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
#INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

INCLUDEPATH += $$HGDM_SRC_GROUP_DIR
INCLUDEPATH += $$PHAONIR_SRC_GROUP_DIR
INCLUDEPATH += $$PHAONLIB_SRC_GROUP_DIR


CONFIG += no_keywords


DEFINES += USE_KANS

DEFINES += DEFAULT_PTR_BYTE_CODE=QT_POINTER_SIZE

HEADERS += \



SOURCES += \
  $$SRC_DIR/main.cpp \



LIBS += -L$$TARGETSDIR  -lphr-graph-core



message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

