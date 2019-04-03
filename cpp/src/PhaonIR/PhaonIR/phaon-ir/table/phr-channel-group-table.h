
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CHANNEL_GROUP_TABLE__H
#define PHR_CHANNEL_GROUP_TABLE__H

#include <QtGlobal>


#include <functional>

#include <QMetaProperty>
#include <QVector>

#include <QSet>

//#include "kans.h"
#include "accessors.h"

//#include "kauvir-type-system/kauvir-universal-class.h"
//#include "kauvir-type-system/kauvir-type-system.h"

#include "relae-graph/relae-caon-ptr.h"

#include "phr-function.h"

//#include "kauvir-code-model/kcm-function-package.h"

#include "phr-symbol-scope.h"

#include "phr-function-package.h"

#include "phaon-ir/channel/phr-channel-group.h"
#include "phaon-ir/types/phr-universal-class.h"

#include <QMap>

//KANS_CLASS_DECLARE(KCM ,KCM_Channel_Group)
//KANS_CLASS_DECLARE(KCM ,KCM_Type_Object)

//USING_KANS(KCM)
//USING_KANS(Kauvir)

//KANS_(PhaonLib)

class PHR_Type_System;
class PHR_Channel_Group;
class PHR_Function_Package;

class PHR_Channel_Group_Table
{
 QMap<PHR_Channel_Group, PHR_Channel_Group*> group_pointers_;

 QMultiMap<QString, QString> declared_types_;

 PHR_Type_System& type_system_;

 // //?
 QMultiMap<QString, QPair<PHR_Channel_Group*, s1_fng_type>> s1_declared_functions_generic_;


public:

 PHR_Channel_Group_Table(PHR_Type_System& type_system);

 ACCESSORS__GET(PHR_Type_System& ,type_system)

 PHR_Channel_Group* find_channel_group(const PHR_Channel_Group& channels);

 PHR_Runtime_Scope* get_runtime_scope(PHR_Symbol_Scope& pss);

 template<typename FN_Type>
 void init_phaon_function(const PHR_Channel_Group& g, PHR_Symbol_Scope& pss,
    QString name, int head_code, FN_Type pfn)
 {
  PHR_Channel_Group* pcg = find_channel_group(g);

  PHR_Function phf(pfn);

  caon_ptr<PHR_Function_Package> pfp = new PHR_Function_Package(pcg);
  pfp->init_byte_code(head_code);

  phf.augment(pfp);

  pss.add_function(name, phf);

  //pss[name].push_back(phf);

 }

 s1_fng_type find_s1_declared_function_0(QString name,
   PHR_Channel_Group* kcg, const PHR_Type_Object** pkto);


};

//_KANS(PhaonLib)

#endif //PHR_CHANNEL_GROUP_TABLE__H
