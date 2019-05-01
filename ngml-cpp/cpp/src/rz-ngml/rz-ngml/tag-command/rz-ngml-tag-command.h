
#ifndef RZ_NGML_TAG_COMMAND__H
#define RZ_NGML_TAG_COMMAND__H

#include <QString>

#include "accessors.h"
#include "flags.h"

#include "whitespace/rz-ngml-whitespace-holder.h"

#include "rzns.h"

RZNS_(NGML)

class NGML_Tag_Command : public NGML_Whitespace_Holder
{
public:

 flags_(2)
  bool is_environment:1;
  bool is_closed:1;
  bool is_html:1;
  bool is_auto_closed:1;
  bool is_tag_assertion:1;
  bool is_tag_query:1;
  bool is_understood_auto_closed:1;
  bool has_main_tile:1;
  bool has_entry:1;
  bool has_attribute_tile:1;
 _flags

public:

 QString name_;
 QString parent_tag_type_;

public:

 ACCESSORS(QString ,name)
 ACCESSORS(QString ,parent_tag_type)

 NGML_Tag_Command(QString name, QString parent_tag_type = QString());

 QString latex_name();

};

_RZNS(NGML)

#endif
