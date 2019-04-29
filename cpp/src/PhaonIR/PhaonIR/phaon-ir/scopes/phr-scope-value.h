
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_SCOPE_VALUE__H
#define PHR_SCOPE_VALUE__H

#include <QString>

class PHR_Type;

struct PHR_Scope_Value
{
 PHR_Type* ty;
 quint64 raw_value;
 QString string_value;

 PHR_Scope_Value();
 PHR_Scope_Value(PHR_Type* _ty, quint64 _raw_value);

 template<typename T>
 T* pValue_as()
 {
  return reinterpret_cast<T*>(raw_value);
 }

};

#endif // PHR_SCOPE__H
