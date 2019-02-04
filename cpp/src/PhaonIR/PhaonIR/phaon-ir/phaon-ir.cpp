
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-ir.h"

#include "types/phr-type-system.h"
#include "channel/phr-program-stack.h"
#include "channel/phr-channel-semantic-protocol.h"
#include "channel/phr-carrier-stack.h"

PhaonIR::PhaonIR() :  type_system_(nullptr),
  program_stack_(nullptr)
{

}

void PhaonIR::init_program_stack()
{
 program_stack_ = new PHR_Program_Stack;
}

void PhaonIR::reset_program_stack()
{
 program_stack_->clear();
}

void PhaonIR::check_semantic_protocol(QString sp_name)
{
 auto it = semantic_protocols_.find(sp_name);
 if(it == semantic_protocols_.end())
 {
  PHR_Channel_Semantic_Protocol* sp = new
    PHR_Channel_Semantic_Protocol;
  sp->set_name(sp_name);
  semantic_protocols_.insert(sp_name, sp);
 }
}

PHR_Carrier_Stack* PhaonIR::get_carrier_stack_by_sp_name(QString sp_name)
{
 auto it = sp_map_.find(semantic_protocols_[sp_name]);
 if(it == sp_map_.end())
 {
  PHR_Carrier_Stack* result = new PHR_Carrier_Stack;
  sp_map_.insert(semantic_protocols_[sp_name], result);
  return result;
 }
 return it.value();
}

void PhaonIR::push_carrier_stack(QString sp_name)
{
 check_semantic_protocol(sp_name);
 PHR_Carrier_Stack* st = get_carrier_stack_by_sp_name(sp_name);
 program_stack_->push(st);
}

void PhaonIR::init_type_system()
{
 type_system_ = new PHR_Type_System;
}

void PhaonIR::init_type(QString type_name)
{
 type_system_->check_add_type_by_name(type_name);
}
