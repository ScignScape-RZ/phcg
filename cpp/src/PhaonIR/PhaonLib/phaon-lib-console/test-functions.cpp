
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "test-functions.h"


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

void prn(qint32 arg)
{
 qDebug() << arg;
}

void init_test_functions(PHR_Code_Model& pcm,
  PHR_Channel_Group_Table& table, PHR_Symbol_Scope& pss)
{
 PHR_Type_System* type_system = pcm.type_system();

 PHR_Channel_Group g1;//(pcm.channel_names());
 {
//  g1.add_lambda_carrier(
//    {pcm.get_pcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
//     QString()
//    );

  table.init_phaon_function(g1, pss, "prn", 700, &prn);

  //?g1.clear_all();
 }

}

//_KANS(PhaonLib)

