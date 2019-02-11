
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CHANNEL_SYSTEM__H
#define PHR_CHANNEL_SYSTEM__H


#include <QString>

#include "accessors.h"

#include <QMap>

class PHR_Channel_Semantic_Protocol;

class PHR_Channel_System : public QMap<QString, PHR_Channel_Semantic_Protocol*>
{

public:

 PHR_Channel_System();

};

#endif // PHR_CHANNEL_SYSTEM__H
