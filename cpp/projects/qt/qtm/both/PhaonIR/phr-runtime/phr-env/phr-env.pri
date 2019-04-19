
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = phr-env

include(../build-group.pri)

DEFINES += USE_KANS


INCLUDEPATH += $$PHAONIR_SRC_GROUP_DIR


HEADERS +=  \
  $$SRC_DIR/phr-env.h \


SOURCES +=  \
  $$SRC_DIR/phr-env.cpp \


CONFIG += no_keywords


LIBS += -L$$TARGETSDIR #-lkcm-scopes
