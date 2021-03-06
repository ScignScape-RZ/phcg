#include "pgvm-plugin.h"
#include "pgvm-plugin_constants.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>

#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/projecttree.h>
#include <projectexplorer/project.h>
#include <projectexplorer/session.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>

#include <QAbstractSocket>

namespace PGVM_plugin {
namespace Internal {

PGVM_Plugin::PGVM_Plugin()
{
 // Create your members
}

PGVM_Plugin::~PGVM_Plugin()
{
 // Unregister objects from the plugin manager's object pool
 // Delete members
}

bool PGVM_Plugin::initialize(const QStringList &arguments, QString *errorString)
{
 // Register objects in the plugin manager's object pool
 // Load settings
 // Add actions to menus
 // Connect to other plugins' signals
 // In the initialize function, a plugin can be sure that the plugins it
 // depends on have initialized their members.

 Q_UNUSED(arguments)
 Q_UNUSED(errorString)

 auto action = new QAction(tr("Activate PGVM Plugin"), this);
 Core::Command *cmd = Core::ActionManager::registerAction(action, Constants::ACTION_ID,
                                                          Core::Context(Core::Constants::C_GLOBAL));
 cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+A")));
 connect(action, &QAction::triggered, this, &PGVM_Plugin::triggerAction);

 Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
 menu->menu()->setTitle(tr("PGVM_Plugin"));
 menu->addAction(cmd);
 Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

 return true;
}

void PGVM_Plugin::extensionsInitialized()
{
 // Retrieve objects from the plugin manager's object pool
 // In the extensionsInitialized function, a plugin can be sure that all
 // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag PGVM_Plugin::aboutToShutdown()
{
 // Save settings
 // Disconnect from signals that are not needed during shutdown
 // Hide UI (if you add UI that is not in the main window directly)
 return SynchronousShutdown;
}

void PGVM_Plugin::triggerAction()
{
 broker_.activate_server();

 broker_.cbfn = [](QString pn, QStringList& qsl)
 {
  const QList<ProjectExplorer::Project*> projects =
    ProjectExplorer::SessionManager::projects();
  for(ProjectExplorer::Project* pp : projects)
  {
   QString dn = pp->displayName();
   if(dn == pn)
   {
    ProjectExplorer::SessionManager::setStartupProject(pp);
    break;
   }
  }

  Core::ICore::instance()->openFiles(qsl);

 };

// QMessageBox::information(Core::ICore::mainWindow(),
//                          tr("Action Triggered"),
//                          tr("This is an action from PGVM."));

// const QList<ProjectExplorer::Project*> projects =
//   ProjectExplorer::SessionManager::projects();

// for(ProjectExplorer::Project* pp : projects)
// {
//  QString dn = pp->displayName();
//  if(dn == "rz-graph-phaon-console")
//  {
//   ProjectExplorer::SessionManager::setStartupProject(pp);
//   break;
//  }
// }

// ProjectExplorer::SessionManager::
//   rz-graph-phaon-console

// ProjectExplorer::Project *project = ProjectExplorer::ProjectTree::currentProject();
// Utils::FileNameList fnl = project->files(ProjectExplorer::Project::SourceFiles);

// for(const Utils::FileName& fn : fnl)
// {
//  qDebug() << fn.toString();
// }

// qDebug() << "DONE.";

 //const QStringList projectFiles = ProjectExplorer::ProjectExplorerPlugin::currentProject()->files(Project::ExcludeGeneratedFiles);

// qDebug() << projectFiles;
}

} // namespace Internal
} // namespace PGVM_plugin
