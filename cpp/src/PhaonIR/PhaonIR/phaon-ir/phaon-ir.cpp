
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

#include "channel/phr-channel-system.h"
#include "table/phr-channel-group-table.h"
#include "runtime/phr-command-package.h"

#include "phr-code-model.h"

#include "phr-direct-eval/phr-direct-eval.h"

#include "textio.h"

USING_KANS(TextIO)


PhaonIR::PhaonIR(PHR_Channel_System* channel_system) :  type_system_(nullptr),
  channel_system_(channel_system), program_stack_(nullptr),
  held_type_(nullptr), current_carrier_stack_(nullptr),
  held_channel_group_(nullptr), load_evaluator_fn_(nullptr),
  current_chief_unwind_scope_index_({0,0,0,0}),
  current_lexical_scope_(nullptr),
  held_symbol_scope_(nullptr), direct_eval_fn_(nullptr),
  source_fn_anon_count_(0)
{
 current_source_fn_name_ = starting_source_fn_name_ = ";_main";
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
  PHR_Runtime_Scope::Storage_Options so;
  PHR_Type* ty = current_lexical_scope_->find_value(sym, val, so);
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
  PHR_Channel_Group_Evaluator* ev = evaluate_channel_group_by_usi_symbol(sym);
  if(ev)
  {
   val = ev->get_result_value_as<qint32>();
  }
  return nullptr;
 }
 //quint64 val;
 //PHR_Runtime_Scope::Storage_Options so;
 //PHR_Type* ty = current_lexical_scope_->find_value(sym, val, so);
 return current_lexical_scope_->find_value(sym, val, so);
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
 auto it = sp_map_.find({usi, (*channel_system_)[sp_name]});
 if(it == sp_map_.end())
 {
  PHR_Carrier_Stack* result = new PHR_Carrier_Stack;
  result->set_sp_name(sp_name);
  sp_map_.insert({usi, (*channel_system_)[sp_name]}, result);
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


void PhaonIR::push_unwind_scope(int level_delta, QString chn)
{
 Unwind_Scope_Index usi = current_chief_unwind_scope_index_;//.project();
 inc_channel_pos();
 current_chief_unwind_scope_index_.chief_channel_pos = usi.level_channel_pos;
 current_chief_unwind_scope_index_.unwind_level = 0;
 current_chief_unwind_scope_index_.unwind_maximum_ = level_delta;
 current_chief_unwind_scope_index_.level_channel_pos = 0;
 current_chief_unwind_scope_index_.channel_name = chn;
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

void PhaonIR::init_table()
{
 table_ = new PHR_Channel_Group_Table(*type_system_);
 code_model_->set_table(table_);
}


void PhaonIR::hold_symbol_scope(PHR_Symbol_Scope* pss)
{
 held_symbol_scope_ = pss;
}

void PhaonIR::evaluate_channel_group()
{
 PHR_Channel_Group_Evaluator* ev = load_evaluator_fn_(*this, *held_channel_group_);

 if(ev)
 {
  ev->run_eval();
  ev->debug_report();
 }
 else
 {
  PHR_Command_Package pcp(*held_channel_group_);
  if(direct_eval_fn_)
    direct_eval_fn_(code_model_, &pcp, held_symbol_scope_);
  //? phr_direct_eval(code_model_, &pcp, held_symbol_scope_);
 }

 for(auto it: anchored_channel_groups_.values(held_channel_group_))
 {
  // //  chance to tailor for different protocols ...
  QString sym = it.sym;
  PHR_Runtime_Scope* scope = it.scope;
  void* pv = ev->get_result_value();
  if(it.cofinalizer)
  {
   quint64 val = (this->*it.cofinalizer)(it, pv);
   scope->update_direct_value(sym, val);
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
   {(*channel_system_)[ch], current_lexical_scope_, sym, nullptr});
}

void PhaonIR::copy_anchor_channel_group(QString sym, QString ch)
{
 anchored_channel_groups_.insert(held_channel_group_,
   {(*channel_system_)[ch], current_lexical_scope_, sym, &default_cofinalizer});
}

void PhaonIR::copy_anchor_channel_group(QString str)
{
 QStringList qsl = str.simplified().split(' ');
 copy_anchor_channel_group(qsl.first(), qsl.last());
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
  pcg->insert(channel_system_->value(pcs.sp_name()), pch);
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

void PhaonIR::push_carrier_anon_fn(QString fn)
{
 push_carrier_symbol(fn.prepend('&'));
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
}

void PhaonIR::init_type(QString type_name, quint8 byte_code)
{
 type_system_->check_add_type_by_name(type_name, byte_code);
}

void PhaonIR::read_line(QString inst)
{
 static QMap<QString, void(PhaonIR::*)()> static_map {{
  { "init_program_stack", &init_program_stack },
  { "enter_lexical_scope", &enter_lexical_scope },
  { "reset_program_stack", &reset_program_stack },
  { "coalesce_channel_group", &coalesce_channel_group },
  { "evaluate_channel_group", &evaluate_channel_group },
  { "delete_temps", &delete_temps },
  { "delete_retired", &delete_retired },
  { "clear_temps", &clear_temps },
  { "reset_program_stack", &reset_program_stack },
  { "pop_unwind_scope", &pop_unwind_scope },
  { "temp_anchor_channel_group", &temp_anchor_channel_group },
  { "push_carrier_expression", &push_carrier_expression }

 }};

 auto it = static_map.find(inst);
 if(it != static_map.end())
 {
  line_ops_[current_source_fn_name_].push_back({nullptr, fn_u{.fn0 = it.value()}});
 }
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
  { "push_carrier_stack", &push_carrier_stack },
  { "hold_type_by_name", &hold_type_by_name },
  { "push_unwind_scope", &push_unwind_scope },
  { "push_carrier_symbol", &push_carrier_symbol },
  { "push_carrier_stack", &push_carrier_stack },
  { "push_carrier_raw_value", &push_carrier_raw_value },
  { "copy_anchor_channel_group", &copy_anchor_channel_group },
  { "push_carrier_anon_fn", &push_carrier_anon_fn },
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
  { "last_source_fn_name", &last_source_fn_name },
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
