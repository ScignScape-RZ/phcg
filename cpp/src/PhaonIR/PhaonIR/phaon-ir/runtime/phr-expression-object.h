
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_EXPRESSION_OBJECT__H
#define PHR_EXPRESSION_OBJECT__H

#include <QString>

#include "accessors.h"


class PhaonIR;
class PHR_Channel_Group;
class PHR_Channel_Group_Evaluator;

class PHR_Expression_Object
{
 PhaonIR* phaon_ir_;
 PHR_Channel_Group* channel_group_;

public:

 PHR_Expression_Object(PhaonIR* phaon_ir, PHR_Channel_Group* channel_group);

 PHR_Channel_Group_Evaluator* run();

};

#endif //PHR_EXPRESSION_OBJECT__H
