
#ifndef RZ_PHAON_PRECYCLE__H
#define RZ_PHAON_PRECYCLE__H

#include "accessors.h"
#include "flags.h"

//#include "rz-lisp-value-holder.h"

#include <QString>
#include <QMap>


#include "rz-lisp-graph-scope-token.h"

#include "accessors.h"

#include "relae-graph/relae-caon-ptr.h"

class PHR_Type_Object;

#include "rzns.h"
RZNS_(GVal)

class RZ_Phaon_Precycle : QList<QPair<caon_ptr<PHR_Type_Object>, QString>>
{
public:
 RZ_Phaon_Precycle();

void add_type(caon_ptr<PHR_Type_Object> pto)
{
 push_back({pto, QString()});
}

};

_RZNS(GVal)

#endif // RZ_PHAON_USER_TYPE__H
