
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CHANNEL_GROUP_EVALUATOR__H
#define PHR_CHANNEL_GROUP_EVALUATOR__H


#include <QMap>

class PHR_Channel_Group;

class PHR_Channel_Group_Evaluator
{
protected:

 PHR_Channel_Group& channel_group_;

public:

 PHR_Channel_Group_Evaluator(PHR_Channel_Group& channel_group);

 virtual void run_eval() = 0;


};

#endif // PHR_CHANNEL_GROUP_EVALUATOR__H
