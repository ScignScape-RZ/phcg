
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-expression-object.h"

#include "phaon-ir.h"

#include <QDebug>

PHR_Expression_Object::PHR_Expression_Object(PhaonIR* phaon_ir,
  PHR_Channel_Group* channel_group)
  :  phaon_ir_(phaon_ir), channel_group_(channel_group)
{

}

PHR_Channel_Group_Evaluator* PHR_Expression_Object::run()
{
 //qDebug() << name_;
 return phaon_ir_->run_expression_object(channel_group_);
}
