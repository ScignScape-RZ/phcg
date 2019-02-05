
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KOP_BASE__H
#define KOP_BASE__H

#include <QPair>
#include <QtGlobal>


template<typename T>
struct PHR_KOP_Base
{

public:

 PHR_KOP_Base()
 {

 }

 virtual void run_eval(QPair<T, T>& args, T& result) = 0;
 virtual void run_eval(QVector<T>& args, T& result) = 0;

};

#endif // KOP_BASE__H
