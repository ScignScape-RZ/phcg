
#include "qyscript-graph.h"

//#include "sy-node.h"

//#include "kernel/sy-root.h"

#include "token/qyscript-token.h"

//#include "tuple/sy-tuple-info.h"
//#include "code/sy-call-entry.h"
//#include "code/sy-block-entry.h"

///#include "kernel/graph/sy-connection.h"

#include "syns.h"

USING_QYNS(QYSGraph)

QY_Script_Graph::QY_Script_Graph(QY_Hyper_Node root_node)
 //?: node_graph<SY_Dominion>(root_node)
{

}

void QY_Script_Graph::report(QTextStream& qts)
{
//? if(caon_ptr<SY_Root> root = root_node_->sy_root())
// {
//  qts << "Root node: " << root->document_path();
// }
 report_from_node(qts, root_node_);
}

void QY_Script_Graph::report_from_node(QTextStream& qts,
 QY_Hyper_Node node, int indent)
{
#ifdef HIDE
 QString padding(indent, ' ');
 qts << "\n" << padding;
 if(caon_ptr<SY_Token> token = node.sy_token())
 {
  qts << "[token= " << token->string_summary() << "]";
 }
 else if(caon_ptr<SY_Call_Entry> rce = node.re_call_entry())
 {
  CAON_PTR_DEBUG(SY_Call_Entry ,rce)
  QString extra;
  if(!rce->prefix().isEmpty())
  {
   extra = QString(" (%1) ").arg(rce->prefix());
  }
  if(rce->flags.no_normalize)
  {
   extra += "nn";
  }
  if(rce->flags.no_anticipate)
  {
   extra += "na";
  }
  qts << QString("<call %1%2>").arg(rce->call_id()).arg(extra);
 }
 else if(caon_ptr<SY_Block_Entry> rbe = node.re_block_entry())
 {
  qts << QString("<block %1:%2>").arg(rbe->call_id()).arg(rbe->nested_depth());
 }
 else if(caon_ptr<SY_Tuple_Info> rti = node.re_tuple_info())
 {
  if(rti->is_entry())
   qts << QString("<data %1 ...>").arg(rti->data_id());
  else
   qts << "<... data>";
 }
 else
 {
  qts << "<<node/" << node.label() << ">>";
 }
  //Run_Data_Entry
 node.each_connection([this, node, &qts, &padding, &indent]
  (const SY_Connectors& connector, const SY_Node& target, const SY_Connection* connection)
 {
  // //   For debugging...
  QString label = node.label();

  // //  Somehow, this connector is causing trouble
  if(connector.case_label == SY_Connectors_Case_Labels::Run_Fundef_Map_Key_Sequence)
  {
   //?return;
  }


  // //  This connector loops ...
  if(connector.case_label == SY_Connectors_Case_Labels::Parent_Block_Map)
  {
   qts << "\n\n" << padding << "Has connection: " << connector.label() << "\n";
   return;
  }

  qts << "\n\n" << padding << "For connection: " << connector.label() << "\n"
      << padding << "==== ";

  if(connection)
  {
   qts << "\n\n" << padding << "Annotated: \n";

   if(caon_ptr<SY_Node> cn = connection->re_node())
   {
    qts << " [[" << cn->label() << "]]\n";
   }

   qts << padding << "---- ";

  }

  report_from_node(qts, target, indent + 1);
  qts << "\n" << padding << "....";
 });
 //report_from_node(root_node_);

#endif//def HIDE
}
