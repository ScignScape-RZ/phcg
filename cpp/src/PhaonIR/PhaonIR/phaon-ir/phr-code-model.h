
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CODE_MODEL__H
#define PHR_CODE_MODEL__H

#include <QString>

#include "accessors.h"

class PHR_Type_System;
class PHR_Scope_System;
class PHR_Command_Package;

class PHR_Symbol_Scope;

class PHR_Channel_Group_Table;

class PhaonIR;
class PHR_Type_Object;

class PHR_Code_Model
{
 PHR_Type_System* type_system_;
 PHR_Scope_System* scopes_;
 PHR_Channel_Group_Table* table_;

 typedef std::function<void(PHR_Code_Model* pcm,
   PHR_Command_Package* pcp, PHR_Symbol_Scope* pss)> direct_eval_fn_type;

 direct_eval_fn_type direct_eval_fn_;

 PhaonIR* phaon_ir_;


public:

 PHR_Code_Model();

 ACCESSORS(PHR_Type_System* ,type_system)
 ACCESSORS(PHR_Scope_System* ,scopes)
 ACCESSORS(PHR_Channel_Group_Table* ,table)

 ACCESSORS(PhaonIR* ,phaon_ir)

//? ACCESSORS(PHR_Symbol_Scope* ,current_symbol_scope)

 ACCESSORS(direct_eval_fn_type ,direct_eval_fn)

 PHR_Type_Object* create_and_register_type_object(QString name);
 PHR_Type_Object* create_and_register_type_object(QString name, int bc);

 void init_scope_system();

 void direct_eval(PHR_Command_Package* pcp, PHR_Symbol_Scope* current_symbol_scope);

};

#endif // PHR_CODE_MODEL__H
