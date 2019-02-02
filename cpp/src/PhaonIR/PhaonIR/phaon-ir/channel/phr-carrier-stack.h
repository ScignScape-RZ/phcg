
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CARRIER_STACK__H
#define PHR_CARRIER_STACK__H


#include <QStack>

class PHR_Carrier;

class PHR_Carrier_Stack : QStack<PHR_Carrier*>
{

public:

 PHR_Carrier_Stack();


};

#endif // PHR_CARRIER_STACK__H
