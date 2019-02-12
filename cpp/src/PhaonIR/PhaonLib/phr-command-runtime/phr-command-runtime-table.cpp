
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-command-runtime-table.h"


#include "phaon-ir/channel/phr-channel-group.h"
#include "phaon-ir/channel/phr-carrier.h"

#include "phaon-ir/scopes/phr-runtime-scope.h"

//#include "kans.h"

#include <QQueue>

//USING_KANS(Kauvir)
//USING_KANS(CMD)




PHR_Command_Runtime_Table::PHR_Command_Runtime_Table(PHR_Type_System& type_system)
  :  PHR_Symbol_Scope(new PHR_Runtime_Scope(nullptr)), type_system_(type_system)
{

}

PHR_Function_Vector* PHR_Command_Runtime_Table::get_phr_function_vector(QString fn)
{
 return runtime_scope_->get_function_vector_value_as<PHR_Function_Vector>(fn);
}

void PHR_Command_Runtime_Table::add_declared_function_package(QString name, PHR_Function phf)
{
 strip_hyphens(name);
 add_function(name, phf);
 //runtime_scope_->add_function_vector_value();
 //(*phr)[name].push_back(phf);
}


PHR_Channel_Group* PHR_Command_Runtime_Table::find_channel_group(const PHR_Channel_Group& channels)
{
 if(group_pointers_.contains(channels))
 {
  return group_pointers_.value(channels);
 }
 PHR_Channel_Group* result = new PHR_Channel_Group(channels);
 group_pointers_[channels] = result;
 return result;
}

s1_fng_type PHR_Command_Runtime_Table::find_s1_declared_function_0(QString name,
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
