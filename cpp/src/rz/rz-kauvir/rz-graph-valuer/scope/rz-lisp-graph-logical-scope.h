
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_GRAPH_LOGICAL_SCOPE__H
#define RZ_LISP_GRAPH_LOGICAL_SCOPE__H

#include "accessors.h"
#include "flags.h"

#include <QString>
#include <QMap>
#include <QList>

#include <QMultiMap>

#include "rz-lisp-graph-lexical-scope.h"

#include "rzns.h"

RZNS_(RECore)

class RE_Node;

_RZNS(RECore)



RZNS_(GBuild)

class RZ_Lisp_Token;

_RZNS(GBuild)



RZNS_(GVal)

class RZ_Phaon_User_Type;

class RZ_Lisp_Graph_Logical_Scope : public RZ_Lisp_Graph_Lexical_Scope
{
 QString name_;

 caon_ptr<RZ_Lisp_Graph_Logical_Scope> parent_scope_;
 caon_ptr<RZ_Phaon_User_Type> user_type_;

public:

 RZ_Lisp_Graph_Logical_Scope(caon_ptr<RZ_Lisp_Graph_Logical_Scope> p = nullptr);

 ACCESSORS(QString ,name)
 ACCESSORS(caon_ptr<RZ_Lisp_Graph_Logical_Scope> ,parent_scope)
 ACCESSORS(caon_ptr<RZ_Phaon_User_Type> ,user_type)


};

_RZNS(GVal)

#endif //RZ_LISP_GRAPH_LOGICAL_SCOPE__H
