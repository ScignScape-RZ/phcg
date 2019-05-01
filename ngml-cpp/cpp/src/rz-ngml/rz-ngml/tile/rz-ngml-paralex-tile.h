
#ifndef RZ_NGML_PARALEX_TILE__H
#define RZ_NGML_PARALEX_TILE__H

#include <QString>
#include <QMap>

#include "accessors.h"
#include "flags.h"

#include "whitespace/rz-ngml-whitespace-holder.h"

#include "rzns.h"

RZNS_(NGML)

class NGML_Paralex_Tile : public NGML_Whitespace_Holder
{
 enum Kind {
  N_A, M_Dash, N_Dash, Dollars, Less_Than,
   Greater_Than, Straight_Single_Quote,
   Accent_With_Argument, Character_Entity_Reference,
   Numeric_Character_Reference
  };

 Kind kind_;
 QString argument_;
 QString command_;

 Kind check_kind(QString key);

 static Kind parse_kind(QString key)
 {
  static QMap<QString, Kind> static_map {{
   {"%--", M_Dash}, {"%$", Dollars},
    {"%<", Less_Than}, {"%>", Greater_Than},
   {"%'", Straight_Single_Quote}
  }};
  return static_map.value(key, N_A);
 }

 static QString parse_accent_code_xml(QString key)
 {
  static QMap<QString, QString> static_map {{
   {"' e", "&eacute;"}, {"` e", "&egrave;"},
  }};
  return static_map.value(key, QString());
 }

public:

 NGML_Paralex_Tile(QString raw_text);

 QString to_string();

 QString thumbnail(int max_characters = 6);
 QString get_accent_as_html();

 template<typename T>
 void write_latex(T& t)
 {
  switch(kind_)
  {
  case M_Dash: t << "\\mdash{}"; break;
  case Dollars: t << "\\$"; break;
  case Less_Than: t << "$<$"; break;
  case Greater_Than: t << "$>$"; break;
  case Straight_Single_Quote: t << "{\\textquotesingle}"; break;
  case Accent_With_Argument: t << '\\' << command_ << '{' << argument_ << '}';
  //  case Character_Entity_Reference: t << ' '
  }
 }

 template<typename T>
 void write_html(T& t)
 {
  switch(kind_)
  {
  case M_Dash: t << "&mdash;"; break;
  case Dollars: t << "$"; break;
  case Less_Than: t << "&lt;"; break;
  case Greater_Than: t << "&gt;"; break;
  case Straight_Single_Quote: t << "'"; break;
  case Accent_With_Argument: t << get_accent_as_html(); break;
   //case Accent_With_Argument: t << '\\' << command_ << '{' << argument_ << '}';
  case Character_Entity_Reference: t << '&' << argument_ << ';'; break;
  }
 }

 template<typename T>
 void write_khif(T& t)
 {
  switch(kind_)
  {
  case M_Dash: t << "&mdash;"; break;
  case Dollars: t << "$"; break;
  case Less_Than: t << "&lt;"; break;
  case Greater_Than: t << "&gt;"; break;
  case Straight_Single_Quote: t << "'"; break;
  case Accent_With_Argument: t << get_accent_as_html(); break;
   //case Accent_With_Argument: t << '\\' << command_ << '{' << argument_ << '}';
  case Character_Entity_Reference: t << '&' << argument_ << ';'; break;
  }
 }

};

_RZNS(NGML)

#endif
