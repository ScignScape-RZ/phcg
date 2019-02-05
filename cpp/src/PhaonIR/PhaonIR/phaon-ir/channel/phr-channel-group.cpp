
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-channel-group.h"

#include "phr-channel.h"

PHR_Channel_Group::PHR_Channel_Group()
{

}

void PHR_Channel_Group::with_find(PHR_Channel_Semantic_Protocol* pcsp,
  std::function<void(PHR_Channel&)> fn)
{
 auto it = find(pcsp);
 if(it != end())
 {
  return fn(*it.value());
 }
}

QString PHR_Channel_Group::get_first_raw_value_string(PHR_Channel_Semantic_Protocol* pcsp)
{
 QString result;
 with_find(pcsp, [&result](PHR_Channel& phc)
 {
  result = phc.get_first_raw_value_string();
 });
 return result;
}

