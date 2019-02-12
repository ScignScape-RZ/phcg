
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-runtime-scope.h"


PHR_Runtime_Scope::PHR_Runtime_Scope(PHR_Runtime_Scope* parent_scope, PHR_Logical_Scope_Info* info)
  :  parent_scope_(parent_scope), info_(info)
{

}

void PHR_Runtime_Scope::add_direct_value(QString key, PHR_Type* ty, quint64 val)
{
 values_[key] = {Storage_Options::Direct, {ty, val}};
}

void PHR_Runtime_Scope::add_pointer_value(QString key, PHR_Type* ty, quint64 val)
{
 values_[key] = {Storage_Options::Pointer, {ty, val}};
}

void PHR_Runtime_Scope::add_function_vector_value(QString key, void* fv)
{
 values_[key] = {Storage_Options::Function_Vector, {nullptr, (quint64) fv}};
}

void PHR_Runtime_Scope::add_function_vector_value(QString key, PHR_Type* ty, quint64 val)
{
 values_[key] = {Storage_Options::Function_Vector, {ty, val}};
}

void PHR_Runtime_Scope::update_direct_value(QString key, quint64 val)
{
 values_[key].second.raw_value = val;
}

void PHR_Runtime_Scope::update_value(QString key, void* pv)
{
 values_[key].second.raw_value = (quint64) pv;
}

PHR_Type* PHR_Runtime_Scope::find_value(QString key, quint64& val, Storage_Options& so)
{
 auto it = values_.find(key);
 if(it == values_.end())
   return nullptr;
 so = it.value().first;
 val = it.value().second.raw_value;
 return it.value().second.ty;
}
