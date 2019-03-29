
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DEQ1D__H
#define DEQ1D__H

#include "accessors.h"

#include "hive-structure.h"
#include "_vec1d.h"

#include <QVector>
#include <QString>
#include <QMap>

#include <QDebug>

#include <functional>

template<typename VAL_Type, typename INDEX_Type = quint16, typename PR_Type>
class Deq1d : protected _Vec1d<VAL_Type>,
  public each_holders<Deq1d<VAL_Type>, VAL_Type, INDEX_Type, PR_Type>
{
 quint16 offset_;

public:

 Deq1d(quint8 bsz = 16)
  :  _Vec1d<VAL_Type>(bsz), offset_(0),
    each_holders<Deq1d<VAL_Type>, VAL_Type, INDEX_Type, PR_Type>({{*this}})
 {
 }

 void set_default_fn(std::function<void(VAL_Type**)> fn)
 {
  _Vec1d<VAL_Type>::set_default_fn(fn);
 }

 void _set_default(std::function<void(VAL_Type**)> fn)
 {
  set_default_fn(fn);
 }

 void pop_front()
 {
  ++offset_;
  if(offset_ == this->hive_structure_->block_size())
  {
   this->hive_structure_->pop_first_block();
   offset_ = 0;
  }
 }

 void push_back(const VAL_Type& v)
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

 void _each(std::function<void(VAL_Type& v, const INDEX_Type& index)> fn)
 {
  if(offset_ == 0)
    _Vec1d<VAL_Type>::_each(fn);
  else
    _Vec1d<VAL_Type>::_each_from_index(offset_, fn);
 }

 PR_Type _pr_each(std::function<typename PR_Type::level_type(VAL_Type& v)> fn)
 {
  if(offset_ == 0)
    return _Vec1d<VAL_Type>::_pr_each(fn);
  else
    return _Vec1d<VAL_Type>::_pr_each_from_index(offset_, fn);
 }

 PR_Type _pr_each(std::function<typename PR_Type::level_type(VAL_Type& v, const INDEX_Type& index)> fn)
 {
  if(offset_ == 0)
    return _Vec1d<VAL_Type>::_pr_each(fn);
  else
    return _Vec1d<VAL_Type>::_pr_each_from_index(offset_, fn);
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



#ifdef HIDE
#include "accessors.h"

#include "hive-structure.h"
#include "_vec1d.h"

#include <QVector>
#include <QString>
#include <QMap>

#include <QDebug>

#include <functional>


template<typename VAL_Type, typename INDEX_Type = quint16, typename PR_Type>
class Deq1d :
  public each_holders<Deq1d<VAL_Type>, VAL_Type, INDEX_Type, PR_Type> //: protected QPair<Vec1d<VAL_Type>, Vec1d<VAL_Type>>
{
 //Hive_Structure* front_hive_;
protected:

 _Vec1d<VAL_Type> front_vec_;
 _Vec1d<VAL_Type> back_vec_;

public:


 Deq1d()
  :  front_vec_(_Vec1d<VAL_Type>()),
     back_vec_(_Vec1d<VAL_Type>()),
     each_holders<Deq1d<VAL_Type>, VAL_Type, INDEX_Type, PR_Type>({{*this}})
 {

 }

 Deq1d(quint8 bsz)
  :  front_vec_(_Vec1d<VAL_Type>(bsz)),
     back_vec_(_Vec1d<VAL_Type>(bsz)),
     each_holders<Deq1d<VAL_Type>, VAL_Type, INDEX_Type, PR_Type>({{*this}})
 {

 }

 Deq1d(quint8 bsz, quint8 fbsz)
  :  front_vec_(_Vec1d<VAL_Type>(bsz)),
     back_vec_(_Vec1d<VAL_Type>(fbsz)),
     each_holders<Deq1d<VAL_Type>, VAL_Type, INDEX_Type, PR_Type>({{*this}})
 {

 }

 void set_default_fn(std::function<void(VAL_Type**)> fn)
 {
  front_vec_.set_default_fn(fn);
  back_vec_.set_default_fn(fn);
 }

 void _set_default(std::function<void(VAL_Type**)> fn)
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

 void _each(std::function<void(VAL_Type& v)> fn)
 {
  front_vec_._reach(fn);
  back_vec_._each(fn);
 }

 void _each(std::function<void(VAL_Type& v, const INDEX_Type& index)> fn)
 {
  front_vec_._reach(fn);
  back_vec_._each(fn);
 }

 PR_Type _pr_each(std::function<typename PR_Type::level_type(VAL_Type& v)> fn)
 {
  PR_Type result = front_vec_._pr_reach(fn);
  if(result.level >= 0)
    return result;
  return back_vec_._pr_each(fn);
 }

 PR_Type _pr_each(std::function<typename PR_Type::level_type(VAL_Type& v, const INDEX_Type& index)> fn)
 {
  PR_Type result = front_vec_._pr_reach(fn);
  if(result.level >= 0)
    return result;
  return back_vec_._pr_each(fn);
 }

 void _reach(std::function<void(VAL_Type& v)> fn)
 {
  back_vec_._reach(fn);
  front_vec_._each(fn);
 }

 void _reach(std::function<void(VAL_Type& v, const INDEX_Type& index)> fn)
 {
  back_vec_._reach(fn);
  front_vec_._each(fn);
 }

 PR_Type _pr_reach(std::function<typename PR_Type::level_type(VAL_Type& v)> fn)
 {
  PR_Type result = back_vec_._pr_reach(fn);
  if(result.level >= 0)
    return result;
  return front_vec_._pr_each(fn);
 }

 PR_Type _pr_reach(std::function<typename PR_Type::level_type(VAL_Type& v, const INDEX_Type& index)> fn)
 {
  PR_Type result = back_vec_._pr_reach(fn);
  if(result.level >= 0)
    return result;
  return front_vec_._pr_each(fn);
 }
};


#endif //def HIDE
#endif // DEQ1D__H
