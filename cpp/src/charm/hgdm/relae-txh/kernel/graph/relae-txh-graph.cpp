
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "relae-txh-graph.h"

#include "kans.h"

USING_KANS(HGDMCore)


RTXH_Graph::RTXH_Graph(RTXH_Node* root_node)
  :  root_node_(root_node)
{
 set_user_data(&hypernodes_);
 set_node_add_function([](phaong<pg_t>& _pg, phaong<pg_t>::Hypernode* hn)
 {
  QVector<hypernode_type*>* hh = _pg.user_data_as<QVector<hypernode_type*>>();
  hh->push_back(hn);
 });
}

// // here offset dfaults to -1 ...
void RTXH_Graph::add_structure_type(QString name, unsigned int l,
  signed int offset)
{
 types_[name] = {l, {offset, -1}};
}

void RTXH_Graph::add_array_type(QString name, unsigned int l,
  unsigned int csize, signed int offset)
{
 types_[name] = {-l, {offset, csize}};
}

// // here offset dfaults to 0 ...
void RTXH_Graph::add_fixed_array_type(QString name, unsigned int l,
  signed int offset)
{
 types_[name] = {l, {offset, -1}};
}

void RTXH_Graph::update_current_field_index(QString type_name,
  QString field_name, int& upd)
{
 auto it = field_indices_.find({type_name, field_name});

 if(it != field_indices_.end())
 {
  upd = *it;
 }
}


void RTXH_Graph::add_read_token(hypernode_type* hn, QString type_name,
  QString field_name, QPair<QString, void*> val)
{
 auto it = field_indices_.find({type_name, field_name});

 if(it != field_indices_.end())
 {
  add_read_token(hn, type_name, *it, val, field_name);
 }
}

void RTXH_Graph::array_append(hypernode_type* hn, hypernode_type* nhn)
{
 append_af(hn, {"", nhn}, {"proxy", nullptr});

// //qint16 ind = hn->get_sf();
// get_sf(hn, 0, [this, nhn, hn](QPair<QString, void*>& pr)
// {
//  qint16 index = (qint16) (quint64) pr.second;
//  set_af(hn, index, {"", nhn}, {"proxy", nullptr});
//  ++index;
//  set_sf(hn, 0, {"", (void*)index}, {"index", nullptr});
// // set_af(hn, index);
//  //qDebug() << pr.first;
// });

}


void RTXH_Graph::add_read_token(hypernode_type* hn, QString type_name,
  int field_index, QPair<QString, void*> val, QString field_name)
{
 auto it = types_.find(type_name);

 if(it != types_.end())
 {
  signed int sz = it->first;
  signed int offs = it->second.first;
  if( (offs >= 0) && !field_name.isEmpty() )
  {
   set_sf(hn, field_index, (hyponode_value_type) val);
  }
  else if( (offs >= 0) || (sz < 0) )
  {
   set_af(hn, field_index, (hyponode_value_type) val);
  }
  else
  {
   set_sf(hn, field_index, (hyponode_value_type) val);
  }
 }
}

void RTXH_Graph::add_type_field_index(QString type_name, QString field_name, int code)
{
 field_indices_.insert({type_name, field_name}, code);
}

RTXH_Graph::hypernode_type* RTXH_Graph::new_hypernode_by_type_name(QString ty)
{
 auto it = types_.find(ty);
 if(it == types_.end())
   return nullptr;

 hypernode_type* result = this->new_hypernode(it.value().first,
   {ty, nullptr}, it.value().second.first, it.value().second.second);

 return result;
}

