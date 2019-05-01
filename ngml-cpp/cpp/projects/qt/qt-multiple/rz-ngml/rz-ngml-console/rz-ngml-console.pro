
PROJECT_NAME = rz-ngml-console


include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_GROUP_DIR/rz-ngml \
  $$RZ_CORE_SRC_GROUP_DIR $$RZ_ROOT_SRC_DIR

QT += widgets


TEMPLATE = app

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES



HEADERS += \


SOURCES += \
 $$SRC_DIR/main.cpp \


LIBS += -L$$TARGETSDIR -lrz-ngml
