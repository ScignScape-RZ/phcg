
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RELAE_PHAON_GRAPH__H
#define RELAE_PHAON_GRAPH__H

///#include "relae-graph/relae-node-ptr.h"

//#include "kernel/sy-dominion.h"

#include <QTextStream>

#include "kans.h"

//#include "qhyp/qhyp-graph/qy-hyper-node.h"
//#include "qhyp/qhyp-graph/qy-hyper-edge.h"
//#include "qhyp/qhyp-graph/qy-ptr.h"
//#include "qhyp/qhyp-graph/qy-node.h"

#include "relae-phaon-node.h"

USING_KANS(HGDMCore)

#include "kernel/relae-phaon-dominion.h"

KANS_(HGDMCore)


class RPH_Graph : public phaong<pg_t>  //: public node_graph<SY_Dominion>
{
 RPH_Node* root_node_;

 QMap<QString, QPair<signed int,
   QPair<signed int, signed int> > > types_;

public:

 typedef phaong<pg_t>::Hypernode hypernode_type;

 RPH_Graph(RPH_Node* root_node = nullptr);

 void add_structure_type(QString name, unsigned int l,
   signed int offset = -1);

 void add_array_type(QString name, unsigned int l,
   unsigned int csize, signed int offset = -1);

 void add_fixed_array_type(QString name, unsigned int l,
   signed int offset = 0);

 hypernode_type* new_hypernode_by_type_name(QString ty);

// void report(QTextStream& qts);
// void report_from_node(QTextStream& qts,
//  QY_Hyper_Node node, int indent = 0);

};

_KANS(HGDMCore)


#endif
