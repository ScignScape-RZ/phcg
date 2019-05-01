
#include "rz-ngml-paralex-tile.h"

#include "rzns.h"

USING_RZNS(NGML)


NGML_Paralex_Tile::NGML_Paralex_Tile(QString raw_text)
{
 kind_ = check_kind(raw_text);
}


QString NGML_Paralex_Tile::get_accent_as_html()
{
 return parse_accent_code_xml(command_ + " " + argument_);
}


NGML_Paralex_Tile::Kind NGML_Paralex_Tile::check_kind(QString key)
{
 if(key.startsWith('&'))
 {
  switch(key[1].toLatin1())
  {
  case '-':
   command_ = key[2];
   argument_ = key.mid(4);
   return Accent_With_Argument;
  case ':':
   argument_ = key.mid(2);
   argument_.chop(1);
   return Character_Entity_Reference;
  case '#':
   argument_ = key.mid(2);
   argument_.chop(1);
   return Numeric_Character_Reference;
  }
 }
 return parse_kind(key);
}


QString NGML_Paralex_Tile::thumbnail(int max_characters)
{
 return to_string();
}

QString NGML_Paralex_Tile::to_string()
{
 switch(kind_)
 {
 case M_Dash:
  return "\\{mdash}";
 }
 return QString();
}


