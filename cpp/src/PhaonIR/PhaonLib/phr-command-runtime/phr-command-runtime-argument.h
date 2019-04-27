
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_COMMAND_RUNTIME_ARGUMENT__H
#define PHR_COMMAND_RUNTIME_ARGUMENT__H

#include <QtGlobal>


#include <functional>

#include <QMetaProperty>
#include <QVector>

#include <QObject>
#include <QMetaObject>

//#include "kans.h"

#include "accessors.h"

//KANS_(CMD)

class PHR_Command_Runtime_Argument
{
public:

  enum class Value_Classification
  {
   N_A, Generic_Ptr, QObject_Ptr, PCV_Ptr,
   Raw_Value_String_Ptr, Raw_Int, Raw_QReal
  };

private:

 QString type_name_;
 void* raw_value_;
 QString bind_code_;

 Value_Classification value_classification_;

 const QMetaObject* qmo_;
 const QMetaObject* pqmo_;
 const QMetaType* qmt_;

public:

 PHR_Command_Runtime_Argument();

 ACCESSORS(Value_Classification ,value_classification)
 ACCESSORS(void* ,raw_value)
 ACCESSORS(QString ,type_name)
 ACCESSORS(QString ,bind_code)
 ACCESSORS(const QMetaObject* ,qmo)
 ACCESSORS(const QMetaObject* ,pqmo)
 ACCESSORS(const QMetaType* ,qmt)

 void** raw_value_as_pointer()
 {
  return &raw_value_;
 }


 QString qob_reflection_type_name();
 QString qob_reflection_modifier();

 static QString type_name_to_qt_type_name(QString tn);

};

//_KANS(CMD)

#endif //PHR_COMMAND_RUNTIME_ARGUMENT__H
