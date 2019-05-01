
#include "rz-ngml-node.h"

#include "rzns.h"
USING_RZNS(NGML)

QString NGML_Node::debug_connectors() const
{
 QString result;
 targets_iterator_type it(targets_);
 while(it.hasNext())
 {
  it.next();
  QString connector = it.key()->label();
  caon_ptr<NGML_Node> target = it.value();
  CAON_PTR_DEBUG(NGML_Node ,target)
  result += QString("\n |%1| %2").arg(connector).arg(target->label());

 }
 return result;
}
