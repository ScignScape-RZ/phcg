
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RTXH_GRAMMAR__H
#define RTXH_GRAMMAR__H

//#include "rz-parser/rz-regex.h"
//#include "rz-parser/rz-parser.h"
//#include "accessors.h"

#include "relae-graph/relae-grammar.h"

#include "relae-phaon/kernel/relae-phaon-dominion.h"

#include "kans.h"


KANS_(HGDMCore)

class RTXH_Graph;
class RTXH_Graph_Build;
class RTXH_Parser;

class RTXH_Grammar : public Relae_Grammar<RTXH_Graph, RTXH_Parser>
{

public:

 RTXH_Grammar();



 void init(RTXH_Parser& p, RTXH_Graph& g,
           RTXH_Graph_Build& graph_build);


};

_KANS(SYCore)

//#include "rz-parser/rz-regex.h"
//#include "rz-parser/rz-parser.h"

//#include "rz-text-typedefs.h"

//class RZ_Text_Parser : public RZ_Parser<RZ_Text_Galaxy>
//{
//public:
// RZ_Text_Parser(RZ_Text_Graph* g);
// void set_raw_text(QString s);


//};

//typedef RZ_Parser<RZ_Text_Galaxy> RZ_Text_Parser;

#endif
