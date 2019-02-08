
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-ir/phaon-ir.h"

#include <QDebug>



void local_program(PhaonIR& phr)
{
 phr.init_type_system();
 phr.init_type("fbase");
 phr.init_type("u4");

 phr.init_program_stack();

 phr.enter_lexical_scope();

 phr.reset_program_stack();

 phr.push_carrier_stack("fuxe");
 phr.hold_type_by_name("fbase");
 phr.push_carrier_raw_value("&prn");

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

#ifdef HIDE
void local_program1(PhaonIR& phr)
{
 phr.init_type_system();
 phr.init_type("fbase");
 phr.init_type("u4");

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
 phr.delete_temps();
 phr.clear_temps();
}
#endif
