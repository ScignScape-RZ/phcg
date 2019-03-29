

//#include "qhyp-graph/qy-hyper-node.h"
//#include "qhyp-graph/qy-hyper-edge.h"
//#include "qhyp-graph/qy-ptr.h"

//
#include "graph/relae-phaon-node.h"

//#include "qhyp-graph/qy-hyper-graph.h"


struct Dominion_Connectors
{
 enum class Connectors
 {
  N_A,

#define DOMINION_MACRO(x,y) _##x,
#include "dominion-connectors.h"
#undef DOMINION_MACRO
 };

//?
// Connectors connector;
// Conr(Connectors c) : connector(c) {}
};


struct Dominion
{
 typedef Dominion_Connectors Connectors_Type;
 //typedef Cons Connections_Type;
};

template<typename DOMINION_Type>
struct Connector
{
 QY_Node connector_node;
 QY_Hyper_Node operator()(QY_Hyper_Node source)
 {
  //?
  return source->find_single_target(connector_node);
 }

 const _QY_Node& node_ref() const
 {
  return *connector_node;
 }

 Connector(QY_Node c = nullptr) : connector_node(c)
 {
 }

 const typename DOMINION_Type::Connectors_Type::Connectors* get_connector() const
 {
  typename DOMINION_Type::Connectors_Type::Connectors* result =
    connector_node->pRestore<typename DOMINION_Type::Connectors_Type::Connectors>();
  return result;
 }

 void operator=(QY_Node c)
 {
  connector_node = c;
 }

};

struct Connectors_Stash
{
 Dominion::Connectors_Type::Connectors N_A;
#define DOMINION_MACRO(x,y) Dominion::Connectors_Type::Connectors x;
#include "dominion-connectors.h"
#undef DOMINION_MACRO

 static const Connectors_Stash& get()
 {
  static Connectors_Stash* the_stash = nullptr;
  if(!the_stash)
   the_stash = new Connectors_Stash;
  return *the_stash;
 }

private:


 Connectors_Stash();
};

struct Connectors_Node_Stash
{
 QY_Node N_A;

#define DOMINION_MACRO(x,y) QY_Node x;
#include "dominion-connectors.h"
#undef DOMINION_MACRO


 static const Connectors_Node_Stash& get()
 {
  static Connectors_Node_Stash* the_stash = nullptr;
  if(!the_stash)
  {
   the_stash = new Connectors_Node_Stash(Connectors_Stash::get());
  }
  return *the_stash;
 }

private:

 Connectors_Node_Stash(const Connectors_Stash& cs);
};


struct Connections
{
#define DOMINION_MACRO(x,y) Connector<Dominion> x;
#include "dominion-connectors.h"
#undef DOMINION_MACRO

 Connections();
};


//QYNS_(Graph)
//template<>
//struct Is_Dominion_Connector<Connector<Dominion>>
//{
// typedef TRUE_Type Type;
//};
//_QYNS(Graph)

