
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-command-package.h"


PHR_Command_Package::PHR_Command_Package(const PHR_Channel_Group& pcg)
  :  PHR_Channel_Group(pcg), bind_pto_(nullptr)
{

}
