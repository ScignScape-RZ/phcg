
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_LOGICAL_SCOPE_INFO__H
#define PHR_LOGICAL_SCOPE_INFO__H

#include <QString>

#include "accessors.h"

class PHR_Logical_Scope_Info
{
 QString name_;

public:

 PHR_Logical_Scope_Info(QString name);

 ACCESSORS(QString ,name)

};

#endif // PHR_LOGICAL_SCOPE_INFO__H
