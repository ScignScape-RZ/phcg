
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-graph-phr-output.h"

#include "kernel/document/phr-graph-document.h"

#include "kernel/graph/phr-graph.h"
#include "kernel/graph/phr-graph-node.h"

#include "kernel/phr-graph-root.h"

#include "token/phr-graph-token.h"

#include "token/phr-graph-token.h"

#include "textio.h"
USING_KANS(TextIO)

#include "rzns.h"
USING_RZNS(PhrGraphCore)


PHR_Graph_PHR_Output::PHR_Graph_PHR_Output(QString outpath, QString inpath)
 : PHR_Graph_Output(nullptr), output_path_(outpath)
{
 document_ = new PHR_Graph_Document(inpath);
}

void PHR_Graph_PHR_Output::generate_from_node(QTextStream& qts,
 const PHR_Graph_Node& node)
{
 if(caon_ptr<PHR_Graph_Node> sen = rq_.Statement_Entry(&node))
 {
  statement_generator_.generate_from_node(qts, *sen);
//  generate_statement()
//  if(caon_ptr<PHR_Graph_Token> sent = sen->phr_graph_token())
//  {
//   qts << sent->raw_text();
//  }
 }
}

void PHR_Graph_PHR_Output::generate(QTextStream& qts)
{
 CAON_PTR_DEBUG(PHR_Graph_Document ,document_)

 caon_ptr<PHR_Graph_Node> node = document_->graph()->root_node();
 generate_from_node(qts, *node);


}

void PHR_Graph_PHR_Output::generate()
{
 QString text;
 QTextStream qts(&text);
 generate(qts);
 save_file(output_path_, text);
}

