
#ifndef RPH_PARSE_CONTEXT__H
#define RPH_PARSE_CONTEXT__H

#include "hgdm/relae-graph/relae-parser.h"

#include "flags.h"

#include "kans.h"
KANS_(HGDMCore)

//USING_RZNS(RECore)

class RPH_Graph;
class RPH_Node;

//flag_(1, inside_tag_body);
//flag_(2, inside_tag_command_main_argument);
//flag_(3, pre_markup);

class RPH_Parse_Context
{
 typedef RPH_Node tNode;

public:
 flags_(1)
  flag_(1, inside_comment)
  flag_(2, end_parse)
 _flags_

private:
//? caon_ptr<RPH_Node> current_open_print_node_;

public:

 RPH_Parse_Context();

};

_KANS(HGDMCore)

#endif
