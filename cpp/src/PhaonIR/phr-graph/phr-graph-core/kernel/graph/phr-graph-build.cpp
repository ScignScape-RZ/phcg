
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

#include "multigraph-token.h"

#include "rzns.h"

USING_RZNS(PhrGraphCore)

PHR_Graph_Build::PHR_Graph_Build(PHR_Graph& graph)
 : graph_(graph), current_node_(nullptr),
  fr_(PHR_Graph_Frame::instance()),
  qy_(PHR_Graph_Query::instance())
{

}

void PHR_Graph_Build::make_root_node()
{
 caon_ptr<PHR_Graph_Document> doc = new PHR_Graph_Document(file_);

 caon_ptr<PHR_Graph_Root> rt = new PHR_Graph_Root(doc.raw_pointer());
 caon_ptr<PHR_Graph_Node> rn = new PHR_Graph_Node(rt);

 graph_.set_root_node(rn);

 current_node_ = rn;
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::make_token_node(MG_Token& mgt)
{
 caon_ptr<PHR_Graph_Token> tok = new PHR_Graph_Token(mgt.raw_text);
 if(mgt.kind == MG_Token_Kinds::Raw_Value)
   tok->flags.gen_raw_value = true;
 return new PHR_Graph_Node(tok);
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::add_channel_raw_value_token(caon_ptr<PHR_Graph_Node> source,
  QString channel, QString txt)
{
 caon_ptr<PHR_Graph_Token> tok = new PHR_Graph_Token(txt);
 tok->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> result = new PHR_Graph_Node(tok);

 caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection(channel);
 source << fr_/qy_.Channel_Entry(cion) >> result;

 return result;
}

caon_ptr<PHR_Graph_Node> PHR_Graph_Build::add_block_entry_node(
  caon_ptr<PHR_Graph_Node> source, caon_ptr<PHR_Graph_Node> target)
{
 caon_ptr<PHR_Graph_Block_Info> bin = new PHR_Graph_Block_Info;
 //caon_ptr<PHR_Graph_Statement_Info> sin = new PHR_Graph_Statement_Info;
 caon_ptr<PHR_Graph_Node> nbin = new PHR_Graph_Node(bin);
 caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection(nbin);

 source << fr_/qy_.Block_Entry(cion) >> target;

 return nbin;
}
