
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

class PHR_Command_Runtime_Table;

class PHR_Code_Model
{
 PHR_Type_System* type_system_;
 PHR_Scope_System* scope_system_;
 PHR_Command_Runtime_Table* table_;

 typedef std::function<void(PHR_Code_Model* pcm,
   PHR_Command_Package* pcp)> direct_eval_fn_type;

 direct_eval_fn_type direct_eval_fn_;


public:

 PHR_Code_Model();

 ACCESSORS(PHR_Type_System* ,type_system)
 ACCESSORS(PHR_Scope_System* ,scope_system)
 ACCESSORS(PHR_Command_Runtime_Table* ,table)

 ACCESSORS(direct_eval_fn_type ,direct_eval_fn)


 void init_scope_system();

 void direct_eval(PHR_Command_Package* pcp);

};

#endif // PHR_CODE_MODEL__H
