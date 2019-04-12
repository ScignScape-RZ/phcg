
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

class PGB_IR_Build
{
// PHR_Graph& graph_;
 QString out_file_;
 QString text_;
 QTextStream qts_;
// caon_ptr<PHR_Graph_Node> current_node_;

// PHR_Graph_Frame& fr_;
// const PHR_Graph_Query& qy_;

public:

 PGB_IR_Build(QString out_file);

 ACCESSORS(QString ,out_file)
 ACCESSORS__RGET(QTextStream ,qts)
 ACCESSORS__RGET(QString ,text)

 void make_root_node(QString target, MG_Token_Subgroups sg);
 void make_token_node(QString arg, MG_Token_Subgroups asg,
   QString target, MG_Token_Subgroups tsg);
 void add_block_entry_node(QString t1, MG_Token_Subgroups sg1,
   QString t2, MG_Token_Subgroups sg2);

 void add_channel_token(QString src, MG_Token_Subgroups srcsg,
   QString chn, QString tok, MG_Token_Subgroups toksg,
   QString target, MG_Token_Subgroups tsg);

 void end_line(QList<MG_Token>&& mgts);

 void generate_file();

 static MG_Token mgtoken(QString rt, MG_Token_Kind_Groups kg, MG_Token_Subgroups sg);



// caon_ptr<PHR_Graph_Node> add_block_entry_node(
//   caon_ptr<PHR_Graph_Node> source, caon_ptr<PHR_Graph_Node> target);

// caon_ptr<PHR_Graph_Node> make_token_node(MG_Token& mgt);
// caon_ptr<PHR_Graph_Node> make_token_node(MG_Token&& mgt)
// {
//  return make_token_node(mgt);
// }

// caon_ptr<PHR_Graph_Node> add_channel_raw_value_token(caon_ptr<PHR_Graph_Node> source,
//   QString channel, QString txt);


};

_RZNS(PhrGraphCore)



#endif // PGB_IR_BUILD__H
