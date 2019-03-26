
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef VEC1D__H
#define VEC1D__H


#include "accessors.h"

#include "hive-structure.h"

#include <QVector>
#include <QString>
#include <QMap>

#include <QDebug>

#include <functional>


template<typename VAL_Type>
class Vec1d
{
protected:
 Hive_Structure* hive_structure_;

public:

 Vec1d(quint8 bsz = 16)
  :  hive_structure_(new Hive_Structure)
 {
  hive_structure_->set_block_size(bsz);
  hive_structure_->set_value_size(sizeof(VAL_Type));
 }

 void push_back(const VAL_Type& v)
 {
  void* spot = hive_structure_->get_push_back_location();
  //VAL_Type* vv = (VAL_Type*) spot;
  memcpy(spot, &v, hive_structure_->value_size());
  hive_structure_->increment_total_size();
 }

 void each_from_index(quint32 ix,
   std::function<void(VAL_Type& v)> fn)
 {
  Hive_Structure::iterator hit = Hive_Structure::iterator::start();
  hive_structure_->position_iterator(hit, ix);
  while(!hit.end())
  {
   VAL_Type* pv = (VAL_Type*) hive_structure_->get_iterator_location(hit);
   fn(*pv);
   hive_structure_->increment_iterator(hit);
  }
 }

 void each(std::function<void(VAL_Type& v)> fn)
 {
  Hive_Structure::iterator hit = Hive_Structure::iterator::start();
  while(!hit.end())
  {
//   qDebug() << QString("hit: %1,%2,%3")
//               .arg(hit.block_index)
//               .arg(hit.inner_index)
//               .arg(hit.total_index);

   VAL_Type* pv = (VAL_Type*) hive_structure_->get_iterator_location(hit);
   fn(*pv);
   hive_structure_->increment_iterator(hit);
  }
 }

 void reach(std::function<void(VAL_Type& v)> fn)
 {
  Hive_Structure::iterator hit = Hive_Structure::iterator::start();
  hive_structure_->reverse_iterator(hit);
  while(!hit.end())
  {
   VAL_Type* pv = (VAL_Type*) hive_structure_->get_iterator_location(hit);
   fn(*pv);
   hive_structure_->decrement_iterator(hit);
  }
 }

};



#endif // VEC1D__H
