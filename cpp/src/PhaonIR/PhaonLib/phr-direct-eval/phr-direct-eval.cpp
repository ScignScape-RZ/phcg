
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-direct-eval.h"

#include "phr-command-runtime/phr-command-runtime-router.h"

#include "defines.h"

#include "phaon-ir/phaon-ir.h"

//#include "kauvir-code-model/kauvir-code-model.h"
//#include "kcm-lisp-bridge/kcm-lisp-bridge.h"
//#include "kcm-command-package/kcm-command-package.h"

//#include "kauvir-code-model/kcm-source-function.h"
//#include "kcm-scopes/kcm-scope-system.h"
//#include "kcm-scopes/kcm-runtime-scope.h"

//#include "kcm-command-runtime/kcm-command-runtime-router.h"


//#include "kcm-command-package/kcm-command-package.h"

//#include "kauvir-code-model/kcm-channel-bridge.h"

//#include "kph-generator/kph-generator.h"


//KCM_Channel_Bridge* make_kcm_channel_bridge(KCM_Command_Runtime_Router& kcrr)
//{
// return new KCM_Channel_Bridge(kcrr.get_channel_group());
//}


//KCM_Command_Package* make_kcm_command_package_from_channel_group(const KCM_Channel_Group& kcg)
//{
// return new KCM_Command_Package(kcg);
//}

//KCM_Command_Package* make_kcm_command_package(QPair<QSet<QString*>*, QMap<KCM_Channel::Kinds, QString*>*>& channel_names, const KCM_Type_Object* kto, QString val, QObject* qob)
//{
// return new KCM_Command_Package(channel_names, kto, val, qob);
//}


#include "phaon-ir/scopes/phr-scope-system.h"
#include "phaon-ir/runtime/phr-command-package.h"

#include "phaon-ir/phr-code-model.h"


void phr_direct_eval(PHR_Code_Model* pcm,
  PHR_Command_Package* pcp, PHR_Symbol_Scope* pss)
{

#ifdef USING_KPH_GEN
 if(kcm->kph_generator())
 {
  KPH_Generator& gen = *kcm->kph_generator();
  gen.encode(*cpkg);
  gen.save_kph_file();
  return;
 }
#endif // USING_KPH_GEN

 PHR_Scope_System* scope_system = pcm->scopes();
 if(pcp->bind_pto())
 {
#ifdef HIDE
  // not a real expression ...
  if( scope_system )
  {
   QString osn = cpkg->output_symbol_name();
   if(osn.isEmpty())
   {
    QString bv = cpkg->bind_val();
    if(bv.startsWith("&:"))
    {
     scope_system->current_scope()->add_declared_fn_type(bv.mid(2), cpkg->bind_kto());
    }
   }
   else
   {
    if(KCM_Channel_Group* kcg = cpkg->bind_kto()->channel_group())
    {
     KCM_Source_Function* kfn = new KCM_Source_Function(kcg);
     kfn->set_local_name(osn);
     kfn->set_full_name(cpkg->bind_val());
     scope_system->current_scope()->add_value(osn, cpkg->bind_kto(),
       (quint64) kfn);
    }
    else if(cpkg->bind_kto()->is_string_like())
    {
     QString* bvp = cpkg->bind_val_as_pointer();
     quint64 bv_result = (quint64) bvp;
     scope_system->current_scope()->add_value(osn, cpkg->bind_kto(),
       bv_result);
    }
    else if(cpkg->bind_qob())
    {
     quint64 bv_result = (quint64) cpkg->bind_qob();
     scope_system->current_scope()->add_value(osn, cpkg->bind_kto(),
       bv_result);
    }
    else
    {
     QString bv = cpkg->bind_val();
     quint64 bv_result = bv.toLongLong();
     scope_system->current_scope()->add_value(osn, cpkg->bind_kto(),
       bv_result);
    }
   }
  }
  return;
#endif
 }

 QString string_result;

 PHR_Command_Runtime_Router pcrr(pcm->table(),
   pcm->phaon_ir(), pss,
                                 scope_system,
   nullptr, //?pcm->current_proxy_scope(),
   string_result);
 //?pcrr.set_envv_fn(pcm->envv_fn());
 pcrr.parse_command_package(pcp);
 //
 QString sfn = pcm->phaon_ir()->find_source_fn(pcrr.fground_name());
 if(!sfn.isEmpty())
 {
  pcm->phaon_ir()->run_callable_value(sfn);
 }
// PHR_Source_Function* ksf = nullptr;
// if(scope_system)
// {
//  ksf = scope_system->find_source_function_from_current_scope(pcrr.fground_name());
// }
// if(ksf)
// {
//  PHR_Lisp_Bridge::bridge_run_source_function(bridge, pcrr, *ksf);
// }
 else
 {
  pcrr.proceed();
 }


 const PHR_Type_Object* pto = pcrr.result_type_object();
 if(pto)
 {

  if(pcrr.string_result_code())
  {
   quint64 eval_result = pcrr.string_result_code();
   QString* qs = (QString*) eval_result;
   pcp->set_string_result(*qs);
   pcp->set_eval_result((quint64) pcp->string_result_as_pointer());
   pcp->set_result_type_object(pto);
  }
  else
  {
   quint64 eval_result = pcrr.call_result();

   pcp->set_eval_result(eval_result);
   pcp->set_result_type_object(pto);
  }


 }


// if(scope_system)
// {
//  QString osn = pcp->output_symbol_name();
//  if(!osn.isEmpty())
//  {
////   if(pcrr.string_result_code())
////   {
////    const PHR_Type_Object* rkto = kcrr.result_type_object();
////    scope_system->current_scope()->add_string_value(osn, rkto, string_result);
////   }
//  }
// }
#ifdef HIDE
 if(scope_system)
 {
  QString osn = cpkg->output_symbol_name();
  if(!osn.isEmpty())
  {
   if(kcrr.string_result_code())
   {
    const PHR_Type_Object* rkto = kcrr.result_type_object();
    scope_system->current_scope()->add_string_value(osn, rkto, string_result);
   }
   else
   {
    quint64 eval_result = kcrr.call_result();
    const PHR_Type_Object* rkto = kcrr.result_type_object();
    scope_system->current_scope()->add_value(osn, rkto, eval_result);
   }
  }
 }
#endif
}
#ifdef HIDE
 KCM_Command_Runtime_Router kcrr(kcm->table(), scope_system, kcm->current_proxy_scope(), string_result);
 kcrr.set_envv_fn(kcm->envv_fn());
 kcrr.parse_command_package(cpkg);
 KCM_Source_Function* ksf = nullptr;
 if(scope_system)
 {
  ksf = scope_system->find_source_function_from_current_scope(kcrr.fground_name());
 }
 if(ksf)
 {
  KCM_Lisp_Bridge::bridge_run_source_function(bridge, kcrr, *ksf);
 }
 else
 {
  kcrr.proceed();
 }
 if(scope_system)
 {
  QString osn = cpkg->output_symbol_name();
  if(!osn.isEmpty())
  {
   if(kcrr.string_result_code())
   {
    const KCM_Type_Object* rkto = kcrr.result_type_object();
    scope_system->current_scope()->add_string_value(osn, rkto, string_result);
   }
   else
   {
    quint64 eval_result = kcrr.call_result();
    const KCM_Type_Object* rkto = kcrr.result_type_object();
    scope_system->current_scope()->add_value(osn, rkto, eval_result);
   }
  }
 }
#endif // HIDE
