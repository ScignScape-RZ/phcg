
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-channel.h"
#include "phr-carrier.h"


PHR_Channel::PHR_Channel()
{

}


void* PHR_Channel::get_first_raw_value()
{
 if(isEmpty())
   return nullptr;
 return first()->raw_value();
}

QString PHR_Channel::get_first_raw_value_string()
{
 if(isEmpty())
   return QString();
 return first()->raw_value_string();
}
