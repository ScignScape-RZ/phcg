#pragma once

#include "pgvm-plugin_global.h"

#include <extensionsystem/iplugin.h>

#include "logic/pgvm-plugin-broker.h"

namespace PGVM_plugin {
namespace Internal {

class PGVM_Plugin : public ExtensionSystem::IPlugin
{
 Q_OBJECT
 Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "pgvm-plugin.json")

public:

 PGVM_Plugin_Broker broker_;

 PGVM_Plugin();
 ~PGVM_Plugin();

 bool initialize(const QStringList &arguments, QString *errorString);
 void extensionsInitialized();
 ShutdownFlag aboutToShutdown();

private:
 void triggerAction();
};

} // namespace Internal
} // namespace PGVM_plugin
