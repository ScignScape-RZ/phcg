
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-graph-core/kernel/graph/phr-graph.h"

#include "phr-graph-core/kernel/graph/phr-graph-node.h"

#include "phr-graph-core/kernel/phr-graph-root.h"

#include "rzns.h"

USING_RZNS(PhrGraphCore)

#include <QDebug>

int main(int argc, char **argv)
{
 PHR_Graph pgr;

 caon_ptr<PHR_Graph_Root> rt = new PHR_Graph_Root(nullptr);
 caon_ptr<PHR_Graph_Node> rn = new PHR_Graph_Node(rt);

 pgr.set_root_node(rn);

 qDebug() << "ok";
 return 0;
}
