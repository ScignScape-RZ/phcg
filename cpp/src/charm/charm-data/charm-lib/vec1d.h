
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef VEC1D__H
#define VEC1D__H


#include "_vec1d.h"


template<typename VAL_Type>
class Vec1d : public _Vec1d<VAL_Type>, public each_holders<Vec1d<VAL_Type>, VAL_Type>
{
public:

 Vec1d(quint8 bsz = 16)
  :  _Vec1d<VAL_Type>(bsz), each_holders<Vec1d<VAL_Type>, VAL_Type>({{*this}})
 {
 }

};

//template<typename VEC_Type>
//struct test
//{
// union{
// _each_holder<VEC_Type> each;
// _reach_holder<VEC_Type> reach;
// };
//};

#endif // VEC1D__H
