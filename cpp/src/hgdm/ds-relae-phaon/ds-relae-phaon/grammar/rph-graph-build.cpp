
#include "rph-graph-build.h"

#include "hgdm/phaon-graph/relae-phaon/kernel/frame/relae-phaon-frame.h"

USING_KANS(HGDMCore)


RPH_Graph_Build::RPH_Graph_Build(RPH_Document* d, RPH_Parser& p, RPH_Graph& g)
 : Flags(0)
   ,document_(d)
   ,graph_(g)
   ,parser_(p)
   ,current_line_(1)
   ,fr_(RPH_Frame::instance())
   //?,current_position_state_(Position_States::Root_Position)
{

}

void RPH_Graph_Build::init()
{

}


