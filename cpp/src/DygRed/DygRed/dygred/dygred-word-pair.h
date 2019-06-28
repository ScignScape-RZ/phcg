
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DYGRED_WORD_PAIR__H
#define DYGRED_WORD_PAIR__H


#include "udpipe.h"

#include "accessors.h"

class DygRed_Sentence;
class DygRed_Word_Pos;

class DygRed_Word_Pair
{
 DygRed_Word_Pos* uhead_;
 DygRed_Word_Pos* udep_;

 DygRed_Word_Pos* shead_;
 DygRed_Word_Pos* sdep_;

 int level;
 int pos;

public:

 DygRed_Word_Pair(DygRed_Word_Pos* uhead, DygRed_Word_Pos* udep);

 ACCESSORS(DygRed_Word_Pos* ,uhead)
 ACCESSORS(DygRed_Word_Pos* ,udep)
 ACCESSORS(DygRed_Word_Pos* ,shead)
 ACCESSORS(DygRed_Word_Pos* ,sdep)


};


#endif
