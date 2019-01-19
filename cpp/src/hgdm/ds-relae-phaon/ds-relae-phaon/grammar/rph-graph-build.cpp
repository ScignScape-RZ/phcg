
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
   ,fr_(RPH_Frame::instance())
   ,current_field_number_(0)
   //?,current_position_state_(Position_States::Root_Position)
{

}

void RPH_Graph_Build::init()
{

}

void RPH_Graph_Build::end_field()
{
 parse_context_.flags.multiline_field = false;
 if(flags.discard_acc)
 {
  flags.discard_acc = false;
  return;
 }
 if(flags.split_acc)
 {
  flags.split_acc = false;
  QStringList qsl = acc_.simplified().split(' ');
  for(QString qs : qsl)
  {
   add_read_token(qs);
   ++current_field_number_;
  }
 }
 else
 {
  add_read_token(acc_.trimmed());
 }
 acc_.clear();
}

void RPH_Graph_Build::read_acc(QString s)
{
 acc_ += s;
}

void RPH_Graph_Build::prepare_field_read(QString prefix, QString field, QString suffix)
{
 if(suffix == ".")
   parse_context_.flags.multiline_field = true;
 else if(suffix == "#")
   flags.split_acc = true;
 else if(suffix == ";")
   flags.discard_acc = true;
 if(prefix == "$$")
 {
  ++current_field_number_;
  current_field_name_.clear();
 }
 else if(prefix == "@@")
 {
  ++current_field_number_;
  current_field_name_.clear();
 }
 else if(prefix.startsWith('$'))
 {
  bool ok;
  current_field_number_ = field.toInt(&ok);
  current_field_name_ = ok? QString() : field;
 }
 else if(prefix.startsWith('@'))
 {
  current_field_number_ = field.toInt();
  current_field_name_.clear();
 }
 flags.array_field = prefix.startsWith('@');
}

void RPH_Graph_Build::add_read_token(QString text)
{

}

void RPH_Graph_Build::start_sample()
{

}

void RPH_Graph_Build::end_sample()
{

}
