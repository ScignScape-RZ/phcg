
#ifndef QY_SCRIPT_GRAPH__H
#define QY_SCRIPT_GRAPH__H

///#include "relae-graph/relae-node-ptr.h"

//#include "kernel/sy-dominion.h"

#include <QTextStream>

#include "qyns.h"

#include "qhyp/qhyp-graph/qy-hyper-node.h"
#include "qhyp/qhyp-graph/qy-hyper-edge.h"
#include "qhyp/qhyp-graph/qy-ptr.h"

#include "qhyp/qhyp-graph/qy-node.h"

USING_QYNS(Graph)

#include "kernel/_dominion.h"

QYNS_(QYSGraph)


class QY_Script_Graph //: public node_graph<SY_Dominion>
{
 QY_Hyper_Node root_node_;

 public:
  QY_Script_Graph(QY_Hyper_Node root_node = nullptr);

 void report(QTextStream& qts);
 void report_from_node(QTextStream& qts,
  QY_Hyper_Node node, int indent = 0);

};

_QYNS(QYSGraph)


#endif
