
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef _VEC1D__H
#define _VEC1D__H


#include "accessors.h"

#include "hive-structure.h"

#include <QVector>
#include <QString>
#include <QMap>

#include <QDebug>

#include <functional>

#include "_each-holders.h"


#define deffn(ty, arg) [](ty** def) \
{ \
 static int _def = arg; \
 *def = &_def; \
} \

#define defzfn(ty) deffn(ty, 0)

#define _default_fn(ty ,arg) set_default_fn(deffn(ty, arg))

#define _default_z(ty) _default_fn(ty ,0)

template<typename VAL_Type>
class Deq1d;


template<typename VAL_Type>
class _Vec1d
{
 std::function<void(VAL_Type**)> default_fn_;

protected:

 friend class Deq1d<VAL_Type>;
 Hive_Structure* hive_structure_;

public:

 _Vec1d(quint8 bsz = 16)
  :  hive_structure_(new Hive_Structure),
    default_fn_(nullptr)
 {
  hive_structure_->set_block_size(bsz);
  hive_structure_->set_value_size(sizeof(VAL_Type));
 }

 typedef VAL_Type Value_type;

 void operator <=(std::function<void(VAL_Type**)> fn)
 {
  set_default_fn(fn);
 }

 ACCESSORS(std::function<void(VAL_Type**)> ,default_fn)

 void push_back(const VAL_Type& v)
 {
  void* spot = hive_structure_->get_push_back_location();
  //VAL_Type* vv = (VAL_Type*) spot;
  memcpy(spot, &v, hive_structure_->value_size());
  hive_structure_->increment_total_size();
 }

 void _each_from_index(quint32 ix,
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

 VAL_Type& last()
 {
  VAL_Type* vv = (VAL_Type*) hive_structure_->get_back_location();
  if(!vv)
    default_fn_(&vv);
  return *vv;
 }

 VAL_Type& first()
 {
  VAL_Type* vv = (VAL_Type*) hive_structure_->get_indexed_location(0);
  if(!vv)
    default_fn_(&vv);
  return *vv;
 }

 void _each(std::function<void(VAL_Type& v)> fn)
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

 void _reach(std::function<void(VAL_Type& v)> fn)
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



#endif // _VEC1D__H
