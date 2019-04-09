
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CALLABLE_VALUE__H
#define PHR_CALLABLE_VALUE__H

#include <QString>

#include "accessors.h"


class PhaonIR;

class PHR_Callable_Value
{
 PhaonIR* phaon_ir_;
 QString name_;

public:

 PHR_Callable_Value(PhaonIR* phaon_ir, QString name);

 void run();

};

#endif //  PHR_CALLABLE_VALUE__H
