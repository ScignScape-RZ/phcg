
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_TYPE__H
#define PHR_TYPE__H

#include <QString>

#include "accessors.h"

class QMetaObject;

class PHR_Type
{
 QString name_;
 quint8 byte_code_;

 const QMetaObject* qmo_;
 const QMetaObject* pqmo_;

 int qmetatype_ptr_code_;

public:

 PHR_Type();

 ACCESSORS(QString ,name)
 ACCESSORS(quint8 ,byte_code)

 ACCESSORS(const QMetaObject* ,qmo)
 ACCESSORS(const QMetaObject* ,pqmo)

 ACCESSORS(int ,qmetatype_ptr_code)

};

#endif // PHR_TYPE__H
