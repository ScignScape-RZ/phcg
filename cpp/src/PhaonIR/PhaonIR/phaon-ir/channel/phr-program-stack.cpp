
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-program-stack.h"

PHR_Program_Stack::PHR_Program_Stack()
{

}

void PHR_Program_Stack::each_carrier_stack(std::function<
  void(PHR_Carrier_Stack&)> fn)
{
 for(PHR_Carrier_Stack* pcs : *this)
   fn(*pcs);
}
