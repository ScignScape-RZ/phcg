
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-ir/phaon-ir.h"

#include "phaon-ir/phr-code-model.h"
#include "phaon-ir/scopes/phr-runtime-scope.h"

#include "phr-direct-eval/phr-direct-eval.h"
#include "phaon-ir/table/phr-symbol-scope.h"
#include "phaon-ir/table/phr-channel-group-table.h"

#include "basic-functions.h"

//#include "phaon-lib/phr-runner.h"

#include <QDebug>

//#ifdef HIDE
void local_program1(PhaonIR& phr)
{
 phr.init_type_system();
 phr.init_type("fbase", DEFAULT_PTR_BYTE_CODE);
 phr.init_type("u4", 4);

 phr.init_code_model();

 PHR_Code_Model& pcm = *phr.code_model();
 pcm.set_type_system(phr.type_system());

 phr.create_channel_semantic_protocol("lambda");
 phr.create_channel_semantic_protocol("result");

 pcm.set_direct_eval_fn(&phr_direct_eval);

 PHR_Runtime_Scope prs(nullptr);

 PHR_Symbol_Scope pss(&prs);

 phr.hold_symbol_scope(&pss);

 phr.init_table();

// PHR_Runner phrn;
// phrn.

 init_test_functions(phr, pcm, *phr.table(), pss);
 //phrn.get_runtime_scope_queue().push_front(&prs);

 phr.init_program_stack();

 phr.enter_lexical_scope();

 phr.reset_program_stack();

 phr.push_carrier_stack("fuxe");
 phr.hold_type_by_name("fbase");
 //?phr.push_carrier_raw_value("&prn");
 phr.push_carrier_symbol("&prn");

 phr.push_carrier_stack("lambda");
 phr.hold_type_by_name("u4");
 phr.push_carrier_raw_value("2");

 phr.coalesce_channel_group();
 phr.evaluate_channel_group();

 phr.delete_temps();
 phr.delete_retired();
 phr.clear_temps();

 phr.reset_program_stack();

}
//#endif // HIDE

//#ifdef HIDE
void local_program(PhaonIR& phr)
{
 phr.init_type_system();
 phr.init_type("fbase", DEFAULT_PTR_BYTE_CODE);
 phr.init_type("u4", 4);


 // //  setup
 phr.init_code_model();

 PHR_Code_Model& pcm = *phr.code_model();
 pcm.set_type_system(phr.type_system());

 phr.create_channel_semantic_protocol("lambda");
 phr.create_channel_semantic_protocol("result");

 pcm.set_direct_eval_fn(&phr_direct_eval);

 PHR_Runtime_Scope prs(nullptr);

 PHR_Symbol_Scope pss(&prs);

 phr.init_table();

// PHR_Runner phrn;
// phrn.

 init_test_functions(phr, pcm, *phr.table(), pss);

 phr.hold_symbol_scope(&pss);
 //phrn.get_runtime_scope_queue().push_front(&prs);
 // //  setup

 phr.read_local_program(DEFAULT_PHR_FOLDER "/t1.phr");

#ifdef HIDE

 phr.init_program_stack();

 phr.enter_lexical_scope();

 phr.reset_program_stack();

 phr.push_carrier_stack("fuxe");
 phr.hold_type_by_name("fbase");
 phr.push_carrier_raw_value("#+");

 phr.push_carrier_stack("lambda");
 phr.hold_type_by_name("u4");
 phr.push_carrier_raw_value("2");

 phr.push_unwind_scope(1);

 phr.push_carrier_stack("fuxe");
 phr.hold_type_by_name("fbase");
 phr.push_carrier_raw_value("#+");

 phr.push_carrier_stack("lambda");
 phr.hold_type_by_name("u4");
 phr.push_carrier_raw_value("7");
 phr.push_carrier_raw_value("9");

 phr.push_carrier_stack("result");
 phr.index_channel_group();
 phr.coalesce_channel_group();

 phr.pop_unwind_scope();
 phr.temp_anchor_channel_group();

 phr.hold_type_by_name("u4");
 phr.push_carrier_expression();
 phr.coalesce_channel_group();
 phr.copy_anchor_channel_group("x", "result");

 phr.evaluate_channel_group();

 phr.delete_temps();
 phr.delete_retired();
 phr.clear_temps();

 phr.reset_program_stack();


 phr.push_carrier_stack("fuxe");
 phr.hold_type_by_name("fbase");
 phr.push_carrier_raw_value("#+");

 phr.push_carrier_stack("lambda");
 phr.hold_type_by_name("u4");
 phr.push_carrier_raw_value("22");
 phr.push_carrier_symbol("x");
 phr.coalesce_channel_group();

 phr.evaluate_channel_group();

 phr.delete_temps();
 phr.delete_retired();
 phr.clear_temps();

 phr.reset_program_stack();

 phr.push_carrier_stack("fuxe");
 phr.hold_type_by_name("fbase");
 //?phr.push_carrier_raw_value("&prn");
 phr.push_carrier_symbol("&prn");

 phr.push_carrier_stack("lambda");
 phr.hold_type_by_name("u4");
 phr.push_carrier_symbol("x");

 phr.coalesce_channel_group();
 phr.evaluate_channel_group();
#endif
}

