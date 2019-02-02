
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-type-system.h"

#include "phr-type.h"

PHR_Type_System::PHR_Type_System()
{

}

void PHR_Type_System::check_add_type_by_name(QString name)
{
 auto it = types_.find(name);
 if(it == types_.end())
 {
  PHR_Type* ty = new PHR_Type;
  ty->set_name(name);
  types_.insert(name, ty);
 }
}
