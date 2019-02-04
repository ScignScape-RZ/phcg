
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHAON_IR__H
#define PHAON_IR__H

#include <QString>
#include <QMap>

class PHR_Channel_Semantic_Protocol;
class PHR_Type_System;
class PHR_Program_Stack;
class PHR_Carrier_Stack;

class PhaonIR
{
 QMap<QString, PHR_Channel_Semantic_Protocol*> semantic_protocols_;
 QMap<PHR_Channel_Semantic_Protocol*, PHR_Carrier_Stack*> sp_map_;
 PHR_Type_System* type_system_;
 PHR_Program_Stack* program_stack_;

 PHR_Carrier_Stack* get_carrier_stack_by_sp_name(QString sp_name);
 void check_semantic_protocol(QString sp_name);

public:

 PhaonIR();

 void init_program_stack();
 void reset_program_stack();
 void init_type_system();
 void init_type(QString type_name);

 void push_carrier_stack(QString sp_name);

};

#endif // PHAON_IR__H
