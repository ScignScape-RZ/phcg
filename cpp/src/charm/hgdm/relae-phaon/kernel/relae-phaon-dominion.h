
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RELAE_PHAON_DOMINION__H
#define RELAE_PHAON_DOMINION__H


#include "relae-graph/relae-node-ptr.h"
#include "relae-graph/relae-caon-ptr.h"


#define DOMINION_HIDE_NO_NAMESPACE
#define DOMINION_TYPE DOMINION_TYPE_DECLARE
#include "dominion/types.h"
#undef DOMINION_TYPE
#undef DOMINION_HIDE_NO_NAMESPACE

#include "kans.h"

KANS_(HGDMCore)

struct RPH_Galaxy;
class RPH_Node;
class RPH_Connectors;
class RPH_Connection;
class RPH_Annotated_Connectors;
class RPH_Frame;
class RPH_Document;
class RPH_Graph;
class RPH_Root;
class RPH_Token;

struct RPH_Dominion
{
 typedef RPH_Galaxy Galaxy_type;
 typedef RPH_Node Node_type;
 typedef RPH_Frame Frame_type;
 typedef RPH_Connectors Connectors_type;
 typedef RPH_Connection Connection_type;
 typedef RPH_Annotated_Connectors Annotated_Connectors_type;
 typedef RPH_Document Document_type;
 typedef RPH_Graph Graph_type;
 typedef RPH_Root Root_type;

// struct Connectors : node_connectors<RPH_Dominion> {

//    Connectors(QString label) : node_connectors<RPH_Dominion>(label){}

// };

 enum class Type_Codes { N_A,
  #define DOMINION_TYPE DOMINION_TYPE_ENUM
  #include "dominion/types.h"
  #undef DOMINION_TYPE
 };

 template<typename T>
 Type_Codes get_type_code()
 {
  return (Type_Codes) 0;
 }
 //typedef Test_Connector Connector_Type;
 // typedef Test_Type_Codes Connector_Type;

};



struct RPH_Galaxy : Node_Ptr_Default_Galaxy<RPH_Dominion>
{
 typedef RPH_Token RPH_Token_type;
// typedef RPH_State RPH_State_type;
// typedef RPH_Clasp_Source_Element Source_Element_type;

};

enum class RPH_Connectors_Case_Labels
{
 #define DOMINION_CONNECTOR(name, label) \
  name,
 #include "kernel/dominion/connectors.h"
 #undef DOMINION_CONNECTOR
};

struct RPH_Connectors : node_connectors<RPH_Dominion>
{
  RPH_Connectors(RPH_Connectors_Case_Labels cl = RPH_Connectors_Case_Labels::N_A,
    QString label = QString())
   : node_connectors<RPH_Dominion>(label), case_label(cl),
     priority(0), order(0){}
  RPH_Connectors_Case_Labels case_label;
  int priority;
  int order;
  bool operator<(const RPH_Connectors& rhs) const
  {
   return order < rhs.order;
  }
  operator bool() const
  {
   return order > 0;
  }
};

struct RPH_Annotated_Connectors :
  node_annotated_connectors<RPH_Dominion>
{
 RPH_Annotated_Connectors(const RPH_Connectors& conn,
   caon_ptr<RPH_Connection> cion)
   : node_annotated_connectors<RPH_Dominion>{conn, cion} {}

};



//class RPH_Node : public node_ptr<RPH_Dominion>
//{
//public:
// #define DOMINION_TYPE DOMINION_NODE_CONSTRUCTOR
// #include "dominion/types.h"
// #undef DOMINION_TYPE
//};

_KANS(HGDMCore)


#endif
