
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rtxh-parser

include(../build-group.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$HGDM_SRC_GROUP_DIR/relae-txh


CONFIG += no_keywords

DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/grammar/rtxh-graph-build.h \
  $$SRC_DIR/grammar/rtxh-grammar.h \
  $$SRC_DIR/grammar/rtxh-parse-context.h \
  $$SRC_DIR/grammar/rtxh-parser.h \
  $$SRC_DIR/rtxh-document.h \


SOURCES += \
  $$SRC_DIR/grammar/rtxh-graph-build.cpp \
  $$SRC_DIR/grammar/rtxh-grammar.cpp \
  $$SRC_DIR/grammar/rtxh-parse-context.cpp \
  $$SRC_DIR/grammar/rtxh-parser.cpp \
  $$SRC_DIR/rtxh-document.cpp \



LIBS += -L$$TARGETSDIR -lrelae-txh


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

