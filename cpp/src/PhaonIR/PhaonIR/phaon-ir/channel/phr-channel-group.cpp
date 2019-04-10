
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-channel-group.h"

#include "phr-channel.h"
#include "phr-carrier.h"
#include "types/phr-type-object.h"

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

void* PHR_Channel_Group::get_first_raw_value(PHR_Channel_Semantic_Protocol* pcsp)
{
 void* result;
 with_find(pcsp, [&result](PHR_Channel& phc)
 {
  result = phc.get_first_raw_value();
 });
 return result;
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

int PHR_Channel_Group::get_lambda_byte_code()
{
 int result = 9;
 for(const PHR_Carrier* c : *lambda_ch())
 {
  result *= 10;
  result += c->type_object()->byte_code();
 }
 return result;
}

int PHR_Channel_Group::get_sigma_lambda_byte_code()
{
 int result = 9;

 if(PHR_Channel* sc = sigma_ch())
 {
  for(const PHR_Carrier* c : *sc)
  {
   result *= 10;
   result += c->type_object()->byte_code();
  }
 }
 else
 {
//  result *= 10;
//  result += 9;
 }

 for(const PHR_Carrier* c : *lambda_ch())
 {
  result *= 10;
  result += c->type_object()->byte_code();
 }
 return result;
}

PHR_Channel_Group* PHR_Channel_Group::clone()
{
 PHR_Channel_Group* result = new PHR_Channel_Group;
 QMapIterator<PHR_Channel_Semantic_Protocol*, PHR_Channel*> it(*this);
 while(it.hasNext())
 {
  it.next();
  PHR_Channel* phc = it.value();
  result->insert(it.key(), phc->clone());
 }
 return result;
}

// //  this is all tmp ...
PHR_Channel* PHR_Channel_Group::find_channel_by_name(QString n,
  PHR_Channel_Semantic_Protocol** pr)
{
 QMapIterator<PHR_Channel_Semantic_Protocol*, PHR_Channel*> it(*this);
 while(it.hasNext())
 {
  it.next();
  if(it.key()->name() == n)
  {
   if(pr)
     *pr = it.key();
   return it.value();
  }
 }
 return nullptr;
}

PHR_Channel* PHR_Channel_Group::fuxe_ch()
{
 return find_channel_by_name("fuxe");
}

PHR_Channel*  PHR_Channel_Group::lambda_ch()
{
 return find_channel_by_name("lambda");
}

PHR_Channel*  PHR_Channel_Group::result_ch()
{
 return find_channel_by_name("result");
}

PHR_Channel*  PHR_Channel_Group::sigma_ch()
{
 return find_channel_by_name("sigma");
}

void PHR_Channel_Group::init_channel(PHR_Channel_Semantic_Protocol* key, int size)
{
 PHR_Channel* phc = new PHR_Channel;
 phc->resize(size);
 insert(key, phc);
}

void PHR_Channel_Group::clear_all_but_sigma()
{
 PHR_Channel_Semantic_Protocol* pr = nullptr;
 PHR_Channel*  ch = find_channel_by_name("sigma", &pr);
 clear();
 if(pr)
   insert(pr, ch);
}
