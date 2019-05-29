
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

#include "language-sample-group.h"
#include "language-sample.h"

#include "kans.h"
USING_KANS(HGDMCore)

USING_KANS(DSM)



int main(int argc, char **argv)
{
 RPH_Document doc(DEFAULT_RPH_FOLDER  "/samples.txt");

 doc.parse();
 //qDebug() << *xx;

 RPH_Graph::hypernode_type* hn = doc.graph()->hypernodes()[0];

// doc.graph()->get_sf(hn, 4, [](QPair<QString, void*>& pr)
// {
//  qDebug() << pr.first;
// });

 QVector<RPH_Graph::hypernode_type*>& hns = doc.top_level_hypernodes();

 QVector<Language_Sample_Group*> lsgs;
 lsgs.resize(hns.size());

 int count = 0;

 std::transform(hns.begin(), hns.end(), lsgs.begin(), [&count,&doc](RPH_Graph::hypernode_type* hn)
 {
  Language_Sample_Group* result = new Language_Sample_Group(count);

  doc.graph()->get_sfs(hn, {1,2,3}, [result](QVector<QPair<QString, void*>>& prs)
  {
   QVector<quint16> nums = {0,0,0};
   std::transform(prs.begin(), prs.end(), nums.begin(), [](QPair<QString, void*>& pr)
   {
    return pr.first.toInt();
   });
   result->set_start_num(nums[0]);
   result->set_end_num(nums[1]);
   result->set_page(nums[2]);
  });

  doc.graph()->all_afs(hn, [&doc](QPair<QString, void*>& pr)
  {
   RPH_Graph::hypernode_type* ihn = (RPH_Graph::hypernode_type*) pr.second;
   doc.graph()->get_sf(ihn, 3, [](QPair<QString, void*>& ipr)
   {
    qDebug() << ipr.first;
   });
   //Language_Sample* ls = ()
   //qDebug() << pr.first;
  });

  return result;
 });

 for(Language_Sample_Group* lsg : lsgs)
 {
   qDebug() << QString("s: %1 e: %2 p: %3").arg(lsg->start_num()).arg(lsg->end_num())
               .arg(lsg->page());
  //});
 }


 return 0;
}

