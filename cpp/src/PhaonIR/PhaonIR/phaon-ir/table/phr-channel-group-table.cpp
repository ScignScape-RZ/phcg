
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-channel-group-table.h"

#include "phaon-ir/channel/phr-channel-group.h"

#include "phaon-ir/channel/phr-carrier.h"

#include "phaon-ir/scopes/phr-runtime-scope.h"

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

s1_fng_type PHR_Channel_Group_Table::find_s1_declared_function_0(QString name,
  PHR_Channel_Group* kcg, const PHR_Type_Object** pkto)
{
 for(QPair<PHR_Channel_Group*, s1_fng_type> pr : s1_declared_functions_generic_.values(name))
 {
  if(pkto)
  {
   PHR_Channel_Group* k_ = pr.first;
   PHR_Channel* result = k_->result_ch();
   if(!result->isEmpty())
   {
    PHR_Carrier* r1 = result->first();
    *pkto = r1->type_object();
   }
   else
   {
    *pkto = nullptr;
   }
  }
  return (s1_fng_type)(pr.second);
 }
 return nullptr;
}


PHR_Runtime_Scope* PHR_Channel_Group_Table::get_runtime_scope(PHR_Symbol_Scope& pss)
{
 //if(symbol_scope_)
   return pss.runtime_scope();
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
