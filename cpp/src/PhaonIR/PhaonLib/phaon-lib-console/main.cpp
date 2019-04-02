
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


//#include "kauvir-phaon/kph-command-package.h"

//#include "kauvir-code-model/kauvir-code-model.h"
//#include "kauvir-code-model/kcm-channel-group.h"
//#include "kcm-scopes/kcm-scope-system.h"

//#include "PhaonLib/phaon-namespace.h"
//#include "PhaonLib/phaon-class.h"
//#include "PhaonLib/phaon-function.h"
//#include "PhaonLib/phaon-symbol-scope.h"

//#include "relae-graph/relae-caon-ptr.h"

//#include "test-functions.h"

//#include "PhaonLib/phaon-channel-group-table.h"
//#include "PhaonLib/phaon-runner.h"

//#include "kcm-direct-eval/kcm-direct-eval.h"

//#include "kans.h"

//USING_KANS(KCM)
//USING_KANS(Phaon)
//USING_KANS(PhaonLib)


#include "phaon-lib/phr-runner.h"

#include "phaon-ir/phaon-ir.h"
#include "phaon-ir/channel/phr-channel-system.h"

#include "phaon-ir/phr-code-model.h"

#include "phaon-lib/phr-symbol-scope.h"


#include "phaon-ir/scopes/phr-runtime-scope.h"

#include "test-functions.h"

void local_program(PhaonIR& phr)
{
 phr.init_type_system();
 phr.init_type("fbase", DEFAULT_PTR_BYTE_CODE);
 phr.init_type("u4", 4);

 phr.init_program_stack();

 phr.enter_lexical_scope();

 phr.reset_program_stack();

 phr.push_carrier_stack("fuxe");
 phr.hold_type_by_name("fbase");
 //? phr.push_carrier_raw_value("&prn");
 phr.push_carrier_symbol("&prn");

 phr.push_carrier_stack("lambda");
 phr.hold_type_by_name("u4");
 phr.push_carrier_raw_value("2");

 phr.coalesce_channel_group();
}

//void phr_direct_eval(PHR_Code_Model* pcm,
//   PHR_Command_Package* pcp);
//{

//}
//kcm_->direct_eval(cpkg, this);

int main(int argc, char* argv[])
{
 PHR_Runner phrn;

 PHR_Channel_System pcs;
 PhaonIR phr(&pcs);

 phr.init_type_system();
 phr.init_type("fbase", DEFAULT_PTR_BYTE_CODE);
 phr.init_type("u4", 4);

 phr.create_channel_semantic_protocol("lambda");
 phr.create_channel_semantic_protocol("result");


// Phaon_Namespace phn("TestNS");
// Phaon_Class phc("Test_Class", &phn);

 PHR_Code_Model& pcm = phrn.get_pcm();
 pcm.set_type_system(phr.type_system());

 pcm.set_direct_eval_fn(&phr_direct_eval);

 PHR_Runtime_Scope prs(nullptr);

 PHR_Symbol_Scope pss(&prs);

 init_test_functions(phr, pcm, phrn.get_table(), pss);
 phrn.get_runtime_scope_queue().push_front(&prs);

// KPH_Command_Package khp;
// khp.parse_from_file( DEFAULT_KPH_FOLDER "/test/raw/t1.kph" );

 local_program(phr);

 PHR_Channel_Group* pcg = phr.get_select_channel_group();

 //khp.init_channel_group(kcm, kcg);
 phrn.run(*pcg);

 return 0;
}
