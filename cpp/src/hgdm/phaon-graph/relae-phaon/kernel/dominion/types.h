
#define DOMINION_NODE_TYPE RPH_Node


#ifndef DOMINION_HIDE_NO_NAMESPACE
// // No namespace
#include "hgdm/relae-graph/dominion-macros.h"
DOMINION_TYPE(dbl, double, Double)
DOMINION_TYPE(integer, int, Int)
DOMINION_TYPE(i8, char, I8)
DOMINION_TYPE(qstring, QString, QStr)
#endif

#include "hgdm/relae-graph/dominion-macros.h"

#define DOMINION_OUTER_NAMESPACE KA


#define DOMINION_INNER_NAMESPACE HGDMCore
#include "hgdm/relae-graph/dominion-macros.h"
DOMINION_TYPE(rph_root, RPH_Root, RPH_Root)
DOMINION_TYPE(rph_token, RPH_Token, RPH_Token)
DOMINION_TYPE(rph_node_base, RPH_Node_Base, RPH_Node_Base)

#undef DOMINION_INNER_NAMESPACE

//#define DOMINION_INNER_NAMESPACE GBuild
//#include "relae-graph/dominion-macros.h"
////?
//DOMINION_TYPE(core_function, SE_Lisp_Graph_Core_Function, Graph_CoreFun)
//DOMINION_TYPE(cfn, SY_Lisp_Core_Function, Token_CoreFun)
//DOMINION_TYPE(null_value, SE_Null_Value, Null_Value)
////DOMINION_TYPE(cfn, RZ_Lisp_Core_Function, CoreFun)
//DOMINION_TYPE(empty_tuple, SE_Lisp_Empty_Tuple, EmptyTuple)
//#undef DOMINION_INNER_NAMESPACE

//#define DOMINION_INNER_NAMESPACE GVal
//#include "relae-graph/dominion-macros.h"
//DOMINION_TYPE(opc, SE_Opaque_Call, Opc)
//DOMINION_TYPE(ops, SE_Opaque_Symbol, Ops)
//DOMINION_TYPE(ots, SE_Opaque_Type_Symbol, Ots)
//DOMINION_TYPE(block_info, SE_Lisp_Graph_Block_Info, Block_Info)
//DOMINION_TYPE(rz_function_def_info, SE_Function_Def_Info, SE_Function_Def_Info)
//#undef DOMINION_INNER_NAMESPACE

#undef DOMINION_OUTER_NAMESPACE
#undef DOMINION_NODE_TYPE
