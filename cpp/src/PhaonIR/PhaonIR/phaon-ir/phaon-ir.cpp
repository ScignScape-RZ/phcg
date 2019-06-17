
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-ir.h"

#include "types/phr-type-system.h"
#include "types/phr-cocyclic-type.h"

#include "channel/phr-program-stack.h"
#include "channel/phr-channel-semantic-protocol.h"
#include "channel/phr-carrier-stack.h"
#include "channel/phr-carrier.h"
#include "channel/phr-channel-group.h"
#include "channel/phr-channel.h"
#include "eval/phr-channel-group-evaluator.h"
#include "scopes/phr-runtime-scope.h"

#include "channel/phr-channel-system.h"
#include "table/phr-channel-group-table.h"
#include "runtime/phr-command-package.h"

#include "types/phr-type-object.h"

#include "phr-code-model.h"

#include "phr-direct-eval/phr-direct-eval.h"

#include "runtime/phr-callable-value.h"
#include "runtime/phr-expression-object.h"

#include "types/phr-type.h"

#include "PhaonIR/phr-runtime/phr-fn-doc/phr-fn-doc.h"

#include <QDebug>

#include "textio.h"

USING_KANS(TextIO)


PhaonIR::PhaonIR(PHR_Channel_System* channel_system) :  type_system_(nullptr),
  channel_system_(channel_system), program_stack_(nullptr),
  held_type_(nullptr), current_carrier_stack_(nullptr),
  held_channel_group_(nullptr), load_evaluator_fn_(nullptr),
   //?current_chief_unwind_scope_index_({0,0,0,0}),
  //current_lexical_scope()(nullptr),
  held_symbol_scope_(nullptr), direct_eval_fn_(nullptr),
  source_fn_anon_count_(0), current_cocyclic_type_(nullptr),
  sp_map_(new QMap<QPair<Unwind_Scope_Index,
    PHR_Channel_Semantic_Protocol*>, PHR_Carrier_Stack*>)
{
 current_source_fn_name_ = starting_source_fn_name_ = ";_main";
 //current_source_function_scope_ = new Source_Function_Scope{current_source_fn_name_};
 init_current_source_function_scope(current_source_fn_name_);
}


void PhaonIR::check_init_program_stack()
{
 auto it = stashed_program_stacks().find(current_chief_unwind_scope_index());
 if(it == stashed_program_stacks().end())
 {
  init_program_stack();
  stashed_program_stacks().insert(current_chief_unwind_scope_index(), program_stack_);
 }
 else
 {
  program_stack_ = it.value();
  program_stack_->clear();
 }
}

void PhaonIR::reinit_program_stack()
{
 program_stack_ = new PHR_Program_Stack;
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
 auto it = channel_system_->find(sp_name);
 if(it == channel_system_->end())
 {
  PHR_Channel_Semantic_Protocol* sp = new
    PHR_Channel_Semantic_Protocol;
  sp->set_name(sp_name);
  channel_system_->insert(sp_name, sp);
 }
}

qint32 PhaonIR::get_s4_symbol_value(QString sym)
{
 if(sym.startsWith('#'))
 {
  PHR_Expression_Object* pxo = nullptr;
  void* pv = nullptr;
  //PHR_Channel_Group* pcg
  PHR_Channel_Group_Evaluator* ev = evaluate_channel_group_by_usi_symbol(sym,
    pxo, pv);
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
  PHR_Runtime_Scope::Storage_Options so;
  PHR_Type* ty = current_lexical_scope()->find_value(sym, val, so);
//  void* pv = (void*) val;
//  return *(qint32*)pv;
  return (qint32) val;
 }
}

PHR_Type* PhaonIR::init_value_from_symbol(QString sym,
  PHR_Runtime_Scope::Storage_Options& so, quint64& val)
{
 if(sym.startsWith('#'))
 {
  //PHR_Channel_Group* pcg
  PHR_Expression_Object* pxo = nullptr;
  void* pv = nullptr;
  PHR_Channel_Group_Evaluator* ev = evaluate_channel_group_by_usi_symbol(
    sym, pxo, pv);
  if(ev)
  {
   so = PHR_Runtime_Scope::Storage_Options::Direct;
   val = ev->get_result_value_as<qint32>();
  }
  else if(pxo)
  {
   so = PHR_Runtime_Scope::Storage_Options::Pointer;
   val = (quint64) pxo;
  }
  else if(pv)
  {
   so = PHR_Runtime_Scope::Storage_Options::Pointer;
   val = (quint64) pv;
  }
  return nullptr;
 }
 //quint64 val;
 //PHR_Runtime_Scope::Storage_Options so;
 //PHR_Type* ty = current_lexical_scope()->find_value(sym, val, so);
 return current_lexical_scope()->find_value(sym, val, so);
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
 indexed_channel_groups().clear();
 unwind_scope_index_parents().clear();
}

void PhaonIR::delete_retired()
{
 for(void* pv : retired_temps_)
 {
  delete pv;
 }
 retired_temps_.clear();
}

PHR_Channel* PhaonIR::get_channel_by_sp_name(QString sp_name, PHR_Channel_Group& pcg)
{
 auto it = channel_system_->find(sp_name);
 if(it == channel_system_->end())
   return nullptr;
 return pcg.value(it.value());
}

PHR_Carrier_Stack* PhaonIR::get_carrier_stack_by_sp_name(Unwind_Scope_Index usi,
  QString sp_name)
{
 auto it = sp_map_->find({usi, (*channel_system_)[sp_name]});
 if(it == sp_map_->end())
 {
  PHR_Carrier_Stack* result = new PHR_Carrier_Stack;
  result->set_sp_name(sp_name);
  sp_map_->insert({usi, (*channel_system_)[sp_name]}, result);
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
 return pcg.get_first_raw_value((*channel_system_)[sp_name]);
}

QString PhaonIR::get_first_raw_value_string(QString sp_name, PHR_Channel_Group& pcg)
{
 return pcg.get_first_raw_value_string((*channel_system_)[sp_name]);
}

void PhaonIR::push_unwind_scope(QString level_delta)
{
 QStringList qsl = level_delta.simplified().split(' ');
 push_unwind_scope(qsl[0].toInt(), qsl[1]);
}

void PhaonIR::enter_cocyclic_type(QString name)
{
 //PHR_Cocyclic_Type* coy =
 current_cocyclic_type_ = new PHR_Cocyclic_Type(name);
}

void PhaonIR::leave_cocyclic_type(QString name)
{

}

void PhaonIR::type_field_decl(QString modifier, QString sym, QString type_name)
{
 if(!current_cocyclic_type_)
   return;

 PHR_Type* ty = type_system_->get_type_by_name(type_name);
 if(modifier == "pr")
 {
  current_cocyclic_type_->add_precycle_field(sym, ty);
 }
 else if(modifier == "co")
 {
  current_cocyclic_type_->add_cocycle_field(sym, ty);
 }
}

void PhaonIR::type_decl(QString sym, QString type_name)
{
 PHR_Type* ty = type_system_->get_type_by_name(type_name);

 // currently only supports...
 PHR_Runtime_Scope::Storage_Options so;
 if(type_name.endsWith('*'))
   so = PHR_Runtime_Scope::Storage_Options::Pointer;
 else if (type_name == "str")
   so = PHR_Runtime_Scope::Storage_Options::String_Pointer;
 else
   so = PHR_Runtime_Scope::Storage_Options::Direct;

 scopes_.current_scope()->type_decl(sym, so, ty);
}

void PhaonIR::type_decl(QString sym_ty)
{
 QStringList qsl = sym_ty.simplified().split(' ');
 type_decl(qsl[0], qsl[1]);
}

void PhaonIR::type_field_decl(QString m_sym_ty)
{
 QStringList qsl = m_sym_ty.simplified().split(' ');
 type_field_decl(qsl[0], qsl[1], qsl[2]);
}

void PhaonIR::push_unwind_scope(int level_delta, QString chn)
{
 Unwind_Scope_Index& usi = current_chief_unwind_scope_index();//.project();
 Unwind_Scope_Index lusi = usi;
 inc_channel_pos();
 usi.chief_channel_pos = lusi.level_channel_pos;
 usi.unwind_level = 0;
 usi.depth = lusi.depth + level_delta;
 usi.unwind_maximum_ = level_delta;
 usi.level_channel_pos = 0;
 usi.channel_name = chn;
 unwind_scope_index_parents()[usi] = lusi;//.project();
 held_program_stacks()[lusi] = {program_stack_, current_carrier_stack_};
 check_init_program_stack();
}

void PhaonIR::pop_unwind_scope()
{
 Unwind_Scope_Index& usi = current_chief_unwind_scope_index();
 Unwind_Scope_Index lusi = usi;
 usi = unwind_scope_index_parents()[lusi.project()];
 program_stack_ = held_program_stacks()[usi].first;
 current_carrier_stack_ = held_program_stacks()[usi].second;
 held_usi_symbol_ = QString("#%1-%2-%3").arg(usi.level_channel_pos)
   .arg(usi.unwind_level)
   .arg(usi.depth);
 QString hsi = held_usi_symbol_;
 qDebug() << hsi;
}


PHR_Channel_Group_Evaluator* PhaonIR::evaluate_channel_group_by_usi_symbol(QString usi_sym,
  PHR_Expression_Object*& pxo, void*& pv)
{
// char by_need = 0;
// if(usi_sym[1] == '?')
// {
//  usi_sym.remove(1, 1);
//  by_need = '?';
// }
 auto it = temp_anchored_channel_groups_.find(usi_sym);
 if( it != temp_anchored_channel_groups_.end())
 {
  PHR_Channel_Group* pcg = it.value();
  if(usi_sym[1] == '?')
  {
   pxo = new PHR_Expression_Object(this, pcg->clone());
   return nullptr;
  }

  PHR_Channel_Group_Evaluator* result = load_evaluator_fn_(*this, *pcg);

  if(result)
  {
   result->run_eval();
   temps_by_channel_group_.insertMulti(pcg, result->get_result_value());
   return result;
  }

  quint64 rv = 0;
  QString string_result;
  const PHR_Type_Object* pto = nullptr;

  evaluate_channel_group_via_direct_eval(pcg, rv,
    string_result, pto, usi_sym);

  // what about non-string returns?
  if(rv == (quint64) &string_result)
  {
   rv = (quint64) new QString(string_result);
   temps_by_channel_group_.insertMulti(pcg, (void*) rv);
  }
  pv = (void*) rv;
  return nullptr;
 }
 return nullptr;
}

PHR_Channel_Group_Evaluator* PhaonIR::run_expression_object(PHR_Channel_Group* pcg)
{
 PHR_Channel_Group_Evaluator* result = load_evaluator_fn_(*this, *pcg);
 result->run_eval();
 //?temps_by_channel_group_.insertMulti(pcg, result->get_result_value());
 return result;
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

void PhaonIR::init_table()
{
 table_ = new PHR_Channel_Group_Table(*type_system_);
 code_model_->set_table(table_);
}


void PhaonIR::hold_symbol_scope(PHR_Symbol_Scope* pss)
{
 held_symbol_scope_ = pss;
}


void PhaonIR::evaluate_channel_group_via_direct_eval(PHR_Channel_Group* pcg,
  quint64& rv, QString& string_result, const PHR_Type_Object*& pto, QString anchor)
{
 PHR_Command_Package pcp(*pcg);
 pcp.set_output_symbol_name(anchor);

 if(direct_eval_fn_)
   direct_eval_fn_(code_model_, &pcp, held_symbol_scope_);

 pto = pcp.result_type_object();
 if(!pto)
   return;
 rv = pcp.eval_result();
 if(rv == (quint64) pcp.string_result_as_pointer())
 {
  string_result = pcp.string_result();
  rv = (quint64) &string_result;
 }
}

void PhaonIR::evaluate_channel_group()
{
 PHR_Channel_Group_Evaluator* ev = load_evaluator_fn_(*this, *held_channel_group_);

 const PHR_Type_Object* pto = nullptr;
 quint64 rv = 0;
 void* pv = nullptr;

 QString string_result;

 if(ev)
 {
  ev->run_eval();
  ev->debug_report();
  pv = ev->get_result_value();
 }
 else
 {
  QString rsym = anchored_channel_groups_.value(held_channel_group_).sym;
  evaluate_channel_group_via_direct_eval(held_channel_group_,
    rv, string_result, pto, rsym);
  //return;
  //? phr_direct_eval(code_model_, &pcp, held_symbol_scope_);
 }


 //pcp.
 //quint64 rv = pcp.

 for(auto it: anchored_channel_groups_.values(held_channel_group_))
 {
  // //  chance to tailor for different protocols ...
  QString sym = it.sym;
  PHR_Runtime_Scope* scope = it.scope;

  if(it.cofinalizer)
  {
   quint64 val = pv?
      (this->*it.cofinalizer)(it, pv) : rv;

   // // just for now ...
   if(pto->ty()->name() == "str")
   {
    QString* qs = (QString*) val;
    scope->update_string_value(sym, val);
   }
   else
   {
    scope->update_direct_value(sym, val);
   }

  }
  else
  {
   void* vv = pv? pv :  (void*) rv;

   scope->update_value(sym, vv);
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
 indexed_channel_groups()[current_chief_unwind_scope_index()] = held_channel_group_;
}

void PhaonIR::mark_void_call()
{

}

void PhaonIR::anchor_without_channel_group(QString sym, QString ch)
{
 PHR_Carrier_Stack* pcs = program_stack_->top();
 PHR_Carrier* phc = pcs->top();
 QString rvs = phc->raw_value_string();

 //void* rv = phc->raw_value();
 if(ch == "parse-literal")
 {
  PHR_Type* ty = phc->phr_type();
  current_lexical_scope()->add_direct_value(sym, ty, rvs.toInt());
 }
 else if(ch == "type-default")
 {
  PHR_Type* ty = scopes_.get_type_for_symbol_name(sym);

  //quint64 vv = scopes_.find_value_from_current_scope(sym, &pty);

  if(!ty)
  {
   return;
  }

  int pid = ty->qmetatype_ptr_code();
  if(pid != QMetaType::UnknownType)
  {
   void* pv = QMetaType::create(pid);
   QObject* qob = static_cast<QObject*>(pv);
   current_lexical_scope()->add_pointer_value(sym, ty, (quint64) pv);
  }
 }
}

void PhaonIR::anchor_channel_group(QString sym, QString ch)
{
 anchored_channel_groups_.insert(held_channel_group_,
   {(*channel_system_)[ch], current_lexical_scope(), sym, nullptr});
}

void PhaonIR::copy_anchor_channel_group(QString sym, QString ch)
{
 anchored_channel_groups_.insert(held_channel_group_,
   {(*channel_system_)[ch], current_lexical_scope(), sym, &PhaonIR::default_cofinalizer});
}

void PhaonIR::anchor_without_channel_group(QString str)
{
 QStringList qsl = str.simplified().split(' ');
 anchor_without_channel_group(qsl.first(), qsl.last());
}

void PhaonIR::copy_anchor_channel_group(QString str)
{
 QStringList qsl = str.simplified().split(' ');
 copy_anchor_channel_group(qsl.first(), qsl.last());
}

void PhaonIR::temp_anchor_channel_group_by_need()
{
 temp_anchored_channel_groups_[held_usi_symbol_.replace(1, 0, '?')] = held_channel_group_;
}

void PhaonIR::temp_anchor_channel_group()
{
 temp_anchored_channel_groups_[held_usi_symbol_] = held_channel_group_;
}

void PhaonIR::finalize_signature(QString fn)
{
 PHR_Type* ty = new PHR_Type;
 //ty->set_name(fn);
 ty->set_signature_channel_group(held_channel_group_->clone());
 scopes_.current_scope()->add_direct_value(fn, ty, 0);
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
  pcg->insert(channel_system_->value(pcs.sp_name()), pch);
 });
 held_channel_group_ = pcg;
}

void PhaonIR::inc_channel_pos()
{
 ++current_chief_unwind_scope_index().level_channel_pos;
}

void PhaonIR::push_carrier_raw_value(QString rv)
{
 inc_channel_pos();
 PHR_Carrier* phc = new PHR_Carrier;
 phc->set_raw_value_string(rv);
 phc->set_phr_type(held_type_);
 current_carrier_stack_->push(phc);
}

void PhaonIR::push_carrier_anon_fn(QString fn)
{
 PHR_Callable_Value* pcv = new PHR_Callable_Value(this, fn);
 //push_carrier_symbol(fn.prepend('&'));
 PHR_Carrier* phc = new PHR_Carrier;
 phc->set_raw_value(pcv);
 phc->set_phr_type(held_type_);
 current_carrier_stack_->push(phc);
}

void PhaonIR::push_carrier_type_holder(QString ty_name)
{
 inc_channel_pos();
 PHR_Carrier* phc = new PHR_Carrier;
 PHR_Type* ty = type_system_->get_type_by_name(ty_name);
// phc->set_symbol_name(sn);
 phc->set_phr_type(ty);
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
 PHR_Carrier_Stack* st = get_carrier_stack_by_sp_name(current_chief_unwind_scope_index(),
   sp_name);
 program_stack_->push(st);
 current_carrier_stack_ = st;
 held_type_ = nullptr;
}

void PhaonIR::enter_lexical_scope()
{
 scopes_.set_current_scope(new PHR_Runtime_Scope(current_lexical_scope()));
}



void PhaonIR::create_channel_semantic_protocol(QString name)
{
 PHR_Channel_Semantic_Protocol* pcsp = new PHR_Channel_Semantic_Protocol;
 pcsp->set_name(name);
 (*channel_system_)[name] = pcsp;
}

void PhaonIR::init_type_system()
{
 type_system_ = new PHR_Type_System;
}

void PhaonIR::init_code_model()
{
 code_model_ = new PHR_Code_Model;
 code_model_->set_type_system(type_system_);
 code_model_->set_phaon_ir(this);
 code_model_->set_scopes(&scopes_);
}

void PhaonIR::init_type(QString type_name, quint8 byte_code)
{
 type_system_->check_add_type_by_name(type_name, byte_code);
}

void PhaonIR::read_line(QString inst)
{
 static QMap<QString, void(PhaonIR::*)()> static_map {{
  { "init_program_stack", &PhaonIR::init_program_stack },
  { "enter_lexical_scope", &PhaonIR::enter_lexical_scope },
  { "reset_program_stack", &PhaonIR::reset_program_stack },
  { "coalesce_channel_group", &PhaonIR::coalesce_channel_group },
  { "evaluate_channel_group", &PhaonIR::evaluate_channel_group },
  { "delete_temps", &PhaonIR::delete_temps },
  { "delete_retired", &PhaonIR::delete_retired },
  { "clear_temps", &PhaonIR::clear_temps },
  { "reset_program_stack", &PhaonIR::reset_program_stack },
  { "pop_unwind_scope", &PhaonIR::pop_unwind_scope },
  { "temp_anchor_channel_group", &PhaonIR::temp_anchor_channel_group },
  { "temp_anchor_channel_group_by_need", &PhaonIR::temp_anchor_channel_group_by_need },
  { "push_carrier_expression", &PhaonIR::push_carrier_expression },
  { "index_channel_group", &PhaonIR::index_channel_group },
  { "mark_void_call", &PhaonIR::mark_void_call }
 }};

 auto it = static_map.find(inst);
 if(it != static_map.end())
 {
  line_ops_[current_source_fn_name_].push_back({nullptr, fn_u{.fn0 = it.value()}});
 }
}

void PhaonIR::init_current_source_function_scope(QString source_fn)
{
 current_source_function_scope_ = new Source_Function_Scope({
   source_fn, {0,0,0,0}, {}, {}, {} , {}
 });
}

void PhaonIR::run_callable_value(QString source_fn)
{
 run_state_stack_.push({current_source_function_scope_,
   program_stack_, current_carrier_stack_,
   held_channel_group_, sp_map_});

 init_current_source_function_scope(source_fn);
 init_program_stack();
 current_carrier_stack_ = nullptr;
 held_channel_group_ = nullptr;
 sp_map_ = new QMap<QPair<Unwind_Scope_Index,
   PHR_Channel_Semantic_Protocol*>, PHR_Carrier_Stack*>;
 run_lines(source_fn);

 //if(current_carrier_stack_) delete?
 delete current_source_function_scope_;
 delete program_stack_;
 delete sp_map_;

 Run_State rs = run_state_stack_.pop();
 current_source_function_scope_ = rs._source_function_scope;
 program_stack_ = rs._program_stack;
 current_carrier_stack_ = rs._carrier_stack;
 held_channel_group_ = rs._held_channel_group;
 sp_map_ = rs._sp_map;
}

void PhaonIR::run_lines(QString source_fn)
{
 auto it = line_ops_.find(source_fn);
 if(it == line_ops_.end())
   return;
 const QList<QPair<QString*, fn_u>>& lines = it.value();
 for(auto& pr: lines)
 {
  if(pr.first)
    (this->*(pr.second.fn1))(*pr.first);
  else
    (this->*(pr.second.fn0))();
 }
}

void PhaonIR::read_line(QString inst, QString arg)
{
 static QMap<QString, void(PhaonIR::*)(QString)> static_map {{
  { "push_carrier_stack", &PhaonIR::push_carrier_stack },
  { "hold_type_by_name", &PhaonIR::hold_type_by_name },
  { "push_unwind_scope", &PhaonIR::push_unwind_scope },
  { "push_carrier_symbol", &PhaonIR::push_carrier_symbol },
  { "push_carrier_stack", &PhaonIR::push_carrier_stack },
  { "push_carrier_raw_value", &PhaonIR::push_carrier_raw_value },
  { "copy_anchor_channel_group", &PhaonIR::copy_anchor_channel_group },
  { "anchor_without_channel_group", &PhaonIR::anchor_without_channel_group },
  { "push_carrier_anon_fn", &PhaonIR::push_carrier_anon_fn },
  { "type_decl", &PhaonIR::type_decl },
  { "type_field_decl", &PhaonIR::type_field_decl },
  { "finalize_signature", &PhaonIR::finalize_signature },
  { "push_carrier_type_holder", &PhaonIR::push_carrier_type_holder },

  { "enter_cocyclic_type", &PhaonIR::enter_cocyclic_type },
  { "leave_cocyclic_type", &PhaonIR::leave_cocyclic_type },

 }};

 auto it = static_map.find(inst);
 if(it != static_map.end())
 {
  QString* a = new QString(arg);
  line_ops_[current_source_fn_name_].push_back({a, fn_u{.fn1=it.value()}});
 }
}

void PhaonIR::parse_fn_line(QString line)
{
 if(line[3] == 'p')
 {
  ++source_fn_anon_count_;
  source_fn_names_.push(current_source_fn_name_);
  current_source_fn_name_ = QString::number(source_fn_anon_count_).prepend(';');
 }
 else if(line[3] == 'e')
 {
  last_source_fn_name_ = current_source_fn_name_;
  current_source_fn_name_ = source_fn_names_.pop();
 }
 else
 {
  QString fn = line.mid(3).simplified();
 }
}

void PhaonIR::reread_substitute(QString& key)
{
 static QMap<QString, QString(PhaonIR::*)() const> static_map {{
  { "last_source_fn_name", &PhaonIR::last_source_fn_name },
 }};

 auto it = static_map.find(key);
 if(it != static_map.end())
 {
  key = (this->**it)();
 }
}

void PhaonIR::read_local_program(QString path)
{
 QString lines;
 load_file(path, lines);

 int pos = 0;
 int end = lines.length();

 while(pos < end)
 {
  int np = lines.indexOf(";.\n", pos);
  if(np == -1)
    np = lines.indexOf("\n.\n", pos);
  if(np == -1)
    break;
  QString l = lines.mid(pos, np - pos).trimmed();
  if(l.startsWith(".;"))
  {
   pos = np + 3;
   continue;
  }
  if(l.startsWith("@fn"))
  {
   parse_fn_line(l);
   pos = np + 3;
   continue;
  }

  bool reread = false;
  int mp = l.indexOf(" $");
  if(mp == -1)
  {
   mp = l.indexOf(" @");
   reread = true;
  }
  if(mp != -1)
  {
   QString l1 = l.mid(0, mp).trimmed();
   QString l2 = l.mid(mp + 2, np - mp - 2).trimmed();
   if(reread)
     reread_substitute(l2);
   read_line(l1, l2);
  }
  else
  {
   read_line(l.trimmed());
  }
  pos = np + 3;
 }
 run_lines(starting_source_fn_name_);
}
