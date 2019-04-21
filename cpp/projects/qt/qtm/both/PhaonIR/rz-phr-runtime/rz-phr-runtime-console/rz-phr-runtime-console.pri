
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = rz-phr-runtime-console

include(../build-group.pri)


DEFINES += USE_KANS


INCLUDEPATH += $$PHAONIR_SRC_GROUP_DIR

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


DEFINES += AR_ROOT_DIR=\\\"$$ROOT_DIR\\\"


SOURCES +=  \
  $$SRC_DIR/main.cpp \

CONFIG += no_keywords


LIBS += -L$$TARGETSDIR #-lkcm-scopes -lkcm-env
