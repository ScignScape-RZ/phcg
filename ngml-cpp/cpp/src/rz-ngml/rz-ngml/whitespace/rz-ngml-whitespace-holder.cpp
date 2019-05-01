
#include "rz-ngml-whitespace-holder.h"

#include "rzns.h"

USING_RZNS(NGML)

void NGML_Whitespace_Holder::attach_whitespace(QString whitespace)
{
 ws_ = NGML_Whitespace(whitespace);
}

