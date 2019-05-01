
#include "rz-ngml-tile.h"

#include "rzns.h"

USING_RZNS(NGML)


NGML_Tile::NGML_Tile(QString raw_text)
 :  raw_text_(raw_text)
{

}


QString NGML_Tile::thumbnail(int max_characters)
{
 QString result;
 if(raw_text_.size() > max_characters)
 {
  result += raw_text_.left(max_characters - 3) + "...";
 }
 else
 {
  result += raw_text_;
 }
 return result;
}

QString NGML_Tile::to_string()
{
 QString result = raw_text_;
 return result;
}


