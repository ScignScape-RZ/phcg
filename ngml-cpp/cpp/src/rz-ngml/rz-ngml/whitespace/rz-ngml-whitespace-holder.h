
#ifndef RZ_NGML_WHITESPACE_HOLDER__H
#define RZ_NGML_WHITESPACE_HOLDER__H

#include <QString>

#include "accessors.h"

#include "rz-ngml-whitespace.h"

#include "rzns.h"

RZNS_(NGML)

class NGML_Whitespace_Holder
{
 NGML_Whitespace ws_;

public:

 NGML_Whitespace_Holder(){}

 ACCESSORS(NGML_Whitespace ,ws)

 void attach_whitespace(QString whitespace);

 template<typename T>
 void write_whitespace(T& t)
 {
  t << ws_.to_string();
 }

};

_RZNS(NGML)

#endif
