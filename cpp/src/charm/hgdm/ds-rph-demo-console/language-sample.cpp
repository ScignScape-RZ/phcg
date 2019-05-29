
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "language-sample.h"

#include "language-sample-group.h"

#include "phaong/phaong-types.h"

#include <QDebug>
#include <QTextStream>

#include "textio.h"

#include "rph-builder.h"

USING_KANS(DSM)
USING_KANS(TextIO)

Language_Sample::Language_Sample(Language_Sample_Group* group, QString text)
  :  text_(text), group_(group)
{
// phg.new_hypernode(this, 6, {"Language_Sample", nullptr});

// {
//  int phaong_data_index = 0;
//  phg.PHAONG_DATA(QString ,text);
//  phg.PHAONG_DATA(QString ,source_title);
//  phg.PHAONG_DATA(int ,index);
//  phg.PHAONG_DATA(QString ,sub_index);
//  phg.PHAONG_DATA(int ,chapter);
//  phg.PHAONG_DATA(int ,page);
// }

}

void Language_Sample::serialize(QTextStream& qts)
{
 RPH_Builder rphb(qts);
 rphb.enter("SE");

 if(!latex_label_.isEmpty())
 {
  rphb.sf("x", latex_label_);
 }
 rphb.msf("t", text_);

 rphb.leave();

// qts << "!/ SE";

}

//int Language_Sample::get_group_id()
//{
// if(group_)
// {
//  return group_->id();
// }
// return 0;
//}

