
#ifndef RZ_NGML_OUTPUT_BASE__H
#define RZ_NGML_OUTPUT_BASE__H

#include "rz-relae/relae-node-ptr.h"

#include "kernel/rz-ngml-dominion.h"

#include "kernel/query/rz-ngml-query.h"

#include <QString>
#include <QTextStream>

#include "accessors.h"

#include "rzns.h"

RZNS_(NGML)

class NGML_Graph;
class NGML_Document;


class NGML_Output_Base
{
protected:

 NGML_Graph& graph_;
 NGML_Document& document_;

 const NGML_Query& qry_;

public:


 NGML_Output_Base(NGML_Document& document);
 virtual void generate(QTextStream& qts) = 0;


};

_RZNS(NGML)


#endif
