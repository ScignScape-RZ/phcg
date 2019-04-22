
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_RUNTIME_SCOPE__H
#define PHR_RUNTIME_SCOPE__H

#include <QString>
#include <QMap>


#include "phr-scope-value.h"

class PHR_Logical_Scope_Info;
class PHR_Type;


class PHR_Runtime_Scope
{
 PHR_Logical_Scope_Info* info_;
 PHR_Runtime_Scope* parent_scope_;

public:

 enum class Storage_Options {
   N_A, Direct, Pointer, Function_Vector, Not_Otherwise_Specified
 };

 QMap<QString, QPair<Storage_Options, PHR_Scope_Value>> values_;

 QMap<QString, QPair<Storage_Options, PHR_Type*>> type_declarations_;

public:

 PHR_Runtime_Scope(PHR_Runtime_Scope* parent_scope, PHR_Logical_Scope_Info* info = nullptr);

 void type_decl(QString sym, Storage_Options so, PHR_Type*);

 void add_direct_value(QString key, PHR_Type* ty, quint64 val);
 void add_pointer_value(QString key, PHR_Type* ty, quint64 val);
 void add_function_vector_value(QString key, PHR_Type* ty, quint64 val);

 void add_function_vector_value(QString key, void* fv);
 void check_type_decl(QString key);

 PHR_Type* get_type_for_symbol_name(QString sym);
 PHR_Type* find_value(QString key, quint64& val, Storage_Options& so);

 void update_value(QString key, void* pv);
 void update_direct_value(QString key, quint64 val);

 template<typename T>
 T* get_pointer_value_as(QString key)
 {
  auto it = values_.find(key);
  if(it == values_.end())
    return nullptr;
  if(it.value().first == Storage_Options::Pointer)
    return it.value().second.pValue_as<T>();
  return nullptr;
 }

 template<typename T>
 T* get_function_vector_value_as(QString key)
 {
  auto it = values_.find(key);
  if(it == values_.end())
    return nullptr;
  if(it.value().first == Storage_Options::Function_Vector)
    return it.value().second.pValue_as<T>();
  return nullptr;
 }

};

#endif // PHR_RUNTIME_SCOPE__H
