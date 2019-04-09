
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-callable-value.h"

#include "phaon-ir.h"

#include <QDebug>

PHR_Callable_Value::PHR_Callable_Value(PhaonIR* phaon_ir, QString name)
  :  phaon_ir_(phaon_ir), name_(name)
{

}

void PHR_Callable_Value::run()
{
 qDebug() << name_;
 phaon_ir_->run_callable_value(name_);
}
