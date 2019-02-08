
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CARRIER__H
#define PHR_CARRIER__H

#include <QString>

#include "accessors.h"

class PHR_Type;
class PHR_Type_Object;

class PHR_Carrier
{
 QString symbol_name_;
 QString raw_value_string_;
 PHR_Type* phr_type_;
 void* raw_value_;

 PHR_Type_Object* type_object_;

public:

 PHR_Carrier();

 ACCESSORS(QString ,symbol_name)
 ACCESSORS(QString ,raw_value_string)
 ACCESSORS(PHR_Type* ,phr_type)
 ACCESSORS(void* ,raw_value)

 ACCESSORS__GDECLARE(PHR_Type_Object* ,type_object)

};

#endif //  PHR_CARRIER__H
