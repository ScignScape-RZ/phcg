
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "statement-generator.h"

#include "expression-generator.h"

#include "kernel/document/phr-graph-document.h"

#include "kernel/graph/phr-graph.h"
#include "kernel/graph/phr-graph-node.h"
#include "kernel/graph/phr-graph-connection.h"

#include "kernel/phr-graph-root.h"

#include "token/phr-graph-token.h"

#include "token/phr-graph-statement-info.h"

#include "textio.h"
USING_KANS(TextIO)

#include "rzns.h"
USING_RZNS(PhrGraphCore)


Statement_Generator::Statement_Generator(Expression_Generator& expression_generator)
 :  rq_(PHR_Graph_Query::instance()),
    expression_generator_(expression_generator)
{
 expression_generator_.set_statement_generator(this);
}

void Statement_Generator::generate_anchor_without_channel_group(QTextStream& qts,
 const PHR_Graph_Node& node, PHR_Graph_Statement_Info& sin)
{
 if(caon_ptr<PHR_Graph_Token> tok = node.phr_graph_token())
 {
  qts << "\ngenerate_anchor_without_channel_group $ " <<
    tok->raw_text() << ' ' << sin.channel_name() << " ;.\n";
 }
}

void Statement_Generator::generate_from_node(QTextStream& qts,
 const PHR_Graph_Node& node, PHR_Graph_Statement_Info* sin)
{
 if(sin && sin->channel_name() == "parse-literal")
 {
  generate_anchor_without_channel_group(qts, node, *sin);
 }
 else
 {
  expression_generator_.generate_from_node(qts, node);
  generate_close(qts, sin);
 }

 node.debug_connections();

 caon_ptr<PHR_Graph_Connection> cion;
 if(caon_ptr<PHR_Graph_Node> sen = rq_.Statement_Sequence[cion](&node))
 {
  PHR_Graph_Statement_Info* sin1 = nullptr;
  if(cion)
    sin1 = cion->phr_node()->statement_info().raw_pointer();
  generate_from_node(qts, *sen, sin1);
 }
}

void Statement_Generator::generate_close(QTextStream& qts, PHR_Graph_Statement_Info* sin)
{
 qts << "coalesce_channel_group ;.\n";
 if(sin)
  qts << "copy_anchor_channel_group $ " <<
  sin->anchor_name() << ' ' << sin->channel_name() << " ;.\n";
 qts <<
  "evaluate_channel_group ;.\n"
  "delete_temps ;.\n"
  "delete_retired ;.\n"
  "clear_temps ;.\n"
  "reset_program_stack ;.\n"
  " .; end of statement ;.\n"
        ;
}
