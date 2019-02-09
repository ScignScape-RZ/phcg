
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-carrier.h"

#include "types/phr-type-object.h"

PHR_Carrier::PHR_Carrier()
{

}

QString* PHR_Carrier::symbol_as_pointer()
{
 return &symbol_name_;
}

PHR_Type_Object* PHR_Carrier::type_object() const
{
 if(!type_object_)
   type_object_ = new PHR_Type_Object(phr_type_);
 return type_object_;
}
