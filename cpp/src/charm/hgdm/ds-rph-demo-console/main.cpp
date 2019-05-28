
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QString>
#include <QDebug>

#include <QVector>

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
 RPH_Document doc(DEFAULT_RPH_FOLDER  "/samples.txt");

 doc.parse();
 //qDebug() << *xx;

 RPH_Graph::hypernode_type* hn = doc.graph()->hypernodes()[0];

 doc.graph()->get_sf(hn, 4, [](QPair<QString, void*>& pr)
 {
  qDebug() << pr.first;
 });

 QVector<RPH_Graph::hypernode_type*>& hns = doc.top_level_hypernodes();

 for(RPH_Graph::hypernode_type* mhn : hns)
 {
  doc.graph()->get_sfs(mhn, {1,2,3}, [](QVector<QPair<QString, void*>>& prs)
  {
   QVector<quint16> nums = {0,0,0};
   std::transform(prs.begin(), prs.end(), nums.begin(), [](QPair<QString, void*>& pr)
   {
    return pr.first.toInt();
   });
   qDebug() << QString("s: %1 e: %2 p: %3").arg(nums[0]).arg(nums[1]).arg(nums[2]);
  });
 }


 return 0;
}

