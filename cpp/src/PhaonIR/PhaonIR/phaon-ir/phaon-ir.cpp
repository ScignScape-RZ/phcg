
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-ir.h"

#include "types/phr-type-system.h"
#include "channel/phr-program-stack.h"
#include "channel/phr-channel-semantic-protocol.h"
#include "channel/phr-carrier-stack.h"
#include "channel/phr-carrier.h"
#include "channel/phr-channel-group.h"
#include "channel/phr-channel.h"
#include "eval/phr-channel-group-evaluator.h"


PhaonIR::PhaonIR() :  type_system_(nullptr),
  program_stack_(nullptr),
  held_type_(nullptr), current_carrier_stack_(nullptr),
  held_channel_group_(nullptr), load_evaluator_fn_(nullptr)
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

PHR_Channel* PhaonIR::get_channel_by_sp_name(QString sp_name, PHR_Channel_Group& pcg)
{
 auto it = semantic_protocols_.find(sp_name);
 if(it == semantic_protocols_.end())
   return nullptr;
 return pcg.value(it.value());
}

PHR_Carrier_Stack* PhaonIR::get_carrier_stack_by_sp_name(QString sp_name)
{
 auto it = sp_map_.find(semantic_protocols_[sp_name]);
 if(it == sp_map_.end())
 {
  PHR_Carrier_Stack* result = new PHR_Carrier_Stack;
  result->set_sp_name(sp_name);
  sp_map_.insert(semantic_protocols_[sp_name], result);
  return result;
 }
 return it.value();
}

void PhaonIR::hold_type_by_name(QString ty_name)
{
 PHR_Type* ty = type_system_->get_type_by_name(ty_name);
 held_type_ = ty;
}

QString PhaonIR::get_first_raw_value_string(QString sp_name, PHR_Channel_Group& pcg)
{
 return pcg.get_first_raw_value_string(semantic_protocols_[sp_name]);
}

void PhaonIR::evaluate_channel_group()
{
 PHR_Channel_Group_Evaluator* ev = load_evaluator_fn_(*this, *held_channel_group_);
 ev->run_eval();
 ev->debug_report();
}

void PhaonIR::coalesce_channel_group()
{
 PHR_Channel_Group* pcg = new PHR_Channel_Group;
 program_stack_->each_carrier_stack([pcg, this] (PHR_Carrier_Stack& pcs)
 {
  PHR_Channel* pch = new PHR_Channel;
  pch->resize(pcs.size());
  pcs.indexed_each_carrier([pch, this] (int i, PHR_Carrier& pcr)
  {
   (*pch)[i] = &pcr;
  });
  pcg->insert(semantic_protocols_.value(pcs.sp_name()), pch);
 });
 held_channel_group_ = pcg;
}

void PhaonIR::push_carrier_raw_value(QString rv)
{
 PHR_Carrier* phc = new PHR_Carrier;
 phc->set_raw_value_string(rv);
 phc->set_phr_type(held_type_);
 current_carrier_stack_->push(phc);
}

void PhaonIR::push_carrier_stack(QString sp_name)
{
 check_semantic_protocol(sp_name);
 PHR_Carrier_Stack* st = get_carrier_stack_by_sp_name(sp_name);
 program_stack_->push(st);
 current_carrier_stack_ = st;
}

void PhaonIR::init_type_system()
{
 type_system_ = new PHR_Type_System;
}

void PhaonIR::init_type(QString type_name)
{
 type_system_->check_add_type_by_name(type_name);
}
