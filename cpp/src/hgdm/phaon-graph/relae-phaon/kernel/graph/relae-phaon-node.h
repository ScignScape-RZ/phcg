
#ifndef RELAE_PHAON_NODE__H
#define RELAE_PHAON_NODE__H

#include "hgdm/relae-graph/relae-node-ptr.h"

#include "kernel/relae-phaon-dominion.h"

#include "kernel/frame/relae-phaon-frame.h"

#include <functional>

#include "kans.h"

KANS_(HGDMCore)


class RPH_Node : public node_ptr<RPH_Dominion>
{
public:
 #define DOMINION_TYPE DOMINION_NODE_CONSTRUCTOR
 #include "kernel/dominion/types.h"
 #undef DOMINION_TYPE

//? caon_ptr<SE_Token> se_token();

 void debug_connections();

 void each_connection(std::function<void(const RPH_Connectors& connector,
  const RPH_Node&, const RPH_Connection* connection)> fn)  const;

 void swap_relation(const RPH_Connectors& connector,
  caon_ptr<RPH_Node> n1, caon_ptr<RPH_Node> n2);

 void delete_relation(const RPH_Connectors& connector,
  caon_ptr<RPH_Node> n1);

};

_KANS(HGDMCore)

#endif
