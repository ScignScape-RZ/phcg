
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = phaon-ir-console

include(../build-group.pri)


DEFINES += DEFAULT_KPH_FOLDER=\\\"$$CPP_ROOT_DIR/kph\\\"

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR
INCLUDEPATH += $$QHYP_SRC_GROUP_DIR
INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR


CONFIG += no_keywords


DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/phaon-ir.h \
  $$SRC_DIR/channel/phr-channel-group.h \
  $$SRC_DIR/channel/phr-program-stack.h \
  $$SRC_DIR/channel/phr-channel-semantic-protocol.h \
  $$SRC_DIR/channel/phr-channel.h \
  $$SRC_DIR/channel/phr-carrier-stack.h \
  $$SRC_DIR/channel/phr-carrier.h \
  $$SRC_DIR/types/phr-type.h \
  $$SRC_DIR/types/phr-type-system.h \
  $$SRC_DIR/eval/phr-channel-group-evaluator.h \
  $$SRC_DIR/eval/phr-minimal-evaluator.h \


SOURCES += \
  $$SRC_DIR/phaon-ir.cpp \
  $$SRC_DIR/channel/phr-channel-group.cpp \
  $$SRC_DIR/channel/phr-program-stack.cpp \
  $$SRC_DIR/channel/phr-channel-semantic-protocol.cpp \
  $$SRC_DIR/channel/phr-channel.cpp \
  $$SRC_DIR/channel/phr-carrier-stack.cpp \
  $$SRC_DIR/channel/phr-carrier.cpp \
  $$SRC_DIR/types/phr-type.cpp \
  $$SRC_DIR/types/phr-type-system.cpp \
  $$SRC_DIR/eval/phr-channel-group-evaluator.cpp \
  $$SRC_DIR/eval/phr-minimal-evaluator.cpp \

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

