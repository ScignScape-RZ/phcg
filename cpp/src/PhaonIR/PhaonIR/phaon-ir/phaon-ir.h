
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHAON_IR__H
#define PHAON_IR__H

#include <QString>
#include <QMap>
#include <QMultiMap>

#include <functional>

#include "accessors.h"

#include "scopes/phr-runtime-scope.h"

#define PASTE_EXPRESSION(...) __VA_ARGS__


class PHR_Channel_Semantic_Protocol;
class PHR_Type_System;
class PHR_Program_Stack;
class PHR_Carrier_Stack;
class PHR_Type;
class PHR_Channel_Group;
class PHR_Channel_Group_Evaluator;
class PHR_Channel;

class PHR_Symbol_Scope;


class PHR_Runtime_Scope;
class PHR_Scope_Value;
class PHR_Channel_System;

class PHR_Code_Model;
class PHR_Channel_Group_Table;

class PhaonIR
{
 struct Unwind_Scope_Index
 {
  quint8 chief_channel_pos;
  quint8 unwind_level;
  quint8 unwind_maximum_;
  quint8 level_channel_pos;

  Unwind_Scope_Index project()
  {
   return {chief_channel_pos, unwind_level, 0, 0};
  }
 };

 PHR_Channel_System* channel_system_;
 QMap<QPair<Unwind_Scope_Index, PHR_Channel_Semantic_Protocol*>, PHR_Carrier_Stack*> sp_map_;
 PHR_Type_System* type_system_;
 PHR_Program_Stack* program_stack_;
 PHR_Type* held_type_;
 PHR_Carrier_Stack* current_carrier_stack_;
 PHR_Channel_Group* held_channel_group_;
 PHR_Channel_Group_Table* table_;

 QString held_usi_symbol_;

 std::function<PHR_Channel_Group_Evaluator*(PhaonIR&,
   PHR_Channel_Group&)> load_evaluator_fn_;

 Unwind_Scope_Index current_chief_unwind_scope_index_;

 QMap<Unwind_Scope_Index, Unwind_Scope_Index> unwind_scope_index_parents_;

 QMap<Unwind_Scope_Index, QPair<PHR_Program_Stack*, PHR_Carrier_Stack*>> held_program_stacks_;
 QMap<Unwind_Scope_Index, PHR_Program_Stack*> stashed_program_stacks_;
 QMap<Unwind_Scope_Index, PHR_Channel_Group*> indexed_channel_groups_;

 QMap<QString, PHR_Channel_Group*> temp_anchored_channel_groups_;

 QMultiMap<PHR_Channel_Group*, void*> temps_by_channel_group_;

 QList<void*> retired_temps_;

 PHR_Code_Model* code_model_;

 struct anchor_channel_link
 {
  PHR_Channel_Semantic_Protocol* protocol;
  PHR_Runtime_Scope* scope;
  QString sym;
  quint64 (PhaonIR::*cofinalizer)(anchor_channel_link& acl, void* pv);
 };

 quint64 default_cofinalizer(anchor_channel_link& acl, void* pv);

 QMultiMap<PHR_Channel_Group*, anchor_channel_link> anchored_channel_groups_;

 PHR_Runtime_Scope* current_lexical_scope_;


 friend bool operator<(const Unwind_Scope_Index& lhs, const Unwind_Scope_Index& rhs)
 {
  if(lhs.chief_channel_pos != rhs.chief_channel_pos)
    return lhs.chief_channel_pos < rhs.chief_channel_pos;
  if(lhs.unwind_level != rhs.unwind_level)
    return lhs.unwind_level < rhs.unwind_level;
  if(lhs.level_channel_pos != rhs.level_channel_pos)
    return lhs.level_channel_pos < rhs.level_channel_pos;
  return false;
 }

 PHR_Carrier_Stack* get_carrier_stack_by_sp_name(Unwind_Scope_Index usi,
   QString sp_name);
 void check_semantic_protocol(QString sp_name);
 void inc_channel_pos();

 void check_init_program_stack();

public:

 PhaonIR(PHR_Channel_System* channel_system);

 ACCESSORS(PASTE_EXPRESSION(std::function<PHR_Channel_Group_Evaluator*(PhaonIR&,
   PHR_Channel_Group&)>) ,load_evaluator_fn)

 ACCESSORS__GET(PHR_Code_Model* ,code_model)
 ACCESSORS__GET(PHR_Channel_System* ,channel_system)
 ACCESSORS__GET(PHR_Type_System* ,type_system)
 ACCESSORS__GET(PHR_Channel_Group_Table* ,table)

 void create_channel_semantic_protocol(QString name);

 PHR_Channel_Group* get_select_channel_group()
 {
  return held_channel_group_;
 }

 void init_table();
 void init_program_stack();
 void reset_program_stack();
 void index_channel_group();
 void temp_anchor_channel_group();
 void anchor_channel_group(QString sym, QString ch);
 void copy_anchor_channel_group(QString sym, QString ch);

 PHR_Type* init_value_from_symbol(QString sym,
   PHR_Runtime_Scope::Storage_Options& so, quint64& val);

 void push_delete(void* pv);

 void delete_temps();
 void delete_retired();
 void clear_temps();

 void init_type_system();
 void init_type(QString type_name, quint8 byte_code);
 void init_code_model();

 qint32 get_s4_symbol_value(QString sym);

 void push_carrier_stack(QString sp_name);
 void push_carrier_raw_value(QString rv);
 void push_carrier_symbol(QString sn);

 PHR_Channel_Group_Evaluator* evaluate_channel_group_by_usi_symbol(QString usi_sym);

 void hold_type_by_name(QString ty_name);
 void coalesce_channel_group();
 void evaluate_channel_group(PHR_Symbol_Scope* pss);

 void enter_lexical_scope();

 void push_unwind_scope(int level_delta);
 void pop_unwind_scope();

 void push_carrier_expression();

 QString get_first_raw_value_string(QString sp_name, PHR_Channel_Group& pcg);
 PHR_Channel* get_channel_by_sp_name(QString sp_name, PHR_Channel_Group& pcg);
 void* get_first_raw_value(QString sp_name, PHR_Channel_Group& pcg);

};

#endif // PHAON_IR__H
