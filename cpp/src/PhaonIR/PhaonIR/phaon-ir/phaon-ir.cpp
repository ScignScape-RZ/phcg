
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-ir.h"

#include "types/phr-type-system.h"

PhaonIR::PhaonIR() :  type_system_(nullptr)
{

}

void PhaonIR::init_channel_group_stack()
{

}

void PhaonIR::init_type_system()
{
 type_system_ = new PHR_Type_System;
}

void PhaonIR::init_type(QString type_name)
{
 type_system_->check_add_type_by_name(type_name);
}
