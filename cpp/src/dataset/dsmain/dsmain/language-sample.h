
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef LANGUAGE_SAMPLE__H
#define LANGUAGE_SAMPLE__H

#include "kans.h"
#include "accessors.h"

#include <QVector>
#include <QString>


KANS_(DSM)

class Language_Sample_Group;

class Language_Sample
{
 QString text_;
 int index_;
 QString sub_index_;
 int chapter_;
 int page_;

 Language_Sample_Group* group_;

 int get_group_id();

public:

 Language_Sample(QString text);

 ACCESSORS(QString ,text)
 ACCESSORS(int ,index)
 ACCESSORS(QString ,sub_index)
 ACCESSORS(int ,chapter)
 ACCESSORS(int ,page)

 ACCESSORS(Language_Sample_Group* ,group)

 static void read_samples_from_file(QString path,
   QVector<Language_Sample*>& result,
  QVector<Language_Sample_Group*>& groups);

 QString get_serialization();

 Language_Sample_Group* get_ref_group();

};


_KANS(DSM)

#endif // LANGUAGE_SAMPLE__H
