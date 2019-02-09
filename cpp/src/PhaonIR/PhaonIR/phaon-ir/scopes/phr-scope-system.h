
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_SCOPE_SYSTEM__H
#define PHR_SCOPE_SYSTEM__H

#include "kans.h"


#include "accessors.h"

#include <QtGlobal>
#include <QQueue>

#include <QMap>

//KANS_CLASS_DECLARE(KCM ,KCM_Lexical_Scope)
//KANS_CLASS_DECLARE(KCM ,Kauvir_Code_Model)
//KANS_CLASS_DECLARE(KCM ,KCM_Overloadable_Symbol)
//KANS_CLASS_DECLARE(KCM ,KCM_Type_Object)
//KANS_CLASS_DECLARE(KCM ,KCM_Expression)
//KANS_CLASS_DECLARE(KCM ,KCM_Source_Function)
//USING_KANS(KCM)

//KANS_CLASS_DECLARE(PhaonLib ,Phaon_Symbol_Scope)
//USING_KANS(PhaonLib)

//KANS_(CMD)

//class KCM_Runtime_Scope;

class PHR_Runtime_Scope;

class PHR_Scope_System
{
 PHR_Runtime_Scope* current_scope_;
// QQueue<Phaon_Symbol_Scope*> phaon_scope_queue_;

// QMap<QString, QPair<quint64, const KCM_Type_Object*>> temporary_bridge_values_;


public:

 PHR_Scope_System();

 ACCESSORS(PHR_Runtime_Scope* ,current_scope)
 //ACCESSORS__RGET(QQueue<Phaon_Symbol_Scope*> ,phaon_scope_queue)

};

//_KANS(CMD)


#endif //PHR_SCOPE_SYSTEM__H

