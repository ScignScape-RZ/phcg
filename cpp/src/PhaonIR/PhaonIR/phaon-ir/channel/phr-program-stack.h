
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_PROGRAM_STACK__H
#define PHR_PROGRAM_STACK__H


#include <QStack>

class PHR_Carrier_Stack;

class PHR_Program_Stack : public QStack<PHR_Carrier_Stack*>
{

public:

 PHR_Program_Stack();


};

#endif // PHR_PROGRAM_STACK__H
