
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dygred-deprel-callbacks.h"

DygRed_Deprel_Callbacks::DygRed_Deprel_Callbacks()
{

}

void DygRed_Deprel_Callbacks::add_cb(QString k, QString s, fn_type fn)
{
 cbs_[k][s] = fn;
}

void DygRed_Deprel_Callbacks::check_run_cb(QString k, QString s, DygRed_Sentence& dgs, word& w,
  DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw, DygRed_Word_Pos** rr) const
{
 if(fn_type fn = cbs_[k].value(s))
 {
  QString redirect = fn(s, dgs, w, dgw, hdgw, rr);
  if(!redirect.isEmpty())
  {
   check_run_cb(k, redirect, dgs, w, dgw, hdgw, rr);
  }
 }
}

