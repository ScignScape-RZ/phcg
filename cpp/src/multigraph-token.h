
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef MULTIGRAPH_TOKEN__H
#define MULTIGRAPH_TOKEN__H

#include <QString>
#include <QMap>

enum class MG_Token_Kinds
{
 N_A, Generic, Raw_Symbol, Raw_Value, String_Literal,
 Arg_Raw_Symbol, Arg_Raw_Value, Target, Known_Target
};

struct MG_Token
{
 MG_Token_Kinds kind;
 QString raw_text;

 QPair<int, int> to_number_pair() const
 {
  int ind = raw_text.indexOf('-');
  if(ind == -1)
  {
   return {0, 0};
  }
  return {raw_text.left(ind).toInt(), raw_text.mid(ind + 1).toInt()};
 }

 static QString get_assignment_kind_name(QString tok)
 {
  static QMap<QString, QString> static_map {{
   { "<<|", "formula" },
   { "<<||", "formula-reinit" },
   }};
  return static_map.value(tok, "generic");
 }

 QString to_number_pair_split_string()
 {
  QString result = raw_text;
  int ind = raw_text.indexOf('-');
  if(ind == -1)
  {
   return QString();
  }
  result[ind] = ' ';
  return result;
 }

 QString first_number_to_string() const
 {
  int ind = raw_text.indexOf('-');
  if(ind == -1)
  {
   return raw_text;
  }
  return raw_text.left(ind);
 }

 int first_number() const
 {
  return first_number_to_string().toInt();
 }

 QString second_number_to_string() const
 {
  int ind = raw_text.indexOf('-');
  if(ind == -1)
  {
   return raw_text;
  }
  return raw_text.mid(ind + 1);
 }

 int second_number() const
 {
  return second_number_to_string().toInt();
 }

 MG_Token to_kind(MG_Token_Kinds k)
 {
  return {k, raw_text};
 }

 void clear()
 {
  raw_text.clear();
  kind = MG_Token_Kinds::N_A;
 }

 bool has_text()
 {
  return !raw_text.isEmpty();
 }

 static MG_Token Null()
 {
  return {MG_Token_Kinds::N_A, QString()};
 }

 static MG_Token check_as(MG_Token_Kinds k1, MG_Token_Kinds k2, QString qs)
 {
  return { (k1 == MG_Token_Kinds::N_A?k2:k1), qs};
 }


 static MG_Token decode_symbol(QString str)
 {
  if(str.startsWith(":|"))
    str = str.mid(2);
  if(str.endsWith('|'))
    str.chop(1);
  return decode(str);
 }

 static MG_Token decode(QString str)
 {
  static QMap<QString, MG_Token_Kinds> static_map {{
#define TEMP_MACRO(X, Y) {Y, MG_Token_Kinds::X},

  TEMP_MACRO(Raw_Symbol, "__@")
  TEMP_MACRO(Raw_Value, "__$")
  TEMP_MACRO(Generic, "|||")

  TEMP_MACRO(Arg_Raw_Symbol, ">_@")
  TEMP_MACRO(Arg_Raw_Value, ">_$")
  TEMP_MACRO(Target, "<->")
  TEMP_MACRO(Known_Target, "<!>")

#undef TEMP_MACRO
  }};

  if(str.startsWith('"'))
  {
   return {MG_Token_Kinds::String_Literal, str};
  }
  else
  {
   QString prefix = str.left(3);
   return {static_map.value(prefix, MG_Token_Kinds::Generic), str.mid(3)};
  }
 }

 QString get_encode_prefix()
 {
  static QMap<MG_Token_Kinds, QString> static_map {{

#define TEMP_MACRO(X, Y) {MG_Token_Kinds::X, Y},

  TEMP_MACRO(Raw_Symbol, "__@")
  TEMP_MACRO(Raw_Value, "__$")
  TEMP_MACRO(Generic, "|||")

  TEMP_MACRO(Arg_Raw_Symbol, ">_@")
  TEMP_MACRO(Arg_Raw_Value, ">_$")
  TEMP_MACRO(Target, "<->")
  TEMP_MACRO(Known_Target, "<!>")

#undef TEMP_MACRO
  }};

  return static_map.value(kind);
 }

 QString escaped_raw_text()
 {
  QString result = raw_text;
  if(result.startsWith(":|"))
  {
   result.insert(1, '\\');
   result.insert(result.size() - 1, '\\');
  }
  return result;
 }

 QString encode()
 {
  switch(kind)
  {
  case MG_Token_Kinds::String_Literal:
   return QString("\"%1\"").arg(raw_text);

  default:
   return QString(":|%1%2|").arg(get_encode_prefix()).arg(escaped_raw_text());
   //return QString("%1%2").arg(get_encode_prefix()).arg(raw_text);
  }
 }
};


#endif //MULTIGRAPH_TOKEN__H
