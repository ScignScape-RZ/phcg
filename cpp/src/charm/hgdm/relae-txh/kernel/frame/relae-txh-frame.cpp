
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "relae-txh-frame.h"

#include "kernel/graph/relae-txh-node.h"

#include "kans.h"

#include <QDebug>


USING_KANS(HGDMCore)

RTXH_Frame::RTXH_Frame()
 : node_frame<RTXH_Dominion>()
{


}

RTXH_Frame& RTXH_Frame::instance()
{
 static RTXH_Frame* the_instance = nullptr;
 if(!the_instance)
  the_instance = new RTXH_Frame;
 return *the_instance;
}
