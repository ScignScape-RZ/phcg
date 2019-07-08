
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RTXH_GRAPH_BUILD__H
#define RTXH_GRAPH_BUILD__H

#include "flags.h"

#include "accessors.h"

#include "grammar/rtxh-parse-context.h"

#include "kernel/graph/relae-txh-graph.h"

#include <QStack>


#include "kans.h"
KANS_(HGDMCore)

//USING_RZNS(RECore)

class RTXH_Graph;
class RTXH_Node;
class RTXH_Document;
class RTXH_Parser;
class RTXH_Graph;
class RTXH_Frame;


//flag_(1, inside_tag_body);
//flag_(2, inside_tag_command_main_argument);
//flag_(3, pre_markup);

class RTXH_Graph_Build
{
public:

 flags_(1)
  bool discard_acc:1;
  bool split_acc:1;
  bool array_field:1;
  bool numeric_acc:1;
  bool replace_acc:1;
  bool wildcard_acc:1;
  bool define_replacement:1;
 _flags

 typedef RTXH_Graph::hypernode_type hypernode_type;
 typedef RTXH_Graph::numeric_index_type numeric_index_type;

private:


 QString acc_;

 RTXH_Parse_Context parse_context_;


 RTXH_Document* document_;
 RTXH_Parser& parser_;
 RTXH_Graph& graph_;

 RTXH_Frame& fr_;

 int current_field_number_;
 QString current_field_name_;
 QString current_type_name_;

 int current_type_field_index_;

 hypernode_type* current_hypernode_;
 hypernode_type* last_hypernode_;

 QStack<hypernode_type*> parent_hypernodes_;

 QVector<hypernode_type*> top_level_hypernodes_;

 QMap<QString, QString> replacements_;

public:

 RTXH_Graph_Build(RTXH_Document* d, RTXH_Parser& p, RTXH_Graph& g);

 ACCESSORS__RGET(RTXH_Parse_Context ,parse_context)
 ACCESSORS__RGET(QVector<hypernode_type*> ,top_level_hypernodes)


 void init();

 void array_append();
 void add_read_token(QString text);
 void add_numeric_read_token(numeric_index_type val);

 void top_level_append();

 void prepare_field_read(QString prefix, QString field, QString suffix);
 void read_acc(QString s);
 void end_field();

 void add_type(QString name, QString length);

 void add_type_field_index(QString name, int code = 0);

 void start_sample(QString ty);
 void end_sample();

 void add_coda_data_line(QString qs);
};

_KANS(HGDMCore)

#endif

