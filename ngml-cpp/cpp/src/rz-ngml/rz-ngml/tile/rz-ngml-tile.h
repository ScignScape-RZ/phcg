
#ifndef RZ_NGML_TILE__H
#define RZ_NGML_TILE__H

#include <QString>

#include "accessors.h"
#include "flags.h"

#include "whitespace/rz-ngml-whitespace-holder.h"

#include "rzns.h"

RZNS_(NGML)

class NGML_Tile : public NGML_Whitespace_Holder
{
 QString raw_text_;

public:

 ACCESSORS(QString ,raw_text)

 NGML_Tile(QString raw_text);

 QString to_string();

 QString thumbnail(int max_characters = 6);

};

_RZNS(NGML)

#endif
