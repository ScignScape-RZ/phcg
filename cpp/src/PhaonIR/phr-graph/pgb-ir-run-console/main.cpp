
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-graph-core/kernel/graph/phr-graph.h"

#include "phr-graph-core/kernel/graph/pgb-ir-run.h"
#include "phr-graph-core/kernel/graph/phr-graph-build.h"
#include "phr-graph-core/kernel/graph/phr-graph.h"

#include "rzns.h"

USING_RZNS(PhrGraphCore)

#include <QDebug>

int main(int argc, char **argv)
{
 PHR_Graph phg;
 PHR_Graph_Build phgb(phg);
 PGB_IR_Run pgb(phgb);

 pgb.run_from_file(DEFAULT_PHR_FOLDER "/pgb/t1.pgb");

 qDebug() << "ok";
 return 0;
}
