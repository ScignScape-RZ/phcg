
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_MINIMAL_EVALUATOR__H
#define PHR_MINIMAL_EVALUATOR__H

#include <QMap>


#include "phr-channel-group-evaluator.h"

#include "accessors.h"

class PHR_Channel_Group;

class PHR_Minimal_Evaluator : public PHR_Channel_Group_Evaluator
{
public:

 enum class Kernal_Operators {
   N_A, Add, Subtract
 };

private:

 Kernal_Operators kernel_operator_;

public:

 PHR_Minimal_Evaluator(PHR_Channel_Group& channel_group);

 ACCESSORS(Kernal_Operators ,kernel_operator)

 static Kernal_Operators parse_kernel_operator(QString fn);

 void run_eval();



};

#endif // PHR_MINIMAL_EVALUATOR__H
