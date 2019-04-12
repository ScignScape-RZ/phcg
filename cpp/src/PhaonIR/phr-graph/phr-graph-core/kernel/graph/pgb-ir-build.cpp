
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

PGB_IR_Build::PGB_IR_Build(QString out_file)
  :  out_file_(out_file), qts_(&text_)
{

}

MG_Token PGB_IR_Build::mgtoken(QString rt, MG_Token_Kind_Groups kg, MG_Token_Subgroups sg)
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

 default: return {MG_Token_Kinds::N_A, rt};
 }
}


MG_Token_Subgroups PGB_IR_Build::get_subgroup(QChar c)
{
 switch (c.toLatin1())
 {
 case '@': return MG_Token_Subgroups::Symbol;
 case '$': return MG_Token_Subgroups::Value;
 case '!': return MG_Token_Subgroups::Known;
 case '&': return MG_Token_Subgroups::Ledger;
 default: return MG_Token_Subgroups::N_A;
 }
}


void PGB_IR_Build::make_root_node(QString target, MG_Token_Subgroups sg)
{
 MG_Token mgt = mgtoken(target, MG_Token_Kind_Groups::Target, sg);
 qts_ << "(pgb::make_root_node "; end_line({mgt});
}

void PGB_IR_Build::make_token_node(QString arg, MG_Token_Subgroups asg,
  QString target, MG_Token_Subgroups tsg)
{
 MG_Token amgt = mgtoken(arg, MG_Token_Kind_Groups::Arg, asg);
 MG_Token tmgt = mgtoken(target, MG_Token_Kind_Groups::Target, tsg);

 qts_ << "(pgb::make_token_node "; end_line({amgt, tmgt});
}


void PGB_IR_Build::add_block_entry_node(QString t1, MG_Token_Subgroups sg1,
  QString t2, MG_Token_Subgroups sg2)
{
 MG_Token mgt1 = mgtoken(t1, MG_Token_Kind_Groups::Arg_Target, sg1);
 MG_Token mgt2 = mgtoken(t2, MG_Token_Kind_Groups::Arg_Target, sg2);

 qts_ << "(pgb::add_block_entry_node "; end_line({mgt1, mgt2});
}

void PGB_IR_Build::end_line(QList<MG_Token>&& mgts)
{
 QListIterator<MG_Token> it(mgts);

 while(it.hasNext())
 {
  qts_ << const_cast<const MG_Token&>(it.next()).encode();
  if(it.hasNext())
    qts_ << ' ';
 }
 qts_ << ")\n";
}

void PGB_IR_Build::add_channel_token(QString src, MG_Token_Subgroups srcsg,
  QString chn, QString tok, MG_Token_Subgroups toksg,
  QString target, MG_Token_Subgroups tsg)
{
 MG_Token mgt1 = mgtoken(src, MG_Token_Kind_Groups::Arg_Target, srcsg);
 MG_Token mgt2 = {MG_Token_Kinds::Arg_String_Literal, chn};
 MG_Token mgt3 = mgtoken(tok, MG_Token_Kind_Groups::Arg, toksg);
 MG_Token mgt4 = mgtoken(target, MG_Token_Kind_Groups::Target, tsg);

 qts_ << "(pgb::add_channel_token "; end_line({mgt1, mgt2, mgt3, mgt4});
}

void PGB_IR_Build::generate_file()
{
 save_file(out_file_, text_);
}

//void PHR_Graph_Build::make_root_node()
//{
// caon_ptr<PHR_Graph_Document> doc = new PHR_Graph_Document(file_);

// caon_ptr<PHR_Graph_Root> rt = new PHR_Graph_Root(doc.raw_pointer());
// caon_ptr<PHR_Graph_Node> rn = new PHR_Graph_Node(rt);

// graph_.set_root_node(rn);

// current_node_ = rn;
//}

//caon_ptr<PHR_Graph_Node> PHR_Graph_Build::make_token_node(MG_Token& mgt)
//{
// caon_ptr<PHR_Graph_Token> tok = new PHR_Graph_Token(mgt.raw_text);
// if(mgt.kind == MG_Token_Kinds::Raw_Value)
//   tok->flags.gen_raw_value = true;
// return new PHR_Graph_Node(tok);
//}

//caon_ptr<PHR_Graph_Node> PHR_Graph_Build::add_channel_raw_value_token(caon_ptr<PHR_Graph_Node> source,
//  QString channel, QString txt)
//{
// caon_ptr<PHR_Graph_Token> tok = new PHR_Graph_Token(txt);
// tok->flags.gen_raw_value = true;
// caon_ptr<PHR_Graph_Node> result = new PHR_Graph_Node(tok);

// caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection(channel);
// source << fr_/qy_.Channel_Entry(cion) >> result;

// return result;
//}

//caon_ptr<PHR_Graph_Node> PHR_Graph_Build::add_block_entry_node(
//  caon_ptr<PHR_Graph_Node> source, caon_ptr<PHR_Graph_Node> target)
//{
// caon_ptr<PHR_Graph_Block_Info> bin = new PHR_Graph_Block_Info;
// //caon_ptr<PHR_Graph_Statement_Info> sin = new PHR_Graph_Statement_Info;
// caon_ptr<PHR_Graph_Node> nbin = new PHR_Graph_Node(bin);
// caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection(nbin);

// source << fr_/qy_.Block_Entry(cion) >> target;

// return nbin;
//}

