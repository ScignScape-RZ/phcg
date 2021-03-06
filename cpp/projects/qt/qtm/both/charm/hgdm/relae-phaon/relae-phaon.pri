
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = relae-phaon

include(../build-group.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR



CONFIG += no_keywords

DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/kernel/relae-phaon-dominion.h \
  $$SRC_DIR/kernel/frame/relae-phaon-frame.h \
  $$SRC_DIR/kernel/query/relae-phaon-query.h \
  $$SRC_DIR/kernel/graph/relae-phaon-node.h \
  $$SRC_DIR/kernel/graph/relae-phaon-graph.h \


SOURCES += \
  $$SRC_DIR/kernel/relae-phaon-dominion.cpp \
  $$SRC_DIR/kernel/frame/relae-phaon-frame.cpp \
  $$SRC_DIR/kernel/query/relae-phaon-query.cpp \
  $$SRC_DIR/kernel/graph/relae-phaon-node.cpp \
  $$SRC_DIR/kernel/graph/relae-phaon-graph.cpp \


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

