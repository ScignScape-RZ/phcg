
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

#include "phr-graph-core/token/phr-graph-fuxe-entry.h"
#include "phr-graph-core/token/phr-graph-statement-info.h"

#include "rzns.h"

USING_RZNS(PhrGraphCore)

#include <QDebug>

int main(int argc, char **argv)
{
 PHR_Graph pgr;

 PHR_Graph_PHR_Output pgo(DEFAULT_PHR_GEN_FOLDER "/t1.phr");

 pgo.document()->set_graph(&pgr);


 PHR_Graph_Frame& fr = PHR_Graph_Frame::instance();
 const PHR_Graph_Query& qy = PHR_Graph_Query::instance();


 caon_ptr<PHR_Graph_Root> rt = new PHR_Graph_Root(pgo.document().raw_pointer());
 caon_ptr<PHR_Graph_Node> rn = new PHR_Graph_Node(rt);

 pgr.set_root_node(rn);

 caon_ptr<PHR_Graph_Token> t1 = new PHR_Graph_Token("if-t-e");
 //t1->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n1 = new PHR_Graph_Node(t1);

// caon_ptr<PHR_Graph_Statement_Info> si = new
//   PHR_Graph_Statement_Info("x", "result", "\\=");
// caon_ptr<PHR_Graph_Node> sin = new PHR_Graph_Node(si);
// caon_ptr<PHR_Graph_Connection> sicion = new PHR_Graph_Connection(sin);
 rn << fr/qy.Statement_Entry >> n1;

 caon_ptr<PHR_Graph_Token> t2 = new PHR_Graph_Token("#<");
 t2->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n2 = new PHR_Graph_Node(t2);

 caon_ptr<PHR_Graph_Token> t3 = new PHR_Graph_Token("21", "u4");
 t3->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n3 = new PHR_Graph_Node(t3);

 caon_ptr<PHR_Graph_Token> t4 = new PHR_Graph_Token("23");
 t4->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n4 = new PHR_Graph_Node(t4);

 caon_ptr<PHR_Graph_Fuxe_Entry> f1 = new PHR_Graph_Fuxe_Entry("?result", "u4");
 caon_ptr<PHR_Graph_Node> fn1 = new PHR_Graph_Node(f1);
 caon_ptr<PHR_Graph_Connection> fc1 = new PHR_Graph_Connection("lambda", fn1);

 caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection("lambda");
 n1 << fr/qy.Channel_Fuxe_Entry(fc1) >> n2;
 n2 << fr/qy.Channel_Entry(cion) >> n3;
 n3 << fr/qy.Channel_Sequence >> n4;


// caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection("lambda");
// n1 << fr/qy.Channel_Entry(cion) >> n2;


 caon_ptr<PHR_Graph_Token> t5 = new PHR_Graph_Token("44", "u4");
 t5->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n5 = new PHR_Graph_Node(t5);

 //caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection("lambda");
 n2 << fr/qy.Channel_Continue >> n5;

 pgo.generate();

 qDebug() << "ok";
 return 0;
}


int main2(int argc, char **argv)
{
 PHR_Graph pgr;

 PHR_Graph_PHR_Output pgo(DEFAULT_PHR_GEN_FOLDER "/t1.phr");

 pgo.document()->set_graph(&pgr);


 PHR_Graph_Frame& fr = PHR_Graph_Frame::instance();
 const PHR_Graph_Query& qy = PHR_Graph_Query::instance();


 caon_ptr<PHR_Graph_Root> rt = new PHR_Graph_Root(pgo.document().raw_pointer());
 caon_ptr<PHR_Graph_Node> rn = new PHR_Graph_Node(rt);

 pgr.set_root_node(rn);

 caon_ptr<PHR_Graph_Token> t1 = new PHR_Graph_Token("#+");
 t1->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n1 = new PHR_Graph_Node(t1);

 caon_ptr<PHR_Graph_Statement_Info> si = new
   PHR_Graph_Statement_Info("x", "result", "\\=");
 caon_ptr<PHR_Graph_Node> sin = new PHR_Graph_Node(si);
 caon_ptr<PHR_Graph_Connection> sicion = new PHR_Graph_Connection(sin);
 rn << fr/qy.Statement_Entry(sicion) >> n1;

 caon_ptr<PHR_Graph_Token> t2 = new PHR_Graph_Token("#+");
 t2->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n2 = new PHR_Graph_Node(t2);

 caon_ptr<PHR_Graph_Token> t3 = new PHR_Graph_Token("21", "u4");
 t3->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n3 = new PHR_Graph_Node(t3);

 caon_ptr<PHR_Graph_Token> t4 = new PHR_Graph_Token("13");
 t4->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n4 = new PHR_Graph_Node(t4);

 caon_ptr<PHR_Graph_Fuxe_Entry> f1 = new PHR_Graph_Fuxe_Entry("result", "u4");
 caon_ptr<PHR_Graph_Node> fn1 = new PHR_Graph_Node(f1);
 caon_ptr<PHR_Graph_Connection> fc1 = new PHR_Graph_Connection("lambda", fn1);

 caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection("lambda");
 n1 << fr/qy.Channel_Fuxe_Entry(fc1) >> n2;
 n2 << fr/qy.Channel_Entry(cion) >> n3;
 n3 << fr/qy.Channel_Sequence >> n4;


// caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection("lambda");
// n1 << fr/qy.Channel_Entry(cion) >> n2;


 caon_ptr<PHR_Graph_Token> t5 = new PHR_Graph_Token("44", "u4");
 t5->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n5 = new PHR_Graph_Node(t5);

 //caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection("lambda");
 n2 << fr/qy.Channel_Continue >> n5;


 caon_ptr<PHR_Graph_Token> t6 = new PHR_Graph_Token("#+");
 t6->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n6 = new PHR_Graph_Node(t6);

 caon_ptr<PHR_Graph_Token> t7 = new PHR_Graph_Token("22", "u4");
 t7->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n7 = new PHR_Graph_Node(t7);

 caon_ptr<PHR_Graph_Connection> cion6 = new PHR_Graph_Connection("lambda");
 n6 << fr/qy.Channel_Entry(cion6) >> n7;

 caon_ptr<PHR_Graph_Token> t8 = new PHR_Graph_Token("x");
 caon_ptr<PHR_Graph_Node> n8 = new PHR_Graph_Node(t8);

 n7 << fr/qy.Channel_Sequence >> n8;

 caon_ptr<PHR_Graph_Statement_Info> si1 = new
   PHR_Graph_Statement_Info("x", "result", "\\=");
 caon_ptr<PHR_Graph_Node> sin1 = new PHR_Graph_Node(si1);
 caon_ptr<PHR_Graph_Connection> sicion1 = new PHR_Graph_Connection(sin1);
 n1 << fr/qy.Statement_Sequence(sicion1) >> n6;

 caon_ptr<PHR_Graph_Token> t9 = new PHR_Graph_Token("&prn");
 caon_ptr<PHR_Graph_Node> n9 = new PHR_Graph_Node(t9);

 caon_ptr<PHR_Graph_Token> t10 = new PHR_Graph_Token("x", "u4");
 caon_ptr<PHR_Graph_Node> n10 = new PHR_Graph_Node(t10);

 caon_ptr<PHR_Graph_Connection> cion9 = new PHR_Graph_Connection("lambda");
 n9 << fr/qy.Channel_Entry(cion9) >> n10;

 n6 << fr/qy.Statement_Sequence >> n9;

 n1->set_label("n1");

 pgo.generate();

 qDebug() << "ok";
 return 0;
}

int main1(int argc, char **argv)
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

 caon_ptr<PHR_Graph_Statement_Info> si = new
   PHR_Graph_Statement_Info("x", "result", "\\=");
 caon_ptr<PHR_Graph_Node> sin = new PHR_Graph_Node(si);
 caon_ptr<PHR_Graph_Connection> sicion = new PHR_Graph_Connection(sin);
 rn << fr/qy.Statement_Entry(sicion) >> n1;

 caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection("lambda");
 n1 << fr/qy.Channel_Entry(cion) >> n2;

 caon_ptr<PHR_Graph_Token> t3 = new PHR_Graph_Token("#+");
 t3->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n3 = new PHR_Graph_Node(t3);

 caon_ptr<PHR_Graph_Token> t4 = new PHR_Graph_Token("21", "u4");
 t4->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n4 = new PHR_Graph_Node(t4);

 caon_ptr<PHR_Graph_Token> t5 = new PHR_Graph_Token("13");
 t5->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n5 = new PHR_Graph_Node(t5);

// caon_ptr<PHR_Graph_Connection> cion = new PHR_Graph_Connection("lambda");

 caon_ptr<PHR_Graph_Fuxe_Entry> f1 = new PHR_Graph_Fuxe_Entry("result", "u4");
 caon_ptr<PHR_Graph_Node> fn1 = new PHR_Graph_Node(f1);
 caon_ptr<PHR_Graph_Connection> fc1 = new PHR_Graph_Connection(fn1);

 n2 << fr/qy.Channel_Fuxe_Entry(fc1) >> n3;
 n3 << fr/qy.Channel_Entry(cion) >> n4;
 n4 << fr/qy.Channel_Sequence >> n5;

 caon_ptr<PHR_Graph_Token> t6 = new PHR_Graph_Token("#+");
 t6->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n6 = new PHR_Graph_Node(t6);

 caon_ptr<PHR_Graph_Token> t7 = new PHR_Graph_Token("22", "u4");
 t7->flags.gen_raw_value = true;
 caon_ptr<PHR_Graph_Node> n7 = new PHR_Graph_Node(t7);

 caon_ptr<PHR_Graph_Connection> cion6 = new PHR_Graph_Connection("lambda");
 n6 << fr/qy.Channel_Entry(cion6) >> n7;

 caon_ptr<PHR_Graph_Token> t8 = new PHR_Graph_Token("x");
 caon_ptr<PHR_Graph_Node> n8 = new PHR_Graph_Node(t8);

 n7 << fr/qy.Channel_Sequence >> n8;

 caon_ptr<PHR_Graph_Statement_Info> si1 = new
   PHR_Graph_Statement_Info("x", "result", "\\=");
 caon_ptr<PHR_Graph_Node> sin1 = new PHR_Graph_Node(si1);
 caon_ptr<PHR_Graph_Connection> sicion1 = new PHR_Graph_Connection(sin1);
 n1 << fr/qy.Statement_Sequence(sicion1) >> n6;

 caon_ptr<PHR_Graph_Token> t9 = new PHR_Graph_Token("&prn");
 caon_ptr<PHR_Graph_Node> n9 = new PHR_Graph_Node(t9);

 caon_ptr<PHR_Graph_Token> t10 = new PHR_Graph_Token("x", "u4");
 caon_ptr<PHR_Graph_Node> n10 = new PHR_Graph_Node(t10);

 caon_ptr<PHR_Graph_Connection> cion9 = new PHR_Graph_Connection("lambda");
 n9 << fr/qy.Channel_Entry(cion9) >> n10;

 n6 << fr/qy.Statement_Sequence >> n9;

 n1->set_label("n1");

 pgo.generate();

 qDebug() << "ok";
 return 0;
}
