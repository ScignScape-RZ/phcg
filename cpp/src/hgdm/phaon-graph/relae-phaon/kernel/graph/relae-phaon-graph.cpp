
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
  signed int offset)
{
 types_[name] = {l, {offset, -1}};
}

void RPH_Graph::add_array_type(QString name, unsigned int l,
  unsigned int csize, signed int offset)
{
 types_[name] = {-l, {offset, csize}};
}

void RPH_Graph::add_fixed_array_type(QString name, unsigned int l,
  signed int offset)
{
 types_[name] = {l, {offset, -1}};
}

RPH_Graph::hypernode_type* RPH_Graph::new_hypernode_by_type_name(QString ty)
{
 auto it = types_.find(ty);
 if(it == types_.end())
   return nullptr;

 hypernode_type* result = this->new_hypernode(it.value().first,
   {ty, nullptr}, it.value().second.first, it.value().second.second);

 return result;
}

