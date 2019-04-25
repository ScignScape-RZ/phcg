
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CODE_MODEL__H
#define PHR_CODE_MODEL__H

#include <QString>

#include "pcm-report-syntax.h"

#include "accessors.h"

class PHR_Type_System;
class PHR_Scope_System;
class PHR_Command_Package;

class PHR_Symbol_Scope;

class PHR_Channel_Group_Table;
class PHR_Channel_Group;
class PHR_Channel;
class PHR_Carrier;

class PhaonIR;
class PHR_Type_Object;

class PHR_Code_Model
{
 PHR_Type_System* type_system_;
 PHR_Scope_System* scopes_;
 PHR_Channel_Group_Table* table_;

 PCM_Report_Syntax lisp_report_synax_;
 PCM_Report_Syntax detailed_report_synax_;

 typedef std::function<void(PHR_Code_Model* pcm,
   PHR_Command_Package* pcp, PHR_Symbol_Scope* pss)> direct_eval_fn_type;

 direct_eval_fn_type direct_eval_fn_;

 PhaonIR* phaon_ir_;


public:

 enum class Code_Environments {
  N_A, Fuxe, Expression, Statement, File, Macro, Class
 };

 enum class Recognized_Channel_Kinds {
  N_A, Fuxe, Lambda, Sigma, Array, Capture, Gamma, Result, Error,
  Preempt_Any, Preempt_Return, Preempt_Continue, Preempt_Break,
  CTOR_Mem, CTOR_Ret
 };

 Recognized_Channel_Kinds parse_channel_kind(QString name);


 PHR_Code_Model();

 ACCESSORS(PHR_Type_System* ,type_system)
 ACCESSORS(PHR_Scope_System* ,scopes)
 ACCESSORS(PHR_Channel_Group_Table* ,table)

 ACCESSORS__RGET(PCM_Report_Syntax ,lisp_report_synax)
 ACCESSORS__RGET(PCM_Report_Syntax ,detailed_report_synax)

 ACCESSORS(PhaonIR* ,phaon_ir)

//? ACCESSORS(PHR_Symbol_Scope* ,current_symbol_scope)

 ACCESSORS(direct_eval_fn_type ,direct_eval_fn)

 PHR_Type_Object* create_and_register_type_object(QString name);
 PHR_Type_Object* create_and_register_type_object(QString name, int bc);

 void init_scope_system();

 void direct_eval(PHR_Command_Package* pcp, PHR_Symbol_Scope* current_symbol_scope);

 void report_carrier(QTextStream& qts, PHR_Carrier* phc, PCM_Report_Syntax& pcrs);
 void report_channel_group(QTextStream& qts, PHR_Channel_Group& pcg,
   PCM_Report_Syntax& pcrs, Code_Environments cenv);

 void report_channel(QTextStream& qts, Recognized_Channel_Kinds rck,
   QString chn, PHR_Channel* ch, PCM_Report_Syntax& pcrs, Code_Environments cenv);
 void report_type_object(QTextStream& qts,
   PHR_Type_Object* pto, PCM_Report_Syntax& pcrs);

};

#endif // PHR_CODE_MODEL__H
