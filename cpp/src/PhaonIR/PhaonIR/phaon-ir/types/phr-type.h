
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_TYPE__H
#define PHR_TYPE__H

#include <QString>

#include "accessors.h"

class PHR_Type
{
 QString name_;

public:

 PHR_Type();

 ACCESSORS(QString ,name)


};

#endif // PHR_TYPE__H
