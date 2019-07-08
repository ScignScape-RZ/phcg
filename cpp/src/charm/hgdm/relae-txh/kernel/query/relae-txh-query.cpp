
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "relae-txh-query.h"

#include "kans.h"


USING_KANS(HGDMCore)


RTXH_Query::RTXH_Query()
 : node_query<RTXH_Dominion>()
  #define DOMINION_CONNECTOR(name, label) \
    ,name(RTXH_Connectors(RTXH_Connectors_Case_Labels::name, label))
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

const RTXH_Query& RTXH_Query::instance()
{
 static RTXH_Query* the_instance = nullptr;
 if(!the_instance)
  the_instance = new RTXH_Query;
 return *the_instance;
}
