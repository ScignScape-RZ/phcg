
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "language-sample-group.h"

#include "language-sample.h"

#include <QDebug>

#include "textio.h"


USING_KANS(DSM)
USING_KANS(TextIO)

Language_Sample_Group::Language_Sample_Group(int id)
  :  id_(id), page_(0), start_num_(0), end_num_(0)
{

}

