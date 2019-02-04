
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CARRIER_STACK__H
#define PHR_CARRIER_STACK__H


#include <QStack>

#include "accessors.h"

class PHR_Carrier;

class PHR_Carrier_Stack : public QStack<PHR_Carrier*>
{
 QString sp_name_;

public:

 PHR_Carrier_Stack();

 ACCESSORS(QString ,sp_name)

 void indexed_each_carrier(std::function<
   void(int, PHR_Carrier&)> fn);


};

#endif // PHR_CARRIER_STACK__H
