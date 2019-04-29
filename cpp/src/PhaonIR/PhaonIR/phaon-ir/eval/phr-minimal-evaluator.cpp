
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-minimal-evaluator.h"

#include "kop-base.h"

#include "kops/add.h"
#include "kops/subtract.h"

#include "channel/phr-channel-group.h"
#include "channel/phr-channel.h"

#include "channel/phr-carrier.h"
#include "phaon-ir.h"

#include "kops/less-than.h"
#include "kops/equal.h"
#include "kops/bool.h"

#include <QDebug>

PHR_Minimal_Evaluator::PHR_Minimal_Evaluator(PhaonIR& phr,
  PHR_Channel_Group& channel_group)
  :  PHR_Channel_Group_Evaluator(phr, channel_group)
{

}

void PHR_Minimal_Evaluator::debug_report()
{
 if(rh_.raw_value)
 {
  qDebug() << *(qint32*)rh_.raw_value;
 }
 else
 {
  qDebug() << rh_.raw_value_string;
 }
}

PHR_Minimal_Evaluator::Kernal_Operators PHR_Minimal_Evaluator::parse_kernel_operator(QString fn)
{
 static QMap<QString, Kernal_Operators> static_map {{
   { "#+", Kernal_Operators::Add },
   { "#-", Kernal_Operators::Subtract },
   { "#<", Kernal_Operators::Less_Than },
   { "#=?", Kernal_Operators::Equal },
   { "#?\\", Kernal_Operators::Bool },
 }};

 return static_map.value(fn, Kernal_Operators::N_A);
}

void PHR_Minimal_Evaluator::run_eval()
{
 PHR_Channel* lc = get_channel_by_sp_name("lambda", channel_group_);
 if(!lc)
   return;
 int sz = lc->size();
 QVector<qint32> args;
 args.resize(sz);
 for(int i = 0; i < sz; ++i)
 {
  PHR_Carrier* pcr = lc->at(i);
  if(pcr->symbol_name().isEmpty())
  {
   args[i] = pcr->raw_value_string().toInt();
  }
  else
  {
   args[i] = phr_get_s4_symbol_value(pcr->symbol_name());
  }
 }
 run_eval(args);
}

void* PHR_Minimal_Evaluator::get_result_value()
{
 return rh_.raw_value;
}

QString PHR_Minimal_Evaluator::get_result_string()
{
 return rh_.raw_value_string;
}

void PHR_Minimal_Evaluator::run_eval(QVector<qint32>& args)
{
 static QMap<Kernal_Operators, PHR_KOP_Base<qint32>*> static_map {{
   { Kernal_Operators::N_A, new PHR_KOP_Add },
   { Kernal_Operators::Add, new PHR_KOP_Add },
   { Kernal_Operators::Subtract, new PHR_KOP_Subtract },
   { Kernal_Operators::Less_Than, new PHR_KOP_Less_Than },
   { Kernal_Operators::Equal, new PHR_KOP_Equal },
   { Kernal_Operators::Bool, new PHR_KOP_Bool },
   }};

 qint32* pres = new qint32();
 *pres = 0;

 static_map[kernel_operator_]->run_eval(args, *pres);

 rh_.raw_value = pres;
}
