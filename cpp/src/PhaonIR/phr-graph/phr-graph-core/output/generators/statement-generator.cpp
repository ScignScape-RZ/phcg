
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "statement-generator.h"

#include "kernel/document/phr-graph-document.h"

#include "kernel/graph/phr-graph.h"
#include "kernel/graph/phr-graph-node.h"
#include "kernel/graph/phr-graph-connection.h"

#include "kernel/phr-graph-root.h"

#include "token/phr-graph-token.h"

#include "token/phr-graph-token.h"

#include "textio.h"
USING_KANS(TextIO)

#include "rzns.h"
USING_RZNS(PhrGraphCore)


Statement_Generator::Statement_Generator()
 :  rq_(PHR_Graph_Query::instance())
{

}

void Statement_Generator::generate_from_node(QTextStream& qts,
 const PHR_Graph_Node& node)
{
 caon_ptr<PHR_Graph_Connection> cion;
 if(caon_ptr<PHR_Graph_Node> n = rq_.Channel_Entry[cion](&node))
 {
  if(cion)
  {
   qts << cion->channel_name();
  }
  if(caon_ptr<PHR_Graph_Token> tokn = n->phr_graph_token())
  {
   qts << tokn->raw_text();
  }
 }
}

