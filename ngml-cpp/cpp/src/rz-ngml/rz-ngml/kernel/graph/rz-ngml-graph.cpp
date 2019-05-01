
#include "rz-ngml-graph.h"
#include "rz-ngml-node.h"

#include "rzns.h"

USING_RZNS(NGML)

NGML_Graph::NGML_Graph(caon_ptr<NGML_Node> root_node)
 : node_graph<NGML_Dominion>(root_node)
{

}
