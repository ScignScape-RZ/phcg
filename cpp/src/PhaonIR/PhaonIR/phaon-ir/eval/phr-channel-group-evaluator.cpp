
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-channel-group-evaluator.h"

#include "phaon-ir.h"


PHR_Channel_Group_Evaluator::PHR_Channel_Group_Evaluator(PhaonIR& phr,
  PHR_Channel_Group& channel_group)
  :  phr_(phr), channel_group_(channel_group)
{

}

PHR_Channel* PHR_Channel_Group_Evaluator::get_channel_by_sp_name(QString sp_name, PHR_Channel_Group& pcg)
{
 return phr_.get_channel_by_sp_name(sp_name, pcg);
}

qint32 PHR_Channel_Group_Evaluator::phr_get_u4_symbol_value(QString sym)
{
 return phr_.get_u4_symbol_value(sym);
}
