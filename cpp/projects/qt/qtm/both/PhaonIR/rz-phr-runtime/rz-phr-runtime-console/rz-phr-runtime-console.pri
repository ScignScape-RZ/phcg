
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = rz-phr-runtime-console

include(../build-group.pri)

#include(../../../../find-ecl-sexp.pri)


TEMPLATE = app
CONFIG += console

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

DEFINES += RZ_DIR=\\\"$$ROOT_DIR/scripts/rz\\\"


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR \
  $$SRC_GROUP_DIR/rz-graph-core  $$SRC_GROUP_DIR/rz-graph-token  \

INCLUDEPATH += $$HGDM_SRC_GROUP_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHR_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$RZ_KAUVIR_SRC_GROUP_DIR
INCLUDEPATH += $$PHAONIR_SRC_GROUP_DIR
INCLUDEPATH += $$PHAONLIB_SRC_GROUP_DIR
INCLUDEPATH += $$PHR_RUNTIME_SRC_GROUP_DIR

#INCLUDEPATH += $$SEXP_DIR


CONFIG += no_keywords

DEFINES += USE_RZNS


DEFINES += DEFAULT_PTR_BYTE_CODE=QT_POINTER_SIZE


HEADERS += \
  $$SRC_DIR/basic-functions.h \

SOURCES += \
  $$SRC_DIR/main.cpp \
  $$SRC_DIR/local-program.cpp \
  $$SRC_DIR/basic-functions.cpp \


LIBS += -L$$TARGETSDIR  \
   -lrz-graph-core \
   -lrz-graph-token \
   -lrz-graph-code \
   -lrz-graph-visit \
   -lrz-code-generators \
   -lrz-graph-build \
   -lrz-graph-valuer \
   -lrz-graph-embed \
   -lrz-graph-embed-run \
   -lrz-graph-run \
   -lrz-graph-sre \
   -lrz-function-def \
   -lrz-code-elements \


LIBS += -lrz-code-generators

LIBS += -lphr-graph-core


LIBS += -L$$TARGETSDIR -lphaon-ir -lphr-direct-eval \
  -lphr-fn-doc   -lphr-env  \
    -lphr-command-runtime



#LIBS += -L$$TARGETSDIR -lsexpr

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
