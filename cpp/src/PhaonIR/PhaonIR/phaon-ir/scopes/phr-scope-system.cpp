
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-scope-system.h"
#include "phr-runtime-scope.h"

#include "kans.h"

//USING_KANS(CMD)


PHR_Scope_System::PHR_Scope_System()
  :  current_scope_(nullptr)
{

}

quint64 PHR_Scope_System::find_value_from_current_scope(QString key)//, quint64& val, PHR_Runtime_Scope::Storage_Options& so)
{
 if(!current_scope_)
   return 0;
 PHR_Runtime_Scope::Storage_Options so;
 quint64 val;
 PHR_Type* ty = current_scope_->find_value(key, val, so);
 return val;
}
