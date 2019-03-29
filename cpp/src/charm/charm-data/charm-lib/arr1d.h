
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ARR1D__H
#define ARR1D__H


#include "_vec1d.h"

#include "accessors.h"


template<typename VAL_Type, typename INDEX_Type = quint16, typename PR_Type = _pr_break>
class Arr1d : public _Vec1d<VAL_Type>,
   public each_holders<Arr1d<VAL_Type>, VAL_Type, INDEX_Type, PR_Type>
{
 quint32 length_;

public:

 Arr1d(quint32 length, quint8 bsz = 16)
  :  _Vec1d<VAL_Type>(bsz),
    each_holders<Arr1d<VAL_Type>, VAL_Type, INDEX_Type, PR_Type>({{*this}}),
    length_(length)
 {
 }

 quint32 push_back(const VAL_Type& v)
 {
  quint32 sz = this->size();
  if(sz >= length_)
    return 0;
  quint32 result = sz - length_;
  _Vec1d<VAL_Type>::push_back(v);
  return result;
 }

};


#endif // ARR1D__H
