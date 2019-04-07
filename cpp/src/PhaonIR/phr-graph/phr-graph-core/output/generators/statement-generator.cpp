
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

}

void Statement_Generator::generate_from_node(QTextStream& qts,
 const PHR_Graph_Node& node, PHR_Graph_Statement_Info* si)
{
 expression_generator_.generate_from_node(qts, node);
 generate_close(qts, si);
}

void Statement_Generator::generate_close(QTextStream& qts, PHR_Graph_Statement_Info* si)
{
 qts << "coalesce_channel_group ;.\n";
 if(si)
   qts << "copy_anchor_channel_group $ " <<
   si->anchor_name() << ' ' << si->channel_name() << " ;.\n";
 qts <<
  "evaluate_channel_group ;.\n"
  "delete_temps ;.\n"
  "delete_retired ;.\n"
  "clear_temps ;.\n"
  "reset_program_stack";
}
