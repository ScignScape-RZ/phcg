
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-cocyclic-type.h"

PHR_Cocyclic_Type::PHR_Cocyclic_Type(QString name)
  :  name_(name)
{

}

void PHR_Cocyclic_Type::add_precycle_field(QString sym, PHR_Type* ty)
{
 precycle_fields_.push_back({sym, ty});
}

void PHR_Cocyclic_Type::add_cocycle_field(QString sym, PHR_Type* ty)
{
 cocycle_fields_.push_back({sym, ty});
}
