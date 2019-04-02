
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-function.h"

//#include "kans.h"

#include <QString>
#include <QDebug>

//USING//_KANS(PhaonLib)


PHR_Function::PHR_Function(void* raw_ptr)
{
 base_ptr_.set_raw_value( (size_t) raw_ptr);
}

PHR_Function::PHR_Function(const PHR_Function& rhs)
 : base_ptr_(rhs.base_ptr_)
{

}

PHR_Function::PHR_Function()
  :  base_ptr_(nullptr)
{

}


void PHR_Function::base_run()
{
 ((void (*)()) base_ptr_.raw_value_as_pointer()) ();
}


void PHR_Function::augment(caon_ptr<_base>* bs)
{
 bs[1] = base_ptr_;
 base_ptr_.set_raw_value( (size_t) bs);
 base_ptr_.set_array();
}

void PHR_Function::descriptive_base_run()
{
 if(base_ptr_.is_array())
 {
  void* rp = base_ptr_.raw_pointer();
  caon_ptr<_base>* brp = (caon_ptr<_base>*) rp;
  caon_ptr<_base> b0 = brp[0];
  caon_ptr<_base> b1 = brp[1];
  QString* qs = (QString*) b0.raw_pointer();
  qDebug() << *qs;
  ((void (*)()) b1.raw_value_as_pointer()) ();
 }
 else
 {
  base_run();
 }
}

