
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QString>
#include <QDebug>


#include "hgdm/phaon-graph/phaong/phaong.h"
#include "hgdm/phaon-graph/phaong/phaong-types.h"


#include "hgdm/phaon-graph/relae-phaon/kernel/graph/relae-phaon-node.h"
#include "hgdm/phaon-graph/relae-phaon/kernel/frame/relae-phaon-frame.h"
#include "hgdm/phaon-graph/relae-phaon/kernel/query/relae-phaon-query.h"

#include "ds-relae-phaon/rph-document.h"

#include "kans.h"
USING_KANS(HGDMCore)



int main(int argc, char **argv)
{
 RPH_Document doc(DEFAULT_RPH_FOLDER  "/t1.txt");

 doc.parse();
 //qDebug() << *xx;

 return 0;
}

