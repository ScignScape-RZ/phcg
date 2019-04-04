
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_GRAPH_CONNECTION__H
#define PHR_GRAPH_CONNECTION__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/phr-graph-dominion.h"

#include <QTextStream>

#include "rzns.h"
#include "accessors.h"

RZNS_(PhrGraphCore)

class Run_Call_Entry;
class PHR_Graph_Node;

class PHR_Graph_Connection
{
 caon_ptr<PHR_Graph_Node> phr_node_;

public:

 ACCESSORS(caon_ptr<PHR_Graph_Node> ,phr_node)

 PHR_Graph_Connection(caon_ptr<PHR_Graph_Node> phr_node);



};


_RZNS(PhrGraphCore)

#endif //PHR_GRAPH_CONNECTION__H

