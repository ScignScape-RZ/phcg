
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-symbol-scope.h"

#include "phr-function-vector.h"

#include "phaon-ir/scopes/phr-runtime-scope.h"

#include "kans.h"


//USING//_KANS(PhaonLib)


PHR_Symbol_Scope::PHR_Symbol_Scope(PHR_Runtime_Scope* runtime_scope)
  :  runtime_scope_(runtime_scope)
{

}

void PHR_Symbol_Scope::add_function(QString name, PHR_Function& phf)
{
 if(PHR_Function_Vector* pfv = runtime_scope_->
   get_function_vector_value_as<PHR_Function_Vector>(name))
 {
  pfv->push_back(phf);
  return;
 }
 PHR_Function_Vector* pfv = new PHR_Function_Vector(phf);
 runtime_scope_->add_function_vector_value(name, pfv);

}

