
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef LANGUAGE_SAMPLE__H
#define LANGUAGE_SAMPLE__H


#include "phaong/phaong.h"
#include "phaong/phaong-types.h"


#include "kans.h"
#include "accessors.h"

#include <QVector>
#include <QString>

class QTextStream;


KANS_(DSM)

class Language_Sample_Group;

class Language_Sample //: phaong<pg_t>::Hypernode
{
 QString text_;
 QString latex_label_;

 Language_Sample_Group* group_;
 QString classification_;

public:

 Language_Sample(Language_Sample_Group* group, QString text);

 ACCESSORS(QString ,text)
 ACCESSORS(QString ,latex_label)
 ACCESSORS(QString ,classification)

 ACCESSORS(Language_Sample_Group* ,group)

 QString get_form();
 QString get_issue();

 void serialize(QTextStream& qts);

};


_KANS(DSM)

#endif // LANGUAGE_SAMPLE__H
