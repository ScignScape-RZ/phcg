
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DYGRED_RUNTIME_ENVIRONMENT__H
#define DYGRED_RUNTIME_ENVIRONMENT__H


#include "accessors.h"

#include "kans.h"

#include "dygred-sentence/dygred-sentence.h"
#include "dygred-sentence/dygred-corpus.h"
#include "dygred-sentence/dygred-word-pos.h"

#include "dygred-sentence/dygred-deprel-callbacks.h"

#include <QString>
#include <QStringList>

#include <QMap>

class QTextStream;

KANS_CLASS_DECLARE(KCM ,Kauvir_Code_Model)

USING_KANS(KCM)

class DygRed_Runtime_Environment
{
 DygRed_Deprel_Callbacks cbs_;
 DygRed_Corpus dgc_;
 QString model_file_;

public:

 DygRed_Runtime_Environment(QString root);

 ACCESSORS__GET__SDECLARE(QString ,model_file)

 ACCESSORS__RGET(DygRed_Corpus ,dgc)

};

//void init_dygred_functions(Kauvir_Code_Model& kcm);


#endif DYGRED_RUNTIME_ENVIRONMENT__H
