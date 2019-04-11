
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-graph-build.h"

#include "phr-graph.h"

#include "kernel/phr-graph-root.h"

#include "token/phr-graph-token.h"

//#include "tuple/rz-re-tuple-info.h"
//#include "code/rz-re-call-entry.h"
//#include "code/rz-re-block-entry.h"
#include "kernel/graph/phr-graph-connection.h"

#include "rzns.h"

USING_RZNS(PhrGraphCore)

PHR_Graph_Build::PHR_Graph_Build(PHR_Graph& graph)
 : graph_(graph)
{

}
