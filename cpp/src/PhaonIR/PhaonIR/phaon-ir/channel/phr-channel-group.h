
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CHANNEL_GROUP__H
#define PHR_CHANNEL_GROUP__H


#include <QMap>

#include "phr-channel.h"
#include "phr-channel-semantic-protocol.h"

class PHR_Channel_Semantic_Protocol;
class PHR_Channel;

class PHR_Channel_Group : public
  QMap<PHR_Channel_Semantic_Protocol*, PHR_Channel*>
{

public:

 PHR_Channel_Group();

 QString get_first_raw_value_string(PHR_Channel_Semantic_Protocol* pcsp);

 void* get_first_raw_value(PHR_Channel_Semantic_Protocol* pcsp);

 void with_find(PHR_Channel_Semantic_Protocol* pcsp,
   std::function<void(PHR_Channel&)> fn);

 int get_lambda_byte_code();
 int get_sigma_lambda_byte_code();

 PHR_Channel* find_channel_by_name(QString n);

 PHR_Channel* fuxe_ch();
 PHR_Channel* lambda_ch();
 PHR_Channel* result_ch();
 PHR_Channel* sigma_ch();


 friend bool operator<(const PHR_Channel_Group& lhs, const PHR_Channel_Group& rhs)
 {
  if(lhs.size() == rhs.size())
  {
   QMapIterator<PHR_Channel_Semantic_Protocol*, PHR_Channel*> lit(lhs);
   QMapIterator<PHR_Channel_Semantic_Protocol*, PHR_Channel*> rit(rhs);
   while(lit.hasNext())
   {
    lit.next();
    rit.next();
    if(*lit.key() == *rit.key())
    {
     if(*lit.value() < *rit.value())
       return true;
     if(*rit.value() < *lit.value())
       return false;
    }
    else if(*lit.key() < *rit.key())
      return true;
    else return false;
   }
  }
  else if(lhs.size() < rhs.size())
  {
   return true;
  }
  return false;
 }

};

#endif // PHR_CHANNEL_GROUP__H
