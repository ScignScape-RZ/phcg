
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RELAE_TXH_DOMINION__H
#define RELAE_TXH_DOMINION__H


#include "relae-graph/relae-node-ptr.h"
#include "relae-graph/relae-caon-ptr.h"


#define DOMINION_HIDE_NO_NAMESPACE
#define DOMINION_TYPE DOMINION_TYPE_DECLARE
#include "dominion/types.h"
#undef DOMINION_TYPE
#undef DOMINION_HIDE_NO_NAMESPACE

#include "kans.h"

KANS_(HGDMCore)

struct RTXH_Galaxy;
class RTXH_Node;
class RTXH_Connectors;
class RTXH_Connection;
class RTXH_Annotated_Connectors;
class RTXH_Frame;
class RTXH_Document;
class RTXH_Graph;
class RTXH_Root;
class RTXH_Token;

struct RTXH_Dominion
{
 typedef RTXH_Galaxy Galaxy_type;
 typedef RTXH_Node Node_type;
 typedef RTXH_Frame Frame_type;
 typedef RTXH_Connectors Connectors_type;
 typedef RTXH_Connection Connection_type;
 typedef RTXH_Annotated_Connectors Annotated_Connectors_type;
 typedef RTXH_Document Document_type;
 typedef RTXH_Graph Graph_type;
 typedef RTXH_Root Root_type;

// struct Connectors : node_connectors<RTXH_Dominion> {

//    Connectors(QString label) : node_connectors<RTXH_Dominion>(label){}

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



struct RTXH_Galaxy : Node_Ptr_Default_Galaxy<RTXH_Dominion>
{
 typedef RTXH_Token RTXH_Token_type;
// typedef RTXH_State RTXH_State_type;
// typedef RTXH_Clasp_Source_Element Source_Element_type;

};

enum class RTXH_Connectors_Case_Labels
{
 #define DOMINION_CONNECTOR(name, label) \
  name,
 #include "kernel/dominion/connectors.h"
 #undef DOMINION_CONNECTOR
};

struct RTXH_Connectors : node_connectors<RTXH_Dominion>
{
  RTXH_Connectors(RTXH_Connectors_Case_Labels cl = RTXH_Connectors_Case_Labels::N_A,
    QString label = QString())
   : node_connectors<RTXH_Dominion>(label), case_label(cl),
     priority(0), order(0){}
  RTXH_Connectors_Case_Labels case_label;
  int priority;
  int order;
  bool operator<(const RTXH_Connectors& rhs) const
  {
   return order < rhs.order;
  }
  operator bool() const
  {
   return order > 0;
  }
};

struct RTXH_Annotated_Connectors :
  node_annotated_connectors<RTXH_Dominion>
{
 RTXH_Annotated_Connectors(const RTXH_Connectors& conn,
   caon_ptr<RTXH_Connection> cion)
   : node_annotated_connectors<RTXH_Dominion>{conn, cion} {}

};



//class RTXH_Node : public node_ptr<RTXH_Dominion>
//{
//public:
// #define DOMINION_TYPE DOMINION_NODE_CONSTRUCTOR
// #include "dominion/types.h"
// #undef DOMINION_TYPE
//};

_KANS(HGDMCore)


#endif
