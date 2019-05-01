
#ifndef RZ_NGML_WHITESPACE__H
#define RZ_NGML_WHITESPACE__H

#include "accessors.h"
#include "flags.h"
#include "rz-relae/relae-caon-ptr.h"


#include <QString>

#include "rzns.h"

RZNS_(NGML)

class NGML_Whitespace
{

 caon_ptr<QString> raw_text_;

public:

 NGML_Whitespace();

 explicit NGML_Whitespace(QString raw_text);

 QString to_string();
 void parse(QString raw_text);
};

_RZNS(NGML)

#endif
