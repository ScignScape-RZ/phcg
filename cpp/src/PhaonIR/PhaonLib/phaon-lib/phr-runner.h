
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_RUNNER__H
#define PHR_RUNNER__H


#include "kans.h"

#include "phr-function.h"

#include <QString>
#include <QQueue>

//KANS_CLASS_DECLARE(KCM ,KCM_Channel_Group)
//KANS_CLASS_DECLARE(KCM ,Kauvir_Code_Model)
//USING_KANS(KCM)

//KANS_CLASS_DECLARE(CMD ,KCM_Scope_System)
//USING_KANS(CMD)


//KANS_(PhaonLib)

class PHR_Symbol_Scope;
class PHR_Function_Vector;
class PHR_Channel_Group_Table;

class PHR_Channel_Group;

class PHR_Scope_System;
class PHR_Code_Model;

class PHR_Runner
{
// Kauvir_Code_Model* kcm_;
 PHR_Code_Model* pcm_;
 PHR_Scope_System* scopes_;
 PHR_Channel_Group_Table* table_;

public:

 PHR_Runner();

// Kauvir_Code_Model& get_kcm()
// {
//  return *kcm_;
// }

 PHR_Channel_Group_Table& get_table()
 {
  return *table_;
 }

 void init_scope_system();
 QQueue<PHR_Symbol_Scope*>& get_phaon_scope_queue();

 void run(PHR_Channel_Group& pcg);

};


//_KANS(PhaonLib)


#endif //PHR_RUNNER__H
