
#ifndef RZ_NODE_PTR__H
#define RZ_NODE_PTR__H

#include "relae-caon-ptr.h"

#include <QMultiMap>
#include <QMapIterator>
#include <QString>
#include <QList>


#ifndef ACCESSORS__GET
#define ACCESSORS__GET(type ,name) \
 type name() const { return name##_; }
#endif

#ifndef ACCESSORS__SET
#define ACCESSORS__SET(type ,name) \
 void set_##name(type t) { name##_ = t; }
#endif

#ifndef ACCESSORS
#define ACCESSORS(type ,name) \
  ACCESSORS__GET(type ,name) \
  ACCESSORS__SET(type ,name)
#endif

#ifdef RELAE_LABEL_NODES
#define RELAE_SET_NODE_LABEL(node, label) \
 node->set_label(label);
#else
#define RELAE_SET_NODE_LABEL(node, label)
#endif


struct Node_Ptr_Basic_Galaxy
{
 typedef QString tString;
 struct Root_Void {};
 typedef caon_ptr<Root_Void> Root_Vertex_type;
 typedef Root_Void Root_Void_type;
};


template<typename DOMINION, typename T>
typename DOMINION::Type_Codes dominion_get_type_code();


template<typename DOMINION>
struct Node_Ptr_Default_Galaxy : Node_Ptr_Basic_Galaxy
{
 typedef typename DOMINION::Connectors_type Connectors_type;
 typedef typename DOMINION::Type_Codes Type_Codes_type;
 typedef typename DOMINION::Node_type Node_type;
 typedef typename DOMINION::Frame_type Frame_type;
 typedef typename DOMINION::Graph_type Graph_type;
 typedef typename DOMINION::Document_type Document_type;
 typedef typename DOMINION::Root_type Root_type;
 typedef caon_ptr<Connectors_type> Connectors_Caon_type;
 typedef caon_ptr<Node_type> Node_Caon_type;
 typedef caon_ptr<Root_type> Root_Caon_type;
};

template<typename DOMINION_Type,
   typename GALAXY_Type = typename DOMINION_Type::Galaxy_type>
class node_connectors
{
 typedef typename GALAXY_Type::tString tString;
 typedef typename GALAXY_Type::Node_type Node_type;
 typedef typename GALAXY_Type::Node_Caon_type Node_Caon_type;
 typedef typename GALAXY_Type::Connectors_type Connectors_type;
 typedef typename GALAXY_Type::Connectors_Caon_type Connectors_Caon_type;

 tString label_;

public:

 node_connectors(tString label) : label_(label) {}

 tString label() const
 {
  return label_;
 }


 Node_Caon_type operator()(Node_Caon_type node) const
 {
  const Connectors_type* cast = static_cast<const Connectors_type*>(this);
  return node->retrieve(*cast);
 }

 bool operator()(Node_Caon_type n, Node_Caon_type target) const
 {
  const Connectors_type* cast = static_cast<const Connectors_type*>(this);
  return n->match_relation(*cast, target);
 }


};


template<typename DOMINION_Type,
   typename GALAXY_Type = typename DOMINION_Type::Galaxy_type>
class node_query
{
protected:
 typedef typename GALAXY_Type::tString tString;
 typedef typename GALAXY_Type::Connectors_type Connectors_type;
};


template<typename DOMINION_Type,
   typename GALAXY_Type = typename DOMINION_Type::Galaxy_type>
class node_graph
{
 typedef typename GALAXY_Type::Root_Caon_type Root_Caon_type;
 typedef typename GALAXY_Type::Node_Caon_type Node_Caon_type;

protected:
 Node_Caon_type root_node_;

public:
 node_graph(Node_Caon_type root_node) : root_node_(root_node){}

 ACCESSORS(Node_Caon_type ,root_node)
 Root_Caon_type root(){ return root_node_->template as<Root_Caon_type>(); }

};

template<typename DOMINION_Type,
   typename GALAXY_Type = typename DOMINION_Type::Galaxy_type>
class node_frame
{
 typedef node_frame<DOMINION_Type, GALAXY_Type> self;
 typedef typename GALAXY_Type::Frame_type Frame_type;
 typedef typename GALAXY_Type::Node_Caon_type Node_Caon_type;
 typedef typename GALAXY_Type::Connectors_type Connectors_type;
 typedef typename GALAXY_Type::Connectors_Caon_type Connectors_Caon_type;

public:
 struct Frame_With_Connector
 {
  Frame_type& frame;
  const Connectors_type& connector;
 };

 friend Frame_With_Connector operator /(Frame_type& frame,
  const Connectors_type& connector)
 {
  return {frame, connector};
 }

 void connect(Node_Caon_type node,
   const Connectors_type& connector, Node_Caon_type target)
 {
  node->connect(connector, target);
 }

};

template<typename DOMINION_Type,
   typename GALAXY_Type = typename DOMINION_Type::Galaxy_type,
   typename VERTEX_Type = typename GALAXY_Type::Root_Vertex_type>
class node_ptr
{
 typedef node_ptr<DOMINION_Type, GALAXY_Type> self;

protected:

 typedef self node_ptr_base_type;

 typedef typename GALAXY_Type::tString tString;
 typedef typename GALAXY_Type::Connectors_type Connectors_type;
 typedef typename GALAXY_Type::Type_Codes_type Type_Codes_type;
 typedef typename GALAXY_Type::Node_Caon_type Node_Caon_type;
 typedef typename GALAXY_Type::Connectors_Caon_type Connectors_Caon_type;
 typedef typename GALAXY_Type::Frame_type Frame_type;

 typedef typename GALAXY_Type::Root_Void_type Root_Void_type;

 Type_Codes_type type_code_;

 QMultiMap<Connectors_Caon_type, Node_Caon_type> targets_;

 typedef QMapIterator<Connectors_Caon_type, Node_Caon_type> targets_iterator_type;

 VERTEX_Type vertex_;

#ifdef RELAE_LABEL_NODES
 tString label_;
#endif


#ifdef NO_CAON
 template<typename T>
 node_ptr(T* v) :
  type_code_(dominion_get_type_code<DOMINION_Type, T>()),
  vertex_(
   (VERTEX_Type) v
   )
 {
 }
#else //NO_CAON
 template<typename T>
 node_ptr(caon_ptr<T> v) :
  type_code_(dominion_get_type_code<DOMINION_Type, T>()),
  vertex_(
   v.template caon_cast<VERTEX_Type>()
   )
 {
 }
#endif

public:

 struct Node_With_Connector {

  Node_Caon_type node;
  typename Frame_type::Frame_With_Connector frame_with_connector;

  friend void operator >>(const Node_With_Connector& lhs, Node_Caon_type rhs)
  {
   lhs.frame_with_connector.frame.connect(lhs.node,
     lhs.frame_with_connector.connector, rhs);
  }


 };

public:

 ACCESSORS(Type_Codes_type ,type_code)
 ACCESSORS(VERTEX_Type ,vertex)

 #ifdef RELAE_LABEL_NODES
  ACCESSORS(tString ,label)
 #else
  static void set_label(tString){}
  static tString label(){ return tString(); }
 #endif


 typedef DOMINION_Type Dominion_type;
 typedef GALAXY_Type Galaxy_type;


 void connect(const Connectors_type& connector, Node_Caon_type target)
 {
  targets_.insert(caon_ptr<Connectors_type>(&connector), target);
 }

 Node_Caon_type retrieve(const Connectors_type& connector)
 {
  return targets_.value(caon_ptr<Connectors_type>(&connector));
 }

 void match_relation(const Connectors_type& connector, QList<Node_Caon_type>& target_nodes)
 {
  targets_iterator_type it(targets_);
  while(it.hasNext())
  {
   it.next();
   Connectors_Caon_type con = it.key();
   if(con == caon_ptr<Connectors_type>(&connector))
   {
    // //  The question here is whether a single relations
    //    can appear multiple times in the list or
    //    just once with a list of targets.
    target_nodes.push_back(it.value());
   }
  }
 }

 bool match_relation(const Connectors_type& connector, Node_Caon_type target)
 {
  targets_iterator_type it(targets_);
  while(it.hasNext())
  {
   it.next();
   Connectors_Caon_type con = it.key();
   if(con == caon_ptr<Connectors_type>(&connector))
   {
    if(it.value() == target)
     return true;
   }
  }
  return false;
 }



 template<typename T>
 caon_ptr<T> as()
 {
  return vertex_.template as<T>();
 }

 friend Node_With_Connector operator<<(Node_Caon_type lhs, typename Frame_type::Frame_With_Connector rhs) //? Frame_With_Connector& rhs
 {
  return {lhs, rhs};
 }

};






#endif
