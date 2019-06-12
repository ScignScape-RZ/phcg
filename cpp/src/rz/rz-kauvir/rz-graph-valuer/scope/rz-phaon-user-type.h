
#ifndef RZ_PHAON_USER_TYPE__H
#define RZ_PHAON_USER_TYPE__H

#include "accessors.h"
#include "flags.h"

//#include "rz-lisp-value-holder.h"

#include <QString>
#include <QMap>


#include "rz-lisp-graph-scope-token.h"

#include "accessors.h"

#include "relae-graph/relae-caon-ptr.h"

#include "rz-phaon-precycle.h"

class PHR_Type_Object;

#include "rzns.h"
RZNS_(GVal)

class RZ_Lisp_Graph_Logical_Scope;

class RZ_Phaon_User_Type
{
 QString name_;
 caon_ptr<RZ_Lisp_Graph_Logical_Scope> scope_;
 RZ_Phaon_Precycle precycle_;
 RZ_Phaon_Precycle cocycle_;


public:

 enum class Declaration_Mode
 {
  None, Precycle, Cocycle, Class
 };

private:

 Declaration_Mode declaration_mode_;

public:

 RZ_Phaon_User_Type(QString name);

 ACCESSORS(QString ,name)
 ACCESSORS(caon_ptr<RZ_Lisp_Graph_Logical_Scope> ,scope)

 ACCESSORS(Declaration_Mode ,declaration_mode)

 ACCESSORS__RGET(RZ_Phaon_Precycle ,precycle)
 ACCESSORS__RGET(RZ_Phaon_Precycle ,cocycle)


// QList<caon_ptr<PHR_Type_Object>>

//?
// template<typename T>
// friend void operator<<(T& t, const RZ_Lisp_Graph_User_Class&)
// {
// }

// friend void operator<<(QDebug qd, RZ_Lisp_Graph_User_Class&)
// {
////  qd << "<fundef>";
// }


};

_RZNS(GVal)

#endif // RZ_PHAON_USER_TYPE__H
