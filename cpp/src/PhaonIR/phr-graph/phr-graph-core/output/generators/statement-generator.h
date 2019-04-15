
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef STATEMENT_GENERATOR__H
#define STATEMENT_GENERATOR__H

#include "accessors.h"
#include "flags.h"

#include "phr-graph-core/kernel/query/phr-graph-query.h"
#include "phr-graph-core/kernel/frame/phr-graph-frame.h"

#include <QTextStream>
#include <QMap>

#include <functional>

#include "rzns.h"
RZNS_(PhrGraphCore)

class PHR_Graph_Node;
class PHR_Graph_Token;

class Expression_Generator;
class PHR_Graph_Statement_Info;

class Statement_Generator
{

 //const PHR_Graph_Frame& fr_;
 const PHR_Graph_Query& rq_;

 Expression_Generator& expression_generator_;

public:

 Statement_Generator(Expression_Generator& expression_generator);

 void generate_close(QTextStream& qts, PHR_Graph_Statement_Info* sin);

 void generate_from_node(QTextStream& qts,
  const PHR_Graph_Node& node, PHR_Graph_Statement_Info* si);

 void generate_anchor_without_channel_group(QTextStream& qts,
  const PHR_Graph_Node& node, PHR_Graph_Statement_Info& sin) ;


};

_RZNS(PhrGraphCore)

#endif // STATEMENT_GENERATOR__H
