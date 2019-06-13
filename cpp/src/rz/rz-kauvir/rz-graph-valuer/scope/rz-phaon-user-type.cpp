
#include "rz-phaon-user-type.h"
//?#include "rz-lisp-graph-logical-scope.h"

#include <QString>
#include <QMap>

USING_RZNS(GVal)

RZ_Phaon_User_Type::RZ_Phaon_User_Type(QString name)
 : name_(name), node_(nullptr), declaration_mode_(Declaration_Mode::None)
{}


