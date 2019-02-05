
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHAON_IR__H
#define PHAON_IR__H

#include <QString>
#include <QMap>

#include <functional>

#include "accessors.h"

#define PASTE_EXPRESSION(...) __VA_ARGS__


class PHR_Channel_Semantic_Protocol;
class PHR_Type_System;
class PHR_Program_Stack;
class PHR_Carrier_Stack;
class PHR_Type;
class PHR_Channel_Group;
class PHR_Channel_Group_Evaluator;

class PhaonIR
{
 QMap<QString, PHR_Channel_Semantic_Protocol*> semantic_protocols_;
 QMap<PHR_Channel_Semantic_Protocol*, PHR_Carrier_Stack*> sp_map_;
 PHR_Type_System* type_system_;
 PHR_Program_Stack* program_stack_;
 PHR_Type* held_type_;
 PHR_Carrier_Stack* current_carrier_stack_;
 PHR_Channel_Group* held_channel_group_;

 std::function<PHR_Channel_Group_Evaluator*(PhaonIR&,
   PHR_Channel_Group&)> load_evaluator_fn_;

 PHR_Carrier_Stack* get_carrier_stack_by_sp_name(QString sp_name);
 void check_semantic_protocol(QString sp_name);

public:

 PhaonIR();

 ACCESSORS(PASTE_EXPRESSION(std::function<PHR_Channel_Group_Evaluator*(PhaonIR&,
   PHR_Channel_Group&)>) ,load_evaluator_fn)

 void init_program_stack();
 void reset_program_stack();
 void init_type_system();
 void init_type(QString type_name);

 void push_carrier_stack(QString sp_name);
 void push_carrier_raw_value(QString rv);

 void hold_type_by_name(QString ty_name);
 void coalesce_channel_group();
 void evaluate_channel_group();

 QString get_first_raw_value_string(QString sp_name, PHR_Channel_Group& pcg);

};

#endif // PHAON_IR__H
