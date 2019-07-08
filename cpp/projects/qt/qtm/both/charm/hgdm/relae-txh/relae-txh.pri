
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = relae-txh

include(../build-group.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR



CONFIG += no_keywords

DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/kernel/relae-txh-dominion.h \
  $$SRC_DIR/kernel/frame/relae-txh-frame.h \
  $$SRC_DIR/kernel/query/relae-txh-query.h \
  $$SRC_DIR/kernel/graph/relae-txh-node.h \
  $$SRC_DIR/kernel/graph/relae-txh-graph.h \


SOURCES += \
  $$SRC_DIR/kernel/relae-txh-dominion.cpp \
  $$SRC_DIR/kernel/frame/relae-txh-frame.cpp \
  $$SRC_DIR/kernel/query/relae-txh-query.cpp \
  $$SRC_DIR/kernel/graph/relae-txh-node.cpp \
  $$SRC_DIR/kernel/graph/relae-txh-graph.cpp \


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

