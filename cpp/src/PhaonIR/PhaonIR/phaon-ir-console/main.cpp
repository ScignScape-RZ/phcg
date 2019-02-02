
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-ir/phaon-ir.h"

#include <QDebug>

int main(int argc, char **argv)
{
 PhaonIR phr;
 phr.init_channel_group_stack();
 qDebug() << "ok";
}
