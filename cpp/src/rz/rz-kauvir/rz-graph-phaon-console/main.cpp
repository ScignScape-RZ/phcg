
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "rz-graph-visit/rz-graph-visitor-phaon.h"


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
#include "rz-code-generators/phaon/rz-phaon-output.h"

#include "phr-graph-core/kernel/graph/phr-graph.h"
#include "phr-graph-core/kernel/graph/phr-graph-build.h"

#include "phr-graph-core/output/phr-graph-phr-output.h"

#include "kans.h"

#include <functional>
#include <QDebug>

USING_RZNS(RECore)

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

// RZ_Lisp_Graph_Visitor_Dynamo visitor_dynamo(*visitor);
// RZ_Dynamo_Output rdo(visitor_dynamo);
// visitor->set_dynamo_output(&rdo);

 RZ_Graph_Visitor_Phaon visitor_phaon(*visitor);
 RZ_Phaon_Output rpo(visitor_phaon);

 doc->report_graph(file_name + ".re1.txt");

 RE_Pre_Normal_Lisp prenorm1(doc);
 prenorm1.output("..prenorm1.txt");

 RE_Prerun_Anticipate anticipate(*visitor, doc->local_path() + ".cprs");

 anticipate.scan(nullptr);//[](RZ_Dynamo_Output& rzdo){rzdo.init_top_level_block();});

 anticipate.run_core_pairs_generations();

 PHR_Graph phg;
 PHR_Graph_Build phgb(phg);

 PHR_Graph_PHR_Output pgo(file_name + "/t1.phr");

 pgo.document()->set_graph(&pgr);

 rpo.init_top_level_block();

// anticipate.write_core_pairs(doc->local_path() + ".cprs.txt");
// anticipate.run_core_pairs();

// QString output;
// QTextStream qts(&output);

 rpo.build_phaon_graph(phgb);


 pgo.generate();

// QString result_file = doc->local_path() + ".cl";
// QFile outfile(result_file);

// if(outfile.open(QIODevice::WriteOnly | QIODevice::Text))
// {
//  QTextStream out(&outfile);
//  out << output;
//  outfile.close();
// }

#ifdef HIDE

 QString output;
 QTextStream qts(&output);

//? rdo.write(qts);

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
#endif // HIDE
}

int main(int argc, char *argv[])
{
 compile_rz(RZ_DIR "/phaon/t1.rz");

 return 0;
}
