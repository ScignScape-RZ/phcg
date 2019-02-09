
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = phaon-lib

include(../build-group.pri)


DEFINES += DEFAULT_KPH_FOLDER=\\\"$$CPP_ROOT_DIR/kph\\\"

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$PHAONLIB_SRC_GROUP_DIR
INCLUDEPATH += $$PHAONIR_SRC_GROUP_DIR
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR


CONFIG += no_keywords


DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/phr-namespace.h \
  $$SRC_DIR/phr-class.h \
  $$SRC_DIR/phr-function.h \
  $$SRC_DIR/phr-channel-group-table.h \
  $$SRC_DIR/phr-symbol-scope.h \
  $$SRC_DIR/phr-function-vector.h \
  $$SRC_DIR/phr-function-package.h \
  $$SRC_DIR/phr-runner.h \


SOURCES += \
  $$SRC_DIR/phr-namespace.cpp \
  $$SRC_DIR/phr-class.cpp \
  $$SRC_DIR/phr-function.cpp \
  $$SRC_DIR/phr-channel-group-table.cpp \
  $$SRC_DIR/phr-symbol-scope.cpp \
  $$SRC_DIR/phr-function-vector.cpp \
  $$SRC_DIR/phr-function-package.cpp \
  $$SRC_DIR/phr-runner.cpp \


LIBS += -L$$TARGETSDIR -lphaon-ir


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

