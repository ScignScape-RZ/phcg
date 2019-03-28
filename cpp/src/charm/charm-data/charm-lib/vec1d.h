
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef VEC1D__H
#define VEC1D__H


#include "_vec1d.h"


template<typename VAL_Type>
class Vec1d : public _Vec1d<VAL_Type>
{
public:

 union{
 _each_holder<Vec1d> each;
 _each_holder<Vec1d> reach;
 };

 Vec1d(quint8 bsz = 16)
  :  _Vec1d<VAL_Type>(bsz), each({*this})
 {
 }

};



#endif // VEC1D__H
