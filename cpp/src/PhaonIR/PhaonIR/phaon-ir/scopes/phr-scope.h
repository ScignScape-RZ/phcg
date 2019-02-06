
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_SCOPE__H
#define PHR_SCOPE__H

#include <QString>

class PHR_Logical_Scope_Info;

class PHR_Scope
{
 PHR_Logical_Scope_Info* info_;
 PHR_Scope* parent_scope_;

public:

 PHR_Scope(PHR_Scope* parent_scope, PHR_Logical_Scope_Info* info = nullptr);

};

#endif // PHR_SCOPE__H
