
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef LANGUAGE_SAMPLE_GROUP__H
#define LANGUAGE_SAMPLE_GROUP__H

#include "kans.h"
#include "accessors.h"

#include <QVector>
#include <QString>


KANS_(DSM)

class Language_Sample;

class Language_Sample_Group : public QVector<Language_Sample*>
{
 int id_;
 int page_;

 int start_num_;
 int end_num_;

public:

 Language_Sample_Group(int id);


 ACCESSORS(int ,id)
 ACCESSORS(int ,page)

 ACCESSORS(int ,start_num)
 ACCESSORS(int ,end_num)

};


_KANS(DSM)

#endif // LANGUAGE_SAMPLE_GROUP__H
