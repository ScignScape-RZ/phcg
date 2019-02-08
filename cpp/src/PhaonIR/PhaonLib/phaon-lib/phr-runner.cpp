
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-runner.h"

#include "phr-symbol-scope.h"
#include "phr-function-vector.h"

//#include "kauvir-code-model/kauvir-code-model.h"
//#include "kcm-scopes/kcm-scope-system.h"

#include "phr-channel-group-table.h"


//#include "kcm-command-package/kcm-command-package.h"


//USING//_KANS(PhaonLib)


PHR_Runner::PHR_Runner()
  :  //kcm_(new Kauvir_Code_Model),
    table_(nullptr)//, scopes_(nullptr)
{
 init_scope_system();
}

void PHR_Runner::init_scope_system()
{
// scopes_ = new KCM_Scope_System;
// kcm_->set_scope_system(scopes_);
// kcm_->init_scope_system();

// Kauvir_Type_System* type_system = kcm_->type_system();
// table_ = new PHR_Channel_Group_Table(*type_system);

}


void PHR_Runner::run(PHR_Channel_Group& pcg)
{
// KCM_Command_Package kcp(kcg);
// kcm_->direct_eval(&kcp, nullptr);
}


QQueue<PHR_Symbol_Scope*>& PHR_Runner::get_phaon_scope_queue()
{
 //return scopes_->phaon_scope_queue();
}

