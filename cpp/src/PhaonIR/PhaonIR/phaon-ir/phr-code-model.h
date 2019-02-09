
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CODE_MODEL__H
#define PHR_CODE_MODEL__H

#include <QString>

#include "accessors.h"

class PHR_Type_System;

class PHR_Code_Model
{
 PHR_Type_System* type_system_;

public:

 PHR_Code_Model();

 ACCESSORS(PHR_Type_System* ,type_system)

};

#endif // PHR_CODE_MODEL__H
