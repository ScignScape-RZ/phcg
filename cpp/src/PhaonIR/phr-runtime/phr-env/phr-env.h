
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_ENV__H
#define PHR_ENV__H


#include "accessors.h"

#include "phaon-ir/types/phr-universal-class.h"


#include <QString>
#include <functional>


//KANS_CLASS_DECLARE(PHR ,Kauvir_Code_Model)
//KANS_CLASS_DECLARE(PHR ,PHR_Channel_Group)
//KANS_CLASS_DECLARE(PHR ,PHR_Type_Object)

//USING_KANS(PHR)

//class PHR_Lisp_Bridge;

//KANS_CLASS_DECLARE(CMD ,PHR_Command_Package)
//KANS_CLASS_DECLARE(CMD ,PHR_Command_Runtime_Router)
//KANS_CLASS_DECLARE(CMD ,PHR_Scope_System)

//USING_KANS(CMD)

class PHR_Scope_System;
class PHR_Code_Model;
class PHR_Channel_Group;

class PHR_Env : public PHR_Universal_Class
{
 PHR_Scope_System* scopes_;
 PHR_Code_Model* pcm_;

 typedef std::function<void (PHR_Code_Model*, PHR_Channel_Group*)> report_channel_group_fn_type;

 report_channel_group_fn_type report_channel_group_fn_;

 typedef std::function<void (PHR_Code_Model*,
   PHR_Channel_Group*, QString, QString, QString*,
     QMap<QString, QString> )> kph_gen_fn_type;
 kph_gen_fn_type kph_gen_fn_;

public:

 PHR_Env(PHR_Code_Model* pcm);

 ACCESSORS(PHR_Scope_System* ,scopes)
 ACCESSORS(PHR_Code_Model* ,pcm)
 ACCESSORS(report_channel_group_fn_type ,report_channel_group_fn)
 ACCESSORS(kph_gen_fn_type ,kph_gen_fn)

 void report_channel_group(PHR_Channel_Group* kcg);

 void kph_gen(PHR_Channel_Group* kcg, QString subs, QString fn,
   QString* text, QMap<QString, QString> );
 void kph_gen(PHR_Channel_Group* kcg, QString fn, QString* text,
   QMap<QString, QString> docus);
};


#endif //PHR_ENV__H
