
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_TYPE_OBJECT__H
#define KCM_TYPE_OBJECT__H

#include <QString>

#include "accessors.h"

class PHR_Type;

class KCM_Type_Object
{
 PHR_Type* ty_;

public:

 KCM_Type_Object(PHR_Type* ty);

 ACCESSORS(PHR_Type* ,ty)


};

#endif // KCM_TYPE_OBJECT__H
