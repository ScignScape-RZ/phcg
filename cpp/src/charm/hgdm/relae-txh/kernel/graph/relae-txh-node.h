
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RELAE_TXH_NODE__H
#define RELAE_TXH_NODE__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/relae-txh-dominion.h"

#include "kernel/frame/relae-txh-frame.h"

#include "phaong/phaong.h"
#include "phaong/phaong-types.h"


#include <functional>

#include "kans.h"

KANS_(HGDMCore)


class RTXH_Node : public node_ptr<RTXH_Dominion>
{
public:
 #define DOMINION_TYPE DOMINION_NODE_CONSTRUCTOR
 #include "kernel/dominion/types.h"
 #undef DOMINION_TYPE


// void debug_connections();

// void each_connection(std::function<void(const RTXH_Connectors& connector,
//  const RTXH_Node&, const RTXH_Connection* connection)> fn)  const;

// void swap_relation(const RTXH_Connectors& connector,
//  caon_ptr<RTXH_Node> n1, caon_ptr<RTXH_Node> n2);

// void delete_relation(const RTXH_Connectors& connector,
//  caon_ptr<RTXH_Node> n1);

};

_KANS(HGDMCore)

#endif
