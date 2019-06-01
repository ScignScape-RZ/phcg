
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "language-sample-group.h"

#include "language-sample.h"

#include <QDebug>

#include "textio.h"

#include <QTextStream>

#include "rph-builder/rph-builder.h"

USING_KANS(DSM)
USING_KANS(RPH)
USING_KANS(TextIO)

Language_Sample_Group::Language_Sample_Group(int id)
  :  id_(id), page_(0), start_num_(0), end_num_(0)
{

}

void Language_Sample_Group::serialize(QTextStream& qts)
{
 RPH_Builder rphb(qts);
 rphb.enter("SG");
 rphb.nsf("i", id_);

 rphb.el();
 for(Language_Sample* ls : *this)
 {
  ls->serialize(qts);
  rphb.array_append();
  rphb.el();
 }
 rphb.el();


 rphb.nsf("s", page_, start_num_, end_num_);

 rphb.leave();
 rphb.top_append();

 rphb.el();

// qts << "!/ SE";


}

void Language_Sample_Group::serialize_samples_to_file(
  QVector<Language_Sample_Group*>& lsgs, QString file)
{
 QString text;

 QTextStream qts(&text);

 RPH_Builder rphb(qts);

 rphb.add_prelude_comment(
    R"|(g=group id  t=text  s=start id
    e=end id  i=id  p=page  x=tex label
    h=theme

    SG=sentence group
    SE=sentence example)|");

 rphb.enter_array_type("SG", 8,4,2);
 rphb.add_type_fields({{"g"},{"s"},{"e"},{"p"}});
 //rphb.add_type_fields("g, i, x, t text, h");
 rphb.leave_type();
 rphb.el();

 rphb.enter_structure_type("SE", 5);
 rphb.add_type_fields({{"g"},{"i"},{"x"},{"t","text"},{"h"}});
 //rphb.add_type_fields("g, i, x, t text, h");
 rphb.leave_type();
 rphb.el();

 rphb.leave_prelude();
 rphb.el();

 for(Language_Sample_Group* lsg: lsgs)
 {
  lsg->serialize(qts);
 }

 rphb.el();

 rphb.enter_coda();
 rphb.el();

 save_file(file, text);
}

