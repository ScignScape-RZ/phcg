
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "relae-phaon-graph.h"


#include "kans.h"

USING_KANS(HGDMCore)

RPH_Graph::RPH_Graph(RPH_Node* root_node)
  :  root_node_(root_node)
{

}

void RPH_Graph::add_structure_type(QString name, unsigned int l,
  unsigned int offset)
{
 types_[name] = {l, offset};
}

void RPH_Graph::add_array_type(QString name, unsigned int l,
  unsigned int offset)
{
 types_[name] = {-l, offset};
}


