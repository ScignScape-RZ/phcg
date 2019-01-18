
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


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

void RPH_Graph_Build::end_field()
{
 parse_context_.flags.multiline_field = false;
 acc_.clear();
}

void RPH_Graph_Build::read_acc(QString s)
{
 acc_ += s;
}

void RPH_Graph_Build::add_read_token(QString prefix, QString field, QString suffix)
{
 if(suffix == ".")
   parse_context_.flags.multiline_field = true;
}
