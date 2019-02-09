
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-function-package.h"

#include "phaon-ir/channel/phr-channel-group.h"
#include "phaon-ir/channel/phr-carrier.h"

//#include "kans.h"

//USING_KANS(KCM)
//USING_KANS(Kauvir)

PHR_Function_Package::PHR_Function_Package(PHR_Channel_Group* pcg)
  :  pcg_(pcg), byte_code_(0)
{

}

void PHR_Function_Package::init_byte_code_s1(bool sr)
{
 int head = sr? 601 : 701;
 init_byte_code(head);
}

void PHR_Function_Package::init_byte_code_s0(bool sr)
{
 int head = sr? 600 : 700;
 init_byte_code(head);
}

void PHR_Function_Package::init_byte_code(int head)
{
 quint32 lbc = pcg_->get_sigma_lambda_byte_code();

 quint32 tmp = lbc;

 int len = 0;
 if ( tmp >= 100000000 ) { len += 8; tmp /= 100000000; }
 if ( tmp >= 10000     ) { len += 4; tmp /= 10000; }
 if ( tmp >= 100       ) { len += 2; tmp /= 100; }
 if ( tmp >= 10        ) { len += 1; }

 quint32 bc = lbc;
 bc *= 10;
 bc += len;

 for(int i = 0; i < len + 2; ++i)
 {
  head *= 10;
 }

 bc += head;

 byte_code_ = bc;

}


const PHR_Type_Object* PHR_Function_Package::result_type_object()
{
 if(pcg_)
 {
  PHR_Channel* rch = pcg_->result_ch();
  if(!rch->isEmpty())
  {
   PHR_Carrier* r1 = rch->first();
   //PHR_Carrier r1; rch->get_carrier_at_position(0, r1);
   return r1->type_object();
  }
 }
 return nullptr;
}

int PHR_Function_Package::split_byte_code(int& xbc)
{
 int bc = byte_code_;
 int len = bc % 10;
 bc /= 10;
 int l10 = 1;
 for(int i = 0; i <= len; ++i)
 {
  l10 *= 10;
 }
 xbc = bc % l10;
 bc /= l10;
 return (bc * 10) + len;
}

void PHR_Function_Package::init_byte_code_s10(bool sr)
{
 int head = sr? 610 : 710;
 init_byte_code(head);
}





