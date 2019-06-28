
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "udpipe.h"

#include <QDebug>

#include "dygred-sentence/dygred-sentence.h"
#include "dygred-sentence/dygred-corpus.h"

#include "dygred-runtime-environment/dygred-runtime-environment.h"

#include "rz-graph-visit/rz-lisp-graph-visitor-dynamo.h"


#include <QtEndian>

#include <QtGlobal>
#include <QtCore>


#include <QDebug>

#include "rzns.h"

#include "rz-graph-core/kernel/document/rz-re-document.h"
#include "rz-graph-core/output/rz-re-pre-normal-lisp.h"

#include "rz-graph-code/prerun/rz-re-prerun-tokens.h"
#include "rz-graph-code/prerun/rz-re-prerun-normalize.h"
#include "rz-graph-code/prerun/rz-re-prerun-anticipate.h"

#include "rz-graph-visit/rz-lisp-graph-visitor.h"
#include "rz-code-generators/rz-dynamo-output.h"


#include "sexp/parser.hpp"
#include "lisp/writer.hpp"


#include "kcm-lisp-runtime.h"

#include "kans.h"

#include "kauvir-type-system/kauvir-universal-class.h"

#include "kcm-runtime-eval/basic-functions/rz-dynamo-basic-functions.h"


#include "kcm-runtime-eval/fn-doc/fn-doc.h"
#include "kcm-runtime-eval/kcm-env/kcm-env.h"


#include <functional>
#include <QDebug>


#include "kcm-lisp-bridge/kcm-lisp-bridge.h"
#include "kcm-lisp-bridge/kcm-lisp-embed-environment.h"
#include "kcm-lisp-bridge/kcm-lisp-eval.h"

#include "kauvir-code-model/kauvir-code-model.h"
#include "kauvir-code-model/kcm-channel-group.h"


#include "kauvir-runtime/kcm-command-runtime/kcm-command-runtime-table.h"
#include "kcm-runtime-eval/kcm-scopes/kcm-scope-system.h"


#include "kcm-runtime-eval/kcm-direct-eval/kcm-direct-eval.h"

#include "rz-dygred-functions.h"



USING_KANS(KCM)
USING_KANS(KCL)
//USING_KANS(QRing)


int mainx(int argc, char* argv[])
{
 QString root = "C:/repos/kauv-rz/data/udpipe/set1";
 DygRed_Corpus dgc(root);

 int result = 0;

 QStringList infiles{"@t1.txt"};
 QString outfile = "@out/t2.txt";

 dgc.add_files(infiles);
 result = dgc.detokenize(outfile);

 return result;
}

void compile_rz(QString file_name)
{
 QString result;

 RE_Document* doc = new RE_Document(file_name);
 doc->parse();

 doc->report_graph(file_name + ".txt");

 RE_Pre_Normal_Lisp prenorm(doc);
 prenorm.output("..prenorm.txt");

 RE_Prerun_Tokens tokens(doc);
 tokens.output("..prenorm2.txt");


 RE_Prerun_Normalize normalize(*doc->graph());


 caon_ptr<RZ_Lisp_Graph_Visitor> visitor = normalize.scan();

 visitor->set_document_directory(doc->local_directory());

 RZ_Lisp_Graph_Visitor_Dynamo visitor_dynamo(*visitor);
 RZ_Dynamo_Output rdo(visitor_dynamo);

 visitor->set_dynamo_output(&rdo);

 doc->report_graph(file_name + ".re1.txt");
 RE_Pre_Normal_Lisp prenorm1(doc);
 prenorm1.output("..prenorm1.txt");
 RE_Prerun_Anticipate anticipate(*visitor);
 anticipate.scan([](RZ_Dynamo_Output& rzdo){rzdo.init_top_level_block();});

 QString output;
 QTextStream qts(&output);
 rdo.write(qts);
 QString result_file = doc->local_path() + ".cl";
 QFile outfile(result_file);
 if(outfile.open(QIODevice::WriteOnly | QIODevice::Text))
 {
  QTextStream out(&outfile);
  out << output;
  outfile.close();
 }
 result = output;

 result.prepend("\n(:|RZ_GENERATED| ");
 result.append(')');
 sexp::Value value = sexp::Parser::from_string(result.toStdString());
 QString clean_result_file = doc->local_path() + ".lisp";
 QFile clean_outfile(clean_result_file);

 if(clean_outfile.open(QIODevice::WriteOnly | QIODevice::Text))
 {
  QTextStream out(&clean_outfile);

  QString vstr = QString::fromStdString(value.str_with_indent(0));
  QString start = "\n(:|RZ_GENERATED| ";
  if(vstr.startsWith(start))
  {
   vstr = vstr.mid(start.length());
  }
  if(vstr.endsWith(')'))
  {
   vstr.chop(1);
  }

  out << vstr;
  clean_outfile.close();
 }
}

void prepare_runtime()
{
 qRegisterMetaType<KCM_Lisp_Bridge>();
 qRegisterMetaType<KCM_Lisp_Bridge*>();


 qRegisterMetaType<Fn_Doc>();
 qRegisterMetaType<Fn_Doc*>();

// qRegisterMetaType<QRing>();
// qRegisterMetaType<QRing*>();


}

void run_dynamo(KCM_Lisp_Eval& kle, QString script_file, KCM_Env* kenv)
{
 kle.prepare_callbacks();

 KCM_Lisp_Runtime* lisp_runtime = kle.kcm_lisp_runtime();
 KCM_Lisp_Bridge& bridge = lisp_runtime->bridge();
 Kauvir_Code_Model& kcm = *bridge.kcm();
 Kauvir_Type_System* type_system = kcm.type_system();

 KCM_Command_Runtime_Table table(*type_system);
 kcm.set_table(&table);

 KCM_Scope_System scopes;
 kcm.set_scope_system(&scopes);

 kcm.init_scope_system();

 kenv->set_scopes(&scopes);
 kenv->set_kcm(&kcm);

 kenv->set_report_channel_group_fn([](Kauvir_Code_Model* kcm, KCM_Channel_Group* kcg)
 {
  QString qs;
  QTextStream qts(&qs);

  kcg->report(qts, *kcm, kcm->detailed_report_synax(),
    KCM_Channel::Code_Environments::Statement);

  qDebug() << qs;
 });

 init_basic_functions_kci(kcm);
 init_dygred_functions(kcm);
 kle.eval_script_file(script_file);
}

int maina(int argc, char* argv[])
{
 QString root = "&" RZ_DIR "/../../udpipe/examples";
 DygRed_Runtime_Environment dre(root);
 dre.set_model_file("@../eng/udpipe-ud-2.0-170801/english-lines-ud-2.0-170801.udpipe");
 return 0;
}

int main(int argc, char* argv[])
{

 qDebug() << "Compiling R/Z to PreDynamo: " RZ_DIR "/dygred/t1.rz";

 compile_rz(RZ_DIR "/dygred/t1.rz");

 prepare_runtime();

 KCM_Lisp_Embed_Environment env(argc, argv);

 QString out_string;
 QTextStream qts(&out_string);

 KCM_Lisp_Eval kle(&env, qts);

 kle.prepare_callbacks();

 KCM_Lisp_Eval::get_make_kcm_channel_bridge_fn_type(&make_kcm_channel_bridge);
 KCM_Lisp_Runtime* lisp_runtime = kle.kcm_lisp_runtime();
 KCM_Lisp_Bridge& bridge = lisp_runtime->bridge();
 Kauvir_Code_Model& kcm = *bridge.kcm();

 kcm.set_direct_eval_fn(&kcm_direct_eval);
 kcm.set_make_kcm_command_package_from_channel_group_fn(&make_kcm_command_package_from_channel_group);
 kcm.set_make_kcm_command_package_fn(&make_kcm_command_package);


 kcm.create_and_register_type_object("Fn_Doc");
 kcm.create_and_register_type_object("Fn_Doc*");

 kcm.create_and_register_type_object("QRing");
 kcm.create_and_register_type_object("QRing*");


 KCM_Env* kenv = new KCM_Env(nullptr);
 QString kenv_typename = "KCM_Env*";
 insert_envv(&kenv_typename, kenv);

 QString root = "&" RZ_DIR "/../../udpipe/examples";
 DygRed_Runtime_Environment* dre = new DygRed_Runtime_Environment(root);
 QString dre_typename = "DygRed_Runtime_Environment*";
 insert_envv(&dre_typename, dre);

 kcm.create_and_register_type_object("DygRed_Runtime_Environment*");
 kcm.create_and_register_type_object("DygRed_Corpus*");

 qDebug() << "Compiling PreDynamo to DynamoIR:" RZ_DIR "/dygred/t1.rz";
 kle.eval_script_file(RZ_DIR "/dygred/t1.rz.lisp");
 qDebug() << "Saving DynamoIR to: " RZ_DIR "/dygred/t1.rz.dyn.cl";
 QFile qf(RZ_DIR "/dygred/t1.rz.dyn.cl");


 if(qf.open(QIODevice::WriteOnly))
 {
  QTextStream os(&qf);
  os << out_string;
  qf.close();
 }

 qDebug() << "Running DynamoIR: " RZ_DIR "/dygred/t1.rz.dyn.cl";

 run_dynamo(kle, RZ_DIR "/dygred/t1.rz.dyn.cl", kenv);

 return 0;
}

