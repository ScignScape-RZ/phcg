
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-fn-doc.h"

#include "phaon-ir/scopes/phr-scope-system.h"

#include "phr-env/phr-env.h"

#include "phaon-ir/types/phr-type-object.h"


#include "phaon-ir/phr-code-model.h"
#include "phaon-ir/channel/phr-channel-group.h"


#include <QTextStream>

#include <QDebug>

PHR_Fn_Doc::PHR_Fn_Doc()
  :  scopes_(nullptr), penv_(nullptr)
{

}

PHR_Fn_Doc::PHR_Fn_Doc(const PHR_Fn_Doc& rhs)
  :  scopes_(rhs.scopes_), penv_(rhs.penv_)
{

}

PHR_Fn_Doc::~PHR_Fn_Doc()
{

}

void PHR_Fn_Doc::init(PHR_Env* penv)
{
 penv_ = penv;
 scopes_ = penv->scopes();
 qDebug() << "init...";
}


QString PHR_Fn_Doc::test_summary()
{
 if(penv_)
   return "PHR_Fn_Doc: Initialized.";
 return "?PHR_Fn_Doc: Not Initialized.";
}


void PHR_Fn_Doc::read(QString fn)
{
 qDebug() << "fn: " << fn;
 const PHR_Type_Object* pto = nullptr;//scopes_->get_type_object_from_symbol_name(fn);
 if(pto)
 {
  if(penv_)
  {
   //penv_->report_channel_group(pto->channel_group());
  }
 }
}

const PHR_Type_Object* PHR_Fn_Doc::get_type_object_from_symbol_name(QString fn)
{
 //return scopes_->get_type_object_from_symbol_name(fn);
}

void PHR_Fn_Doc::kph_gen(QString subs)
{
 qDebug() << "fn: " << held_fn_;
 const PHR_Type_Object* pto = nullptr;//scopes_->get_type_object_from_symbol_name(held_fn_);
 if(pto)
 {
  if(penv_)
  {
   //penv_->kph_gen(pto->channel_group(), subs,  held_fn_, nullptr, docus_[held_fn_]);
  }
 }
}

void PHR_Fn_Doc::add_documentation(QString key_val)
{
 int index = key_val.indexOf(':');
 if(index != -1)
 {
  docus_[held_fn_][key_val.left(index)] = key_val.mid(index + 1).trimmed();
 }
}

void PHR_Fn_Doc::hold_function_name(QString fn)
{
 held_fn_ = fn;
}

void PHR_Fn_Doc::kph_gen(const PHR_Type_Object* pto, QString fn, QString& text)
{
 if(penv_)
 {
  //penv_->kph_gen(pto->channel_group(), fn, &text, docus_[fn]);
 }
}
