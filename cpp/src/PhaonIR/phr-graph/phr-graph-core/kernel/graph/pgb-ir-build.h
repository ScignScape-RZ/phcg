
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PGB_IR_BUILD__H
#define PGB_IR_BUILD__H


#include "relae-graph/relae-node-ptr.h"

#include "phr-graph-core/kernel/phr-graph-dominion.h"

#include "accessors.h"

#include "multigraph-token.h"

#include <QTextStream>

#include "rzns.h"

struct MG_Token;

RZNS_(PhrGraphCore)

class PHR_Graph;
class PHR_Graph_Frame;
class PHR_Graph_Query;

class _PGB_IR_Build
{
 QTextStream& qts_;

public:

 _PGB_IR_Build(QTextStream& qts);

 ACCESSORS__RGET(QTextStream ,qts)


 void make_root_node(QString target, MG_Token_Subgroups sg);
 void make_root_node(QString target)
 {
  make_root_node(target.mid(1), get_subgroup(target[0]));
 }

 void make_statement_info_node(QString anchor_name,
   MG_Token_Subgroups asg, QString channel_name,
   MG_Token_Subgroups csg, QString anchor_kind,
   MG_Token_Subgroups aksg, QString target, MG_Token_Subgroups tsg);
 void make_statement_info_node(QString anchor_name,
   QString channel_name, QString anchor_kind, QString target)
 {
  make_statement_info_node(anchor_name.mid(1), get_subgroup(anchor_name[0]),
    channel_name.mid(1), get_subgroup(channel_name[0]),
    anchor_kind.mid(1), get_subgroup(anchor_kind[0]),
    target.mid(1), get_subgroup(target[0]));
 }

 void make_token_node(QString arg, MG_Token_Subgroups asg,
   QString target, MG_Token_Subgroups tsg);
 void make_token_node(QString arg, QString target)
 {
  make_token_node(arg.mid(1), get_subgroup(arg[0]),
    target.mid(1), get_subgroup(target[0]));
 }

 void add_block_entry_node(QString t1, MG_Token_Subgroups sg1,
   QString t2, MG_Token_Subgroups sg2);
 void add_block_entry_node(QString t1, QString t2)
 {
  add_block_entry_node(t1.mid(1), get_subgroup(t1[0]),
    t2.mid(1), get_subgroup(t2[0]));
 }

 void add_statement_sequence_node(QString t1, MG_Token_Subgroups sg1,
   QString t2, MG_Token_Subgroups sg2);
 void add_statement_sequence_node(QString t1, QString t2)
 {
  add_statement_sequence_node(t1.mid(1), get_subgroup(t1[0]),
    t2.mid(1), get_subgroup(t2[0]));
 }

 void add_channel_token(QString src, MG_Token_Subgroups srcsg,
   QString tok, MG_Token_Subgroups toksg,
   QString target, MG_Token_Subgroups tsg);
 void add_channel_token(QString src,
   QString tok, QString target)
 {
  add_channel_token(src.mid(1), get_subgroup(src[0]),
    tok.mid(1), get_subgroup(tok[0]),
    target.mid(1), get_subgroup(target[0]));
 }

 void add_channel_entry_token(QString src, MG_Token_Subgroups srcsg,
   QString chn, QString tok, MG_Token_Subgroups toksg,
   QString target, MG_Token_Subgroups tsg);
 void add_channel_entry_token(QString src, QString chn,
   QString tok, QString target)
 {
  add_channel_entry_token(src.mid(1), get_subgroup(src[0]), chn,
    tok.mid(1), get_subgroup(tok[0]),
    target.mid(1), get_subgroup(target[0]));
 }


 void copy_value(QString t1, MG_Token_Subgroups sg1,
   QString t2, MG_Token_Subgroups sg2);
 void copy_value(QString t1, QString t2)
 {
  copy_value(t1.mid(1), get_subgroup(t1[0]),
    t2.mid(1), get_subgroup(t2[0]));
 }

 void end_line(QList<MG_Token>&& mgts);

 MG_Token_Subgroups get_subgroup(QChar c);


 void generate_file();

 static MG_Token mgtoken(QString rt, MG_Token_Kind_Groups kg, MG_Token_Subgroups sg);

};

class PGB_IR_Build
{
 QString out_file_;
 //QString text_;
 QTextStream qts_;

public:

 PGB_IR_Build(QString out_file);

 ACCESSORS(QString ,out_file)

 _PGB_IR_Build operator()(QString& qs);
 _PGB_IR_Build operator()(QStringList& qsl);
 _PGB_IR_Build operator[](QStringList& qsl);

 void generate_file(QStringList& qsl);

// ACCESSORS__RGET(QTextStream ,qts)
// ACCESSORS__RGET(QString ,text)

 //PGB_IR_Build::PGB_IR_Build(QString out_file)
 // :  out_file_(out_file), qts_(&text_)

};

_RZNS(PhrGraphCore)



#endif // PGB_IR_BUILD__H
