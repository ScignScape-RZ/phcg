
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHAON_IR__H
#define PHAON_IR__H

#include <QString>


class PHR_Type_System;

class PhaonIR
{
 PHR_Type_System* type_system_;

public:

 PhaonIR();

 void init_channel_group_stack();
 void init_type_system();
 void init_type(QString type_name);

};

#endif // PHAON_IR__H
