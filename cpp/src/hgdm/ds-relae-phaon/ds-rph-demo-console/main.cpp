
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QString>
#include <QDebug>


#include "phaong/phaong.h"
#include "phaong/phaong-types.h"


#include "relae-phaon/kernel/graph/relae-phaon-node.h"
#include "relae-phaon/kernel/frame/relae-phaon-frame.h"
#include "relae-phaon/kernel/query/relae-phaon-query.h"

#include "relae-phaon/kernel/graph/relae-phaon-graph.h"

#include "ds-relae-phaon/rph-document.h"

#include "kans.h"
USING_KANS(HGDMCore)



int main(int argc, char **argv)
{
 RPH_Document doc(DEFAULT_RPH_FOLDER  "/demo.txt");

 doc.parse();
 //qDebug() << *xx;

 RPH_Graph::hypernode_type* hn = doc.graph()->hypernodes()[0];

 doc.graph()->get_sf(hn, 3, [](QPair<QString, void*>& pr)
 {
  qDebug() << pr.first;
 });

 return 0;
}

