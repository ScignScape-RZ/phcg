
#ifndef RZ_NGML_FRAME__H
#define RZ_NGML_FRAME__H

#include "rz-relae/relae-node-ptr.h"

#include "kernel/rz-ngml-dominion.h"

#include "rzns.h"

RZNS_(NGML)


class NGML_Frame : public node_frame<NGML_Dominion>
{
 NGML_Frame();

public:

 static NGML_Frame& instance();

};

_RZNS(NGML)

#endif
