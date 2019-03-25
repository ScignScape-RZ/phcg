
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QUE1D__H
#define QUE1D__H


#include "accessors.h"

#include "hive-structure.h"
#include "vec1d.h"

#include <QVector>
#include <QString>
#include <QMap>

#include <QDebug>

#include <functional>


template<typename VAL_Type>
class Que1d : protected Vec1d<VAL_Type>
{

public:

 Que1d(quint8 bsz = 16)
  :  Vec1d<VAL_Type>(bsz)
 {
 }

 void enqueue(const VAL_Type& v)
 {
  Vec1d<VAL_Type>::push_back(v);
 }

 void each(std::function<void(VAL_Type& v)> fn)
 {
  Vec1d<VAL_Type>::each(fn);
 }


};



#endif // QUE1D__H
