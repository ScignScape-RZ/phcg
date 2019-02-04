
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CARRIER__H
#define PHR_CARRIER__H

#include <QString>

#include "accessors.h"

class PHR_Type;

class PHR_Carrier
{
 QString symbol_name_;
 QString raw_value_;
 PHR_Type* phr_type_;

public:

 PHR_Carrier();

 ACCESSORS(QString ,symbol_name)
 ACCESSORS(QString ,raw_value)
 ACCESSORS(PHR_Type* ,phr_type)

};

#endif //  PHR_CARRIER__H
