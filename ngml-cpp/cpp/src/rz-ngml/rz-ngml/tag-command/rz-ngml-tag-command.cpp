
#include "rz-ngml-tag-command.h"

#include "rzns.h"
USING_RZNS(NGML)


NGML_Tag_Command::NGML_Tag_Command(QString name, QString parent_tag_type)
 : Flags(0), name_(name), parent_tag_type_(parent_tag_type)
{

}


QString NGML_Tag_Command::latex_name()
{
 QString result = name_;
 result.remove('-');
 return result;
}

