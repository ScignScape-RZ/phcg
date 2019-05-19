DEFINES += PGVM_PLUGIN_LIBRARY

# PGVM_PLUGIN files

SOURCES += pgvm-plugin.cpp

HEADERS += pgvm-plugin.h \
        pgvm-plugin_global.h \
        pgvm-plugin_constants.h

#?INCLUDEPATH += c:/qtsrc/qt-creator/src/libs/ c:/qtsrc/qt-creator/src/plugins

INCLUDEPATH += /home/nlevisrael/QtSrc/QtCreator/src/qt-creator/src/libs/
INCLUDEPATH += /home/nlevisrael/QtSrc/QtCreator/src/qt-creator/src/plugins/

#/home/nlevisrael/QtSrc/QtCreator/src/qt-creator/src/plugins/projectexplorer/projectexplorer.h

QT += core widgets network

TEMPLATE = lib

# Qt Creator linking

## Either set the IDE_SOURCE_TREE when running qmake,
## or set the QTC_SOURCE environment variable, to override the default setting
#isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = $$(QTC_SOURCE)
#isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = "C:/qtsrc/qt-creator/src/"

## Either set the IDE_BUILD_TREE when running qmake,
## or set the QTC_BUILD environment variable, to override the default setting
#isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = $$(QTC_BUILD)
#isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = "C:/Qt511/Tools/QtCreator/bin"

## uncomment to build plugin into user config directory
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%\QtProject\qtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/data/QtProject/qtcreator" or "~/.local/share/data/QtProject/qtcreator" on Linux
##    "~/Library/Application Support/QtProject/Qt Creator" on OS X
#USE_USER_DESTDIR = yes

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = PGVM_PLUGIN
QTC_LIB_DEPENDS += \
    # nothing here at this time

QTC_PLUGIN_DEPENDS += \
    coreplugin

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######
include(/home/nlevisrael/QtSrc/QtCreator/src/qt-creator/src/qtcreatorplugin.pri)

#include($$IDE_SOURCE_TREE/src/qtcreatorplugin.pri)
#

LIBS += -L/home/nlevisrael/Qt5123/qt/Tools/QtCreator/lib/qtcreator -lExtensionSystem
LIBS += -L/home/nlevisrael/Qt5123/qt/Tools/QtCreator/lib/qtcreator/plugins -lCore

LIBS += -L/home/nlevisrael/Qt5123/qt/Tools/QtCreator/lib/qtcreator/plugins -lProjectExplorer

#LIBS += -LC:/qtsrc/build-qtcreator-qt511-Debug/lib/qtcreator

#LIBS += -LC:/qtsrc/build-qtcreator-qt511-Debug/lib/qtcreator
#LIBS += -LC:/qtsrc/build-qtcreator-qt511-Debug/lib/qtcreator/plugins

#LIBS += -LC:/qtsrc/build-qtcreator-MSVC_Qt510-Debug/lib/qtcreator
#LIBS += -LC:/qtsrc/build-qtcreator-MSVC_Qt510-Debug/lib/qtcreator/plugins


#include(C:/qtsrc/qt-creator/src/qtcreatorplugin.pri)


#?
#LIBS += C:/qtsrc/build-qtcreator-qt511-Debug/lib/qtcreator/libExtensionSystemd4.a
#LIBS += C:/qtsrc/build-qtcreator-qt511-Debug/lib/qtcreator/plugins/libCored4.a


#LIBS += c:/Qt510/Tools/QtCreator/bin/ExtensionSystem4.dll
#LIBS += "C:/Qt511/Tools/QtCreator/bin/ExtensionSystem4.dll"
#LIBS += "C:/Qt511/Tools/QtCreator/bin/Utils4.dll"
#/c/Qt510/Tools/QtCreator/bin/Utils4.dll

#DISTFILES += \
#    pgvm-plugin.json.in



