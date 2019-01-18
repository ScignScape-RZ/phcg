
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


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
