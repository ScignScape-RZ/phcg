
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "charm-lib/vec1d.h"

//#include "kans.h"

//USING_KANS(KDMI)

#include <QDebug>


int main(int argc, char **argv)
{
 Vec1d<int> v1d;

 v1d.push_back(7);
 v1d.push_back(9);
 v1d.push_back(17);
 v1d.push_back(19);
 v1d.push_back(27);
 v1d.push_back(29);
 v1d.push_back(37);
 v1d.push_back(39);
 v1d.push_back(19);
 v1d.push_back(27);
 v1d.push_back(29);
 v1d.push_back(37);
 v1d.push_back(39);

 v1d.each([](int& i)
 {
  qDebug() << i;
 });

 qDebug() << "ok";
 return 0;
}
