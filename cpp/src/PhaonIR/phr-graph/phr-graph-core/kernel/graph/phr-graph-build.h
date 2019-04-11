
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_GRAPH_BUILD__H
#define PHR_GRAPH_BUILD__H


#include "relae-graph/relae-node-ptr.h"

#include "phr-graph-core/kernel/phr-graph-dominion.h"

#include <QTextStream>

#include "rzns.h"

RZNS_(PhrGraphCore)

class PHR_Graph;

class PHR_Graph_Build
{
 PHR_Graph& graph_;

 public:

  PHR_Graph_Build(PHR_Graph& graph);



};

_RZNS(PhrGraphCore)



#endif // PHR_GRAPH_BUILD__H
