
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "pgb-ir-build.h"

#include "multigraph-token.h"

#include "textio.h"
USING_KANS(TextIO)

#include "rzns.h"

USING_RZNS(PhrGraphCore)

_PGB_IR_Build::_PGB_IR_Build(QTextStream& qts)
  :  qts_(qts)
{

}

MG_Token _PGB_IR_Build::mgtoken(QString rt, MG_Token_Kind_Groups kg, MG_Token_Subgroups sg)
{
 switch(kg)
 {
 case MG_Token_Kind_Groups::Target:
  if(sg == MG_Token_Subgroups::Ledger)
    return {MG_Token_Kinds::Ledger_Target, rt};
  return {MG_Token_Kinds::Known_Target, rt};

 case MG_Token_Kind_Groups::Arg_Target:
  if(sg == MG_Token_Subgroups::Ledger)
    return {MG_Token_Kinds::Arg_Ledger_Target, rt};
  return {MG_Token_Kinds::Arg_Known_Target, rt};

 case MG_Token_Kind_Groups::Arg:
  if(sg == MG_Token_Subgroups::Value)
    return {MG_Token_Kinds::Arg_Raw_Value, rt};
  if(sg == MG_Token_Subgroups::Symbol)
    return {MG_Token_Kinds::Arg_Raw_Symbol, rt};
  return {MG_Token_Kinds::Generic, rt};

 case MG_Token_Kind_Groups::Generic:
  return {MG_Token_Kinds::Generic, rt};

 default: return {MG_Token_Kinds::N_A, rt};
 }
}


MG_Token_Subgroups _PGB_IR_Build::get_subgroup(QChar c)
{
 switch (c.toLatin1())
 {
 case '@': return MG_Token_Subgroups::Symbol;
 case '$': return MG_Token_Subgroups::Value;
 case '!': return MG_Token_Subgroups::Known;
 case '&': return MG_Token_Subgroups::Ledger;
 case ':': return MG_Token_Subgroups::Generic;
 default: return MG_Token_Subgroups::N_A;
 }
}


void _PGB_IR_Build::make_root_node(QString target, MG_Token_Subgroups sg)
{
 MG_Token mgt = mgtoken(target, MG_Token_Kind_Groups::Target, sg);
 qts_ << "(pgb::make_root_node "; end_line({mgt});
}

void _PGB_IR_Build::make_token_node(QString arg, MG_Token_Subgroups asg,
  QString target, MG_Token_Subgroups tsg)
{
 MG_Token amgt = mgtoken(arg, MG_Token_Kind_Groups::Arg, asg);
 MG_Token tmgt = mgtoken(target, MG_Token_Kind_Groups::Target, tsg);

 qts_ << "(pgb::make_token_node "; end_line({amgt, tmgt});
}

void _PGB_IR_Build::make_channel_fuxe_entry_node(QString arg1,
  MG_Token_Subgroups asg1, QString arg2,
  MG_Token_Subgroups asg2,
  QString target, MG_Token_Subgroups tsg)
{
 MG_Token mgt1 = mgtoken(arg1, MG_Token_Kind_Groups::Generic, asg1);
 MG_Token mgt2 = mgtoken(arg2, MG_Token_Kind_Groups::Generic, asg2);
 MG_Token tmgt = mgtoken(target, MG_Token_Kind_Groups::Target, tsg);

 qts_ << "(pgb::make_channel_fuxe_node "; end_line({mgt1, mgt2, tmgt});
}

void _PGB_IR_Build::make_statement_info_node(QString anchor_name,
  MG_Token_Subgroups asg, QString channel_name, MG_Token_Subgroups csg,
  QString anchor_kind, MG_Token_Subgroups aksg,
  QString target, MG_Token_Subgroups tsg)
{
 MG_Token amgt = mgtoken(anchor_name, MG_Token_Kind_Groups::Arg, asg);
 MG_Token cmgt = mgtoken(channel_name, MG_Token_Kind_Groups::Generic, csg);
 MG_Token kmgt = mgtoken(anchor_kind, MG_Token_Kind_Groups::Generic, aksg);
 MG_Token tmgt = mgtoken(target, MG_Token_Kind_Groups::Target, tsg);


 //?qts_ << const_cast<const MG_Token&>(it.next()).encode();
 qts_ << "(pgb::make_statement_info_node  ";
 end_line({amgt, cmgt, kmgt, tmgt});
}

void _PGB_IR_Build::add_channel_fuxe_entry_node(QString t1, MG_Token_Subgroups sg1,
  QString t2, MG_Token_Subgroups sg2,
  QString chn,
  MG_Token_Subgroups chnsg,
  QString cfen,
  MG_Token_Subgroups cfensg)
{
 MG_Token mgt1 = mgtoken(t1, MG_Token_Kind_Groups::Arg_Target, sg1);
 MG_Token mgt2 = mgtoken(t2, MG_Token_Kind_Groups::Arg_Target, sg2);

 if(cfen.isEmpty())
 {
  qts_ << "(pgb::add_channel_fuxe_entry_node "; end_line({mgt1, mgt2});
 }
 else
 {
  MG_Token mgt3 = mgtoken(chn, MG_Token_Kind_Groups::Generic, chnsg);
  MG_Token mgt4 = mgtoken(cfen, MG_Token_Kind_Groups::Arg_Target, chnsg);
  qts_ << "(pgb::add_channel_fuxe_entry_node ";
  end_line({mgt1, mgt2, mgt3, mgt4});
 }
}

void _PGB_IR_Build::add_block_entry_node(QString t1, MG_Token_Subgroups sg1,
  QString t2, MG_Token_Subgroups sg2, QString anchor_name, MG_Token_Subgroups ansg)
{
 MG_Token mgt1 = mgtoken(t1, MG_Token_Kind_Groups::Arg_Target, sg1);
 MG_Token mgt2 = mgtoken(t2, MG_Token_Kind_Groups::Arg_Target, sg2);

 if(anchor_name.isEmpty())
 {
  qts_ << "(pgb::add_block_entry_node "; end_line({mgt1, mgt2});
 }
 else
 {
  MG_Token mgt3 = mgtoken(anchor_name, MG_Token_Kind_Groups::Arg_Target, ansg);
  qts_ << "(pgb::add_block_entry_node "; end_line({mgt1, mgt2, mgt3});
 }
}

void _PGB_IR_Build::add_statement_sequence_node(QString t1, MG_Token_Subgroups sg1,
  QString t2, MG_Token_Subgroups sg2, QString anchor_name, MG_Token_Subgroups ansg)
{
 MG_Token mgt1 = mgtoken(t1, MG_Token_Kind_Groups::Arg_Target, sg1);
 MG_Token mgt2 = mgtoken(t2, MG_Token_Kind_Groups::Arg_Target, sg2);

 if(anchor_name.isEmpty())
 {
  qts_ << "(pgb::add_statement_sequence_node "; end_line({mgt1, mgt2});
 }
 else
 {
  MG_Token mgt3 = mgtoken(anchor_name, MG_Token_Kind_Groups::Arg_Target, ansg);
  qts_ << "(pgb::add_statement_sequence_node "; end_line({mgt1, mgt2, mgt3});
 }
}

void _PGB_IR_Build::copy_value(QString t1, MG_Token_Subgroups sg1,
  QString t2, MG_Token_Subgroups sg2)
{
 MG_Token mgt1 = mgtoken(t1, MG_Token_Kind_Groups::Arg_Target, sg1);
 MG_Token mgt2 = mgtoken(t2, MG_Token_Kind_Groups::Target, sg2);

 qts_ << "(pgb::copy_value "; end_line({mgt1, mgt2});
}

void _PGB_IR_Build::end_line(QList<MG_Token>&& mgts)
{
 QListIterator<MG_Token> it(mgts);

 while(it.hasNext())
 {
  qts_ << const_cast<const MG_Token&>(it.next()).encode();
  if(it.hasNext())
    qts_ << ' ';
 }
 qts_ << ")";
}

void _PGB_IR_Build::add_channel_token(QString src, MG_Token_Subgroups srcsg,
  QString tok, MG_Token_Subgroups toksg,
  QString target, MG_Token_Subgroups tsg)
{
 MG_Token mgt1 = mgtoken(src, MG_Token_Kind_Groups::Arg_Target, srcsg);
 MG_Token mgt2 = mgtoken(tok, MG_Token_Kind_Groups::Arg, toksg);
 MG_Token mgt3 = mgtoken(target, MG_Token_Kind_Groups::Target, tsg);

 qts_ << "(pgb::add_channel_token "; end_line({mgt1, mgt2, mgt3});
}

void _PGB_IR_Build::add_statement_sequence_token(QString src, MG_Token_Subgroups srcsg,
  QString tok, MG_Token_Subgroups toksg,
  QString sin, MG_Token_Subgroups sinsg,
  QString target, MG_Token_Subgroups tsg)
{
 MG_Token mgt1 = mgtoken(src, MG_Token_Kind_Groups::Arg_Target, srcsg);
 MG_Token mgt2 = mgtoken(tok, MG_Token_Kind_Groups::Arg, toksg);
 MG_Token mgt3 = mgtoken(sin, MG_Token_Kind_Groups::Arg_Target, sinsg);
 MG_Token mgt4 = mgtoken(target, MG_Token_Kind_Groups::Target, tsg);

 qts_ << "(pgb::add_statement_sequence_token "; end_line({mgt1, mgt2, mgt3, mgt4});
}

void _PGB_IR_Build::add_block_entry_token(QString src, MG_Token_Subgroups srcsg,
  QString tok, MG_Token_Subgroups toksg, QString sin, MG_Token_Subgroups sinsg,
  QString target, MG_Token_Subgroups tsg)
{
 MG_Token mgt1 = mgtoken(src, MG_Token_Kind_Groups::Arg_Target, srcsg);
 MG_Token mgt2 = mgtoken(tok, MG_Token_Kind_Groups::Arg, toksg);
 MG_Token mgt3 = mgtoken(sin, MG_Token_Kind_Groups::Arg_Target, sinsg);
 MG_Token mgt4 = mgtoken(target, MG_Token_Kind_Groups::Target, tsg);

 qts_ << "(pgb::add_block_entry_token "; end_line({mgt1, mgt2, mgt3, mgt4});
}

void _PGB_IR_Build::add_channel_entry_token(QString src, MG_Token_Subgroups srcsg,
  QString chn, QString tok, MG_Token_Subgroups toksg,
  QString target, MG_Token_Subgroups tsg)
{
 MG_Token mgt1 = mgtoken(src, MG_Token_Kind_Groups::Arg_Target, srcsg);
 MG_Token mgt2 = {MG_Token_Kinds::Arg_String_Literal, chn};
 MG_Token mgt3 = mgtoken(tok, MG_Token_Kind_Groups::Arg, toksg);
 MG_Token mgt4 = mgtoken(target, MG_Token_Kind_Groups::Target, tsg);

 qts_ << "(pgb::add_channel_entry_token "; end_line({mgt1, mgt2, mgt3, mgt4});
}

PGB_IR_Build::PGB_IR_Build(QString out_file)
  :  out_file_(out_file)//, qts_(&text)
{

}

_PGB_IR_Build PGB_IR_Build::operator()(QString& qs)
{
 qts_.setString(&qs);
 _PGB_IR_Build result(qts_);
 return result;
}

_PGB_IR_Build PGB_IR_Build::operator()(QStringList& qsl)
{
 qsl.push_back(QString());
 QString& qs = qsl.back();
 return operator()(qs);
// qts_.setString(&qs);
// _PGB_IR_Build result(qts_);
// return result;
}

_PGB_IR_Build PGB_IR_Build::operator[](QStringList& qsl)
{
 qsl.push_front(QString());
 QString& qs = qsl.front();
 return operator()(qs);
// qts_.setString(&qs);
// _PGB_IR_Build result(qts_);
// return result;
}

void PGB_IR_Build::generate_file(QStringList& qsl)
{
 save_file(out_file_, qsl.join('\n'));
}

