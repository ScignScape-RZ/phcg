
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-function-vector.h"

//#include "kauvir-code-model/kcm-function-package.h"
//#include "kauvir-code-model/kcm-type-object.h"
//#include "kans.h"


#include <QString>
#include <QDebug>

//USING_KANS(KCM)

//USING//_KANS(PhaonLib)

#include "phr-function-package.h"

PHR_Function_Vector::PHR_Function_Vector()
 :  QVector<PHR_Function>()
{

}

PHR_Function_Vector::PHR_Function_Vector(PHR_Function& phf)
 :  QVector<PHR_Function>({phf})
{

}

void* PHR_Function_Vector::get_first()
{
 PHR_Function phf = first();
 PHR_Function_Package* pfp;
 void* fnp = phf.de_augment(pfp);
 return fnp;
}

void* PHR_Function_Vector::find_argvec_function(int& mc, int& rbc,
  const PHR_Type_Object** ppto)
{
 for(PHR_Function phf : *this)
 {
  PHR_Function_Package* pfp;
  void* fnp = phf.de_augment(pfp);
  int bc;
  int xbc = pfp->split_byte_code(bc);
  if( (bc % 10) == 9 )
  {
   mc = xbc;
   rbc = bc;
   if(ppto)
   {
    *ppto = pfp->result_type_object();
   }
   return fnp;
  }
 }
 return nullptr;
}

void* PHR_Function_Vector::match_against_codes(const QSet<int>& codes,
  int& mc, int& rbc, const PHR_Type_Object** ppto)
{
 for(PHR_Function phf : *this)
 {
  PHR_Function_Package* pfp;
  void* fnp = phf.de_augment(pfp);
  int bc;
  int xbc = pfp->split_byte_code(bc);
  if(codes.contains(xbc))
  {
   mc = xbc;
   rbc = bc;
   if(ppto)
   {
    *ppto = pfp->result_type_object();
   }
   return fnp;
  }
 }
 return nullptr;
}
