
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = phr-graph-core

include(../build-group.pri)


DEFINES += DEFAULT_KPH_FOLDER=\\\"$$CPP_ROOT_DIR/kph\\\"



INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


DEFINES += USE_RZNS
DEFINES += CAON_DEBUG

#INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR
#INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR
#INCLUDEPATH += $$QHYP_SRC_GROUP_DIR
#INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
#INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR
#INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

INCLUDEPATH += $$HGDM_SRC_GROUP_DIR
INCLUDEPATH += $$PHAONLIB_SRC_GROUP_DIR

CONFIG += no_keywords

DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/kernel/graph/phr-graph.h \
  $$SRC_DIR/kernel/graph/phr-graph-connection.h \
  $$SRC_DIR/kernel/graph/phr-graph-node.h \
  $$SRC_DIR/kernel/phr-graph-dominion.h \
  $$SRC_DIR/kernel/dominion/types.h \
  $$SRC_DIR/kernel/dominion/connectors.h \
  $$SRC_DIR/kernel/phr-graph-root.h \
  $$SRC_DIR/kernel/document/phr-graph-document.h \
  $$SRC_DIR/kernel/frame/phr-graph-frame.h \
  $$SRC_DIR/kernel/query/phr-graph-query.h \
  $$SRC_DIR/token/phr-graph-token.h \
  $$SRC_DIR/output/phr-graph-output.h \
  $$SRC_DIR/output/phr-graph-phr-output.h \
  $$SRC_DIR/output/generators/statement-generator.h \


SOURCES += \
  $$SRC_DIR/kernel/graph/phr-graph.cpp \
  $$SRC_DIR/kernel/graph/phr-graph-connection.cpp \
  $$SRC_DIR/kernel/graph/phr-graph-node.cpp \
  $$SRC_DIR/kernel/phr-graph-dominion.cpp \
  $$SRC_DIR/kernel/phr-graph-root.cpp \
  $$SRC_DIR/kernel/document/phr-graph-document.cpp \
  $$SRC_DIR/kernel/frame/phr-graph-frame.cpp \
  $$SRC_DIR/kernel/query/phr-graph-query.cpp \
  $$SRC_DIR/token/phr-graph-token.cpp \
  $$SRC_DIR/output/phr-graph-output.cpp \
  $$SRC_DIR/output/phr-graph-phr-output.cpp \
  $$SRC_DIR/output/generators/statement-generator.cpp \

#LIBS += -L$$TARGETSDIR  -lphr-direct-eval

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

