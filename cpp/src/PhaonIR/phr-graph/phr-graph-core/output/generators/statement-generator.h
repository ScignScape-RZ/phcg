
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef STATEMENT_GENERATOR__H
#define STATEMENT_GENERATOR__H

#include "accessors.h"
#include "flags.h"

#include "kernel/query/phr-graph-query.h"
#include "kernel/frame/phr-graph-frame.h"

#include <QTextStream>
#include <QMap>

#include <functional>

#include "rzns.h"
RZNS_(PhrGraphCore)

class PHR_Graph_Node;
class PHR_Graph_Token;

class Statement_Generator
{

 //const PHR_Graph_Frame& fr_;
 const PHR_Graph_Query& rq_;

public:

 Statement_Generator();

 void generate_close(QTextStream& qts);

 void generate_from_node(QTextStream& qts,
  const PHR_Graph_Node& node);

 void generate_from_fn_node(QTextStream& qts,
  PHR_Graph_Token& tok, QString channel_name, const PHR_Graph_Node& arg_node);

 void generate_arg_carriers(QTextStream& qts,
  QString channel_name, const PHR_Graph_Node& arg_node);

 void generate_carrier_with_symbol(QTextStream& qts,
  PHR_Graph_Token& tok);

 void generate_carrier_with_raw_value(QTextStream& qts,
  PHR_Graph_Token& tok);

};

_RZNS(PhrGraphCore)

#endif //PHR_GRAPH_PHR_OUTPUT__H
