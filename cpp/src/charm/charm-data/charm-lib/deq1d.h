
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DEQ1D__H
#define DEQ1D__H


#include "accessors.h"

#include "hive-structure.h"
#include "vec1d.h"

#include <QVector>
#include <QString>
#include <QMap>

#include <QDebug>

#include <functional>


template<typename VAL_Type>
class Deq1d //: protected QPair<Vec1d<VAL_Type>, Vec1d<VAL_Type>>
{
 //Hive_Structure* front_hive_;
protected:

 Vec1d<VAL_Type> front_vec_;
 Vec1d<VAL_Type> back_vec_;

public:

 Deq1d()
  :  front_vec_(Vec1d<VAL_Type>()),
     back_vec_(Vec1d<VAL_Type>())
 {

 }

 Deq1d(quint8 bsz)
  :  front_vec_(Vec1d<VAL_Type>(bsz)),
     back_vec_(Vec1d<VAL_Type>(bsz))
 {

 }

 Deq1d(quint8 bsz, quint8 fbsz)
  :  front_vec_(Vec1d<VAL_Type>(bsz)),
     back_vec_(Vec1d<VAL_Type>(fbsz))
 {

 }

 void set_default_fn(std::function<void(VAL_Type**)> fn)
 {
  front_vec_.set_default_fn(fn);
  back_vec_.set_default_fn(fn);
 }

 void operator <=(std::function<void(VAL_Type**)> fn)
 {
  set_default_fn(fn);
 }

 void push_back(const VAL_Type& v)
 {
  back_vec_.push_back(v);
 }

 void push_front(const VAL_Type& v)
 {
  front_vec_.push_back(v);
 }

 void pop_back()
 {
  back_vec_.hive_structure_->pop_back();
 }

 void pop_front()
 {
  front_vec_.hive_structure_->pop_back();
 }

 VAL_Type& back()
 {
  return back_vec_.last();
 }

 VAL_Type& front()
 {
  return front_vec_.last();
 }

 void each(std::function<void(VAL_Type& v)> fn)
 {
  front_vec_.reach(fn);
  back_vec_.each(fn);
 }


};



#endif // DEQ1D__H