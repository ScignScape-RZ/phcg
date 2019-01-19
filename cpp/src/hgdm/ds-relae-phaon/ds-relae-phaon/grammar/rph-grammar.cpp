
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


 Context prelude_context = add_context("prelude-context");
 track_context({&prelude_context});

 Context coda_context = add_context("coda-context");
 track_context({&coda_context});

 Context sample_context = add_context("sample-context");
 track_context({&sample_context});

 Context group_context = add_context("group-context");
 track_context({&group_context});

 Context read_context = add_context("read-context",
   {sample_context, group_context});

 activate(prelude_context);

 RPH_Parse_Context& parse_context = graph_build.parse_context();

 add_rule(flags_none_(parse_context ,multiline_field), read_context,
   "activate-coda-context",
   " \\n /& ",
   [&]
 {
  activate("coda-context");
 });

 add_rule(coda_context,
   "all-coda",
   " .* \\Z ",
   [&]
 {
  graph_build.add_coda_data(p.match_text());
 });

 add_rule(prelude_context,
   "activate-read-context",
   " \\n &/ (?= \\n) ",
   [&]
 {
  activate("read-context");
 });

 add_rule(prelude_context,
   "type-decl",
   " \\n &type .single-space.+ "
   "(?<name> \\S+) .single-space.+ "
   "(?<length> [[{] \\d+ [\\]}]) ",
   [&]
 {
  QString name = p.matched("name");
  QString length = p.matched("length");

  graph_build.add_type(name, length);
 });

 add_rule(prelude_context,
   "read-one-prelude-newline",
   " \\n ",
   [&]
 {
 });

 add_rule(flags_all_(parse_context ,multiline_field), read_context,
   "multiline-end-field",
   " \\n[.] (?= \\n) ",
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
   "start-sample",
   " \\n+!/ .single-space.* "
   " (?: (?<ty> \\S+ ) .single-space.* ) (?= \\n) ",
   [&]
 {
  QString ty = p.matched("ty");
  graph_build.start_sample(ty);
 });

 add_rule(read_context,
   "end-sample",
   " \\n/!\\n ",
   [&]
 {
  graph_build.end_sample();
 });

 add_rule(read_context,
   "read-acc-field",
   " [^\\n]+ (?= \\n ) ",
   [&]
 {
  QString s = p.match_text();
  graph_build.read_acc(s);
  if(!parse_context.flags.multiline_field)
    graph_build.end_field();
 });

// add_rule(read_context,
//   "end-field",
//   " (?= \\n ) ",
//   [&]
// {
//  graph_build.end_field();
// });

 add_rule( read_context, "prepare-field",
   "\\n"
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
}

