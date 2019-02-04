
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CHANNEL_GROUP__H
#define PHR_CHANNEL_GROUP__H


#include <QMap>


class PHR_Channel_Semantic_Protocol;
class PHR_Carrier_Stack;

class PHR_Channel_Group : public
  QMap<PHR_Channel_Semantic_Protocol*, PHR_Carrier_Stack*>
{

public:

 PHR_Channel_Group();


};

#endif // PHR_CHANNEL_GROUP__H
