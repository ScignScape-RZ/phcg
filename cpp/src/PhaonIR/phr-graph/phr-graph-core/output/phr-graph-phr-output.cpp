
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-graph-phr-output.h"

#include "kernel/document/phr-graph-document.h"

#include "kernel/graph/phr-graph.h"
#include "kernel/graph/phr-graph-node.h"

#include "kernel/phr-graph-root.h"

#include "token/phr-graph-token.h"

#include "token/phr-graph-token.h"

#include "textio.h"
USING_KANS(TextIO)

#include "rzns.h"
USING_RZNS(PhrGraphCore)


PHR_Graph_PHR_Output::PHR_Graph_PHR_Output(QString outpath, QString inpath)
 : PHR_Graph_Output(nullptr), output_path_(outpath)
{
 document_ = new PHR_Graph_Document(inpath);
}

void PHR_Graph_PHR_Output::generate(QTextStream& qts)
{
 qts << "yy";
}

void PHR_Graph_PHR_Output::generate()
{
 QString text;
 QTextStream qts(&text);
 generate(qts);
 save_file(output_path_, text);
}

