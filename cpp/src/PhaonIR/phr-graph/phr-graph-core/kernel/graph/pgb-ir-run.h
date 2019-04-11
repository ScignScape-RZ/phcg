
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PGB_IR_RUN__H
#define PGB_IR_RUN__H


#include "relae-graph/relae-node-ptr.h"

#include "phr-graph-core/kernel/phr-graph-dominion.h"

#include "accessors.h"

#include "multigraph-token.h"

#include <QTextStream>

#include "rzns.h"

struct MG_Token;

RZNS_(PhrGraphCore)

class PHR_Graph_Build;


class PGB_IR_Run
{
 PHR_Graph_Build& graph_build_;


public:

 PGB_IR_Run(PHR_Graph_Build& graph_build);

 void run_from_file(QString file);

 void run_lines(QString& lines);

 void run_line(QString line);

 void run_line(QString fn, QMultiMap<MG_Token_Kinds, QString>& mgts);

};

_RZNS(PhrGraphCore)



#endif // PGB_IR_RUN__H
