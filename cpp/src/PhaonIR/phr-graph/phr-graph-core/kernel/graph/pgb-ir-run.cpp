
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
 }};

#undef TEMP_MACRO

 return static_map.value(key.toLower(), PGB_Methods::N_A);
}

caon_ptr<PHR_Graph_Node>* PGB_IR_Run::get_target(const QMultiMap<MG_Token_Kinds, QString>& mgts)
{
 if(mgts.values(MG_Token_Kinds::Known_Target).isEmpty())
 {
  return &ledger_[mgts.value(MG_Token_Kinds::Target)];
 }
 QString tr = mgts.value(MG_Token_Kinds::Known_Target);
 return get_known_target(tr);
}

caon_ptr<PHR_Graph_Node>* PGB_IR_Run::get_known_target(QString tr)
{
 if(tr == "current_node")
   return &graph_build_.current_node_;
 return nullptr;
}

caon_ptr<PHR_Graph_Node> PGB_IR_Run::get_arg(const QMultiMap<MG_Token_Kinds, QString>& mgts)
{
 if(mgts.values(MG_Token_Kinds::Arg_Known_Target).isEmpty())
   return ledger_[mgts.value(MG_Token_Kinds::Arg_Target)];
 QString tr = mgts.value(MG_Token_Kinds::Arg_Known_Target);
 return unpoint(get_known_target(tr));
}

QPair<caon_ptr<PHR_Graph_Node>, caon_ptr<PHR_Graph_Node>>
  PGB_IR_Run::get_args(const QMultiMap<MG_Token_Kinds, QString>& mgts)
{
 caon_ptr<PHR_Graph_Node> r1, r2;
 if(mgts.values(MG_Token_Kinds::Arg_Known_Target).isEmpty())
 {
  auto vs = mgts.values(MG_Token_Kinds::Arg_Target);
  r1 = ledger_[vs.value(0)];
  r2 = ledger_[vs.value(1)];
 }
 else if(mgts.values(MG_Token_Kinds::Arg_Known_Target).size() == 1)
 {
  r1 = unpoint(get_known_target(mgts.value(MG_Token_Kinds::Arg_Known_Target)));
  r2 = ledger_[mgts.value(MG_Token_Kinds::Arg_Target)];
 }
 else
 {
  auto vs = mgts.values(MG_Token_Kinds::Arg_Known_Target);
  r1 = unpoint(get_known_target(vs.value(0)));
  r2 = unpoint(get_known_target(vs.value(1)));
 }
 return {r1, r2};
}

MG_Token PGB_IR_Run::get_arg_token(const QMultiMap<MG_Token_Kinds, QString>& mgts)
{
 if(mgts.values(MG_Token_Kinds::Arg_Raw_Symbol).isEmpty())
   return {MG_Token_Kinds::Arg_Raw_Value, mgts.value(MG_Token_Kinds::Arg_Raw_Value)};
 return {MG_Token_Kinds::Arg_Raw_Symbol, mgts.value(MG_Token_Kinds::Arg_Raw_Symbol)};
}

QString PGB_IR_Run::get_string_arg(const QMultiMap<MG_Token_Kinds, QString>& mgts)
{
 return mgts.value(MG_Token_Kinds::Arg_String_Literal);
}

void PGB_IR_Run::run_line(QString fn, QMultiMap<MG_Token_Kinds, QString>& mgts)
{
 PGB_Methods md = parse_pgb_method(fn);

 switch (md)
 {
 case PGB_Methods::make_root_node:
  {
   caon_ptr<PHR_Graph_Node>* tr = get_target(mgts);
   if(tr)
     *tr = graph_build_.make_root_node();
  };
  break;
 case PGB_Methods::make_token_node:
  {
   caon_ptr<PHR_Graph_Node>* tr = get_target(mgts);
   MG_Token tok = get_arg_token(mgts);
   if(tr)
     *tr = graph_build_.make_token_node(tok);
   else
     graph_build_.make_token_node(tok);
  };
  break;
 case PGB_Methods::add_block_entry_node:
  {
   auto pr = get_args(mgts);
   graph_build_.add_block_entry_node(pr.first, pr.second);
  }
  break;
 case PGB_Methods::add_channel_token:
  {
   caon_ptr<PHR_Graph_Node> n = get_arg(mgts);
   QString cn = get_string_arg(mgts);
   MG_Token mgt = get_arg_token(mgts);
   caon_ptr<PHR_Graph_Node>* tr = get_target(mgts);
   if(tr)
     *tr = graph_build_.add_channel_token(n, cn, mgt);
   else
     graph_build_.add_channel_token(n, cn, mgt);
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
 QMultiMap<MG_Token_Kinds, QString> mgts;
 for(QString qs: qsl)
 {
  MG_Token mgt = MG_Token::decode_symbol(qs);
  mgts.insert(mgt.kind, mgt.raw_text);
 }
 run_line(fn, mgts);
}

