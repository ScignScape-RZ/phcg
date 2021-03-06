
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RELAE_PHAON_QUERY__H
#define RELAE_PHAON_QUERY__H

#include "kernel/relae-phaon-dominion.h"

#include "relae-graph/relae-node-ptr.h"

#include "kans.h"

KANS_(HGDMCore)

//class SY_Connector
//{
// //public:
// QString label_;

// public:
//  SY_Connector(QString label) : label_(label){}

//};

//template<type

class RPH_Query : public node_query<RPH_Dominion>
{
 RPH_Query();
 // SY_Dominion::Connectors N_A;
 public:
  #define DOMINION_CONNECTOR(name, label) \
   RPH_Connectors name;
  #include "kernel/dominion/connectors.h"
  #undef DOMINION_CONNECTOR

 static const RPH_Query& instance();
};

_KANS(HGDMCore)

#endif
