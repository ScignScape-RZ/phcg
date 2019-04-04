
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_GRAPH_NODE__H
#define PHR_GRAPH_NODE__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/phr-graph-dominion.h"

#include "kernel/frame/phr-graph-frame.h"

#include "accessors.h"

#include <functional>

#include <QVector>

#include "rzns.h"


//RZNS_(GBuild)

// class RZ_Lisp_Token;

//_RZNS(GBuild)


RZNS_(PhrGraphCore)


class PHR_Graph_Node : public node_ptr<PHR_Graph_Dominion>
{

 QVector<caon_ptr<PHR_Graph_Node>> hyponodes_;
 caon_ptr<PHR_Graph_Node> parent_;

public:

 #define DOMINION_TYPE DOMINION_NODE_CONSTRUCTOR
 #include "kernel/dominion/types.h"
 #undef DOMINION_TYPE

 ACCESSORS__RGET(QVector<caon_ptr<PHR_Graph_Node>> ,hyponodes)
 ACCESSORS(caon_ptr<PHR_Graph_Node> ,parent)

 void debug_connections();

 void each_connection(std::function<void(const PHR_Graph_Connectors& connector,
  const PHR_Graph_Node&, const PHR_Graph_Connection* connection)> fn)  const;

 void swap_relation(const PHR_Graph_Connectors& connector,
  caon_ptr<PHR_Graph_Node> n1, caon_ptr<PHR_Graph_Node> n2);

 void delete_relation(const PHR_Graph_Connectors& connector,
  caon_ptr<PHR_Graph_Node> n1);

 void add_hyponode(caon_ptr<PHR_Graph_Node> n);


};

_RZNS(PhrGraphCore)


#endif //PHR_GRAPH_NODE__H
