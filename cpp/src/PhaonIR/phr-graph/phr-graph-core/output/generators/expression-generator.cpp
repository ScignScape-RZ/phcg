
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
#include "token/phr-graph-fuxe-entry.h"

#include "textio.h"
USING_KANS(TextIO)

#include "rzns.h"
USING_RZNS(PhrGraphCore)


Expression_Generator::Expression_Generator()
 :  rq_(PHR_Graph_Query::instance())
{

}

void Expression_Generator::generate_from_node(QTextStream& qts,
 const PHR_Graph_Node& node, int unw)
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
   generate_from_fn_node(qts, *tokn, channel_name, *n, unw);
  }
 }
}

void Expression_Generator::generate_fuxe_entry(QTextStream& qts,
  PHR_Graph_Fuxe_Entry& fen,
  const PHR_Graph_Node& node, int unw)
{
 if(unw > 0)
   qts << "\npush_unwind_scope $ "
   << unw << ' ' << fen.channel_name() << " ;.\n";
 else
 {
  qts << "push_carrier_stack $ " << fen.channel_name() << " ;.\n";
  if(!fen.result_type_name().isEmpty())
    qts << "hold_type_by_name $ " << fen.result_type_name() << " ;.\n";
  generate_line(qts, "index_channel_group");
 }
 generate_from_node(qts, node, unw);
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

void Expression_Generator::generate_line(QTextStream& qts, QString ln)
{
 qts << ln << " ;.\n";
}

void Expression_Generator::generate_empty_line(QTextStream& qts, int n)
{
 qts << QString(n, '\n');
}

void Expression_Generator::generate_comment_line(QTextStream& qts,
  QString ln, int n)
{
 if(n > 0)
   generate_empty_line(qts, n);
 qts << " .; " << ln << " ;.\n";
}

void Expression_Generator::generate_from_fn_node(QTextStream& qts,
  PHR_Graph_Token& tok, QString channel_name,
  const PHR_Graph_Node& arg_node, int unw)
{
 if(unw > 0)
 {
  qts << "\n .; unwind_scope: " << unw << " ;.\n";
 }
 generate_comment_line(qts, "generate_from_fn_node", (unw > 0)?1:2);
 qts << "push_carrier_stack $ fuxe ;.\n";
 if(tok.type_name().isEmpty())
   tok.set_type_name("fbase");
 generate_carrier(qts, tok);
 generate_comment_line(qts, "args");
 generate_arg_carriers(qts, channel_name, arg_node, unw);
}

void Expression_Generator::generate_arg_carriers(QTextStream& qts,
 QString channel_name, const PHR_Graph_Node& arg_node, int unw)
{
 qts << "push_carrier_stack $ " << channel_name << " ;.\n";
 if(caon_ptr<PHR_Graph_Token> tokn = arg_node.phr_graph_token())
 {
  generate_carrier(qts, *tokn);
 }
 caon_ptr<PHR_Graph_Node> n = &arg_node;
 caon_ptr<PHR_Graph_Node> n1 = nullptr;
 while(n)
 {
  caon_ptr<PHR_Graph_Connection> cion1;
  if(n1 = rq_.Channel_Sequence(n))
  {
   if(caon_ptr<PHR_Graph_Token> tok = n1->phr_graph_token())
   {
    generate_carrier(qts, *tok);
   }
  }
  else if(n1 = rq_.Channel_Fuxe_Entry[cion1](n))
  {
   if(caon_ptr<PHR_Graph_Fuxe_Entry> fen = cion1->phr_node()->fuxe_entry())
   {
    generate_fuxe_entry(qts, *fen, *n1, unw + 1);
   }
  }
  n = n1;
 }
}

void Expression_Generator::generate_carrier(QTextStream& qts,
  PHR_Graph_Token& tokn)
{
 if(tokn.flags.gen_raw_value)
   generate_carrier_with_raw_value(qts, tokn);
 else
   generate_carrier_with_symbol(qts, tokn);
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

