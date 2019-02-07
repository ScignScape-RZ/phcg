
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-scope.h"


PHR_Scope::PHR_Scope(PHR_Scope* parent_scope, PHR_Logical_Scope_Info* info)
  :  parent_scope_(parent_scope), info_(info)
{

}

void PHR_Scope::add_value(QString key, PHR_Type* ty, quint64 val)
{
 values_[key] = {ty, val};
}

void PHR_Scope::update_value(QString key, void* pv)
{
 values_[key].raw_value = (quint64) pv;
}

PHR_Type* PHR_Scope::find_value(QString key, quint64& val)
{
 auto it = values_.find(key);
 if(it == values_.end())
   return nullptr;
 val = it.value().raw_value;
 return it.value().ty;
}
