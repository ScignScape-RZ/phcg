
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = phaon-ir

include(../build-group.pri)


DEFINES += DEFAULT_KPH_FOLDER=\\\"$$CPP_ROOT_DIR/kph\\\"

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


#INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR
#INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR
#INCLUDEPATH += $$QHYP_SRC_GROUP_DIR
#INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
#INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR
#INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

INCLUDEPATH += $$HGDM_SRC_GROUP_DIR
INCLUDEPATH += $$PHAONLIB_SRC_GROUP_DIR

CONFIG += no_keywords

DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/phaon-ir.h \
  $$SRC_DIR/phr-result-holder.h \
  $$SRC_DIR/channel/phr-channel-group.h \
  $$SRC_DIR/channel/phr-program-stack.h \
  $$SRC_DIR/channel/phr-channel-semantic-protocol.h \
  $$SRC_DIR/channel/phr-channel.h \
  $$SRC_DIR/channel/phr-carrier-stack.h \
  $$SRC_DIR/channel/phr-carrier.h \
  $$SRC_DIR/channel/phr-channel-system.h \
  $$SRC_DIR/runtime/phr-command-package.h \
  $$SRC_DIR/types/phr-type.h \
  $$SRC_DIR/types/phr-type-object.h \
  $$SRC_DIR/types/phr-universal-class.h \
  $$SRC_DIR/types/phr-type-system.h \
  $$SRC_DIR/eval/phr-channel-group-evaluator.h \
  $$SRC_DIR/eval/phr-minimal-evaluator.h \
  $$SRC_DIR/eval/kop-base.h \
  $$SRC_DIR/eval/kops/add.h \
  $$SRC_DIR/eval/kops/subtract.h \
  $$SRC_DIR/eval/kops/less-than.h \
  $$SRC_DIR/scopes/phr-runtime-scope.h \
  $$SRC_DIR/scopes/phr-scope-value.h \
  $$SRC_DIR/scopes/phr-scope-system.h \
  $$SRC_DIR/scopes/phr-logical-scope-info.h \
  $$SRC_DIR/phr-code-model.h \
  $$SRC_DIR/table/phr-channel-group-table.h \
  $$SRC_DIR/table/phr-symbol-scope.h \
  $$SRC_DIR/table/phr-function.h \
  $$SRC_DIR/table/phr-function-vector.h \
  $$SRC_DIR/table/phr-function-package.h \


SOURCES += \
  $$SRC_DIR/phaon-ir.cpp \
  $$SRC_DIR/phr-result-holder.cpp \
  $$SRC_DIR/channel/phr-channel-group.cpp \
  $$SRC_DIR/channel/phr-program-stack.cpp \
  $$SRC_DIR/channel/phr-channel-semantic-protocol.cpp \
  $$SRC_DIR/channel/phr-channel.cpp \
  $$SRC_DIR/channel/phr-carrier-stack.cpp \
  $$SRC_DIR/channel/phr-carrier.cpp \
  $$SRC_DIR/channel/phr-channel-system.cpp \
  $$SRC_DIR/runtime/phr-command-package.cpp \
  $$SRC_DIR/types/phr-type.cpp \
  $$SRC_DIR/types/phr-type-object.cpp \
  $$SRC_DIR/types/phr-universal-class.cpp \
  $$SRC_DIR/types/phr-type-system.cpp \
  $$SRC_DIR/eval/phr-channel-group-evaluator.cpp \
  $$SRC_DIR/eval/phr-minimal-evaluator.cpp \
  $$SRC_DIR/eval/kops/add.cpp \
  $$SRC_DIR/eval/kops/subtract.cpp \
  $$SRC_DIR/eval/kops/less-than.cpp \
  $$SRC_DIR/scopes/phr-runtime-scope.cpp \
  $$SRC_DIR/scopes/phr-scope-value.cpp \
  $$SRC_DIR/scopes/phr-scope-system.cpp \
  $$SRC_DIR/scopes/phr-logical-scope-info.cpp \
  $$SRC_DIR/phr-code-model.cpp \
  $$SRC_DIR/table/phr-channel-group-table.cpp \
  $$SRC_DIR/table/phr-symbol-scope.cpp \
  $$SRC_DIR/table/phr-function.cpp \
  $$SRC_DIR/table/phr-function-vector.cpp \
  $$SRC_DIR/table/phr-function-package.cpp \


LIBS += -L$$TARGETSDIR  -lphr-direct-eval

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

