
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-graph-core/kernel/graph/phr-graph.h"

#include "phr-graph-core/kernel/graph/pgb-ir-run.h"
#include "phr-graph-core/kernel/graph/phr-graph-build.h"
#include "phr-graph-core/kernel/graph/phr-graph.h"

#include "phr-graph-core/output/phr-graph-phr-output.h"
#include "phr-graph-core/kernel/document/phr-graph-document.h"

#include "rzns.h"

USING_RZNS(PhrGraphCore)

#include <QDebug>

int main(int argc, char **argv)
{
 PHR_Graph phg;
 PHR_Graph_Build phgb(phg);
 //PGB_IR_Run pgb(phgb);

//
//phgb.load_from_pgb_file(DEFAULT_PHR_FOLDER "/pgb/t1.gen.pgb");
 phgb.load_from_pgb_file(DEFAULT_PHR_FOLDER "/pgb/t1.pgb");
//?
 //pgb.run_from_file(DEFAULT_PHR_FOLDER "/pgb/t1.gen.pgb");
 //pgb.run_from_file("C:/scign/phcg/ar/scripts/rz/phaon" "/t1.rz.gen.pgb");
// phgb.load_from_pgb_file("C:/scign/phcg/ar/scripts/rz/phaon" "/t1.rz.gen.pgb");
//?
//PHR_Graph_PHR_Output pgo(DEFAULT_PHR_FOLDER "/pgb/t1.gen.pgb.phr");
 PHR_Graph_PHR_Output pgo(DEFAULT_PHR_FOLDER "/pgb/t1.gen.pgb.phr");
 //PHR_Graph_PHR_Output pgo("C:/scign/phcg/ar/scripts/rz/phaon" "/t1.rz.gen.pgbx.phr");

 pgo.document()->set_graph(&phg);

 pgo.generate();

 qDebug() << "ok";
 return 0;
}
