
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CALLABLE_VALUE__H
#define PHR_CALLABLE_VALUE__H

#include <QString>

#include "accessors.h"

#include <functional>

#include "phaon-ir/scopes/phr-runtime-scope.h"

class PhaonIR;
class PHR_Type_Object;
class PHR_Scope_Value;
class PHR_Carrier;

class PHR_Callable_Value
{
 PhaonIR* phaon_ir_;
 QString name_;

public:

 typedef std::function<void(QString, QString&,
   PHR_Type_Object*, PHR_Carrier&, PHR_Scope_Value*&,
   PHR_Runtime_Scope::Storage_Options& so)> fn_type;

 PHR_Callable_Value(PhaonIR* phaon_ir, QString name);

 void run(fn_type fn = nullptr);
 void register_with_name(QString name);

};

#endif //  PHR_CALLABLE_VALUE__H
