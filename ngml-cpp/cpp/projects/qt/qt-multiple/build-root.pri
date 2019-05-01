
QT       += core

CONFIG   += console

TEMPLATE = lib

####  This should hold a path where there's a test Qt Creator build
#     (not the main Qt Creator, since plugins have to be tested
#      by starting a new Creator instance).



####  These regex matches should identify the pertinent directories and
##    build settings for Qt and qmake, based on the qmake output directory
##    (assuming you're using shadow build).  If not, a workaround would be
##    to set some of these constants by hand (most of these constants
##    are set assuming a common directory structure underneath ROOT_DIR).
##    To see the settings obtained from these substitutions,
##    uncomment the "message" lines below.

ROOT_DIR = $$OUT_PWD

ROOT_DIR ~= s!/cpp/projects.qt/.*!!


BUILD_DIR_CODE = $$OUT_PWD
BUILD_DIR_CODE ~= s!.*/(build|release)-($$PROJECT_NAME)-(.*)-(Debug|Release)!\3


TARGET_QT_VERSION = $$QT_VERSION

TARGET_QT_VERSION ~= s/\./-

TARGET_CODE = $$TARGET_QT_VERSION-$$BUILD_DIR_CODE

TARGET_NUM = targets-$${TARGET_CODE}

CPP_ROOT_DIR = $$ROOT_DIR/cpp

PROJECTS_ROOT_DIR = $$ROOT_DIR/projects

QT_PROJECTS_ROOT_DIR = $$PROJECTS_ROOT_DIR/qt

PROJECTS_DIR = $$QT_PROJECTS_ROOT_DIR/qt$$TARGET_CODE

SRC_ROOT_DIR = $$CPP_ROOT_DIR/src

SRC_GLOBAL_DIR = $$CPP_ROOT_DIR/src/global

SRC_GROUP_DIR = $$SRC_ROOT_DIR/$$PROJECT_GROUP

SRC_DIR = $$SRC_GROUP_DIR/$$PROJECT_NAME

#message($$SRC_DIR)



TARGET = $$PROJECT_NAME

 #   Here the projects are separated more as distinct repositories ...
 #   but an alternative is to keep the project and source files in a
 #   common folder.  In either case they need a common TARGET folder.
 #
 #   MULTI_PROJECT_TARGETS_DIR = $$CPP_ROOT_DIR/

MULTI_PROJECT_TARGETS_DIR = $$CPP_ROOT_DIR/ngml-targets

 #   This might need to be edited
 #MULTI_PROJECT_TARGETS_DIR = $$ROOT_DIR/../../rz-targets



TARGETS_ROOT_DIR = $$MULTI_PROJECT_TARGETS_DIR/targets/qt/qt-multiple

TARGETSDIR = $$TARGETS_ROOT_DIR/$$TARGET_NUM


CONFIG(debug, debug|release) {
    OBJECTS_DIR = $$TARGETSDIR/PROJECT_OBJECTS/$$PROJECT_NAME/debug
} else {
    OBJECTS_DIR = $$TARGETSDIR/PROJECT_OBJECTS/$$PROJECT_NAME/release
}



#  This sometimes comes in handy for Qt Creator Plugins
CONFIG(debug, debug|release) {
    DESTDIR = $$TARGETSDIR
} else {
 #   DESTDIR = $$QT_PLUGINS_LIB_DIR
}


QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -std=gnu++0x -w

INCLUDEPATH += $$SRC_DIR $$SRC_ROOT_DIR $$SRC_GLOBAL_DIR


#DEFINES += NO_CAON

#  This applies for projects grouped in the file system;
#  for repositories however they may be more separated so
#  the other groups' locations have to be managed for each group.

#groups
#RZ_CORE_SRC_GROUP_DIR = $$SRC_ROOT_DIR/rz-core
#RZ_NGML_SRC_GROUP_DIR = $$SRC_ROOT_DIR/rz-ngml



