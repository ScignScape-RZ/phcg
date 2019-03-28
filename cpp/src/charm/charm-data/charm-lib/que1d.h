
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QUE1D__H
#define QUE1D__H


#include "accessors.h"

#include "hive-structure.h"
#include "_vec1d.h"

#include <QVector>
#include <QString>
#include <QMap>

#include <QDebug>

#include <functional>


template<typename VAL_Type>
class Que1d : protected _Vec1d<VAL_Type>, public each_holders<Que1d<VAL_Type>, VAL_Type>
{
 quint16 offset_;

public:

 typedef VAL_Type Value_type;

// union{
// _each_holder<Que1d> each;
// _each_holder<Que1d> reach;
// };

 Que1d(quint8 bsz = 16)
  :  _Vec1d<VAL_Type>(bsz), offset_(0), each_holders<Que1d<VAL_Type>, VAL_Type>({{*this}})
 {
 }

 void set_default_fn(std::function<void(VAL_Type**)> fn)
 {
  _Vec1d<VAL_Type>::set_default_fn(fn);
 }

 void operator <=(std::function<void(VAL_Type**)> fn)
 {
  set_default_fn(fn);
 }

 void dequeue()
 {
  ++offset_;
  if(offset_ == this->hive_structure_->block_size())
  {
   this->hive_structure_->pop_first_block();
   offset_ = 0;
  }
 }

 void enqueue(const VAL_Type& v)
 {
  _Vec1d<VAL_Type>::push_back(v);
 }

 void _each(std::function<void(VAL_Type& v)> fn)
 {
  if(offset_ == 0)
    _Vec1d<VAL_Type>::_each(fn);
  else
    _Vec1d<VAL_Type>::_each_from_index(offset_, fn);
 }

 VAL_Type& tail()
 {
  return this->last();
 }

 VAL_Type& head()
 {
  return this->first();
 }

};



#endif // QUE1D__H
