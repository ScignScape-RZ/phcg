
#include "relae-phaon-query.h"

#include "kans.h"


USING_KANS(HGDMCore)


RPH_Query::RPH_Query()
 : node_query<RPH_Dominion>()
  #define DOMINION_CONNECTOR(name, label) \
    ,name(RPH_Connectors(RPH_Connectors_Case_Labels::name, label))
  #include "kernel/dominion/connectors.h"
  #undef DOMINION_CONNECTOR
{
 int order = 0;
 #define DOMINION_CONNECTOR(name, label) \
  name.order = order; \
  ++order;
 #include "kernel/dominion/connectors.h"
 #undef DOMINION_CONNECTOR
}

const RPH_Query& RPH_Query::instance()
{
 static RPH_Query* the_instance = nullptr;
 if(!the_instance)
  the_instance = new RPH_Query;
 return *the_instance;
}
