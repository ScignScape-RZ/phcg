
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-graph-block-info.h"

#include <QRegularExpression>

#include <QDebug>

#include "rzns.h"

USING_RZNS(PhrGraphCore)

PHR_Graph_Block_Info::PHR_Graph_Block_Info(QString anchor_name,
  QString channel_name, QString anchor_kind)
 :  anchor_name_(anchor_name), channel_name_(channel_name), anchor_kind_(anchor_kind)
{
}


