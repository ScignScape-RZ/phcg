
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

PGB_IR_Macro::Macros PGB_IR_Macro::parse_macro(QString key)
{
#define TEMP_MACRO(x) {#x, Macros::x},

 static QMap<QString, Macros> static_map {{
  TEMP_MACRO(add_empty_channel)
 }};

#undef TEMP_MACRO

 return static_map.value(key.toLower(), Macros::N_A);
}


void PGB_IR_Macro::write_expand(PGB_IR_Build& pgb,
  QList<PGB_IR_Build::Text_With_Purpose>& tps)
{
 switch(macro_)
 {
 case Macros::add_empty_channel:
  break;

 }
}



