
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-scope.h"

PHR_Result_Holder::PHR_Result_Holder()
  :  raw_value(nullptr)
{

}

PHR_Scope::PHR_Scope(PHR_Scope* parent_scope, PHR_Logical_Scope_Info* info)
  :  parent_scope_(parent_scope), info_(info)
{

}
