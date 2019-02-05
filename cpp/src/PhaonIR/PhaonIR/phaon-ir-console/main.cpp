
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-ir/phaon-ir.h"

#include "phaon-ir/eval/phr-channel-group-evaluator.h"

#include <QDebug>


extern void local_program(PhaonIR& phr);


PHR_Channel_Group_Evaluator* load_evaluator(PhaonIR& phr, PHR_Channel_Group& pcg)
{
 QString fname = phr.get_first_raw_value_string("fuxe", pcg);
 if(fname.startsWith('#'))
 {

 }
}

int main(int argc, char **argv)
{
 PhaonIR phr;
 phr.set_load_evaluator_fn(&load_evaluator);
 local_program(phr);
 qDebug() << "ok";
}
