
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "basic-functions.h"


//#include "kauvir-code-model/kauvir-code-model.h"

//#include "kauvir-code-model/pcm-channel-group.h"

//#include "kauvir-type-system/kauvir-type-system.h"

//#include "kauvir-code-model/pcm-callable-value.h"

//#include "pcm-command-runtime/pcm-command-runtime-table.h"

//#include "pcm-command-runtime/pcm-command-runtime-router.h"

//#include "pcm-lisp-bridge/pcm-lisp-eval.h"

//#include "PhaonLib/phaon-channel-group-table.h"
//#include "PhaonLib/phaon-symbol-scope.h"
//#include "PhaonLib/phaon-function.h"


#include <QTextStream>

#include <QDebug>

#include <QEventLoop>


//USING_KANS(KCL)

//KANS_(PhaonLib)

//void test_0_ss(QString s1, QString s2)
//{
// qDebug() << "s1 = " << s1 << "s2 = " << s2;
//}

//void test_0_s(QString s1)
//{
// qDebug() << "s1 = " << s1;
//}

//QString test_s_ss(QString s1, QString s2)
//{
// qDebug() << "s1 = " << s1 << "s2 = " << s2;
// qDebug() << "returning: s_ss";
// return "s_ss";
//}

//QString test_s_s(QString s1)
//{
// qDebug() << "s1 = " << s1;
// qDebug() << "returning: s_s";
// return "s_s";
//}

//int test_i_ss(QString s1, QString s2)
//{
// qDebug() << "s1 = " << s1 << "s2 = " << s2;
// qDebug() << "returning: 66";
// return 66;
//}

//int test_i_s(QString s1)
//{
// qDebug() << "s1 = " << s1;
// qDebug() << "returning: 66";
// return 66;
//}

#include "phaon-ir/types/phr-type-system.h"
#include "phaon-ir/phr-code-model.h"
#include "phaon-ir/channel/phr-channel-group.h"
#include "phaon-lib/phr-channel-group-table.h"

#include "phaon-ir/channel/phr-channel-system.h"
#include "phaon-ir/channel/phr-carrier.h"
#include "phaon-ir/phaon-ir.h"


void prn(qint32 arg)
{
 qDebug() << arg;
}

void test_if_then_else(quint64 args_ptr)
{
 QVector<quint64>& args = *(QVector<quint64>*)(args_ptr);

 int i = 0;
 bool test = false;
 for(quint64 qui: args)
 {
  qint32 i1 = *(qint32*) qui;
  if(i % 2)
  {
   if(test)
   {
//    KCM_Callable_Value** kcv = (KCM_Callable_Value**) qui;
//    KCM_Command_Runtime_Router* kcrr = (*kcv)->kcrr();
//    kcrr->run_callable_value(*kcv);
    return;
   }
  }
  else
  {
//   quint64 qclo = *((quint64*)qui);

//   quint64 result;
//   KCM_Lisp_Eval::eval_lisp_callable_deferred_value(qclo, result, "bool");
//   qDebug() << result;
//   test = (bool) result;
  }
  ++i;
 }
}

void if_t_e(quint64 args_ptr)
{
 test_if_then_else(args_ptr);
}

void init_test_functions(PhaonIR& phr, PHR_Code_Model& pcm,
  PHR_Channel_Group_Table& table, PHR_Symbol_Scope& pss)
{
 PHR_Type_System* type_system = pcm.type_system();
 PHR_Channel_System& pcs = *phr.channel_system();

 PHR_Channel_Semantic_Protocol* lambda = pcs["lambda"];
 PHR_Channel_Group g1;//(pcm.channel_names());
 {
  PHR_Type* ty = type_system->get_type_by_name("u4");
  PHR_Carrier* phc = new PHR_Carrier;
  phc->set_phr_type(ty);
  //PHR_Channel_Semantic_Protocol* pcsp = pcs["lambda"];
  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc;

//  g1.add_lambda_carrier(
//    {pcm.get_pcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
//     QString()
//    );

  table.init_phaon_function(g1, pss, "prn", 700, &prn);

  //?
  g1.clear_all();
 }
 {
//  g1.add_lambda_carrier(
//     {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__argument_vector() ), nullptr},
//      QString()
//     );

  PHR_Type* ty = type_system->get_type_by_name("argvec");
  PHR_Carrier* phc = new PHR_Carrier;
  phc->set_phr_type(ty);
  //PHR_Channel_Semantic_Protocol* pcsp = pcs["lambda"];
  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc;

  table.init_phaon_function(g1, pss, "if-t-e", 700, &if_t_e);

  g1.clear_all();
 }

}

//_KANS(PhaonLib)

