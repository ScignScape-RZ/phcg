
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
#include "scopes/phr-runtime-scope.h"

#include "phr-code-model.h"


PhaonIR::PhaonIR() :  type_system_(nullptr),
  program_stack_(nullptr),
  held_type_(nullptr), current_carrier_stack_(nullptr),
  held_channel_group_(nullptr), load_evaluator_fn_(nullptr),
  current_chief_unwind_scope_index_({0,0,0,0}),
  current_lexical_scope_(nullptr)
{

}


void PhaonIR::check_init_program_stack()
{
 auto it = stashed_program_stacks_.find(current_chief_unwind_scope_index_);
 if(it == stashed_program_stacks_.end())
 {
  init_program_stack();
  stashed_program_stacks_.insert(current_chief_unwind_scope_index_, program_stack_);
 }
 else
 {
  program_stack_ = it.value();
  program_stack_->clear();
 }
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

qint32 PhaonIR::get_s4_symbol_value(QString sym)
{
 if(sym.startsWith('#'))
 {
  //PHR_Channel_Group* pcg
  PHR_Channel_Group_Evaluator* ev = evaluate_channel_group_by_usi_symbol(sym);
  if(ev)
  {
   return ev->get_result_value_as<qint32>();
  }
  else
    return 0;
 }
 else
 {
  quint64 val;
  PHR_Type* ty = current_lexical_scope_->find_value(sym, val);
//  void* pv = (void*) val;
//  return *(qint32*)pv;
  return (qint32) val;
 }
}

void PhaonIR::delete_temps()
{
 retired_temps_.append(temps_by_channel_group_.values());
// QMapIterator<PHR_Channel_Group*> it(temps_by_channel_group_);
// while(it.hasNext())
// {
//  it.next();
// }
}

void PhaonIR::clear_temps()
{
 temp_anchored_channel_groups_.clear();
 temps_by_channel_group_.clear();
 indexed_channel_groups_.clear();
 unwind_scope_index_parents_.clear();
}

void PhaonIR::delete_retired()
{
 for(void* pv : retired_temps_)
 {
  delete pv;
 }
}

PHR_Channel* PhaonIR::get_channel_by_sp_name(QString sp_name, PHR_Channel_Group& pcg)
{
 auto it = semantic_protocols_.find(sp_name);
 if(it == semantic_protocols_.end())
   return nullptr;
 return pcg.value(it.value());
}

PHR_Carrier_Stack* PhaonIR::get_carrier_stack_by_sp_name(Unwind_Scope_Index usi,
  QString sp_name)
{
 auto it = sp_map_.find({usi, semantic_protocols_[sp_name]});
 if(it == sp_map_.end())
 {
  PHR_Carrier_Stack* result = new PHR_Carrier_Stack;
  result->set_sp_name(sp_name);
  sp_map_.insert({usi, semantic_protocols_[sp_name]}, result);
  return result;
 }
 return it.value();
}

void PhaonIR::hold_type_by_name(QString ty_name)
{
 PHR_Type* ty = type_system_->get_type_by_name(ty_name);
 held_type_ = ty;
}

void* PhaonIR::get_first_raw_value(QString sp_name, PHR_Channel_Group& pcg)
{
 return pcg.get_first_raw_value(semantic_protocols_[sp_name]);
}

QString PhaonIR::get_first_raw_value_string(QString sp_name, PHR_Channel_Group& pcg)
{
 return pcg.get_first_raw_value_string(semantic_protocols_[sp_name]);
}

void PhaonIR::push_unwind_scope(int level_delta)
{
 Unwind_Scope_Index usi = current_chief_unwind_scope_index_;//.project();
 inc_channel_pos();
 current_chief_unwind_scope_index_.chief_channel_pos = usi.level_channel_pos;
 current_chief_unwind_scope_index_.unwind_level = 0;
 current_chief_unwind_scope_index_.unwind_maximum_ = level_delta;
 current_chief_unwind_scope_index_.level_channel_pos = 0;
 unwind_scope_index_parents_[current_chief_unwind_scope_index_] = usi;//.project();
 held_program_stacks_[usi] = {program_stack_, current_carrier_stack_};
 check_init_program_stack();
}

void PhaonIR::pop_unwind_scope()
{
 current_chief_unwind_scope_index_ = unwind_scope_index_parents_[current_chief_unwind_scope_index_.project()];
 program_stack_ = held_program_stacks_[current_chief_unwind_scope_index_].first;
 current_carrier_stack_ = held_program_stacks_[current_chief_unwind_scope_index_].second;
 held_usi_symbol_ = QString("#%1-%2").arg(current_chief_unwind_scope_index_.chief_channel_pos)
   .arg(current_chief_unwind_scope_index_.unwind_level);
}


PHR_Channel_Group_Evaluator* PhaonIR::evaluate_channel_group_by_usi_symbol(QString usi_sym)
{
 auto it = temp_anchored_channel_groups_.find(usi_sym);
 if( it != temp_anchored_channel_groups_.end())
 {
  PHR_Channel_Group* pcg = it.value();
  PHR_Channel_Group_Evaluator* result = load_evaluator_fn_(*this, *pcg);
  result->run_eval();
  temps_by_channel_group_.insertMulti(pcg, result->get_result_value());
  return result;
 }
 return nullptr;
}

quint64 PhaonIR::default_cofinalizer(anchor_channel_link& acl, void* pv)
{
 qint32 result = *(qint32*)(pv);
 push_delete(pv);
 return result;
}

void PhaonIR::push_delete(void* pv)
{
 retired_temps_.push_back(pv);
}

void PhaonIR::evaluate_channel_group()
{
 PHR_Channel_Group_Evaluator* ev = load_evaluator_fn_(*this, *held_channel_group_);
 ev->run_eval();
 ev->debug_report();

 for(auto it: anchored_channel_groups_.values(held_channel_group_))
 {
  // //  chance to tailor for different protocols ...
  QString sym = it.sym;
  PHR_Runtime_Scope* scope = it.scope;
  void* pv = ev->get_result_value();
  if(it.cofinalizer)
  {
   quint64 val = (this->*it.cofinalizer)(it, pv);
   scope->update_raw_value(sym, val);
  }
  else
  {
   scope->update_value(sym, pv);
  }
 }

 // clean up anchored_channel_groups_? ...
}

void PhaonIR::push_carrier_expression()
{
 push_carrier_symbol(held_usi_symbol_);
}

void PhaonIR::index_channel_group()
{
 indexed_channel_groups_[current_chief_unwind_scope_index_] = held_channel_group_;
}

void PhaonIR::anchor_channel_group(QString sym, QString ch)
{
 anchored_channel_groups_.insert(held_channel_group_,
   {semantic_protocols_[ch], current_lexical_scope_, sym, nullptr});
}

void PhaonIR::copy_anchor_channel_group(QString sym, QString ch)
{
 anchored_channel_groups_.insert(held_channel_group_,
   {semantic_protocols_[ch], current_lexical_scope_, sym, &default_cofinalizer});
}

void PhaonIR::temp_anchor_channel_group()
{
 temp_anchored_channel_groups_[held_usi_symbol_] = held_channel_group_;
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

void PhaonIR::inc_channel_pos()
{
 ++current_chief_unwind_scope_index_.level_channel_pos;
}

void PhaonIR::push_carrier_raw_value(QString rv)
{
 inc_channel_pos();
 PHR_Carrier* phc = new PHR_Carrier;
 phc->set_raw_value_string(rv);
 phc->set_phr_type(held_type_);
 current_carrier_stack_->push(phc);
}

void PhaonIR::push_carrier_symbol(QString sn)
{
 inc_channel_pos();
 PHR_Carrier* phc = new PHR_Carrier;
 phc->set_symbol_name(sn);
 phc->set_phr_type(held_type_);
 current_carrier_stack_->push(phc);
}

void PhaonIR::push_carrier_stack(QString sp_name)
{
 check_semantic_protocol(sp_name);
 PHR_Carrier_Stack* st = get_carrier_stack_by_sp_name(current_chief_unwind_scope_index_,
   sp_name);
 program_stack_->push(st);
 current_carrier_stack_ = st;
}

void PhaonIR::enter_lexical_scope()
{
 current_lexical_scope_ = new PHR_Runtime_Scope(current_lexical_scope_);
}

void PhaonIR::init_type_system()
{
 type_system_ = new PHR_Type_System;
}

void PhaonIR::init_code_model()
{
 code_model_ = new PHR_Code_Model;
 code_model_->set_type_system(type_system_);
}

void PhaonIR::init_type(QString type_name, quint8 byte_code)
{
 type_system_->check_add_type_by_name(type_name, byte_code);
}
