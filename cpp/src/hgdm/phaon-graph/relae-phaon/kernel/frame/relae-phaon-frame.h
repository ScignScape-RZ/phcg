
#ifndef RELAE_PHAON_FRAME__H
#define RELAE_PHAON_FRAME__H


#include "hgdm/relae-graph/relae-node-ptr.h"

#include "kernel/relae-phaon-dominion.h"

#include "kans.h"

KANS_(HGDMCore)

class RPH_Frame : public node_frame<RPH_Dominion>
{
 RPH_Frame();
 // SY_Dominion::Connectors N_A;
 public:

 static RPH_Frame& instance();

};


_KANS(HGDMCore)

#endif
