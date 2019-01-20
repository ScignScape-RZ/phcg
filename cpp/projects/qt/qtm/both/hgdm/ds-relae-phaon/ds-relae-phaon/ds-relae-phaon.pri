
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = ds-rph-console

include(../build-group.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR


INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR/relae-phaon


CONFIG += no_keywords

DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/grammar/rph-graph-build.h \
  $$SRC_DIR/grammar/rph-grammar.h \
  $$SRC_DIR/grammar/rph-parse-context.h \
  $$SRC_DIR/grammar/rph-parser.h \
  $$SRC_DIR/rph-document.h \


SOURCES += \
  $$SRC_DIR/grammar/rph-graph-build.cpp \
  $$SRC_DIR/grammar/rph-grammar.cpp \
  $$SRC_DIR/grammar/rph-parse-context.cpp \
  $$SRC_DIR/grammar/rph-parser.cpp \
  $$SRC_DIR/rph-document.cpp \



LIBS += -L$$TARGETSDIR -lrelae-phaon


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

