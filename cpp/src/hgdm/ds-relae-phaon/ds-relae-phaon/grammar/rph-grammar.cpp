
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

 Context read_context = add_context("read-context");

 track_context({&read_context});

// Context run_or_print_context = add_context("run-or-print",
// {run_context, print_context});


 activate(read_context);

 RPH_Parse_Context& parse_context = graph_build.parse_context();

 add_rule( read_context, "read-token",
  " (?<prefix> [@$]+ )"
  " (?<word> .script-word.?) "
  " (?<suffix> [:.] ) ",
   [&]
 {
  QString prefix = p.matched("prefix");
  QString m = p.matched("word");
  QString suffix = p.matched("suffix");

  graph_build.add_read_token(prefix, m, suffix);
 });

}

