
#include "sy-frame.h"

#include "kernel/graph/sy-node.h"

#include "syns.h"

#include <QDebug>


USING_SYNS(SYCore)

SY_Frame::SY_Frame()
 : node_frame<SY_Dominion>()
{


}

SY_Frame& SY_Frame::instance()
{
 static SY_Frame* the_instance = nullptr;
 if(!the_instance)
  the_instance = new SY_Frame;
 return *the_instance;
}
