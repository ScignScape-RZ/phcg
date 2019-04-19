
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-env.h"

#include "phaon-ir/scopes/phr-scope-system.h"


#include <QDebug>

PHR_Env::PHR_Env(PHR_Code_Model* pcm)
  :  scopes_(nullptr), pcm_(pcm), report_channel_group_fn_(nullptr),
     kph_gen_fn_(nullptr)
{

}

void PHR_Env::report_channel_group(PHR_Channel_Group* kcg)
{
 if(report_channel_group_fn_)
 {
  report_channel_group_fn_(pcm_, kcg);
 }
}

void PHR_Env::kph_gen(PHR_Channel_Group* kcg, QString subs, QString fn,
  QString* text, QMap<QString, QString> docus)
{
 if(kph_gen_fn_)
 {
  kph_gen_fn_(pcm_, kcg, subs, fn, text, docus);
 }
}

void PHR_Env::kph_gen(PHR_Channel_Group* kcg, QString fn,
  QString* text, QMap<QString, QString> docus)
{
 if(kph_gen_fn_)
 {
  kph_gen_fn_(pcm_, kcg, QString(), fn, text, docus);
 }
}

