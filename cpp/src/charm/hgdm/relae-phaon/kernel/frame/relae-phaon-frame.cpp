
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "relae-phaon-frame.h"

#include "kernel/graph/relae-phaon-node.h"

#include "kans.h"

#include <QDebug>


USING_KANS(HGDMCore)

RPH_Frame::RPH_Frame()
 : node_frame<RPH_Dominion>()
{


}

RPH_Frame& RPH_Frame::instance()
{
 static RPH_Frame* the_instance = nullptr;
 if(!the_instance)
  the_instance = new RPH_Frame;
 return *the_instance;
}
