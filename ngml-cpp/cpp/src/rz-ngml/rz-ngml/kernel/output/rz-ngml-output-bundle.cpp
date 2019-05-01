
#include "rz-ngml-output-bundle.h"

#include "rzns.h"
USING_RZNS(NGML)

NGML_Output_Bundle NGML_Output_Bundle::with(QTextStream& new_qts) const
{
 return {new_qts, node, connection_descriptor, cb};
}

NGML_Output_Bundle NGML_Output_Bundle::with(NGML_Connection_Descriptor descriptor) const
{
 return {qts, node, descriptor, cb};
}

NGML_Output_Bundle NGML_Output_Bundle::with(caon_ptr<tNode> n, NGML_Connection_Descriptor descriptor) const
{
 return {qts, n, descriptor, cb};
}

NGML_Output_Bundle NGML_Output_Bundle::with_node(caon_ptr<tNode> n) const
{
 return {qts, n, connection_descriptor, cb};
}

NGML_Output_Bundle NGML_Output_Bundle::with_callback(caon_ptr<NGML_Command_Callback> c) const
{
 return {qts, node, connection_descriptor, c};
}



