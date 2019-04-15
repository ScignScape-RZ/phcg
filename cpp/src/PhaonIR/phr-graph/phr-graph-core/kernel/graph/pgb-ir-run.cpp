
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "pgb-ir-run.h"

#include "phr-graph-build.h"

#include "textio.h"

USING_KANS(TextIO)

#include "multigraph-token.h"

#include "rzns.h"

USING_RZNS(PhrGraphCore)

PGB_IR_Run::PGB_IR_Run(PHR_Graph_Build& graph_build)
 : graph_build_(graph_build)
{

}

void PGB_IR_Run::run_from_file(QString file)
{
 QString lines;
 load_file(file, lines);

 run_lines(lines);
}

void PGB_IR_Run::run_lines(QString& lines)
{
 int pos = 0;
 int end = lines.length();

 while(pos < end)
 {
  int sp = lines.indexOf("(pgb::", pos);
  if(sp == -1)
    break;
  int np = lines.indexOf(')', sp + 6);
//  if(np == -1)
//    np = lines.indexOf("\n.\n", pos);
  if(np == -1)
    break;
  QString l = lines.mid(sp + 6, np - sp - 6).simplified();
  run_line(l);
  pos = np + 1;
 }
}


PGB_IR_Run::PGB_Methods PGB_IR_Run::parse_pgb_method(QString key)
{
#define TEMP_MACRO(x) {#x, PGB_Methods::x},

 static QMap<QString, PGB_Methods> static_map {{

  TEMP_MACRO(make_root_node)
  TEMP_MACRO(make_token_node)
  TEMP_MACRO(add_block_entry_node)
  TEMP_MACRO(add_channel_token)
  TEMP_MACRO(add_channel_entry_token)
  TEMP_MACRO(copy_value)
  TEMP_MACRO(add_statement_sequence_node)
  TEMP_MACRO(make_statement_info_node)

 }};

#undef TEMP_MACRO

 return static_map.value(key.toLower(), PGB_Methods::N_A);
}

QList<MG_Token> PGB_IR_Run::mgts_by_kind_group(const QMultiMap<MG_Token_Kinds, QPair<MG_Token, int>>& mgtm,
  MG_Token_Kind_Groups g)
{
 QList<QPair<MG_Token, int>> qlp;
 QList<MG_Token_Kinds> ks = MG_Token_Kind_Group_to_kinds(g);
 for(MG_Token_Kinds k : ks)
   qlp.append(mgtm.values(k));
 qSort(qlp.begin(), qlp.end(), [](const QPair<MG_Token, int>& pr1,
   const QPair<MG_Token, int>& pr2)
 {
  return pr1.second < pr2.second;
 });

 QList<MG_Token> result;
 std::transform(qlp.begin(), qlp.end(),
                std::back_inserter(result),
   std::bind(&QPair<MG_Token, int>::first, std::placeholders::_1)
//   [](const QPair<MG_Token, int>& pr)
//  {return pr.first;}
                //std::mem_fun(&QPair<MG_Token, int>::second)
                );
 //for(const QPair<MG_Token, int>& pr: qlp)
 return result;
}

caon_ptr<PHR_Graph_Node>* PGB_IR_Run::get_target(const QMultiMap<MG_Token_Kinds, QPair<MG_Token, int>>& mgtm)
{
 QList<MG_Token> mgts = mgts_by_kind_group(mgtm, MG_Token_Kind_Groups::Target);
 MG_Token& mgt = mgts[0];
 if(mgt.kind == MG_Token_Kinds::Ledger_Target)
   return &ledger_[mgt.raw_text];
// QString tr = mgt
// if(mgtm.values(MG_Token_Kinds::Known_Target).isEmpty())
// {
//  return &ledger_[mgtm.value(MG_Token_Kinds::Ledger_Target)];
// }
// QString tr = mgtm.value(MG_Token_Kinds::Known_Target);
 return get_known_target(mgt.raw_text);
}

caon_ptr<PHR_Graph_Node>* PGB_IR_Run::get_known_target(QString tr)
{
 if(tr == "current_node")
   return &graph_build_.current_node_;
 if(tr == "last_statement_entry_node")
   return &graph_build_.last_statement_entry_node_;
 if(tr == "last_block_pre_entry_node")
   return &graph_build_.last_block_pre_entry_node_;

 return nullptr;
}

caon_ptr<PHR_Graph_Node> PGB_IR_Run::get_arg(const QMultiMap<MG_Token_Kinds, QPair<MG_Token, int>>& mgtm)
{
 QList<MG_Token> mgts = mgts_by_kind_group(mgtm, MG_Token_Kind_Groups::Arg_Target);
 MG_Token& mgt = mgts[0];
 if(mgt.kind == MG_Token_Kinds::Arg_Ledger_Target)
   return ledger_[mgt.raw_text];
// if(mgtm.values(MG_Token_Kinds::Arg_Known_Target).isEmpty())
//   return ledger_[mgtm.value(MG_Token_Kinds::Arg_Target)];
// QString tr = mgtm.value(MG_Token_Kinds::Arg_Known_Target);
 return unpoint(get_known_target(mgt.raw_text));
}

QPair<caon_ptr<PHR_Graph_Node>, caon_ptr<PHR_Graph_Node>>
  PGB_IR_Run::get_args(const QMultiMap<MG_Token_Kinds, QPair<MG_Token, int>>& mgtm)
{
 caon_ptr<PHR_Graph_Node> r1, r2;
 QList<MG_Token> mgts = mgts_by_kind_group(mgtm, MG_Token_Kind_Groups::Arg_Target);
 MG_Token& mgt0 = mgts[0];
 if(mgt0.kind == MG_Token_Kinds::Arg_Ledger_Target)
   r1 = ledger_[mgt0.raw_text];
 else
   r1 = unpoint(get_known_target(mgt0.raw_text));
 MG_Token& mgt1 = mgts[1];
 if(mgt1.kind == MG_Token_Kinds::Arg_Ledger_Target)
   r2 = ledger_[mgt1.raw_text];
 else
   r2 = unpoint(get_known_target(mgt1.raw_text));


// if(mgtm.values(MG_Token_Kinds::Arg_Known_Target).isEmpty())
// {
//  auto vs = mgtm.values(MG_Token_Kinds::Arg_Target);
//  r1 = ledger_[vs.value(0)];
//  r2 = ledger_[vs.value(1)];
// }
// else if(mgtm.values(MG_Token_Kinds::Arg_Known_Target).size() == 1)
// {
//  r1 = unpoint(get_known_target(mgtm.value(MG_Token_Kinds::Arg_Known_Target)));
//  r2 = ledger_[mgtm.value(MG_Token_Kinds::Arg_Target)];
// }
// else
// {
//  auto vs = mgtm.values(MG_Token_Kinds::Arg_Known_Target);
//  r1 = unpoint(get_known_target(vs.value(0)));
//  r2 = unpoint(get_known_target(vs.value(1)));
// }
 return {r1, r2};
}

QList<MG_Token> PGB_IR_Run::get_generic_tokens(const QMultiMap<MG_Token_Kinds,
  QPair<MG_Token, int>>& mgtm)
{
 return mgts_by_kind_group(mgtm, MG_Token_Kind_Groups::Generic);
}

MG_Token PGB_IR_Run::get_arg_token(const QMultiMap<MG_Token_Kinds, QPair<MG_Token, int>>& mgtm)
{
 QList<MG_Token> mgts = mgts_by_kind_group(mgtm, MG_Token_Kind_Groups::Arg);
 return mgts[0];
// QList<MG_Token> mgts = mgts_by_kind_group(mgtm, MG_Token_Kind_Groups::Arg_Target);
// return mgts[0];

// if(mgtm.values(MG_Token_Kinds::Arg_Raw_Symbol).isEmpty())
//   return {MG_Token_Kinds::Arg_Raw_Value, mgtm.value(MG_Token_Kinds::Arg_Raw_Value)};
// return {MG_Token_Kinds::Arg_Raw_Symbol, mgtm.value(MG_Token_Kinds::Arg_Raw_Symbol)};
}

QString PGB_IR_Run::get_string_arg(const QMultiMap<MG_Token_Kinds, QPair<MG_Token, int>>& mgtm)
{
 return mgtm.value(MG_Token_Kinds::Arg_String_Literal).first.raw_text;
}

void PGB_IR_Run::run_line(QString fn, QMultiMap<MG_Token_Kinds, QPair<MG_Token, int>>& mgtm)
{
 PGB_Methods md = parse_pgb_method(fn);

 switch (md)
 {
 case PGB_Methods::make_root_node:
  {
   caon_ptr<PHR_Graph_Node>* tr = get_target(mgtm);
   if(tr)
     *tr = graph_build_.make_root_node();
  };
  break;
 case PGB_Methods::make_token_node:
  {
   caon_ptr<PHR_Graph_Node>* tr = get_target(mgtm);
   MG_Token tok = get_arg_token(mgtm);
   if(tr)
     *tr = graph_build_.make_token_node(tok);
   else
     graph_build_.make_token_node(tok);
  };
  break;
 case PGB_Methods::make_statement_info_node:
  {
   caon_ptr<PHR_Graph_Node>* tr = get_target(mgtm);
   QList<MG_Token> mgts = get_generic_tokens(mgtm);
   MG_Token tok = get_arg_token(mgtm);
   if(tr)
     *tr = graph_build_.make_statement_info_node(tok.raw_text,
     mgts[0].raw_text, mgts[1].raw_text);
   else
     graph_build_.make_statement_info_node(tok.raw_text,
     mgts[0].raw_text, mgts[1].raw_text);
  }
  break;
 case PGB_Methods::add_block_entry_node:
  {
   auto pr = get_args(mgtm);
   graph_build_.add_block_entry_node(pr.first, pr.second);
  }
  break;
 case PGB_Methods::add_statement_sequence_node:
  {
   auto pr = get_args(mgtm);
   graph_build_.add_statement_sequence_node(pr.first, pr.second);
  }
  break;
 case PGB_Methods::copy_value:
  {
   caon_ptr<PHR_Graph_Node>* tr = get_target(mgtm);
   caon_ptr<PHR_Graph_Node> n = get_arg(mgtm);
   if(tr)
     *tr = n;
  }
  break;
 case PGB_Methods::add_channel_token:
  {
   caon_ptr<PHR_Graph_Node> n = get_arg(mgtm);
   MG_Token mgt = get_arg_token(mgtm);
   caon_ptr<PHR_Graph_Node>* tr = get_target(mgtm);
   if(tr)
     *tr = graph_build_.add_channel_token(n, mgt);
   else
     graph_build_.add_channel_token(n, mgt);
  }
  break;
 case PGB_Methods::add_channel_entry_token:
  {
   caon_ptr<PHR_Graph_Node> n = get_arg(mgtm);
   QString cn = get_string_arg(mgtm);
   MG_Token mgt = get_arg_token(mgtm);
   caon_ptr<PHR_Graph_Node>* tr = get_target(mgtm);
   if(tr)
     *tr = graph_build_.add_channel_entry_token(n, cn, mgt);
   else
     graph_build_.add_channel_entry_token(n, cn, mgt);
  }
  break;
 default:
  break;
 }
}


void PGB_IR_Run::run_line(QString line)
{
 QStringList qsl = line.split(' ');
 QString fn = qsl.takeFirst();
 QMultiMap<MG_Token_Kinds, QPair<MG_Token, int>> mgtm;
 int i = 0;
 for(QString qs: qsl)
 {
  MG_Token mgt = MG_Token::decode_symbol(qs);
  mgtm.insert(mgt.kind, {mgt, i++});
 }
 run_line(fn, mgtm);
}

