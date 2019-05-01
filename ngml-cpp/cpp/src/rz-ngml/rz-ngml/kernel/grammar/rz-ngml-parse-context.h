
#ifndef RZ_NGML_PARSE_CONTEXT__H
#define RZ_NGML_PARSE_CONTEXT__H

#include "rz-relae/relae-parser.h"

#include "flags.h"

#include "rzns.h"
RZNS_(NGML)


class NGML_Graph;
class NGML_Node;


class NGML_Parse_Context
{
 typedef NGML_Node tNode;

public:
 flags_(1)
  flag_(1, inside_khif_tile);
  flag_(2, inside_multiline_comment);
  flag_(3, inside_tag_body);
  flag_(4, inside_html_tag_body);
  flag_(5, inside_html_tag_attribute_single_quote);
  flag_(6, inside_html_tag_attribute_double_quote);
  flag_(7, inside_html_script_tag);
  flag_(8, inside_html_style_tag);
 _flags_

public:

 NGML_Parse_Context();

};

_RZNS(NGML)

#endif
