
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-code-model.h"


PHR_Code_Model::PHR_Code_Model()
  :  type_system_(nullptr), scope_system_(nullptr), table_(nullptr)
{

}

void PHR_Code_Model::direct_eval(PHR_Command_Package* pcp)
{
 if(direct_eval_fn_)
 {
  direct_eval_fn_(this, pcp);
 }
}

void PHR_Code_Model::init_scope_system()
{
 //scope_system_->join_lexical_scope(current_lexical_scope_);
}
