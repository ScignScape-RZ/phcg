
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CHANNEL_GROUP__H
#define PHR_CHANNEL_GROUP__H


#include <QMap>


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


};

#endif // PHR_CHANNEL_GROUP__H
