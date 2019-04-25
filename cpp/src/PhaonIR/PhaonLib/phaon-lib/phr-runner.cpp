
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

#include "phaon-ir/scopes/phr-scope-system.h"
#include "phaon-ir/phr-code-model.h"

#include "phaon-ir/runtime/phr-command-package.h"


//#include "kcm-command-package/kcm-command-package.h"


//USING//_KANS(PhaonLib)


PHR_Runner::PHR_Runner()
  :  pcm_(new PHR_Code_Model),
    table_(nullptr)//, scopes_(nullptr)
{
 init_scope_system();
 pcm_->set_table(table_);
}

void PHR_Runner::init_scope_system()
{
 scopes_ = new PHR_Scope_System;
 pcm_->set_scopes(scopes_);
 pcm_->init_scope_system();

 PHR_Type_System* type_system = pcm_->type_system();
 table_ = new PHR_Channel_Group_Table(*type_system);
}


void PHR_Runner::run(PHR_Channel_Group& pcg, PHR_Symbol_Scope* pss)
{
 PHR_Command_Package pcp(pcg);
// KCM_Command_Package kcp(kcg);
 pcm_->direct_eval(&pcp, pss);
}


QQueue<PHR_Runtime_Scope*>& PHR_Runner::get_runtime_scope_queue()
{
 return scopes_->phr_scope_queue();
}

