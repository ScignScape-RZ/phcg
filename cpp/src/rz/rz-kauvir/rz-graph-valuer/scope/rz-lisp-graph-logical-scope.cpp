
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include <QString>
#include <QMap>

#include <QStringList>

#include "rz-lisp-graph-logical-scope.h"


USING_RZNS(GVal)

RZ_Lisp_Graph_Logical_Scope::RZ_Lisp_Graph_Logical_Scope(caon_ptr<RZ_Lisp_Graph_Logical_Scope> p)
 :  RZ_Lisp_Graph_Lexical_Scope(nullptr), parent_scope_(p), user_type_(nullptr)
{
 if(p)
 {
  set_parent(p.raw_pointer());
 }
}

