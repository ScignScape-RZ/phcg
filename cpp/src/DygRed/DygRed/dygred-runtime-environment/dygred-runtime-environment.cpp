
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dygred-runtime-environment.h"



#include "udpipe.h"

#include <QDebug>

#include "dygred-sentence/dygred-sentence.h"
#include "dygred-sentence/dygred-corpus.h"

#include "rz-graph-visit/rz-lisp-graph-visitor-dynamo.h"



#include "kauvir-code-model/kauvir-code-model.h"

#include "kauvir-code-model/kcm-channel-group.h"

#include "kauvir-type-system/kauvir-type-system.h"

#include "kauvir-code-model/kcm-callable-value.h"

#include "kauvir-runtime/kcm-command-runtime/kcm-command-runtime-table.h"

#include "kauvir-runtime/kcm-command-runtime/kcm-command-runtime-router.h"

#include "kcm-lisp-bridge/kcm-lisp-eval.h"

#include <QTextStream>

#include <QDebug>

#include <QEventLoop>


USING_KANS(KCL)


DygRed_Runtime_Environment::DygRed_Runtime_Environment(QString root)
  :  dgc_(root)
{
 DygRed_Sentence::init_callcacks(cbs_);
}

void DygRed_Runtime_Environment::set_model_file(QString mf)
{
 model_file_ = dgc_.expand_external_file(mf);
 qDebug() << "mf: " << model_file_;
}
