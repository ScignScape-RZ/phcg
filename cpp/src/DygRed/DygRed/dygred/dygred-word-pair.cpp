
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dygred-word-pair.h"

//#include "dygred-sentence.h"

DygRed_Word_Pair::DygRed_Word_Pair(DygRed_Word_Pos* uhead, DygRed_Word_Pos* udep)
  : uhead_(uhead), udep_(udep), shead_(nullptr), sdep_(nullptr),
    level(-1), pos(-1)
{

}
