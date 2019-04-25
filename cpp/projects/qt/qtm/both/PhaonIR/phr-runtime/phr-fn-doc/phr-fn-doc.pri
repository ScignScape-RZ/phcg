
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = phr-fn-doc

include(../build-group.pri)


DEFINES += USE_KANS


INCLUDEPATH += $$PHAONIR_SRC_GROUP_DIR

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


DEFINES += AR_ROOT_DIR=\\\"$$ROOT_DIR\\\"




HEADERS +=  \
  $$SRC_DIR/phr-fn-doc.h \
  $$SRC_DIR/phr-fn-doc-multi.h \

SOURCES +=  \
  $$SRC_DIR/phr-fn-doc.cpp \
  $$SRC_DIR/phr-fn-doc-multi.cpp \

CONFIG += no_keywords


LIBS += -L$$TARGETSDIR -lphaon-ir #-lkcm-scopes -lkcm-env
