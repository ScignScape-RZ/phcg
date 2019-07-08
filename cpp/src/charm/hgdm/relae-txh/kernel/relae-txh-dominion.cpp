
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "relae-txh-dominion.h"

#include "graph/relae-txh-node.h"

#define DOMINION_NODE_NAMESPACE KA::HGDMCore
#define DOMINION_TYPE DOMINION_RETRIEVE_TYPE_CODE
#include "dominion/types.h"
#undef DOMINION_TYPE
#undef DOMINION_NODE_NAMESPACE



//#include "_dominion.h"

//Connectors_Stash::Connectors_Stash():
// N_A(Dominion::Connectors_Type::Connectors::N_A)
// #define DOMINION_MACRO(x,y) ,x(Dominion::Connectors_Type::Connectors::_##x)
// #include "dominion-connectors.h"
// #undef DOMINION_MACRO
//{ }

//Connectors_Node_Stash::Connectors_Node_Stash(const Connectors_Stash& cs):
//  N_A(new _QY_Node(&cs.N_A))
//#define DOMINION_MACRO(x,y) ,x(new _QY_Node(&cs.x))
//#include "dominion-connectors.h"
//#undef DOMINION_MACRO
//  { }


//Connections::Connections()
//{
// const Connectors_Node_Stash& stash = Connectors_Node_Stash::get();
//#define DOMINION_MACRO(x,y) x = stash.x;
//#include "dominion-connectors.h"
//#undef DOMINION_MACRO
//}
