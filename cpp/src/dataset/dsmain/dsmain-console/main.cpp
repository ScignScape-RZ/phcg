
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <QApplication>
#include <QGraphicsView>

#include <QList>
#include <QDebug>

#include <QMessageBox>

#include <QMenu>

#include <QGraphicsItem>

#include <QScreen>
#include <QTimer>
#include <QTime>

#include <QImage>

#include <QApplication>
#include <QDesktopWidget>

#include <QFileDialog>

#include "defines.h"

#include "ScignStage-ling/ScignStage-ling-dialog.h"

#include "ScignStage-ling/xpdf-bridge.h"


//?#include "lexpair/lexpair-dialog.h"

#include "dsmain/language-sample.h"

//?#include "kauvir-code-model/kauvir-code-model.h"

#include "PhaonLib/phaon-runner.h"

//?#include "kcm-direct-eval/kcm-direct-eval.h"

#include "PhaonLib/phaon-symbol-scope.h"
#include "test-functions.h"

#include "dsmain/language-sample-group.h"

#include "dsmain/dataset.h"

#include "application-model/application-config-model.h"
#include "application-model/application-model.h"

#include "config-dialog/config-dialog.h"



#include "kans.h"

//?#include <QThread>

#include "textio.h"

USING_KANS(TextIO)


USING_KANS(KCM)
#ifdef USING_KPH
USING_KANS(Phaon)
USING_KANS(PhaonLib)
#endif
USING_QSNS(ScignStage)

#ifdef HIDE
void launch_config_dialog(Config_Dialog*& dlg, QWidget* parent)
{
 if(!dlg)
 {
  dlg = new Config_Dialog(parent);
 }

 dlg->set_reset_callback([]()
 {
  Application_Config_Model::reset(
  {
   DEFINES_SRC_FOLDER "/UNIBUILD-custom_defines.h",
   CHOICES_PRI_FOLDER "/UNIBUILD-custom_choices.pri",
   UNIBUILD_PRI_FOLDER "/build-custom.pro",
   CUSTOM_LIBS_PRI_FOLDER "/_xpdf.pri",
   CUSTOM_LIBS_PRI_FOLDER "/_kph.pri",
   CUSTOM_LIBS_PRI_FOLDER "/_ss3d.pri",
  }, ".reset");
 });

 dlg->set_proceed_callback([&dlg](QString qs)
 {
  qDebug() << qs;

  Application_Config_Model acm;
  //qs.prepend("gen_test__");
  acm.parse_config_code(qs);
  {
   QString result;
   QString f = acm.insert_to_defines(DEFINES_SRC_FOLDER "/UNIBUILD-custom_defines.h", result);
   save_file(f, result);
  }

  {
   QString result;
   QString f = acm.insert_to_choices(CHOICES_PRI_FOLDER "/UNIBUILD-custom_choices.pri", result);
   save_file(f, result);
  }

  {
   QString result;
   QString f = acm.insert_to_unibuild(UNIBUILD_PRI_FOLDER "/build-custom.pro", result);
   save_file(f, result);
  }

  {
   QMap<QString, QString> result;
   QMap<QString, QString> files {{
     { "xpdf", CUSTOM_LIBS_PRI_FOLDER "/_xpdf.pri" },
     { "kph", CUSTOM_LIBS_PRI_FOLDER "/_kph.pri" },
     { "ss3d", CUSTOM_LIBS_PRI_FOLDER "/_ss3d.pri" }
    }};
   acm.insert_to_custom_libs(files, result);

   QMapIterator<QString, QString> it(result);

   while(it.hasNext())
   {
    it.next();
    save_file(it.key(), it.value());
   }
  }

  dlg->register_proceed_completed(qs);
 });

 dlg->show();
}
#endif //def HIDE


int main(int argc, char **argv)
{
 QApplication qapp(argc, argv);
 qapp.setWindowIcon(QIcon(DEFAULT_ICON_FOLDER "/app-icon.png"));

// Dataset ds (DATA_FOLDER "/chapters/all.txt");
// QVector<Language_Sample*>& samps = ds.samples();

// phaong<pg_t> pg;

// QVector<Language_Sample_Group*>& groups = ds.groups();
// Language_Sample_Group::read_groups_from_file
//   (DATA_FOLDER "/chapters/all.g.txt", groups);

// Language_Sample::read_samples_from_file
//   (pg, DATA_FOLDER "/chapters/all.txt", samps, groups);

 Dataset ds;// (DEFAULT_RPH_FOLDER  "/samples.txt");
 ds.load_from_file(DEFAULT_RPH_FOLDER  "/samples.txt");



#ifdef USING_XPDF
 XPDF_Bridge xpdf_bridge(argc, argv);
 ScignStage_Ling_Dialog dlg (&xpdf_bridge, ds);
#else
 ScignStage_Ling_Dialog dlg (nullptr, ds);
#endif

#ifdef USING_KPH
 dlg.set_phr_init_function([&dlg](Phaon_Runner& phr)
 {
  Kauvir_Code_Model& kcm = phr.get_kcm();
  kcm.set_direct_eval_fn(&kcm_direct_eval);

  Phaon_Symbol_Scope* pss = new Phaon_Symbol_Scope;
  init_test_functions(&dlg, kcm, phr.get_table(), *pss);
  phr.get_phaon_scope_queue().push_front(pss);
 });
#endif

//?
// Application_Model apm(&dlg);
// dlg.set_application_model(&apm);

 dlg.set_launch_lexpair_dialog_function([](QString s)
 {
//  Lexpair_Dialog* dlg = new Lexpair_Dialog(Lexpair_Dialog::split(s), nullptr);
//  dlg->show();
 });

 dlg.set_screenshot_function([&dlg, &qapp]()
 {
  QScreen* screen = QGuiApplication::primaryScreen();
  if (!screen)
    return;
  QApplication::beep();
  int target_window_id  = dlg.winId();

  QTimer::singleShot(10000, [=]
  {
   QPixmap pixmap = screen->grabWindow(target_window_id );
   QString path = SCREENSHOTS_FOLDER "/ScignStage_Ling_Dialog.png";
   qDebug() << "Saving to path: " << path;

   QFile file(path);
   if(file.open(QIODevice::WriteOnly))
   {
    pixmap.save(&file, "PNG");
   }
  });
 });

 Config_Dialog* cdlg = nullptr;

 dlg.set_launch_config_function([&cdlg, &dlg]()
 {
  //?launch_config_dialog(cdlg, &dlg);
 });

 dlg.show();

 qapp.exec();

}
