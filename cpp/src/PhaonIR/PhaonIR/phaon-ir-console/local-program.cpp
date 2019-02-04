
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-ir/phaon-ir.h"

#include <QDebug>

void local_program(PhaonIR& phr)
{
 phr.init_type_system();
 phr.init_type("u4");

 phr.init_program_stack();
 phr.reset_program_stack();

 phr.push_carrier_stack("lambda");

}
