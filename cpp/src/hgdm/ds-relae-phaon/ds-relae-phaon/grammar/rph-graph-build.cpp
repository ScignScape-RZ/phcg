
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "rph-graph-build.h"

#include "hgdm/phaon-graph/relae-phaon/kernel/frame/relae-phaon-frame.h"

#include "hgdm/phaon-graph/relae-phaon/kernel/graph/relae-phaon-graph.h"

USING_KANS(HGDMCore)


RPH_Graph_Build::RPH_Graph_Build(RPH_Document* d, RPH_Parser& p, RPH_Graph& g)
 : Flags(0)
   ,document_(d)
   ,graph_(g)
   ,parser_(p)
   ,fr_(RPH_Frame::instance())
   ,current_field_number_(0)
   ,current_hypernode_(nullptr)
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

void RPH_Graph_Build::add_type(QString name, QString length)
{
 QStringList ls = length.mid(1, length.size() - 2).split(';');

 int l = ls[0].toInt();
 signed int cs, offs;
 if(ls.size() > 1)
   cs = ls[1].toInt();
 else
   cs = -1;

 if(ls.size() > 2)
   offs = ls[2].toInt();
 else
   offs = -1;

 if(length.startsWith('{'))
 {
  graph_.add_structure_type(name, l, offs);
 }
 else if(length.startsWith('['))
 {
  graph_.add_array_type(name, l, cs, offs);
 }
}

void RPH_Graph_Build::add_coda_data(QString qs)
{

}

void RPH_Graph_Build::add_read_token(QString text)
{

}

void RPH_Graph_Build::start_sample(QString ty)
{
 current_hypernode_ = graph_.new_hypernode_by_type_name(ty);
// phaong<pg_t>::Hypernode* hn = pg.new_hypernode(5);
// pg.set_sf(hn, 0, {"xx", nullptr}, {"QString", nullptr});

}

void RPH_Graph_Build::end_sample()
{

}
