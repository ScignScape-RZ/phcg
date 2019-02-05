
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-minimal-evaluator.h"

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

void PHR_Minimal_Evaluator::run_eval()
{

}
