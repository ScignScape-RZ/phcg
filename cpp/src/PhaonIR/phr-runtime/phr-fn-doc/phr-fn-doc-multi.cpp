
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-fn-doc-multi.h"

#include "phaon-ir/scopes/phr-scope-system.h"

#include "phr-env/phr-env.h"

#include "phaon-ir/types/phr-type-object.h"
#include "phaon-ir/phr-code-model.h"
#include "phaon-ir/channel/phr-channel-group.h"

#include "phr-fn-doc.h"

#include "textio.h"

#include <QTextStream>
#include <QDebug>

USING_KANS(TextIO)


PHR_Fn_Doc_Multi::PHR_Fn_Doc_Multi()
  :  fnd_(nullptr)
{

}

PHR_Fn_Doc_Multi::PHR_Fn_Doc_Multi(const PHR_Fn_Doc_Multi& rhs)
  :  fnd_(rhs.fnd_)
{

}

PHR_Fn_Doc_Multi::~PHR_Fn_Doc_Multi()
{
 // // should be unnecessary
 // // delete fnd_;
}

void PHR_Fn_Doc_Multi::init(PHR_Env* kenv)
{
 fnd_ = new PHR_Fn_Doc;
 fnd_->init(kenv);
}


void PHR_Fn_Doc_Multi::read(QString fn)
{
 PHR_Type_Object pto = fnd_->get_type_object_from_symbol_name(fn);
 if(pto.ty())
 {
  fns_.push_back({fn, pto});
 }
}

void PHR_Fn_Doc_Multi::kph_gen_multi(QString path)
{
 QString text;
 QListIterator<QPair<QString, PHR_Type_Object>> it(fns_);
 while(it.hasNext())
 {
  const QPair<QString, PHR_Type_Object>& pr = it.next();
  QString txt;
  QString fn = pr.first;
  PHR_Type_Object pto = pr.second;
  fnd_->kph_gen(pto, fn, txt);
  if(it.hasNext())
  {
   if(txt.endsWith('-'))
   {
    txt.chop(1);
    txt += "##\n.\n";
   }
  }
  text += txt;
 }
 if(path.startsWith('@'))
 {
  path = path.mid(1);
  path.prepend(AR_ROOT_DIR);
 }
 save_file(path, text);
}
