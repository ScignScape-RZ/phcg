
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DYGRED_CBS_EMBED_INCLUDE
#include "dygred-deprel-callbacks.h"
#include "dygred-sentence.h"

namespace {
void init_cbs()
{
 DygRed_Deprel_Callbacks cbs;
#endif

cbs.add_cb("claims", "amod", [](QString dp, DygRed_Sentence& dgs, word& w,
           DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw, DygRed_Word_Pos** rr) -> QString
{
 hdgw->claim_parent(dgw, "amod", 0, 0);
 hdgw->set_super(dgw);
 if(rr && hdgw == *rr)
   *rr = dgw;
 return QString();
});

#ifndef DYGRED_CBS_EMBED_INCLUDE
}}
#endif
