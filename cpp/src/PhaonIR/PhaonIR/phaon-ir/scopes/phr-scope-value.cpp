
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-scope-value.h"

PHR_Scope_Value::PHR_Scope_Value(PHR_Type* _ty, quint64 _raw_value)
  : ty(_ty), raw_value(_raw_value)
{

}

PHR_Scope_Value::PHR_Scope_Value()
  :  ty(nullptr), raw_value(0)
{

}
