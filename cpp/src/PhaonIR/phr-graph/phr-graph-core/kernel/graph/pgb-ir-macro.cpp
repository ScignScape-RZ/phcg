
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "pgb-ir-macro.h"

#include "pgb-ir-build.h"


#include "multigraph-token.h"

#include "rzns.h"

USING_RZNS(PhrGraphCore)

PGB_IR_Macro::PGB_IR_Macro(QString mn, QList<MG_Token>& mgts)
 : macro_(parse_macro(mn)), mgts_(mgts)
{

}

void PGB_IR_Macro::write_expand(PGB_IR_Build& pgb,
  QList<PGB_IR_Build::Text_With_Purpose>& tps)
{
 switch(macro_)
 {
 case add_empty_channel:
  break;

 }
}



