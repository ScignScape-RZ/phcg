
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-channel-group-table.h"

#include "phaon-ir/channel/phr-channel-group.h"

//#include "kauvir-code-model/kcm-channel-group.h"

//#include "kans.h"

#include <QQueue>

//USING_KANS(Kauvir)
//USING_KANS(CMD)

//USING//_KANS(PhaonLib)


PHR_Channel_Group_Table::PHR_Channel_Group_Table(PHR_Type_System& type_system)
  :  type_system_(type_system)
{

}



PHR_Channel_Group* PHR_Channel_Group_Table::find_channel_group(const PHR_Channel_Group& channels)
{
 if(group_pointers_.contains(channels))
 {
  return group_pointers_.value(channels);
 }
 PHR_Channel_Group* result = new PHR_Channel_Group(channels);
 group_pointers_[channels] = result;
 return result;
}
