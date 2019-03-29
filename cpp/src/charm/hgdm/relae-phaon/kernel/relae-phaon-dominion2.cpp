
#include "relae-phaon-dominion.h"

Connectors_Stash::Connectors_Stash():
 N_A(Dominion::Connectors_Type::Connectors::N_A)
 #define DOMINION_MACRO(x,y) ,x(Dominion::Connectors_Type::Connectors::_##x)
 #include "dominion-connectors.h"
 #undef DOMINION_MACRO
{ }

Connectors_Node_Stash::Connectors_Node_Stash(const Connectors_Stash& cs):
  N_A(new _QY_Node(&cs.N_A))
#define DOMINION_MACRO(x,y) ,x(new _QY_Node(&cs.x))
#include "dominion-connectors.h"
#undef DOMINION_MACRO
  { }


Connections::Connections()
{
 const Connectors_Node_Stash& stash = Connectors_Node_Stash::get();
#define DOMINION_MACRO(x,y) x = stash.x;
#include "dominion-connectors.h"
#undef DOMINION_MACRO
}
