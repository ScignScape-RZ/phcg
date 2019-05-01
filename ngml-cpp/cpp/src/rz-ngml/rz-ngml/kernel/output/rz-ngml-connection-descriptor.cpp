
#include "rz-ngml-connection-descriptor.h"

#include "rzns.h"
USING_RZNS(NGML)

NGML_Connection_Descriptor::NGML_Connection_Descriptor(Descriptors descriptor)
 : descriptor_(descriptor)
{

}

QString NGML_Connection_Descriptor::to_string(QString left, QString right)
{
 QString result = left;
 if(right.isEmpty())
  right = left;
 switch(descriptor_)
 {
// case Call_Entry: result += "CE"; break;
// case Call_Sequence: result += "CS"; break;
// case Cross_Sequence: result += "CX"; break;
// case Call_Continue: result += "CC"; break;
 }
 result += right;
 return result;
}
