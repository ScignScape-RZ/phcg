
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CHANNEL_SEMANTIC_PROTOCOL__H
#define PHR_CHANNEL_SEMANTIC_PROTOCOL__H


#include <QStack>

#include "accessors.h"



class PHR_Channel_Semantic_Protocol
{
 QString name_;

public:

 PHR_Channel_Semantic_Protocol();

 ACCESSORS(QString ,name)


};

#endif // PHR_CHANNEL_SEMANTIC_PROTOCOL__H
