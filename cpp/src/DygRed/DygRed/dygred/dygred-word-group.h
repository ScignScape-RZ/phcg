
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DYGRED_WORD_GROUP__H
#define DYGRED_WORD_PROUP__H


#include "udpipe.h"

#include "accessors.h"

#include <QSet>

class DygRed_Sentence;
class DygRed_Word_Pos;

class DygRed_Word_Group
{
 QString kind_;

 QSet<DygRed_Word_Pos*> poss_;

 DygRed_Word_Pos* urep_;
 DygRed_Word_Pos* rep_;
 DygRed_Word_Pos* leaf_;


public:

 DygRed_Word_Group(QString kind);

 ACCESSORS(QString ,kind)
 ACCESSORS(DygRed_Word_Pos* ,urep)
 ACCESSORS(DygRed_Word_Pos* ,rep)
 ACCESSORS(DygRed_Word_Pos* ,leaf)

 ACCESSORS__RGET(QSet<DygRed_Word_Pos*> ,poss)

 QList<DygRed_Word_Pos*> inner_list();

 int size()
 {
  return poss_.size();
 }

 void check_add(DygRed_Word_Pos* dgw);

 void check_add(DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw);

 DygRed_Word_Pos* urep_to_rep();
 DygRed_Word_Pos* non_urep_to_rep();
 DygRed_Word_Pos* non_urep();
 DygRed_Word_Pos* non_rep();
};


#endif
