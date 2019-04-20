
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-graph-build.h"

#include "phr-graph.h"

#include "kernel/phr-graph-root.h"

#include "token/phr-graph-token.h"

#include "token/phr-graph-block-info.h"

//#include "tuple/rz-re-tuple-info.h"
//#include "code/rz-re-call-entry.h"
//#include "code/rz-re-block-entry.h"
#include "kernel/graph/phr-graph-connection.h"

#include "phr-graph-core/kernel/phr-graph-root.h"

#include "kernel/document/phr-graph-document.h"
#include "kernel/graph/phr-graph-node.h"

#include "phr-graph-core/kernel/frame/phr-graph-frame.h"
#include "phr-graph-core/kernel/query/phr-graph-query.h"

#include "phr-graph-core/token/phr-graph-statement-info.h"
#include "phr-graph-core/token/phr-graph-fuxe-entry.h"

#include "pgb-ir-run.h"

#include "multigraph-token.h"

#include "rzns.h"

USING_RZNS(PhrGraphCore)

PHR_Graph_Build::PHR_Graph_Build(PHR_Graph& graph)
 : graph_(graph), current_node_(nullptr),
   last_statement_entry_node_(nullptr),
   last_block_pre_entry_node_(nullptr),
   last_expression_entry_node_(nullptr),
  fr_(PHR_Graph_Frame::instance()),
  qy_(PHR_Graph_Query::instance())
{

}


void PHR_Graph_Build::load_from_pgb_file(QString file)
{
 PGB_IR_Run pgbr(*this);
 pgbr.run_from_file(file);
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::make_root_node()
{
 caon_ptr<PHR_Graph_Document> doc = new PHR_Graph_Document(file_);

 caon_ptr<PHR_Graph_Root> rt = new PHR_Graph_Root(doc.raw_pointer());
 caon_ptr<PHR_Graph_Node> result = new PHR_Graph_Node(rt);

 graph_.set_root_node(result);

 result->set_label("<root>");

 return result;

 //?current_node_ = rn;
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::make_token_node(MG_Token& mgt)
{
 bool rv = (mgt.kind == MG_Token_Kinds::Raw_Value)
   || (mgt.kind == MG_Token_Kinds::Arg_Raw_Value);
 bool sl = false;
 QString rt = mgt.raw_text;
 if(rv && rt.startsWith('"'))
 {
  sl = true;
  rt = rt.mid(1);
  if(rt.endsWith('"'))
    rt.chop(1);
 }

 caon_ptr<PHR_Graph_Token> tok = new PHR_Graph_Token(rt);
 if(rv)
   tok->flags.gen_raw_value = true;
 if(sl)
   tok->flags.is_string_literal = true;

 caon_ptr<PHR_Graph_Node> result = new PHR_Graph_Node(tok);
 result->set_label(mgt.raw_text);
 return result;
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::add_channel_token(caon_ptr<PHR_Graph_Node> source,
  MG_Token& mgt)
{
 CAON_PTR_DEBUG(PHR_Graph_Node ,source)

 caon_ptr<PHR_Graph_Node> result = make_token_node(mgt);

 source << fr_/qy_.Channel_Sequence >> result;

 return result;
}


caon_ptr<PHR_Graph_Node> PHR_Graph_Build::add_channel_continue_token(caon_ptr<PHR_Graph_Node> source,
  MG_Token& mgt)
{
 CAON_PTR_DEBUG(PHR_Graph_Node ,source)

 caon_ptr<PHR_Graph_Node> result = make_token_node(mgt);

 source << fr_/qy_.Channel_Continue >> result;

 return result;
}


caon_ptr<PHR_Graph_Node> PHR_Graph_Build::add_channel_entry_token(caon_ptr<PHR_Graph_Node> source,
  QString channel, MG_Token& mgt)
{
 CAON_PTR_DEBUG(PHR_Graph_Node ,source)

 caon_ptr<PHR_Graph_Node> result = make_token_node(mgt);

 caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection(channel);
 source << fr_/qy_.Channel_Entry(cion) >> result;

 return result;
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::add_channel_xentry_token(caon_ptr<PHR_Graph_Node> source,
  QString channel, MG_Token& mgt)
{
 CAON_PTR_DEBUG(PHR_Graph_Node ,source)

 caon_ptr<PHR_Graph_Node> result = make_token_node(mgt);

 caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection(channel);
 source << fr_/qy_.Channel_XEntry(cion) >> result;

 return result;
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::make_block_info_node()
{
 caon_ptr<PHR_Graph_Block_Info> bin = new
   PHR_Graph_Block_Info();
 caon_ptr<PHR_Graph_Node> result = new PHR_Graph_Node(bin);
 result->set_label(QString("<block-info>"));
 return result;
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::make_statement_info_node(QString anchor_name,
   QString channel_name, QString anchor_kind)
{
 caon_ptr<PHR_Graph_Statement_Info> sin = new
   PHR_Graph_Statement_Info(anchor_name, channel_name, anchor_kind);
 caon_ptr<PHR_Graph_Node> result = new PHR_Graph_Node(sin);
 result->set_label(QString("<statement-info:%1%2>").arg(anchor_name).arg(anchor_kind));
 return result;
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::add_statement_sequence_token(caon_ptr<PHR_Graph_Node> source,
  MG_Token& mgt, caon_ptr<PHR_Graph_Node> statement_info_node)
{
 CAON_PTR_DEBUG(PHR_Graph_Node ,source)
 CAON_PTR_DEBUG(PHR_Graph_Node ,statement_info_node)

 caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection(statement_info_node);

 caon_ptr<PHR_Graph_Node> result = make_token_node(mgt);

 CAON_PTR_DEBUG(PHR_Graph_Connection ,cion)

 source << fr_/qy_.Statement_Sequence(cion) >> result;

 return result;
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::add_block_entry_token(caon_ptr<PHR_Graph_Node> source,
  MG_Token& mgt, caon_ptr<PHR_Graph_Node> statement_info_node)
{
 CAON_PTR_DEBUG(PHR_Graph_Node ,source)
 CAON_PTR_DEBUG(PHR_Graph_Node ,statement_info_node)

 caon_ptr<PHR_Graph_Block_Info> bin = new PHR_Graph_Block_Info;
 caon_ptr<PHR_Graph_Node> nbin = new PHR_Graph_Node(bin);
 caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection(nbin);
 cion->add_node(statement_info_node);

 caon_ptr<PHR_Graph_Node> result = make_token_node(mgt);

 CAON_PTR_DEBUG(PHR_Graph_Connection ,cion)

 source << fr_/qy_.Block_Entry(cion) >> result;

 return result;
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::make_channel_fuxe_entry_node(QString chn, QString ty)
{
 caon_ptr<PHR_Graph_Fuxe_Entry> fen = new PHR_Graph_Fuxe_Entry(chn, ty);
 caon_ptr<PHR_Graph_Node> result = new PHR_Graph_Node(fen);
 result->set_label("<channel-fuxe-entry>");
 return result;
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::add_channel_fuxe_entry_node(
  caon_ptr<PHR_Graph_Node> source,
  caon_ptr<PHR_Graph_Node> target, QString chn,
  caon_ptr<PHR_Graph_Node> cfen)
{
 CAON_PTR_DEBUG(PHR_Graph_Node ,source)
 CAON_PTR_DEBUG(PHR_Graph_Node ,target)

 if(cfen)
 {
  caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection(chn, cfen);
  source << fr_/qy_.Channel_Fuxe_Entry(cion) >> target;
 }
 else
   source << fr_/qy_.Channel_Fuxe_Entry >> target;
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::add_channel_fuxe_cross_node(
  caon_ptr<PHR_Graph_Node> source,
  caon_ptr<PHR_Graph_Node> target, QString chn,
  caon_ptr<PHR_Graph_Node> cfen)
{
 CAON_PTR_DEBUG(PHR_Graph_Node ,source)
 CAON_PTR_DEBUG(PHR_Graph_Node ,target)

 if(cfen)
 {
  caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection(chn, cfen);
  source << fr_/qy_.Channel_Fuxe_Cross(cion) >> target;
 }
 else
   source << fr_/qy_.Channel_Fuxe_Cross >> target;
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::add_channel_fuxe_coentry_node(
  caon_ptr<PHR_Graph_Node> source,
  caon_ptr<PHR_Graph_Node> target, QString chn,
  caon_ptr<PHR_Graph_Node> cfen)
{
 CAON_PTR_DEBUG(PHR_Graph_Node ,source)
 CAON_PTR_DEBUG(PHR_Graph_Node ,target)

 if(cfen)
 {
  caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection(chn, cfen);
  source << fr_/qy_.Channel_Fuxe_Coentry(cion) >> target;
 }
 else
   source << fr_/qy_.Channel_Fuxe_Coentry >> target;
}


void PHR_Graph_Build::add_channel_continue_block_node(
  caon_ptr<PHR_Graph_Node> source,
  caon_ptr<PHR_Graph_Node> target, caon_ptr<PHR_Graph_Node> bin)
{
 CAON_PTR_DEBUG(PHR_Graph_Node ,source)
 CAON_PTR_DEBUG(PHR_Graph_Node ,target)

 caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection(bin);

 source << fr_/qy_.Channel_Continue_Block(cion) >> target;
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::add_block_entry_node(
  caon_ptr<PHR_Graph_Node> source,
  caon_ptr<PHR_Graph_Node> target, caon_ptr<PHR_Graph_Node> sin)
{
 CAON_PTR_DEBUG(PHR_Graph_Node ,source)
 CAON_PTR_DEBUG(PHR_Graph_Node ,target)

 caon_ptr<PHR_Graph_Block_Info> bin = new PHR_Graph_Block_Info;
 //caon_ptr<PHR_Graph_Statement_Info> sin = new PHR_Graph_Statement_Info;
 caon_ptr<PHR_Graph_Node> nbin = new PHR_Graph_Node(bin);
 caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection(nbin);

 if(sin)
   cion->add_node(sin);

 source << fr_/qy_.Block_Entry(cion) >> target;

 return nbin;
}


void PHR_Graph_Build::add_statement_sequence_node(
  caon_ptr<PHR_Graph_Node> source,
  caon_ptr<PHR_Graph_Node> target, caon_ptr<PHR_Graph_Node> sin)
{
 CAON_PTR_DEBUG(PHR_Graph_Node ,source)
 CAON_PTR_DEBUG(PHR_Graph_Node ,target)

 if(sin)
 {
  caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection(sin);
    source << fr_/qy_.Statement_Sequence(cion) >> target;
 }
 else
   source << fr_/qy_.Statement_Sequence >> target;
}
