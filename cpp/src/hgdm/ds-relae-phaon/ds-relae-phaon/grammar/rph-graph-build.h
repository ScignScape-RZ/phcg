
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RPH_GRAPH_BUILD__H
#define RPH_GRAPH_BUILD__H

#include "flags.h"

#include "accessors.h"

#include "grammar/rph-parse-context.h"

#include "kans.h"
KANS_(HGDMCore)

//USING_RZNS(RECore)

class RPH_Graph;
class RPH_Node;
class RPH_Document;
class RPH_Parser;
class RPH_Graph;
class RPH_Frame;


//flag_(1, inside_tag_body);
//flag_(2, inside_tag_command_main_argument);
//flag_(3, pre_markup);

class RPH_Graph_Build
{
public:

 flags_(1)
  bool next_token_closes_expression:1;
  bool inside_array_with_formation:1;
 _flags

 QString acc_;

 RPH_Parse_Context parse_context_;


 RPH_Document* document_;
 RPH_Parser& parser_;
 RPH_Graph& graph_;

 RPH_Frame& fr_;

 int current_line_;


public:

 RPH_Graph_Build(RPH_Document* d, RPH_Parser& p, RPH_Graph& g);

 ACCESSORS__RGET(RPH_Parse_Context ,parse_context)

 void init();

};

_KANS(HGDMCore)

#endif

