
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "rph-grammar.h"

#include "rph-parse-context.h"

#include "rph-graph-build.h"

#include "rph-parser.h"

#include "hgdm/relae-graph/relae-parser.templates.h"

USING_KANS(HGDMCore)

RPH_Grammar::RPH_Grammar()
{
}

void RPH_Grammar::init(RPH_Parser& p, RPH_Graph& g, RPH_Graph_Build& graph_build)
{
 // //  Check for package privates...?
 pre_rule( "script-word", "(?:[^{}()\\[\\]\\s`;,:]|(?:\\w::?\\w))+" );
 pre_rule( "ns-word", "(?: [^{}()\\[\\]\\s`;,:]+ )" );

//? pre_rule( "space-to-end-of-line", "[__\\t]* (?: ;- [^\\n]+ )? (?= \\n )" );
//? pre_rule( "end-of-line", "[__\\t\\S]* \\n" );
 pre_rule( "single-space", "[__\\t]" );


 Context sample_context = add_context("sample-context");
 track_context({&sample_context});

 Context group_context = add_context("group-context");
 track_context({&group_context});

 Context read_context = add_context("read",
   {sample_context, group_context});


 activate(read_context);

 RPH_Parse_Context& parse_context = graph_build.parse_context();

 add_rule( read_context, "read-token",
  " (?<prefix> [@$]+ )"
  " (?<word> .script-word.?) "
  " (?<suffix> [:;#.] ) ",
   [&]
 {
  QString prefix = p.matched("prefix");
  QString f = p.matched("word");
  QString suffix = p.matched("suffix");

  graph_build.prepare_field_read(prefix, f, suffix);
 });

 add_rule(flags_all_(parse_context ,multiline_field), read_context,
   "multiline-end-field",
   " \\n[.]\\n ",
   [&]
 {
  //QString s = p.match_text();
  graph_build.end_field();
 });

 add_rule(flags_all_(parse_context ,multiline_field), read_context,
   "consume-newlines",
   " \\n+ ",
   [&]
 {
  QString s = p.match_text();
  graph_build.read_acc(s);
 });


 add_rule(read_context,
   "read-acc-field",
   " [^\\n]+ ",
   [&]
 {
  QString s = p.match_text();
  graph_build.read_acc(s);
 });

 add_rule(read_context,
   "end-field",
   " \\n ",
   [&]
 {
  graph_build.end_field();
 });

}

