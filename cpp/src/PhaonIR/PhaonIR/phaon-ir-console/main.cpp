
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-ir/phaon-ir.h"

#include "phaon-ir/eval/phr-channel-group-evaluator.h"
#include "phaon-ir/eval/phr-minimal-evaluator.h"

#include "phaon-ir/channel/phr-channel-system.h"

#include <QDebug>


extern void local_program(PhaonIR& phr);


PHR_Channel_Group_Evaluator* load_evaluator(PhaonIR& phr, PHR_Channel_Group& pcg)
{
 QString fname = phr.get_first_raw_value_string("fuxe", pcg);
 if(fname.startsWith('#'))
 {
  PHR_Minimal_Evaluator::Kernal_Operators kop =
    PHR_Minimal_Evaluator::parse_kernel_operator(fname);
  if(kop != PHR_Minimal_Evaluator::Kernal_Operators::N_A)
  {
   PHR_Minimal_Evaluator* result = new PHR_Minimal_Evaluator(phr, pcg);
   result->set_kernel_operator(kop);
   return result;
  }
 }
 return nullptr;
}

int main(int argc, char **argv)
{
 PHR_Channel_System pcs;

 PhaonIR phr(&pcs);

 phr.set_load_evaluator_fn(&load_evaluator);
 local_program(phr);
 qDebug() << "ok";
}
