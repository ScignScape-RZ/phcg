
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef VEC1D__H
#define VEC1D__H


#include "_vec1d.h"


template<typename VAL_Type, typename INDEX_Type = quint16, typename PR_Type = _pr_break>
class Vec1d : public _Vec1d<VAL_Type>,
   public each_holders<Vec1d<VAL_Type>, VAL_Type, INDEX_Type, PR_Type>
{
public:

 Vec1d(quint8 bsz = 16)
  :  _Vec1d<VAL_Type>(bsz),
    each_holders<Vec1d<VAL_Type>, VAL_Type, INDEX_Type, PR_Type>({{*this}})
 {
 }

};


#endif // VEC1D__H
