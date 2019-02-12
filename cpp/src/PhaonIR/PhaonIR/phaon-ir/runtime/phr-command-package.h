
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_COMMAND_PACKAGE__H
#define PHR_COMMAND_PACKAGE__H

#include <QString>

#include "accessors.h"

#include "phaon-ir/channel/phr-channel-group.h"

class PHR_Type;
class PHR_Type_Object;

class PHR_Command_Package : public PHR_Channel_Group
{
 QString bind_val_;

 PHR_Type_Object* bind_pto_;

public:

 PHR_Command_Package(const PHR_Channel_Group& pcg);

 ACCESSORS(PHR_Type_Object* ,bind_pto)


};

#endif //  PHR_COMMAND_PACKAGE__H