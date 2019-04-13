
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-phaon-output.h"
#include "rzns.h"

#include "rz-phaon-block.h"

#include "phr-graph-core/kernel/graph/pgb-ir-build.h"

USING_RZNS(GVal)

RZ_Phaon_Output::RZ_Phaon_Output(RZ_Graph_Visitor_Phaon& visitor_phaon)
  :  visitor_phaon_(visitor_phaon), top_level_block_(nullptr)
{
}

void RZ_Phaon_Output::init_function_def_syntax()
{
}

void RZ_Phaon_Output::init_top_level_block()
{
 top_level_block_ = new RZ_Phaon_Block();
}


void RZ_Phaon_Output::build_phaon_graph(PGB_IR_Build& pgb)
{
 //caon_ptr<PHR_Graph_Node> n =
   //?pgb.make_root_node("!current_node");
 //phgb.set_current_node(n);
 if(top_level_block_)
 {
  top_level_block_->scan_top_level(pgb, visitor_phaon_);
  top_level_block_->build_phaon_graph(pgb);
 }
}
