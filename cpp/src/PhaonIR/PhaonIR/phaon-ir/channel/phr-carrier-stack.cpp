
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-carrier-stack.h"

PHR_Carrier_Stack::PHR_Carrier_Stack()
{

}

void PHR_Carrier_Stack::indexed_each_carrier(std::function<
  void(int, PHR_Carrier&)> fn)
{
 int i = 0;
 for(PHR_Carrier* pcr : *this)
   fn(i++, *pcr);
}
