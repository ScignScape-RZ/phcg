
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RELAE_PHAON_GRAPH__H
#define RELAE_PHAON_GRAPH__H


#include <QTextStream>

#include "accessors.h"

#include "kans.h"


#include "relae-phaon-node.h"

USING_KANS(HGDMCore)

#include "kernel/relae-phaon-dominion.h"

KANS_(HGDMCore)


class RPH_Graph : public phaong<pg_t>
{
 RPH_Node* root_node_;

 QMap<QString, QPair<signed int,
   QPair<signed int, signed int> > > types_;

 QMap<QPair<QString, QString>, int> field_indices_;

public:
 typedef phaong<pg_t>::Hypernode hypernode_type;
 typedef phaong<pg_t>::numeric_index_type numeric_index_type;

private:
 QVector<hypernode_type*> hypernodes_;

public:

 ACCESSORS__CONST_RGET(QVector<hypernode_type*> ,hypernodes)

 RPH_Graph(RPH_Node* root_node = nullptr);

 void update_current_field_index(QString type_name,
   QString field_name, int& upd);

 void add_structure_type(QString name, unsigned int l,
   signed int offset = -1);

 void add_array_type(QString name, unsigned int l,
   unsigned int csize, signed int offset = -1);

 void add_fixed_array_type(QString name, unsigned int l,
   signed int offset = 0);

 void add_type_field_index(QString type_name, QString field_name, int code);

 void add_read_token(hypernode_type* hn, QString type_name,
   QString field_name, QPair<QString, void*> val);

 void add_read_token(hypernode_type* hn, QString type_name,
   int field_index, QPair<QString, void*> val, QString field_name = QString() );

 void array_append(hypernode_type* hn, hypernode_type* nhn);

// void add_numeric_read_token(hypernode_type* hn, QString type_name,
//   int field_index, numeric_index_type val);

 hypernode_type* new_hypernode_by_type_name(QString ty);

};

_KANS(HGDMCore)


#endif
