
#ifndef RPH_GRAMMAR__H
#define RPH_GRAMMAR__H

//#include "rz-parser/rz-regex.h"
//#include "rz-parser/rz-parser.h"
//#include "accessors.h"

#include "hgdm/relae-graph/relae-grammar.h"

#include "hgdm/phaon-graph/relae-phaon/kernel/relae-phaon-dominion.h"

#include "kans.h"


KANS_(HGDMCore)

class RPH_Graph;
class RPH_Graph_Build;
class RPH_Parser;

class RPH_Grammar : public Relae_Grammar<RPH_Graph, RPH_Parser>
{

public:

 RPH_Grammar();



 void init(RPH_Parser& p, RPH_Graph& g,
           RPH_Graph_Build& graph_build);


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
