
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_FUNCTION_PACKAGE__H
#define PHR_FUNCTION_PACKAGE__H


#include "kans.h"

#include "accessors.h"
#include "flags.h"

#include <QVector>
#include <QTextStream>


//KANS_CLASS_DECLARE(Kauvir ,Kauvir_Type_Object)
//USING_KANS(Kauvir)

//KANS_(KCM)

class PHR_Channel_Group;
class PHR_Type_Object;

class PHR_Function_Package
{
 PHR_Channel_Group* pcg_;
 quint32 byte_code_;

public:

 PHR_Function_Package(PHR_Channel_Group* pcg);

 ACCESSORS(PHR_Channel_Group* ,pcg)
 ACCESSORS(quint32 ,byte_code)

 void init_byte_code_s1(bool sr = false);
 void init_byte_code_s0(bool sr = false);
 void init_byte_code_s10(bool sr = false);

 void init_byte_code(int head);

 int split_byte_code(int& xbc);

 const PHR_Type_Object* result_type_object();

};


//_KANS(KCM)


#endif //PHR_FUNCTION_PACKAGE__H
