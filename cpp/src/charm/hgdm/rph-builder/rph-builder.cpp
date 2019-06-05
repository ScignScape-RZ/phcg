
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "rph-builder.h"


#include <QDebug>
#include <QTextStream>



USING_KANS(RPH)

RPH_Builder::RPH_Builder(QTextStream& qts)
  : qts_(qts)
{

}

void RPH_Builder::enter(QString type_name)
{
 qts_ << "\n!/" << type_name;
}

void RPH_Builder::leave()
{
 qts_ << "\n/!";
}

void RPH_Builder::leave_type()
{
 qts_ << ';';
}

void RPH_Builder::leave_prelude()
{
 qts_ << "\n&/";
}

void RPH_Builder::enter_coda()
{
 qts_ << "\n/&";
}

void RPH_Builder::add_replacement(QString key, QString val)
{
 qts_ << "\n%" << key << ": " << val;
}

void RPH_Builder::el(int i)
{
 for(int j = 0; j < i; ++j)
   qts_ << "\n";
}

void RPH_Builder::add_array_type_entry(QString type_name, QString codes)
{
 qts_ << "\n&" << type_name << " [" << codes << "] ";
}

void RPH_Builder::add_structure_type_entry(QString type_name, QString codes)
{
 qts_ << "\n&" << type_name << " {" << codes << "} ";
}

void RPH_Builder::ssf(QString field_name, QString val)
{
 qts_ << "\n$" << field_name << "# " << val;
}


void RPH_Builder::sf(QString field_name, QString val)
{
 qts_ << "\n$" << field_name << ": " << val;
}

void RPH_Builder::msf(QString field_name, QString val)
{
 qts_ << "\n$" << field_name << ". " << val << "\n.";
}

void RPH_Builder::array_append()
{
 qts_ << "\n<>>";
}

void RPH_Builder::top_append()
{
 qts_ << "\n<+>";
}

void RPH_Builder::add_type_fields(QString qs, int start)
{
 QList<QStringList> fs;

 QStringList qsl = qs.split(",", QString::SplitBehavior::SkipEmptyParts);

 for(QString iqs : qsl)
 {
  QStringList iqsl = iqs.simplified().split(' ');
  fs.push_back(iqsl);
 }

 add_type_fields(fs, start);
}

void RPH_Builder::add_type_fields(QList<QStringList>&& fs, int start)
{
 add_type_fields(fs, start);
}

void RPH_Builder::add_type_fields(QList<QStringList>& fs, int start)
{
 int i = start;
 for(QStringList& qsl : fs)
 {
  qts_ << "\n ";
  for(QString qs : qsl)
  {
   qts_ << ':' << qs << ':' << i << ' ';
  }
  ++i;
 }
}

void RPH_Builder::add_prelude_comment(QString qs)
{
 qts_ << "\n- " << qs << "\n.\n";
}

void RPH_Builder::add_sl_comment(QString qs)
{
 qts_ << ";;- " << qs << '\n';
}

void RPH_Builder::add_ml_comment(QString qs)
{
 qts_ << "\n;;-- " << qs << "\n --;;";
}



