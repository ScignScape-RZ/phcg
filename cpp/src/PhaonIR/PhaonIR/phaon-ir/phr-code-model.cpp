
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-code-model.h"

#include "types/phr-type.h"
#include "types/phr-type-object.h"

#include "types/phr-type-system.h"
#include "channel/phr-channel-semantic-protocol.h"
#include "channel/phr-channel-group.h"
#include "channel/phr-carrier.h"

#include <QMetaType>


PHR_Code_Model::PHR_Code_Model()
  :  type_system_(nullptr), scopes_(nullptr),
     //?current_symbol_scope_(nullptr),
     table_(nullptr)
{
 lisp_report_synax_.flags.compress_fground_channel = true;
 lisp_report_synax_.flags.merge_fground_and_lambda = true;
 lisp_report_synax_.flags.expand_array_indicators = true;

 detailed_report_synax_.flags.identify_channel_names = true;
 detailed_report_synax_.flags.identify_types = true;
 detailed_report_synax_.flags.surround_type_expressions = true;
 detailed_report_synax_.flags.write_empty_lambda_channel = true;
}

PHR_Type_Object* PHR_Code_Model::create_and_register_type_object(QString name)
{
 if(name.endsWith('*'))
 {
  return create_and_register_type_object(name, DEFAULT_PTR_BYTE_CODE);
 }
 else
 {
  return create_and_register_type_object(name, 8);
 }
}

PHR_Type_Object* PHR_Code_Model::create_and_register_type_object(QString name, int bc)
{
 PHR_Type* pt = type_system_->check_add_type_by_name(name, bc);
 PHR_Type_Object* pto = new PHR_Type_Object(pt);
// KCM_Type_Object* result = new KCM_Type_Object(kto);

 if(name.endsWith('*'))
 {
  int pid = QMetaType::type(name.toLatin1());
  if(pid != QMetaType::UnknownType)
  {
   const QMetaObject* pqmo = QMetaType::metaObjectForType(pid);
   if(pqmo)
   {
    pt->set_pqmo(pqmo);
   }
  }
  name.chop(1);
  int id = QMetaType::type(name.toLatin1());
  if(id != QMetaType::UnknownType)
  {
   pt->set_qmetatype_ptr_code(id);
   const QMetaObject* qmo = QMetaType::metaObjectForType(id);
   if(qmo)
   {
    pt->set_qmo(qmo);
   }
  }
 }
 else
 {
  int id = QMetaType::type(name.toLatin1());
  if(id != QMetaType::UnknownType)
  {
   pt->set_qmetatype_ptr_code(id);
   const QMetaObject* qmo = QMetaType::metaObjectForType(id);
   if(qmo)
   {
    pt->set_qmo(qmo);
   }
  }
  int pid = QMetaType::type( (name + "*").toLatin1() );
  if(pid != QMetaType::UnknownType)
  {
   const QMetaObject* pqmo = QMetaType::metaObjectForType(pid);
   if(pqmo)
   {
    pt->set_pqmo(pqmo);
    pt->set_qmetatype_ptr_code(pid);
    // // kto->check_register_variant_and_metatype_info(QVariant::UserType, pid);
   }
  }
 }
 return pto;
}

void PHR_Code_Model::direct_eval(PHR_Command_Package* pcp, PHR_Symbol_Scope* current_symbol_scope)
{
 if(direct_eval_fn_)
 {
  //?current_symbol_scope_ = current_symbol_scope;
  direct_eval_fn_(this, pcp, current_symbol_scope);
 }
}

void PHR_Code_Model::init_scope_system()
{
 //scope_system_->join_lexical_scope(current_lexical_scope_);
}


void PHR_Code_Model::report_channel_group(QTextStream& qts, PHR_Channel_Group& pcg,
  PCM_Report_Syntax& pcrs, Code_Environments cenv)
{
 QMapIterator<PHR_Channel_Semantic_Protocol*, PHR_Channel*> it(pcg);
 while(it.hasNext())
 {
  it.next();
  QString chn = it.key()->name();
  report_channel(qts, parse_channel_kind(chn), chn, it.value(), pcrs, cenv);
 }
// report({KCM_Channel::Kinds::FGround, KCM_Channel::Kinds::Lambda,
//   KCM_Channel::Kinds::Sigma, KCM_Channel::Kinds::Result}, qts, kcm, kcrs, cenv);
}

PHR_Code_Model::Recognized_Channel_Kinds PHR_Code_Model::parse_channel_kind(QString name)
{
 static QMap<QString, Recognized_Channel_Kinds> static_map {{
   {"fground", Recognized_Channel_Kinds::FGround},
   {"lambda", Recognized_Channel_Kinds::Lambda},
   {"sigma", Recognized_Channel_Kinds::Sigma},
   {"array", Recognized_Channel_Kinds::Array},
   {"capture", Recognized_Channel_Kinds::Capture},
   {"gamma", Recognized_Channel_Kinds::Gamma},
   {"result", Recognized_Channel_Kinds::Result},
   {"error", Recognized_Channel_Kinds::Error},
   {"preempt-any", Recognized_Channel_Kinds::Preempt_Any},
   {"preempt-return", Recognized_Channel_Kinds::Preempt_Return},
   {"preempt-continue", Recognized_Channel_Kinds::Preempt_Continue},
   {"preempt-break", Recognized_Channel_Kinds::Preempt_Break},
   {"ctor-mem", Recognized_Channel_Kinds::CTOR_Mem},
   {"ctor-ret", Recognized_Channel_Kinds::CTOR_Ret}
   }};

 return static_map.value(name, Recognized_Channel_Kinds::N_A);
}

void PHR_Code_Model::report_type_object(QTextStream& qts,
  PHR_Type_Object* pto, PCM_Report_Syntax& pcrs)
{
 QString pto_type_rep;
 if(pto->ty())
 {
  pto_type_rep = pto->ty()->name(); //?pcm.string_rep(pto->ty());
 }
//?
// if(kcrs.flags.use_thorin_array_types)
// {
//  if(array_length_ == -1)
//  {
//   kto_type_rep.prepend('[');
//   kto_type_rep.append(']');
//  }
//  else if(array_length_ > 0)
//  {
//   kto_type_rep = QString("[%1 * %2]").arg(kto_type_rep).arg(array_length_);
//  }
// }
// switch()
// {
// case Modifiers::Pointer:
//  kto_type_rep.prepend('&');
//  break;
// default:
//  break;
// }
 if(pcrs.flags.surround_type_expressions)
 {
  qts << pto_type_rep;
 }
 else
 {
  qts << pto_type_rep;
 }
}

void PHR_Code_Model::report_carrier(QTextStream& qts, PHR_Carrier* phc, PCM_Report_Syntax& pcrs)
{
 if(phc->symbol_name().startsWith("\\."))
 {
//?
//  kcm.report_expression_from_code(qts, phc->symbol_name(), kcrs);
//  if(kcrs.flags.cast_after_expression)
//  {
//   if(cast_type_object_)
//   {
//    qts << " as " << kcm.get_ouput_type_name(kcrs, cast_type_object_);
//   }
//  }
 }
 else
 {
  if(pcrs.flags.surround_carriers)
  {
   qts << "(" << phc->symbol_name() << ")";
  }
  else
  {
   qts << phc->symbol_name();
  }
  if(pcrs.flags.identify_types)
  {
   if(phc->type_object())
   {
    report_type_object(qts, phc->type_object(), pcrs);
   }
  }
  if(pcrs.flags.cast_after_expression)
  {
//?
//   if(cast_type_object_)
//   {
//    qts << " as " << kcm.get_ouput_type_name(kcrs, cast_type_object_);
//   }
  }
 }
}

void PHR_Code_Model::report_channel(QTextStream& qts, Recognized_Channel_Kinds rck,
   QString chn, PHR_Channel* ch, PCM_Report_Syntax& pcrs, Code_Environments cenv)
{
 if( (cenv == Code_Environments::Statement) &&
  pcrs.flags.arrow_before_result_channel && rck == Recognized_Channel_Kinds::Result)
 {
  qts << " -> ";
 }
 if(ch->isEmpty())
 {
  QString pre;
  QString post;
  if(pcrs.flags.identify_channel_names)
  {
   pre = QString("[%1").arg(chn); //kind_to_string(kcrs));
   post = " ]";
  }

  if(pcrs.flags.write_empty_lambda_channel && rck == Recognized_Channel_Kinds::Lambda)
  {
   qts << pre << " <<void>>" << post;
  }
  else if( (cenv == Code_Environments::Statement) &&
   pcrs.flags.write_empty_result_channel && rck == Recognized_Channel_Kinds::Result)
  {
   qts << pre << " <<void>>" << post;
  }
  return;
 }

 if(pcrs.flags.merge_fground_and_lambda && rck == Recognized_Channel_Kinds::Lambda)
 {

 }
 else if(rck == Recognized_Channel_Kinds::FGround && cenv == Code_Environments::Expression)
 {
  if(pcrs.flags.merge_fground_and_lambda)
  {
   qts << '(';
  }
 }
 else if(rck == Recognized_Channel_Kinds::Array)
 {
  if(pcrs.flags.expand_array_indicators)
  {
   qts << "(arr ";
  }
  else
  {
   qts << '[';
  }
 }
 else
 {
  qts << '(';
 }

 if(pcrs.flags.identify_channel_names)
 {
  qts << '[' << chn << "] ";
 }

 int count = 0;
 int max = ch->size();
 for(PHR_Carrier* phc : *ch)
 {
  ++count;
  report_carrier(qts, phc, pcrs);
  if(count < max)
  {
   if(pcrs.flags.comma_separate_channel_carriers)
   {
    qts << ", ";
   }
   else
   {
    qts << ' ';
   }
  }
 }

 if(pcrs.flags.merge_fground_and_lambda && rck == Recognized_Channel_Kinds::FGround)
 {
  qts << ' ';
 }
 else if(rck == Recognized_Channel_Kinds::FGround && cenv == Code_Environments::Expression)
 {

 }
 else if(rck == Recognized_Channel_Kinds::Array)
 {
  if(pcrs.flags.expand_array_indicators)
  {
   qts << ')';
  }
  else
  {
   qts << ']';
  }
 }
 else
 {
  qts << ')';
 }

}


