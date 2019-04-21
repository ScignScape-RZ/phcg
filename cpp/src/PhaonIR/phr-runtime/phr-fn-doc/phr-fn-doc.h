
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_FN_DOC__H
#define PHR_FN_DOC__H


#include "kans.h"

#include "phaon-ir/types/phr-universal-class.h"
#include "accessors.h"

#include <QString>
#include <QObject>
#include <QMap>

class PHR_Scope_System;
class PHR_Env;
class PHR_Type_Object;

class PHR_Fn_Doc : public QObject, public PHR_Universal_Class
{
 Q_OBJECT

 PHR_Scope_System* scopes_;
 PHR_Env* penv_;

 QMap<QString, QMap<QString, QString>> docus_;

 QString held_fn_;

public:

 PHR_Fn_Doc();

 PHR_Fn_Doc(const PHR_Fn_Doc& rhs);

 ~PHR_Fn_Doc();

 ACCESSORS(PHR_Scope_System* ,scopes)

 ACCESSORS(QString ,held_fn)

 Q_INVOKABLE void read(QString fn);
 Q_INVOKABLE void init(PHR_Env* penv);
 Q_INVOKABLE void kph_gen(QString subs);

 Q_INVOKABLE void hold_function_name(QString fn);

 Q_INVOKABLE void add_documentation(QString key_val);

 Q_INVOKABLE void test();

 const PHR_Type_Object* get_type_object_from_symbol_name(QString fn);

 QString test_summary();

 void kph_gen(const PHR_Type_Object* kto, QString fn, QString& text);

};


Q_DECLARE_METATYPE(PHR_Fn_Doc)
Q_DECLARE_METATYPE(PHR_Fn_Doc*)

#endif //PHR_FN_DOC__H
