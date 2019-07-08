
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RELAE_TXH_FRAME__H
#define RELAE_TXH_FRAME__H


#include "relae-graph/relae-node-ptr.h"

#include "kernel/relae-txh-dominion.h"

#include "kans.h"

KANS_(HGDMCore)

class RTXH_Frame : public node_frame<RTXH_Dominion>
{
 RTXH_Frame();
 // SY_Dominion::Connectors N_A;
 public:

 static RTXH_Frame& instance();

};


_KANS(HGDMCore)

#endif
