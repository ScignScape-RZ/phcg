
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-minimal-evaluator.h"

#include "kop-base.h"

#include "kops/add.h"
#include "kops/subtract.h"


PHR_Minimal_Evaluator::PHR_Minimal_Evaluator(PHR_Channel_Group& channel_group)
  :  PHR_Channel_Group_Evaluator(channel_group)
{

}

PHR_Minimal_Evaluator::Kernal_Operators PHR_Minimal_Evaluator::parse_kernel_operator(QString fn)
{
 static QMap<QString, Kernal_Operators> static_map {{
   { "#+", Kernal_Operators::Add },
   { "#-", Kernal_Operators::Subtract },
 }};

 return static_map.value(fn, Kernal_Operators::N_A);
}

void PHR_Minimal_Evaluator::run_eval(QVector<qint32>& args)
{
 static QMap<Kernal_Operators, PHR_KOP_Base<qint32>*> static_map {{
   { Kernal_Operators::N_A, new PHR_KOP_Add },
   { Kernal_Operators::Add, new PHR_KOP_Add },
   { Kernal_Operators::Subtract, new PHR_KOP_Subtract },
   }};

 qint32* pres = new qint32();
 *pres = 0;

 static_map[kernel_operator_]->run_eval(args, *pres);

 rh_.raw_value = pres;
}
