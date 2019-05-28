
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = ds-rph-demo-console

include(../build-group.pri)

TEMPLATE = app


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$HGDM_SRC_GROUP_DIR/relae-phaon


DEFINES += DEFAULT_RPH_FOLDER=\\\"$$DATA_ROOT_DIR/rph\\\"


CONFIG += no_keywords

DEFINES += USE_KANS

HEADERS += \
  $$SRC_DIR/language-sample.h \
  $$SRC_DIR/language-sample-group.h \


SOURCES += \
  $$SRC_DIR/main.cpp \
  $$SRC_DIR/language-sample.cpp \
  $$SRC_DIR/language-sample-group.cpp \


LIBS += -L$$TARGETSDIR  -lrelae-phaon  -lds-relae-phaon


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

