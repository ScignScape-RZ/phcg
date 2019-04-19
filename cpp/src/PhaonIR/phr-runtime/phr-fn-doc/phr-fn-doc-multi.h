
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_FN_DOC_MULTI__H
#define PHR_FN_DOC_MULTI__H


#include "kans.h"

#include "phaon-ir/types/phr-universal-class.h"

#include <QString>
#include <QObject>
#include <QList>
#include <QPair>


//KANS_CLASS_DECLARE(KCM ,Kauvir_Code_Model)
//KANS_CLASS_DECLARE(KCM ,KCM_Channel_Group)
//KANS_CLASS_DECLARE(KCM ,KCM_Type_Object)

//USING_KANS(KCM)

//class KCM_Lisp_Bridge;

//KANS_CLASS_DECLARE(CMD ,KCM_Command_Package)
//KANS_CLASS_DECLARE(CMD ,KCM_Command_Runtime_Router)
//KANS_CLASS_DECLARE(CMD ,KCM_Scope_System)

//USING_KANS(CMD)

class PHR_Env;
class PHR_Fn_Doc;
class PHR_Type_Object;

class PHR_Fn_Doc_Multi : public QObject, public PHR_Universal_Class
{
 Q_OBJECT

 PHR_Fn_Doc* fnd_;

 QList<QPair<QString, const PHR_Type_Object*>> fns_;

public:

 PHR_Fn_Doc_Multi();

 PHR_Fn_Doc_Multi(const PHR_Fn_Doc_Multi& rhs);

 ~PHR_Fn_Doc_Multi();

 Q_INVOKABLE void read(QString fn);
 Q_INVOKABLE void init(PHR_Env* penv);

 Q_INVOKABLE void kph_gen_multi(QString path);

};


Q_DECLARE_METATYPE(PHR_Fn_Doc_Multi)
Q_DECLARE_METATYPE(PHR_Fn_Doc_Multi*)

#endif //PHR_FN_DOC_MULTI__H
