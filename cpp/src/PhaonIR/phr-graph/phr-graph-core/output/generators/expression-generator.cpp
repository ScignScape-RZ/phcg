
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "expression-generator.h"

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


Expression_Generator::Expression_Generator()
 :  rq_(PHR_Graph_Query::instance())
{

}

void Expression_Generator::generate_from_node(QTextStream& qts,
 const PHR_Graph_Node& node)
{
 caon_ptr<PHR_Graph_Connection> cion;
 if(caon_ptr<PHR_Graph_Node> n = rq_.Channel_Entry[cion](&node))
 {
  QString channel_name;
  if(cion)
  {
   channel_name = cion->channel_name();
  }
  if(caon_ptr<PHR_Graph_Token> tokn = node.phr_graph_token())
  {
   generate_from_fn_node(qts, *tokn, channel_name, *n);
  }
  caon_ptr<PHR_Graph_Connection> cion1;
  if(caon_ptr<PHR_Graph_Node> n1 = rq_.Channel_Fuxe_Entry[cion1](n))
  {
   generate_from_node(qts, node);
  }
  if(caon_ptr<PHR_Graph_Node> n2 = rq_.Channel_Sequence(n))
  {
   if(caon_ptr<PHR_Graph_Token> tokn = n2->phr_graph_token())
   {
    generate_carrier_with_symbol(qts, *tokn);
   }
  }
 }
}



//void Expression_Generator::generate_close(QTextStream& qts)
//{
// qts << "coalesce_channel_group ;.\n"
//  "evaluate_channel_group ;.\n"
//  "delete_temps ;.\n"
//  "delete_retired ;.\n"
//  "clear_temps ;.\n"
//  "reset_program_stack";
//}


void Expression_Generator::generate_from_fn_node(QTextStream& qts,
 PHR_Graph_Token& tok, QString channel_name, const PHR_Graph_Node& arg_node)
{
 qts << "push_carrier_stack $ fuxe ;.\n";
 if(tok.type_name().isEmpty())
   tok.set_type_name("fbase");
 generate_carrier_with_symbol(qts, tok);
 generate_arg_carriers(qts, channel_name, arg_node);
}

void Expression_Generator::generate_arg_carriers(QTextStream& qts,
 QString channel_name, const PHR_Graph_Node& arg_node)
{
 qts << "push_carrier_stack $ " << channel_name << " ;.\n";
 if(caon_ptr<PHR_Graph_Token> tokn = arg_node.phr_graph_token())
 {
  if(tokn->flags.gen_raw_value)
    generate_carrier_with_raw_value(qts, *tokn);
  else
   generate_carrier_with_symbol(qts, *tokn);
 }
}

void Expression_Generator::generate_carrier_with_symbol(QTextStream& qts,
 PHR_Graph_Token& tok)
{
 QString ty = tok.type_name();
 if(!ty.isEmpty())
   qts << "hold_type_by_name $ " << ty << " ;.\n";
 qts << "push_carrier_symbol $ " << tok.raw_text() << " ;.\n";
}

void Expression_Generator::generate_carrier_with_raw_value(QTextStream& qts,
 PHR_Graph_Token& tok)
{
 QString ty = tok.type_name();
 if(!ty.isEmpty())
   qts << "hold_type_by_name $ " << ty << " ;.\n";
 qts << "push_carrier_raw_value $ " << tok.raw_text() << " ;.\n";
}

