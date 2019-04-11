
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_GRAPH_BUILD__H
#define PHR_GRAPH_BUILD__H


#include "relae-graph/relae-node-ptr.h"

#include "phr-graph-core/kernel/phr-graph-dominion.h"

#include "accessors.h"

#include <QTextStream>

#include "rzns.h"

struct MG_Token;

RZNS_(PhrGraphCore)

class PHR_Graph;
class PHR_Graph_Frame;
class PHR_Graph_Query;

class PHR_Graph_Build
{
 friend class PGB_IR_Run;

 PHR_Graph& graph_;
 QString file_;
 caon_ptr<PHR_Graph_Node> current_node_;

 PHR_Graph_Frame& fr_;
 const PHR_Graph_Query& qy_;

public:

 PHR_Graph_Build(PHR_Graph& graph);

 ACCESSORS(QString ,file)
 ACCESSORS(caon_ptr<PHR_Graph_Node> ,current_node)

 void make_root_node();

 caon_ptr<PHR_Graph_Node> add_block_entry_node(
   caon_ptr<PHR_Graph_Node> source, caon_ptr<PHR_Graph_Node> target);

 caon_ptr<PHR_Graph_Node> make_token_node(MG_Token& mgt);
 caon_ptr<PHR_Graph_Node> make_token_node(MG_Token&& mgt)
 {
  return make_token_node(mgt);
 }

 caon_ptr<PHR_Graph_Node> add_channel_raw_value_token(caon_ptr<PHR_Graph_Node> source,
   QString channel, QString txt);


};

_RZNS(PhrGraphCore)



#endif // PHR_GRAPH_BUILD__H
