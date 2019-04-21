
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "expression-generator.h"

#include "statement-generator.h"

#include "kernel/document/phr-graph-document.h"

#include "kernel/graph/phr-graph.h"
#include "kernel/graph/phr-graph-node.h"
#include "kernel/graph/phr-graph-connection.h"

#include "kernel/phr-graph-root.h"

#include "token/phr-graph-token.h"

#include "token/phr-graph-token.h"
#include "token/phr-graph-fuxe-entry.h"
#include "token/phr-graph-block-info.h"
#include "token/phr-graph-type-declaration.h"

#include "textio.h"
USING_KANS(TextIO)

#include "rzns.h"
USING_RZNS(PhrGraphCore)


Expression_Generator::Expression_Generator()
 :  rq_(PHR_Graph_Query::instance()), statement_generator_(nullptr)
{

}

void Expression_Generator::generate_from_node(QTextStream& qts,
 const PHR_Graph_Node& node, int unw)
{
 check_generate_type_declaration(qts, node);

 caon_ptr<PHR_Graph_Connection> cion;
 QString channel_name;
 if(caon_ptr<PHR_Graph_Node> n = rq_.Channel_Entry[cion](&node))
 {
  CAON_PTR_DEBUG(PHR_Graph_Node ,n)
  if(cion)
    channel_name = cion->channel_name();
  if(caon_ptr<PHR_Graph_Token> tokn = node.phr_graph_token())
    generate_from_fn_node(qts, *tokn, channel_name, *n, unw);
 }
 else if(n = rq_.Channel_Fuxe_Coentry[cion](&node))
 {
  CAON_PTR_DEBUG(PHR_Graph_Node ,n)
  if(cion)
  {
   if(caon_ptr<PHR_Graph_Fuxe_Entry> fen = cion->phr_node()->fuxe_entry())
   {
    if(caon_ptr<PHR_Graph_Token> tokn = node.phr_graph_token())
    {
     CAON_PTR_DEBUG(PHR_Graph_Token ,tokn)
     channel_name = cion->channel_name();
     generate_from_fn_node(qts, *tokn, channel_name, *n, unw, fen.raw_pointer());

     //generate_fuxe_entry(qts, *fen, *n1, unw + 1);
//     qts << "hold_type_by_name $ " << fen->result_type_name() << " ;.\n";
//     generate_line(qts, "!push_carrier_expression");
    }
   }
  }
 }

 caon_ptr<PHR_Graph_Connection> xcion;
 QString xchannel_name;
 caon_ptr<PHR_Graph_Node> xn = &node;
 if(xn = rq_.Channel_XEntry[cion](xn))
 {
  CAON_PTR_DEBUG(PHR_Graph_Node ,xn)
  if(cion)
    xchannel_name = cion->channel_name();
  generate_xchannel(qts, xchannel_name, *xn, unw);
 }
}

void Expression_Generator::generate_fuxe_entry(QTextStream& qts,
  PHR_Graph_Fuxe_Entry& fen,
  const PHR_Graph_Node& node, int unw)
{
 char fc = 0;
 QString cn = fen.channel_name();
 if(cn.startsWith('?'))
 {
  fc = '?';
  cn = cn.mid(1);
 }

 if(unw > 0)
   qts << "\npush_unwind_scope $ 1 "
   << cn << " ;.\n";

// qts << "\npush_unwind_scope $ "
// << unw << ' ' << cn << " ;.\n";

// else
// {
//  qts << "push_carrier_stack $ " << fen.channel_name() << " ;.\n";
//  if(!fen.result_type_name().isEmpty())
//    qts << "hold_type_by_name $ " << fen.result_type_name() << " ;.\n";
//  generate_line(qts, "index_channel_group");
// }
 generate_from_node(qts, node, unw);

 if(unw > 0)
 {
  qts << "push_carrier_stack $ " << cn << " ;.\n";
//?
//  if(!fen.result_type_name().isEmpty())
//    qts << "hold_type_by_name $ " << fen.result_type_name() << " ;.\n";
  generate_line(qts, "index_channel_group");
  generate_line(qts, "coalesce_channel_group");
  generate_comment_line(qts, "pop");
  generate_line(qts, "pop_unwind_scope");
  if(fc == '?')
    generate_line(qts, "temp_anchor_channel_group_by_need");
  else
    generate_line(qts, "temp_anchor_channel_group");
 }
 generate_comment_line(qts, "end fuxe entry");
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
  const PHR_Graph_Node& arg_node, int unw, PHR_Graph_Fuxe_Entry* fen)
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
 if(fen)
   generate_arg_carriers(qts, channel_name, arg_node, unw, fen);
 else
   generate_arg_carriers(qts, channel_name, arg_node, unw);
}

void Expression_Generator::generate_arg_carriers(QTextStream& qts,
 QString channel_name, const PHR_Graph_Node& arg_node, int unw, PHR_Graph_Fuxe_Entry* fen)
{
 qts << "push_carrier_stack $ " << channel_name << " ;.\n";
 // assume depth 1 for now ...
 generate_fuxe_entry(qts, *fen, arg_node, unw + 1);
      qts << "hold_type_by_name $ " << fen->result_type_name() << " ;.\n";
      generate_line(qts, "push_carrier_expression");
 caon_ptr<PHR_Graph_Node> n = &arg_node;
 caon_ptr<PHR_Graph_Node> n1 = nullptr;
 while(n)
 {
  CAON_PTR_DEBUG(PHR_Graph_Node ,n)
  caon_ptr<PHR_Graph_Connection> cion1;
  if(n1 = rq_.Channel_Continue(n))
  {
   if(caon_ptr<PHR_Graph_Token> tok = n1->phr_graph_token())
   {
    CAON_PTR_DEBUG(PHR_Graph_Token ,tok)
    generate_carrier(qts, *tok);
   }
  }
  else if(n1 = rq_.Channel_Fuxe_Entry[cion1](n))
  {
   // // already handled ...?
//?
#ifdef PROB_CUT
//   if(n == &arg_node)
//   {
//    n = rq_.Channel_Continue(n1);
//    continue;
//   }
#endif // PROB_CUT
   CAON_PTR_DEBUG(PHR_Graph_Node ,n1)
   if(caon_ptr<PHR_Graph_Fuxe_Entry> fen = cion1->phr_node()->fuxe_entry())
   {
    generate_fuxe_entry(qts, *fen, *n1, unw + 1);
    qts << "hold_type_by_name $ " << fen->result_type_name() << " ;.\n";
    generate_line(qts, "push_carrier_expression");
   }
  }
  else if(n1 = rq_.Channel_Fuxe_Coentry[cion1](n))
  {
   CAON_PTR_DEBUG(PHR_Graph_Node ,n1)
//     // // already handled ...?
//     if(n == &arg_node)
//     {
      n = rq_.Channel_Continue(n1);
      continue;
#ifdef PROB_CUT
//     }
//   if(caon_ptr<PHR_Graph_Fuxe_Entry> fen = cion1->phr_node()->fuxe_entry())
//   {
//    generate_fuxe_entry(qts, *fen, *n1, unw + 1);
//    qts << "hold_type_by_name $ " << fen->result_type_name() << " ;.\n";
//    generate_line(qts, "push_carrier_expression");
//   }
#endif // PROB_CUT
  }
  else if(n1 = rq_.Channel_Fuxe_Cross[cion1](n))
  {
   CAON_PTR_DEBUG(PHR_Graph_Node ,n1)
   if(caon_ptr<PHR_Graph_Fuxe_Entry> fen = cion1->phr_node()->fuxe_entry())
   {
    generate_fuxe_entry(qts, *fen, *n1, unw + 1);
    qts << "hold_type_by_name $ " << fen->result_type_name() << " ;.\n";
    generate_line(qts, "push_carrier_expression");
   }
  }
  else if(n1 = rq_.Channel_Continue_Block[cion1](n))
  {
   if(caon_ptr<PHR_Graph_Block_Info> bin = cion1->phr_node()->block_info())
   {
    if(cion1->phr_node(1))
    {
     if(caon_ptr<PHR_Graph_Statement_Info> sin = cion1->phr_node(1)->statement_info())
     {
      generate_block(qts, *bin, *n1, sin.raw_pointer());
     }
    }
    else
    {
     generate_block(qts, *bin, *n1);
    }
   }
  }
  n = n1;
 }
}

void Expression_Generator::generate_block(QTextStream& qts, PHR_Graph_Block_Info& bin,
  const PHR_Graph_Node& node, PHR_Graph_Statement_Info* sin)
{
 generate_comment_line(qts, "block ...", 2);
 generate_line(qts, "@fnp");
 statement_generator_->generate_from_node(qts, node, sin);
 generate_line(qts, "@fne");
 generate_comment_line(qts, "end block ...", 1);
 generate_empty_line(qts);
 generate_line(qts, "hold_type_by_name $ pcv");
 if(bin.fn_name().isEmpty())
   generate_line(qts, "push_carrier_anon_fn @ last_source_fn_name");
 else
   //?
   qts << "push_carrier_named_fn @ =" << bin.fn_name() << " ;.\n";

 generate_empty_line(qts);
}

void Expression_Generator::generate_xchannel(QTextStream& qts, QString channel_name,
 const PHR_Graph_Node& arg_node, int unw)
{
 generate_arg_carriers(qts, channel_name, arg_node, unw);
}

void Expression_Generator::check_generate_type_declaration(QTextStream& qts,
  const PHR_Graph_Node& node)
{
 if(caon_ptr<PHR_Graph_Node> tdn = rq_.Type_Declaration(&node))
 {
  if(caon_ptr<PHR_Graph_Type_Declaration> td = tdn->type_declaration())
  {
   CAON_PTR_DEBUG(PHR_Graph_Type_Declaration ,td)
   qts << "\ntype_decl $ " <<
     td->symbol_name() << ' ' << td->type_name() << " ;.\n";
  }
 }
}

void Expression_Generator::generate_arg_carriers(QTextStream& qts,
 QString channel_name, const PHR_Graph_Node& arg_node, int unw)
{
 qts << "push_carrier_stack $ " << channel_name << " ;.\n";
 if(caon_ptr<PHR_Graph_Token> tokn = arg_node.phr_graph_token())
 {
  CAON_PTR_DEBUG(PHR_Graph_Token ,tokn)
  generate_carrier(qts, *tokn);
 }
 caon_ptr<PHR_Graph_Node> n = &arg_node;
 caon_ptr<PHR_Graph_Node> n1 = nullptr;
 while(n)
 {
  CAON_PTR_DEBUG(PHR_Graph_Node ,n)
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
    qts << "hold_type_by_name $ " << fen->result_type_name() << " ;.\n";
    generate_line(qts, "push_carrier_expression");
   }
  }
  // no coentry right? ...
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

 //?
 if(ty.isEmpty())
 {
  if(tok.flags.is_string_literal)
    ty = "str";
  else
    ty = "u4";
 }

 if(!ty.isEmpty())
   qts << "hold_type_by_name $ " << ty << " ;.\n";

 if(tok.flags.is_string_literal)
   qts << "push_carrier_raw_value $ \"" << tok.raw_text() << "\" ;.\n";
 else
   qts << "push_carrier_raw_value $ " << tok.raw_text() << " ;.\n";
}

