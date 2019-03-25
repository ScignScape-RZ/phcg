
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


template<typename VAL_Type>
class Vec1d
{
 Hive_Structure* hive_structure_;

public:

 Vec1d(quint8 bsz = 16)
  :  hive_structure_(new Hive_Structure)
 {
  hive_structure_->set_block_size(bsz);
  hive_structure_->set_value_size(sizeof(VAL_Type));
 }


 void push_back(VAL_Type& v)
 {
  void* spot = hive_structure_.get_push_back_location();

 }

};



#endif // VEC1D__H
