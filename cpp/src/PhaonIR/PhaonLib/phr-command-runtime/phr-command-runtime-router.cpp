
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-command-runtime-router.h"

#include "phr-command-runtime-router-qob.h"

#include "phaon-ir/channel/phr-carrier.h"
#include "phaon-ir/types/phr-type-object.h"
#include "phaon-ir/types/phr-type.h"

#include "phaon-ir/phaon-ir.h"

#include "phaon-ir/scopes/phr-runtime-scope.h"

#include "phaon-ir/scopes/phr-scope-system.h"

#include "phr-command-runtime-argument.h"

#include "phaon-ir/runtime/phr-command-package.h"

//#include "phr-command-runtime-table.h"

#include "phaon-ir/table/phr-channel-group-table.h"

//#include "PHR-command-runtime-router-qob.h"

//#include "PHR-command-package/PHR-command-package.h"
//#include "PHR-command-runtime-argument.h"

//#include "kauvir-type-system/kauvir-universal-class.h"

//#include "PHR-command-runtime-table.h"
//#include "kauvir-code-model/PHR-type-object.h"

//#include "PHR-scopes/PHR-scope-system.h"

//#include "kauvir-code-model/PHR-callable-value.h"

//#include "kauvir-code-model/PHR-proxy-scope.h"

//#include "kauvir-code-model/PHR-expression.h"

//#include "kauvir-code-model/PHR-channel-bridge.h"

//#include "PHR-lisp-bridge/PHR-lisp-bridge.h"
//#include "PHR-lisp-bridge/PHR-lisp-eval.h"

//#include "PhaonLib/phaon-function-vector.h"

//#include "kauvir-code-model/PHR-function-package.h"



#include <QDebug>

//USING_KANS(KCL)


//USING_KANS(CMD)


PHR_Command_Runtime_Router::PHR_Command_Runtime_Router(PHR_Channel_Group_Table* table,
  PhaonIR* phaon_ir, PHR_Symbol_Scope* symbol_scope,
  PHR_Scope_System* scopes, PHR_Proxy_Scope* proxy_scope,
  QString& string_result)
  :  sigma_argument_(nullptr), phr_expression_(nullptr),
     result_type_object_(nullptr), string_result_(string_result),
     table_(table), scopes_(scopes), proxy_scope_(proxy_scope),
     phaon_ir_(phaon_ir), symbol_scope_(symbol_scope),
     call_result_(0),
     reflection_convention_(Reflection_Conventions::N_A),
     string_result_code_(0), envv_fn_(nullptr)
{

}

QString PHR_Command_Runtime_Router::return_type_name_strip_namespace()
{
 int li = return_type_name().lastIndexOf("::");
 if(li != -1)
 {
  return return_type_name().mid(li + 2);
 }
 else
 {
  return return_type_name();
 }
}

QObject* PHR_Command_Runtime_Router::this_object()
{
 return static_cast<QObject*>(argument_info_[0].void_argument);
}

PHR_Command_Runtime_Argument* PHR_Command_Runtime_Router::parse_carrier_to_argument(PHR_Carrier& phc, int pos)
{
 PHR_Command_Runtime_Argument* result;
 QString sym = phc.symbol_name();
 const PHR_Type_Object* pto = phc.type_object();
 if(pto)
 {
  result = new PHR_Command_Runtime_Argument;

  if(pto->ty()->name() == "pcv")
  {
   result->set_raw_value(phc.raw_value());
   result->set_value_classification(
     PHR_Command_Runtime_Argument::Value_Classification::PCV_Ptr);
   return result;
  }

//  const Kauvir_Type_Object* kvto =  pto->kauvir_type_object();
//  result->set_type_name(kvto->name());

//  result->set_qmo(kvto->qmo());
//  result->set_pqmo(kvto->pqmo());

  void* k = phc.symbol_as_pointer();
  QString* qs = reinterpret_cast<QString*>(k);

//  if(phc.flags.literal_string)
//  {
//   result->set_raw_value(phc.symbol_as_pointer());
//   result->set_value_classification(PHR_Command_Runtime_Argument::Value_Classification::Generic_Ptr);
//  }
//  else if(phc.flags.value_string)
//  {
//   result->set_raw_value(phc.symbol_as_pointer());
//   result->set_value_classification(PHR_Command_Runtime_Argument::Value_Classification::Generic_Ptr);
//  }

  QString rvs = phc.raw_value_string();

  if(rvs.isEmpty())
  {
   result->set_bind_code(sym);
   result->set_raw_value(phc.symbol_as_pointer());
   result->set_value_classification(PHR_Command_Runtime_Argument::Value_Classification::Generic_Ptr);
  }
  else
  {
   result->set_raw_value(phc.raw_value_string_as_pointer());
   result->set_value_classification(PHR_Command_Runtime_Argument::Value_Classification::Raw_Value_String_Ptr);
  }
 }
// else if(phc.flags.literal_string)
// {
//  result = new PHR_Command_Runtime_Argument;
//  result->set_type_name("QString");

//  void* k = phc.symbol_as_pointer();
//  QString* qs = reinterpret_cast<QString*>(k);

//  result->set_raw_value(phc.symbol_as_pointer());
//  result->set_value_classification(PHR_Command_Runtime_Argument::Value_Classification::Generic_Ptr);
// }
// else if(phc.declaration_scope())
// {
//  // //  currently declaration_scope is only used
//   //    as a signal that phc is scoped ...
//  result = new PHR_Command_Runtime_Argument;
//  const PHR_Type_Object* rpto;

//  quint64 qv =  PHR_Lisp_Bridge::get_value_of_symbol(phc.symbol(), scopes_, &rpto);

//  if(rpto)
//  {
//   result->set_type_name(rpto->kauvir_type_object()->name());
//  }

//  result->set_raw_value( (void*) qv);
//  result->set_value_classification(PHR_Command_Runtime_Argument::Value_Classification::QObject_Ptr);
// }
 else
 {
  result = new PHR_Command_Runtime_Argument;
  QString qs = phc.symbol_name();
  result->set_bind_code(qs);
 }
 return result;
}

QString PHR_Command_Runtime_Router::return_type_name()
{
 if(result_type_object_)
  return result_type_object_->ty()->name();//kauvir_type_object()->name();
 return QString();
}


void PHR_Command_Runtime_Router::parse_command_package(PHR_Command_Package* cpkg)
{
 //?phr_expression_ = cpkg->phr_expression();

//? cpkg_output_symbol_name_ = cpkg->output_symbol_name();

 PHR_Channel* sigma = cpkg->sigma_ch();
 if(sigma  && !sigma->isEmpty())
 {
  PHR_Carrier* s1 = sigma->first();
  PHR_Command_Runtime_Argument* s1a = new PHR_Command_Runtime_Argument;
//?
//  if(s1->flags.literal_string)
//  {
//   s1a->set_raw_value(s1.symbol_as_pointer());
//   s1a->set_value_classification(PHR_Command_Runtime_Argument::Value_Classification::Generic_Ptr);
//  }
//  else
//  {
   s1a->set_bind_code(s1->symbol_name());
//  }
  sigma_argument_ = s1a;
 }

 PHR_Channel* fuxe = cpkg->fuxe_ch();
 if(fuxe->isEmpty())
 {
  // no function name!
  return;
 }
 PHR_Channel* result = cpkg->result_ch();
 if(result)
 {
  if(!result->isEmpty())
  {
   PHR_Carrier* r1 = result->first();
   result_type_object_ = r1->type_object();
  }
 }
 PHR_Carrier* phc = fuxe->first();
 fuxe_name_ = phc->symbol_name();

 PHR_Channel* lambda = cpkg->lambda_ch();

 if(lambda)
 {
  int size = lambda->size();
  for(int i = 0; i < size; ++i)
  {
   PHR_Carrier* phc = lambda->at(i);
   PHR_Command_Runtime_Argument* la = parse_carrier_to_argument(*phc, i);
   lambda_arguments_.push_back(la);
  }
 }
}

PHR_Function_Vector* PHR_Command_Runtime_Router::get_phr_function_vector(QString fn)
{
 //?
// for(PHR_Symbol_Scope* pss : scopes_->phaon_scope_queue())
// {
//  auto it = pss->find(fn);
//  if(it != pss->end())
//    return &it.value();
// }
 if(table_)
 {
  PHR_Runtime_Scope* prs = table_->get_runtime_scope(*symbol_scope_);
  //?return prs->get_phr_function_vector(fn);

  if(fn.startsWith('&'))
    fn = fn.mid(1);

  return prs->get_function_vector_value_as<PHR_Function_Vector>(fn);

//  auto it = table_->find(fn);
//  if(it != table_->end())
//    return &it.value();
 }
 return nullptr;
}

void PHR_Command_Runtime_Router::proceed()
{
 PHR_Function_Vector* pfv = get_phr_function_vector(fuxe_name_);

 if(sigma_argument_)
 {
  proceed_s1(pfv);
 }
 else
 {
  proceed_s0(pfv);
 }
}

PHR_Channel_Group* PHR_Command_Runtime_Router::get_channel_group()
{
 if(phr_expression_)
 {
 //? return phr_expression_->channel_group();
 }
}


void PHR_Command_Runtime_Router::proceed_s0(PHR_Function_Vector* pfv)
{
 void* result;

 s0_fn1_p_type fn = nullptr;

 int mc = 0;
 int bc = 0;
 bool sr = false;

 if(pfv)
 {
  fn = (s0_fn1_p_type) pfv->find_argvec_function(mc, bc);
  sr = ((mc / 1000) == 6);
 }
 else
 {
  // tbd ...
 }

 if(fn)
 {
  int default_argvec_bytecode = 99;
  proceed_s0_argvec(fn, &result, default_argvec_bytecode, sr);
  goto set_result;
 }

 switch(lambda_arguments_.size())
 {
 case 0:
  proceed_s0_0(pfv, &result);
  break;
 case 1:
  proceed_s0_1(pfv, &result);
  break;
 case 2:
  proceed_s0_2(pfv, &result);
  break;
 default:
  break;
 }
set_result:
 if(result)
 {
  call_result_ = (quint64) result;
 }
}

void PHR_Command_Runtime_Router::proceed_s1(PHR_Function_Vector* pfv)
{
 void* result = nullptr;

 s0_fn1_p_p_type fn = nullptr;

 int mc = 0;
 int bc = 0;

 if(pfv)
 {
  fn = (s0_fn1_p_p_type) pfv->find_argvec_function(mc, bc);
 }
 else
 {
  // tbd ...
 }

 if(fn)
 {
  proceed_s0_argvec((s0_fn1_p_type) fn, &result,
    bc, 1);
  goto set_result;
 }

 {
  QString code = sigma_argument_->bind_code();
  const PHR_Type_Object* pto = nullptr;
  const PHR_Type_Object* cpto = nullptr;
  QString encoded_value;

  QPair<int, quint64> qclo_value = {0, 0};
  void* raw_value;//? = scopes_->find_raw_value_from_current_scope(code, envv_fn_, phr_expression_,
    //?pto, cpto, encoded_value, qclo_value);

  switch(lambda_arguments_.size())
  {
  case 0:
   proceed_s1_0(pfv, &result, raw_value);
   break;
  case 1:
   proceed_s1_1(pfv, &result, raw_value);
   break;
  case 2:
   proceed_s1_2(pfv, &result, raw_value);
   break;
  default:
   break;
  }
 }

set_result:
 if(result)
 {
  call_result_ = (quint64) result;
 }
}

void PHR_Command_Runtime_Router::proceed_s1_2(PHR_Function_Vector* pfv, void** pResult, void* raw_value)
{
 void* result = nullptr;

 int byte_code;
 s0_fn1_p_p_type fn0 = nullptr;
 bool sr;

 int mc = 0;
 int bc = 0;

 if(pfv)
 {
  if(void* fnp = pfv->match_against_codes({6103, 7103}, mc, bc, &result_type_object_))
  {
   fn0 = (s0_fn1_p_p_type) fnp;
   byte_code = bc;
   sr = mc == 6103;
  }
  else byte_code = 0;
 }
 else
 {

 }
 if(fn0)
 {
  if(pResult)
  {
   *pResult = result;
  }
  return;
 }

 //PHR_Runtime_Scope* prs = table_->get_runtime_scope(*symbol_scope_);

 s1_fng_type fn = table_->find_s1_declared_function_0(fuxe_name_, nullptr, &result_type_object_);
 if(fn)
 {
  // //  raw_value is quint64* standing for void** ...
  PHR_Universal_Class* uo = (PHR_Universal_Class*) (* (void**)raw_value) ;
  void* la0 = nullptr;
  quint64 mem = 0;
  QPair<PHR_Scope_System*, QPair<int, quint64>> qclo_value = {scopes_, {0, 0}};
  QString qs_mem;
  QString* pqs_mem = &qs_mem;

  void* la1 = nullptr;
  quint64 mem1 = 0;
  QString qs_mem1;
  QString* pqs_mem1 = &qs_mem1;
  QPair<PHR_Scope_System*, QPair<int, quint64>> qclo_value1 = {scopes_, {0, 0}};

  FN_Codes fnc = result_type_object_? FN_Codes::RET_CC:FN_Codes::NOR_CC;

  int ptr_depth1;
  int ptr_depth2;
  FN_Codes fnc1 = check_init_raw_value(lambda_arguments_[0], fnc, mem,
    qclo_value, pqs_mem, la0, ptr_depth1);
  FN_Codes fnc2 = check_init_raw_value(lambda_arguments_[1], fnc1, mem1,
    qclo_value1, pqs_mem1, la1, ptr_depth2);

  if(result_type_object_)
  {
   fn2_pp_wrtn_type pfn = (fn2_pp_wrtn_type) fn;
   result = (uo->*pfn)( (void*) *((quint64*) la0),  (void*) *((quint64*) la1));
  }
  else
  {
   fn2_pp_type pfn = (fn2_pp_type) fn;
   (uo->*pfn)( (void*) *((quint64*) la0),  (void*) *((quint64*) la1));
  }

  if(pResult)
  {
   *pResult = result;
  }
 }
 else
 {
  reflection_convention_ = Reflection_Conventions::Qt_Meta_Object;
  do_invoke_method(lambda_arguments_);
 }
}

//void PHR_Command_Runtime_Router::run_callable_value(PHR_Callable_Value* kcv)
//{
// PHR_Lisp_Eval::run_source_function(*this, (quint64) kcv->as_pVoid() );
//}

QString PHR_Command_Runtime_Router::output_type_string()
{
 if(cpkg_output_symbol_name_.isEmpty())
 {
  return QString();
 }
 //?
// if(const PHR_Type_Object* pto = scopes_->get_type_object_from_symbol_name(cpkg_output_symbol_name_))
// {
//  return pto->get_name_string();
// }
 return QString();
}

PHR_Command_Runtime_Router::FN_Codes PHR_Command_Runtime_Router::check_init_raw_value(PHR_Command_Runtime_Argument* kcra,
  FN_Codes fnc, quint64& mem, QPair<PHR_Scope_System*, QPair<int, quint64>>& qclo_value,
  QString* const& qs_mem, void*& result, int& ptr_depth)
{
 const PHR_Type_Object* pto;
 if(kcra->bind_code().isEmpty())
 {
  QString* qs = (QString*) kcra->raw_value();

  int* pi = (int*) kcra->raw_value();

  QString tn = kcra->type_name();
  if(tn.isEmpty())
  {
   if(kcra->value_classification() == PHR_Command_Runtime_Argument::Value_Classification::Raw_Value_String_Ptr)
   {
    tn = "str";
    if(qs->startsWith('"'))
      *qs = qs->mid(1);
    if(qs->endsWith('"'))
      qs->chop(1);
   }
  }

  if(tn == "str")
  {

   // //  account for how scopes store strings ...
   if(kcra->value_classification() ==
     PHR_Command_Runtime_Argument::Value_Classification::QObject_Ptr)
   {
    qs = (QString*) *(quint64*) qs;
   }

   *qs_mem = *qs;
   result = const_cast<void*>( (const void*) &qs_mem);

   ptr_depth = 2;
   return add_string_cast_to_fn_code(fnc);
  }
  else
  {
   if(kcra->value_classification() == PHR_Command_Runtime_Argument::Value_Classification::Raw_Value_String_Ptr)
   {
    int i = qs->toInt();
    mem = qs->toLongLong();
   }

   // //  are these value classifications misleading?
   if(kcra->value_classification() == PHR_Command_Runtime_Argument::Value_Classification::Generic_Ptr)
   {
    mem = qs->toLongLong();
   }
   else if(kcra->value_classification() == PHR_Command_Runtime_Argument::Value_Classification::QObject_Ptr)
   {
    mem = *(quint64*) kcra->raw_value();
   }
   else if(kcra->value_classification() == PHR_Command_Runtime_Argument::Value_Classification::PCV_Ptr)
   {
    mem = *(quint64*) kcra->raw_value();
   }

   result = &mem;
   ptr_depth = 1;
   return add_ptr_cast_to_fn_code(fnc);
  }
 }
 else if(kcra->bind_code() == "_$")
 {
  QString rs = output_type_string();
  if(rs.isEmpty() && !result_type_object_)
  {
   mem = (quint64) 0;
   result = &mem;
  }
  else
  {
   *qs_mem = rs;
   mem = (quint64) qs_mem;
   result = &mem;
  }
 }
#ifdef HIDE
 else if(quint64 temp = scopes_->find_temporary_bridge_value(kcra->bind_code(), pto))
 {
  // // actually need to check of pto is anon fdef ...
  PHR_Callable_Value* kcv = (PHR_Callable_Value*) temp;
  kcv->set_kcrr(this);
  mem = (quint64) kcv;
  result = &mem;
 }
#endif
 else
 {
  const PHR_Type_Object* pto;
  const PHR_Type_Object* cpto;
  QString encoded_value;

  const PHR_Type_Object* xpto;
  QString proxy_coords_code;// = proxy_scope_->find_proxy_coords_for_symbol_name(kcra->bind_code(), xpto);

  if(proxy_coords_code.isEmpty())
  {
   quint64* rv;//? = scopes_->find_raw_value_from_current_scope(kcra->bind_code(), envv_fn_, PHR_expression_,
     //pto, cpto, encoded_value, qclo_value.second);

   quint64 prv;
   PHR_Runtime_Scope::Storage_Options so;

   PHR_Type* ty = phaon_ir_->init_value_from_symbol(kcra->bind_code(), so, prv);

   if(so != PHR_Runtime_Scope::Storage_Options::N_A)
   {
    if(ty)
    {
     if(so == PHR_Runtime_Scope::Storage_Options::Direct)
     {
      mem = prv;
      result = &mem;
     }
     //...
    }
    else
    {
     mem = prv;
     result = &mem;
    }
   }
   else
   if(rv == (quint64*) &encoded_value)
   {
    if(!pto)
    {
     // // means nested_expression_store could not find the pair ...
    }

#ifdef HIDE
    else if(pto->is_lisp_list_like())
    {
     QString key = encoded_value; //? ".1.";
     quint64 lisp_val = scopes_->find_held_lisp_list_from_current_scope(key);
     PHR_Lisp_Eval::run_held_lisp_list(lisp_val, mem);
     result = &mem;
     //mem = lisp_val;
    }
#endif

    // need to parse the encoded ...
    else if(pto->is_string_like())
    {
     // // is this OK given the QString** stuff?
     *qs_mem = encoded_value;
     result = qs_mem;
    }

//    else if(pto->is_callable_lisp_deferred_value_like())
//    {
//     mem = (quint64) &qclo_value;
//     result = (void*) &mem;
//    }

    else
    {
     // // probably have to deal with multiple types ...
     mem = encoded_value.toInt();
     result = &mem;
    }
   }
   else if(rv)
   {
    // what about str? ...
    mem = *rv;

    if(mem == 0)
    {
     QString exc = QString("Unrecognized Symbol: %1 -- Exception Will Be Thrown").arg(kcra->bind_code());
     qDebug() << "\n\n" << exc << "\n";
     throw exc;
    }

    result = &mem;
   }
   else
   {
    result = nullptr;
   }
   return add_ptr_cast_to_fn_code(fnc);
  }
  else
  {
   //?PHR_Channel_Bridge* bridge = proxy_scope_->PHR_channel_bridge();
   PHR_Carrier* pcr;// = bridge->get_carrier_by_proxy_coords_code(proxy_coords_code);

   const PHR_Type_Object* pto = pcr->type_object();

   // // any issue of checking between pto and xpto?
    //   ... xpto;

   if(pto->is_string_like())
   {
    //    Again the QString** stuff: this only gets to QString* ...
    //    QString encoded_value = kcr->symbol();
    //    qs_mem = encoded_value;
    //    result = &qs_mem;

    QString* pqs = pcr->symbol_as_pointer();
    mem = (quint64) pqs;
    result = &mem;
   }
   else
   {
    // // now this only works for ints ...
    QString encoded_value = pcr->symbol_name();
    mem = encoded_value.toInt();
    result = &mem;
   }
  }
 }
 return FN_Codes::N_A;
}

PHR_Command_Runtime_Router::FN_Codes PHR_Command_Runtime_Router::add_string_cast_to_fn_code(FN_Codes fnc)
{
 static QMap<FN_Codes,FN_Codes> static_map {{
#define TEMP_MACRO(X, Y) {FN_Codes::NOR_##X, FN_Codes::NOR_##Y}, {FN_Codes::RET_##X, FN_Codes::RET_##Y},
   TEMP_MACRO(C,S)
   TEMP_MACRO(CC,SC)
   TEMP_MACRO(PC,PS)
   TEMP_MACRO(RC,RS)
   TEMP_MACRO(SC,SS)
#undef TEMP_MACRO
   }};
 return static_map.value(fnc, FN_Codes::N_A);
}

PHR_Command_Runtime_Router::FN_Codes PHR_Command_Runtime_Router::add_ptr_cast_to_fn_code(FN_Codes fnc)
{
 static QMap<FN_Codes,FN_Codes> static_map {{
#define TEMP_MACRO(X, Y) {FN_Codes::NOR_##X, FN_Codes::NOR_##Y}, {FN_Codes::RET_##X, FN_Codes::RET_##Y},
   TEMP_MACRO(C,P)
   TEMP_MACRO(CC,SP)
   TEMP_MACRO(PC,PP)
   TEMP_MACRO(RC,RP)
   TEMP_MACRO(SC,SP)
#undef TEMP_MACRO
   }};
 return static_map.value(fnc, FN_Codes::N_A);
}


void PHR_Command_Runtime_Router::proceed_s1_1(PHR_Function_Vector* pfv, void** pResult, void* raw_value)
{
 void* result = nullptr;

 int byte_code;
 s0_fn1_p_p_type fn0 = nullptr;
 bool sr;

 int mc = 0;
 int bc = 0;

 if(pfv)
 {
  if(void* fnp = pfv->match_against_codes({6102, 7102}, mc, bc, &result_type_object_))
  {
   fn0 = (s0_fn1_p_p_type) fnp;
   byte_code = bc;
   sr = mc == 6102;
  }
  else byte_code = 0;
 }
 else
 {
  // tbd ...
 }


 if(fn0)
 {
  proceed_s0<2, s0_fn1_p_p_type>(&result, fn0, byte_code, sr, true);
  if(pResult)
  {
   *pResult = result;
  }
  return;
 }


 s1_fng_type fn = table_->find_s1_declared_function_0(fuxe_name_, nullptr, &result_type_object_);
 if(fn)
 {
  // raw_value is quint64* standing for void** ...
  PHR_Universal_Class* uo = (PHR_Universal_Class*) (* (void**)raw_value) ;
  void* la0 = nullptr;
  quint64 mem = 0;
  QString qs_mem;
  QPair<PHR_Scope_System*, QPair<int, quint64>> qclo_value = {scopes_, {0, 0}};
  QString* pqs_mem = &qs_mem;

  FN_Codes fnc = result_type_object_? FN_Codes::RET_C:FN_Codes::NOR_C;

  int ptr_depth = 0;
  FN_Codes fnc1 = check_init_raw_value(lambda_arguments_[0], fnc, mem,
    qclo_value, pqs_mem, la0, ptr_depth);

  switch(fnc1)
  {
  case FN_Codes::RET_P:
   {
    fn1_p_wrtn_type pfn = (fn1_p_wrtn_type) fn;
    result = (uo->*pfn)((void*) la0);
   }
   break;
  case FN_Codes::NOR_P:
   {
    s1_fn1_p_type pfn = (s1_fn1_p_type) fn;
    (uo->*pfn)( (void*) *((quint64*) la0) );
   }
   break;

  case FN_Codes::RET_S:
   {
    fn1_s_wrtn_type pfn = (fn1_s_wrtn_type) fn;
    result = (uo->*pfn)(qs_mem);
   }
   break;
  case FN_Codes::NOR_S:
   {
    fn1_s_type pfn = (fn1_s_type) fn;
    (uo->*pfn)(qs_mem);
   }
   break;

  default: break;
  }

  // // does this go here?
  if(pResult)
  {
   *pResult = result;
  }

 }
 else
 {
  reflection_convention_ = Reflection_Conventions::Qt_Meta_Object;
  do_invoke_method(lambda_arguments_);
 }


}

void PHR_Command_Runtime_Router::proceed_s1_0(PHR_Function_Vector* pfv, void** pResult, void* raw_value)
{
 void* result = nullptr;

 int byte_code;
 s0_fn1_p_type fn0 = nullptr;
 bool sr;

 int mc = 0;
 int bc = 0;

 if(pfv)
 {
  if(void* fnp = pfv->match_against_codes({6101, 7101}, mc, bc, &result_type_object_))
  {
   fn0 = (s0_fn1_p_type) fnp;
   byte_code = bc;
   sr = mc == 6101;
  }
  else byte_code = 0;
 }
 else
 {
  // tbd ...
 }

 if(fn0)
 {
  proceed_s0<1, s0_fn1_p_type>(&result, fn0, byte_code, sr, true);
  if(pResult)
  {
   *pResult = result;
  }
  return;
 }

 s1_fng_type fn = table_->find_s1_declared_function_0(fuxe_name_, nullptr, &result_type_object_);
 if(fn)
 {
  // raw_value is quint64* standing for void** ...
  PHR_Universal_Class* uo = (PHR_Universal_Class*) (* (void**)raw_value) ;
  if(result_type_object_)
  {
   result = (uo->*fn)();
  }
  else
  {
   (uo->*fn)();
  }
 }
 if(pResult)
 {
  *pResult = result;
 }
 else
 {
  reflection_convention_ = Reflection_Conventions::Qt_Meta_Object;
  do_invoke_method(lambda_arguments_);
 }
}


void PHR_Command_Runtime_Router::proceed_s0_2(PHR_Function_Vector* pfv, void** pResult)
{
 int byte_code = 0;

 s0_fn1_p_p_type fn = nullptr;
 bool sr;

 int mc = 0;
 int bc = 0;

 if(pfv)
 {
  if(void* fnp = pfv->match_against_codes({6002, 7002}, mc, bc, &result_type_object_))
  {
   fn = (s0_fn1_p_p_type) fnp;
   byte_code = bc;
   sr = mc == 6002;
  }
  else byte_code = 0;
 }

 else
 {
  // tbd ...
 }

 if(fn)
 {
  proceed_s0<2, s0_fn1_p_p_type>(pResult, fn, byte_code, sr, false);
 }

 else if(pResult)
 {
  *pResult = nullptr;
 }
}

template<int c, typename fn_type>
void PHR_Command_Runtime_Router::proceed_s0(void** pResult, fn_type fn, int byte_code, bool sr, bool s10)
{
 FN_Codes fnc = result_type_object_? FN_Codes::RET_CC:FN_Codes::NOR_CC;

 // // populate a vec
 QVector<quint64> args;
 quint64 s10_arg;

 int sz = lambda_arguments_.size();


 int s10_size = s10?1:0;

 int ssz = sz + s10_size;

 args.resize(ssz);

 quint64 memvec[ssz];
 QString qs_memvec[ssz];
 QString* pqs_memvec[ssz];

 QPair<PHR_Scope_System*, QPair<int, quint64>> qclo_valuevec[ssz];

 for(int i = 0; i < ssz; ++i)
 {
  void* lai = nullptr;
  memvec[i] = 0;
  qclo_valuevec[i] = {scopes_, {0, 0}};

  pqs_memvec[i] = &qs_memvec[i];

  FN_Codes fnc = result_type_object_? FN_Codes::RET_CC:FN_Codes::NOR_CC;

  int ptr_depth = 0;

  if(i < s10_size)
  {
   if(i == 0)
   {
    FN_Codes fnc1 = check_init_raw_value(sigma_argument_, fnc, memvec[i],
       qclo_valuevec[i], pqs_memvec[i], lai, ptr_depth);
    args[i] = (quint64) lai;
   }
   else
   {
    // //  only s10 arguments for now ...
   }
  }
  else
  {
   FN_Codes fnc1 = check_init_raw_value(lambda_arguments_[i - s10_size], fnc, memvec[i],
      qclo_valuevec[i], pqs_memvec[i], lai, ptr_depth);
   args[i] = (quint64) lai;
  }
 }

 proceed_s0<c, fn_type>(args, pResult, fn, byte_code, sr);

}

template<int arg_count>
struct tybc_;

template<>
struct tybc_<2>
{
 template<int byc, typename fn_type>
 static void run(QVector<quint64>& args, void*& result,
  fn_type fn)
 {
  result = ( (typename tybc<byc>::_r) fn)
     ( (typename tybc<byc>::a0) *((quint64*) args[0]),  (typename tybc<byc>::a1) *((quint64*) args[1]) );
 }

 template<int byc, typename fn_type>
 static void run(QVector<quint64>& args, QString& string_result, fn_type fn)
 {
  string_result = ( (typename tybc<byc>::_sr) fn)
     ( (typename tybc<byc>::a0) *((quint64*) args[0]), (typename tybc<byc>::a1) *((quint64*) args[1]) );

 }

 template<int byc, typename fn_type>
 static void run(QVector<quint64>& args, fn_type fn)
 {
  ( (typename tybc<byc>::_nor) fn)
       ( (typename tybc<byc>::a0) *((quint64*) args[0]), (typename tybc<byc>::a1) *((quint64*) args[1]) );

 }
};


template<>
struct tybc_<1>
{
 template<int byc, typename fn_type>
 static void run(QVector<quint64>& args, void*& result,
  fn_type fn)
 {
  result = ( (typename tybc<byc>::_r) fn)
     ( (typename tybc<byc>::a0) *((quint64*) args[0]) );
 }

 template<int byc, typename fn_type>
 static void run(QVector<quint64>& args, QString& string_result, fn_type fn)
 {
  string_result = ( (typename tybc<byc>::_sr) fn)
     ( (typename tybc<byc>::a0) *((quint64*) args[0]) );

 }

 template<int byc, typename fn_type>
 static void run(QVector<quint64>& args, fn_type fn)
 {
  ( (typename tybc<byc>::_nor) fn)
       ( (typename tybc<byc>::a0) *((quint64*) args[0]) );

 }
};

//?KANS_(CMD)

template<>
void PHR_Command_Runtime_Router::proceed_s0_r<2, s0_fn1_p_p_type>(QVector<quint64>& args, void*& result,
  s0_fn1_p_p_type fn, int byte_code)
{
 switch(byte_code)
 {
 case 944: tybc_<2>::run<944, s0_fn1_p_p_type>(args, result, fn); break;
 case 984: tybc_<2>::run<984, s0_fn1_p_p_type>(args, result, fn); break;
 case 948: tybc_<2>::run<948, s0_fn1_p_p_type>(args, result, fn); break;
 default:
 case 988: tybc_<2>::run<988, s0_fn1_p_p_type>(args, result, fn); break;
 }
}

template<>
void PHR_Command_Runtime_Router::proceed_s0_sr<2, s0_fn1_p_p_type>(QVector<quint64>& args, //QString& str_result,
  s0_fn1_p_p_type fn, int byte_code)
{
 QString str_result;
 switch(byte_code)
 {
 case 944: tybc_<2>::run<944, s0_fn1_p_p_type>(args, str_result, fn); break;
 case 984: tybc_<2>::run<984, s0_fn1_p_p_type>(args, str_result, fn); break;
 case 948: tybc_<2>::run<948, s0_fn1_p_p_type>(args, str_result, fn); break;
 default:
 case 988: tybc_<2>::run<988, s0_fn1_p_p_type>(args, str_result, fn); break;
 }
 hold_string_result(str_result);
}

template<>
void PHR_Command_Runtime_Router::proceed_s0_nor<2, s0_fn1_p_p_type>(QVector<quint64>& args, //QString& str_result,
  s0_fn1_p_p_type fn, int byte_code)
{
 switch(byte_code)
 {
 case 944: tybc_<2>::run<944, s0_fn1_p_p_type>(args, fn); break;
 case 984: tybc_<2>::run<984, s0_fn1_p_p_type>(args, fn); break;
 case 948: tybc_<2>::run<948, s0_fn1_p_p_type>(args, fn); break;
 default:
 case 988: tybc_<2>::run<988, s0_fn1_p_p_type>(args, fn); break;
 }
}

template<>
void PHR_Command_Runtime_Router::proceed_s0_r<1, s0_fn1_p_type>(QVector<quint64>& args, void*& result,
  s0_fn1_p_type fn, int byte_code)
{
 switch(byte_code)
 {
 case 94: tybc_<1>::run<94, s0_fn1_p_type>(args, result, fn); break;
 default:
 case 98: tybc_<1>::run<98, s0_fn1_p_type>(args, result, fn); break;
 }
}

template<>
void PHR_Command_Runtime_Router::proceed_s0_sr<1, s0_fn1_p_type>(QVector<quint64>& args, //QString& str_result,
  s0_fn1_p_type fn, int byte_code)
{
 QString str_result;
 switch(byte_code)
 {
 case 94: tybc_<1>::run<94, s0_fn1_p_type>(args, str_result, fn); break;
 default:
 case 98: tybc_<1>::run<98, s0_fn1_p_type>(args, str_result, fn); break;
 }
 hold_string_result(str_result);
}

template<>
void PHR_Command_Runtime_Router::proceed_s0_nor<1, s0_fn1_p_type>(QVector<quint64>& args, //QString& str_result,
  s0_fn1_p_type fn, int byte_code)
{
 switch(byte_code)
 {
 case 94: tybc_<1>::run<94, s0_fn1_p_type>(args, fn); break;
 default:
 case 98: tybc_<1>::run<98, s0_fn1_p_type>(args, fn); break;
 }
}

template<int c, typename fn_type>
void PHR_Command_Runtime_Router::proceed_s0(QVector<quint64>& args, void** pResult,
  fn_type fn, int byte_code, bool sr)
{
 void* result = nullptr;
 if(result_type_object_)
 {
  if(sr)
  {
   proceed_s0_sr<c>(args, fn, byte_code);
  }
  else
  {
   proceed_s0_r<c>(args, result, fn, byte_code);
  }
 }
 else
 {
  proceed_s0_nor<c>(args, fn, byte_code);
 }
 if(pResult)
 {
  *pResult = result;
 }
}

//?_KANS(CMD)


void PHR_Command_Runtime_Router::proceed_s0_argvec(s0_fn1_p_type fn, void** pResult,
  int sl_byte_code, bool sr, int s10_size)
{
 void* result = nullptr;

 // // populate a vec
 QVector<quint64> args;
 quint64 s10_arg;

 int sz = lambda_arguments_.size();
 args.resize(sz);

 int ssz = sz + s10_size;

 quint64 memvec[ssz];
 QString qs_memvec[ssz];
 QString* pqs_memvec[ssz];

 QPair<PHR_Scope_System*, QPair<int, quint64>> qclo_valuevec[ssz];

 for(int i = 0; i < ssz; ++i)
 {
  void* lai = nullptr;
  memvec[i] = 0;
  qclo_valuevec[i] = {scopes_, {0, 0}};

  pqs_memvec[i] = &qs_memvec[i];

  FN_Codes fnc = result_type_object_? FN_Codes::RET_CC:FN_Codes::NOR_CC;

  int ptr_depth = 0;

  if(i < s10_size)
  {
   if(i == 0)
   {
    FN_Codes fnc1 = check_init_raw_value(sigma_argument_, fnc, memvec[i],
       qclo_valuevec[i], pqs_memvec[i], lai, ptr_depth);
    s10_arg = (quint64) lai;
   }
   else
   {
    // //  only s10 arguments for now ...
   }
  }
  else
  {
   FN_Codes fnc1 = check_init_raw_value(lambda_arguments_[i - s10_size], fnc, memvec[i],
      qclo_valuevec[i], pqs_memvec[i], lai, ptr_depth);
   args[i - s10_size] = (quint64) lai;
  }
 }


 if(result_type_object_)
 {
  if(sr)
  {
   s0_fn1_p__s_type sfn = (s0_fn1_p__s_type) fn;
   QString str_result = sfn( (void*) &args );
   hold_string_result(str_result);
  }
  else
  {
   result = fn( (void*) &args );
  }
 }
 else
 {
  switch (sl_byte_code)
  {
  case 99:
   ((s0_fn1_64_type) fn)( (quint64) &args ); break;
  case 949:
   ((_s0_fn1_32_64_type) fn)( (quint32) *((quint64*) s10_arg), (quint64) &args ); break;
  case 989:
   ((s0_fn1_64_64_type) fn)( (quint64) *((quint64*) s10_arg), (quint64) &args ); break;
  }
 }
 if(pResult)
 {
  *pResult = result;
 }
}

void PHR_Command_Runtime_Router::proceed_s0_0(PHR_Function_Vector* pfv, void** pResult)
{
 void* result = nullptr;

 int byte_code = 0;

 s0_fn1_p_type fn = nullptr;
 bool sr;

 int mc = 0;
 int bc = 0;

 if(pfv)
 {
  if(void* fnp = pfv->match_against_codes({6000, 7000}, mc, bc, &result_type_object_))
  {
   fn = (s0_fn1_p_type) fnp;
   byte_code = bc;
   sr = mc == 6000;
  }
  else byte_code = 0;
 }

 else
 {
  // tbd ...
 }

 if(fn)
 {
  if(result_type_object_)
  {
   if(sr)
   {
    s0_fn1_void__s_type sfn = (s0_fn1_void__s_type) fn;
    QString str_result = sfn( );
    hold_string_result(str_result);
   }
   else
   {
    result = ((s0_fn1_void_type) fn)();
   }
  }
  else
  {
   ((s0_fn1_void_type) fn)();
  }
 }
 if(pResult)
 {
  *pResult = result;
 }
}


void PHR_Command_Runtime_Router::proceed_s0_1(PHR_Function_Vector* pfv, void** pResult)
{
 int byte_code = 0;

 s0_fn1_p_type fn = nullptr;
 bool sr;

 int mc = 0;
 int bc = 0;

 if(pfv)
 {
  if(void* fnp = pfv->match_against_codes({6001, 7001}, mc, bc, &result_type_object_))
  {
   fn = (s0_fn1_p_type) fnp;
   byte_code = bc;
   sr = mc == 6001;
  }
  else byte_code = 0;
 }

 else
 {
  // tbd ...
 }

 if(fn)
 {
  proceed_s0<1, s0_fn1_p_type>(pResult, fn, byte_code, sr);
 }
 else if(pResult)
 {
  *pResult = nullptr;
 }
}

void PHR_Command_Runtime_Router::do_invoke_method(QVector<PHR_Command_Runtime_Argument*>& args)
{
 if(reflection_convention_ == Reflection_Conventions::Qt_Meta_Object)
 {
  argument_info_.resize(args.size() + 1);
  argument_info_[0].qmo = sigma_argument_->qmo();
  argument_info_[0].qmt = sigma_argument_->qmt();
 }
 else
 {
  argument_info_.resize(args.size());
 }
 QVector<quint64> store;
 init_argument_info(args, store);

 QString rtn = return_type_name();

 if(rtn.isEmpty())
 {
  return_type_code_ = Arg_Type_Codes::No_Return;
 }
 else
 {
  return_type_code_ = parse_return_type_code(rtn);
 }


#define MAX_UC_ARG_COUNT 2

 switch(args.size())
 {

 case 0: Do_Invoke_Method_<0, 0 <= MAX_UC_ARG_COUNT>::run(this, args); break;

 case 1: Do_Invoke_Method_<1, 1 <= MAX_UC_ARG_COUNT>::run(this, args); break;
 case 2: Do_Invoke_Method_<2, 2 <= MAX_UC_ARG_COUNT>::run(this, args); break;
 }

 // for return...
 switch(return_type_code_)
 {
 case Arg_Type_Codes::No_Return:
  break;
 case Arg_Type_Codes::Int:
  break;
 default:
  break;
 }

}

void PHR_Command_Runtime_Router::init_argument_info(QVector<PHR_Command_Runtime_Argument*>& args,
  QVector<quint64>& store)
{
 store.resize(args.size());
 switch(reflection_convention_)
 {
 case Reflection_Conventions::Qt_Meta_Object:
  init_argument_info_qob(args, store);
  break;
 case Reflection_Conventions::Universal_Class:
  init_argument_info_uc(args, store);
  break;
 default:
  break;
 }
}


PHR_Command_Runtime_Router::QOB_Argument_Conventions PHR_Command_Runtime_Router::qob_argument_convention_from_type_name(QString tn)
{
 static QMap<QString, PHR_Command_Runtime_Router::QOB_Argument_Conventions> static_map {{
   {"u32", PHR_Command_Runtime_Router::QOB_Argument_Conventions::Value_From_QString},
   {"str", PHR_Command_Runtime_Router::QOB_Argument_Conventions::QString_Direct},
  }};

 return static_map.value(tn, PHR_Command_Runtime_Router::QOB_Argument_Conventions::N_A);
}

void PHR_Command_Runtime_Router::init_argument_info_qob(QVector<PHR_Command_Runtime_Argument*>& args,
  QVector<quint64>& store)
{
 for(int i = 0; i < args.size(); ++i)
 {
  PHR_Command_Runtime_Argument* arg = args[i];

  QString tn = arg->type_name();
  QOB_Argument_Conventions ac;

  if(tn.isEmpty())
  {
   // //  others?
   if(arg->value_classification() == PHR_Command_Runtime_Argument::Value_Classification::QObject_Ptr)
   {
    ac = QOB_Argument_Conventions::QObject_Direct;
   }
  }
  else
  {
   ac = qob_argument_convention_from_type_name(tn);
  }
  if(ac == QOB_Argument_Conventions::N_A)
  {
   if(arg->value_classification() == PHR_Command_Runtime_Argument::Value_Classification::QObject_Ptr)
   {
    ac = QOB_Argument_Conventions::QObject_Direct;
   }
  }

  QString abc = arg->bind_code();
  if(!abc.isEmpty())
  {
   const PHR_Type_Object* pto;
   const PHR_Type_Object* cpto;
   QString encoded_value;
   QPair<int, quint64> qclo_value = {0, 0};
   quint64 rv = scopes_->find_value_from_current_scope(abc);

   // = scopes_->find_raw_value_from_current_scope(abc, envv_fn_, PHR_expression_,
     //pto, cpto, encoded_value, qclo_value);
   store[i] = rv;
   argument_info_[i + 1].qob_convention = ac;
   argument_info_[i + 1].void_argument = &store[i];
   continue;
  }

  switch(ac)
  {
  case QOB_Argument_Conventions::Value_From_QString:
   {
    QString* qs = (QString*) arg->raw_value();
    int qsi = qs->toInt();
    store[i] = qsi;
    argument_info_[i + 1].qob_convention = ac;
    argument_info_[i + 1].void_argument = &store[i];
   }
   break;

  case QOB_Argument_Conventions::QString_Direct:
   {
    QString* qs = (QString*) arg->raw_value();
    store[i] = (quint64) qs;
    argument_info_[i + 1].qob_convention = ac;
    argument_info_[i + 1].void_argument = (void*) store[i];
   }
   break;

  case QOB_Argument_Conventions::QObject_Direct:
   {
    void* pv = arg->raw_value();
    store[i] = (quint64) pv;
    argument_info_[i + 1].qob_convention = ac;
    argument_info_[i + 1].void_argument = (void*) store[i];
   }
   break;

  }
 }

 QString bc = sigma_argument_->bind_code();
 if(bc.isEmpty())
 {
  argument_info_[0].void_argument = sigma_argument_->raw_value();
 }
 else
 {
  const PHR_Type_Object* pto;
  const PHR_Type_Object* cpto;
  QString encoded_value;
  QPair<int, quint64> qclo_value = {0, 0};

//  quint64* rv;// = scopes_->find_raw_value_from_current_scope(bc, envv_fn_, PHR_expression_,
//    //pto, cpto, encoded_value, qclo_value);
//  argument_info_[0].void_argument = (void*) *rv;

  quint64 rv = scopes_->find_value_from_current_scope(bc);
  argument_info_[0].void_argument = (void*) rv;

 }
}

void PHR_Command_Runtime_Router::init_argument_info_uc(QVector<PHR_Command_Runtime_Argument*>& args,
  QVector<quint64>& store)
{
}


template<int Arg_Count>
void PHR_Command_Runtime_Router::Do_Invoke_Method<Arg_Count>
 ::run(PHR_Command_Runtime_Router* this_, QVector<PHR_Command_Runtime_Argument*>& args)
{
  switch(this_->reflection_convention_)
  {//?

  case Reflection_Conventions::Qt_Meta_Object:
   Do_Invoke_Method__Cast_Schedule__QOB__Cast_<Arg_Count>
     ::Type::template run<QObject*, typename Type_List__All_Cast_Needed<Arg_Count>::Type //,
     >
      (this_->fuxe_name(),
      this_->this_object(), 0, *this_,
      this_->argument_info(), args);
   break;
  }
}
