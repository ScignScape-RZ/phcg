
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_RESULT_HOLDER__H
#define PHR_RESULT_HOLDER__H

#include <QString>

struct PHR_Result_Holder
{
 QString raw_value_string;
 void* raw_value;

 PHR_Result_Holder();
};

#endif // PHR_RESULT_HOLDER__H
