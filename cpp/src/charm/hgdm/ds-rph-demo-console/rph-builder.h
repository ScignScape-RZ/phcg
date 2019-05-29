
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

 template<typename... Ts>
 void nsf(QString field_name, Ts... vals)
 {
  QStringList qsl;
  std::vector<typename std::common_type<Ts...>::type> vec {vals...};
  std::transform(vec.begin(), vec.end(),
    std::back_inserter(qsl),[](typename std::common_type<Ts...>::type val)
  {
   return QString::number(val);
  });
  ssf(field_name, qsl.join(' '));
 }



};


_KANS(DSM)

#endif // RPH_BUILDER__H
