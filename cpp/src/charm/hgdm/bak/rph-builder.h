
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RPH_BUILDER__H
#define RPH_BUILDER__H


#include "phaong/phaong.h"
#include "phaong/phaong-types.h"


#include "kans.h"
#include "accessors.h"

#include <type_traits>

#include <QVector>
#include <QString>

class QTextStream;


KANS_(DSM)

class Language_Sample_Group;

class RPH_Builder //: phaong<pg_t>::Hypernode
{
 QTextStream& qts_;

public:

 RPH_Builder(QTextStream& qts);

 void enter(QString type_name);
 void leave();

 void sf(QString field_name, QString val);
 void msf(QString field_name, QString val);
 void ssf(QString field_name, QString val);

 void array_append();
 void top_append();

 template<typename T>
 void nsf(QString field_name, T val)
 {
  sf(field_name, QString::number(val));
 }

 void el(int i = 1);

 void add_array_type_entry(QString type_name, QString codes);
 void add_structure_type_entry(QString type_name, QString codes);

 template<typename... Ts>
 static QString join(QString sep, Ts... vals)
 {
  QStringList qsl;
  std::vector<typename std::common_type<Ts...>::type> vec {vals...};
  std::transform(vec.begin(), vec.end(),
    std::back_inserter(qsl),[](typename std::common_type<Ts...>::type val)
  {
   return QString::number(val);
  });
  return qsl.join(sep);
 }

 template<typename... Ts>
 static QString join(QChar sep, Ts... vals)
 {
  join(QString(sep), vals...);
 }

 template<typename... Ts>
 static QString join(Ts... vals)
 {
  join(QString(" "), vals...);
 }

 template<typename... Ts>
 void nsf(QString field_name, Ts... vals)
 {
  ssf(field_name, join(vals...));
 }

 template<typename... Ts>
 void enter_array_type(QString type_name, Ts... vals)
 {
  add_array_type_entry(type_name, join(';', vals...));
 }

 template<typename... Ts>
 void enter_structure_type(QString type_name, Ts... vals)
 {
  add_structure_type_entry(type_name, join(';', vals...));
 }

 void leave_type();

 void _add_type_fields(QList<QStringList>& fs, int start = 0);

 void add_type_fields(QString qs, int start = 0);

 void atf(QString& qs);


 void leave_prelude();
 void enter_coda();

};


_KANS(DSM)

#endif // RPH_BUILDER__H