
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-graph-core/kernel/graph/phr-graph.h"

#include "phr-graph-core/output/phr-graph-phr-output.h"
#include "phr-graph-core/kernel/graph/phr-graph-node.h"
#include "phr-graph-core/kernel/graph/phr-graph-connection.h"

#include "phr-graph-core/kernel/phr-graph-root.h"
#include "phr-graph-core/token/phr-graph-token.h"
#include "phr-graph-core/kernel/document/phr-graph-document.h"

#include "phr-graph-core/kernel/frame/phr-graph-frame.h"
#include "phr-graph-core/kernel/query/phr-graph-query.h"

#include "rzns.h"

USING_RZNS(PhrGraphCore)

#include <QDebug>

int main(int argc, char **argv)
{
 PHR_Graph pgr;

 PHR_Graph_PHR_Output pgo(DEFAULT_PHR_GEN_FOLDER "/t1.phr");

 pgo.document()->set_graph(&pgr);

 caon_ptr<PHR_Graph_Root> rt = new PHR_Graph_Root(pgo.document().raw_pointer());
 caon_ptr<PHR_Graph_Node> rn = new PHR_Graph_Node(rt);

 pgr.set_root_node(rn);

 caon_ptr<PHR_Graph_Token> t1 = new PHR_Graph_Token("#+");
 t1->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n1 = new PHR_Graph_Node(t1);

 caon_ptr<PHR_Graph_Token> t2 = new PHR_Graph_Token("44", "u4");
 t2->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n2 = new PHR_Graph_Node(t2);

 PHR_Graph_Frame& fr = PHR_Graph_Frame::instance();
 const PHR_Graph_Query& qy = PHR_Graph_Query::instance();

 rn << fr/qy.Statement_Entry >> n1;

 caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection("lambda");
 n1 << fr/qy.Channel_Entry(cion) >> n2;

 caon_ptr<PHR_Graph_Token> t3 = new PHR_Graph_Token("#+");
 t3->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n3 = new PHR_Graph_Node(t3);

 caon_ptr<PHR_Graph_Token> t4 = new PHR_Graph_Token("21", "u4");
 t4->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n4 = new PHR_Graph_Node(t4);

 caon_ptr<PHR_Graph_Token> t5 = new PHR_Graph_Token("3", "u4");
 t5->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n5 = new PHR_Graph_Node(t5);

// caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection("lambda");

 n2 << fr/qy.Channel_Fuxe_Entry(cion) >> n3;
 n3 << fr/qy.Channel_Entry(cion) >> n4;
 n4 << fr/qy.Channel_Sequence >> n5;

 pgo.generate();

 qDebug() << "ok";
 return 0;
}
