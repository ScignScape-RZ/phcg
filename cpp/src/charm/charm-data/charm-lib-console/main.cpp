
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "charm-lib/vec1d.h"
#include "charm-lib/stk1d.h"
#include "charm-lib/que1d.h"
#include "charm-lib/deq1d.h"

//#include "kans.h"

//USING_KANS(KDMI)

#include <QDebug>

int main(int argc, char **argv)
{
 Deq1d<int> d1d;

 d1d.push_back(7);
 d1d.push_back(9);
 d1d.push_front(17);

 d1d.each([](int& i)
 {
  qDebug() << i;
 });

 qDebug() << "ok";
 return 0;
}

int main3(int argc, char **argv)
{
 Que1d<int> q1d;

 q1d.enqueue(7);
 q1d.enqueue(9);
 q1d.enqueue(17);

 q1d.each([](int& i)
 {
  qDebug() << i;
 });

 qDebug() << "ok";
 return 0;
}

int main2(int argc, char **argv)
{
 Stk1d<int> s1d;

 s1d.push(7);
 s1d.push(9);
 s1d.push(17);

 s1d.each([](int& i)
 {
  qDebug() << i;
 });

 qDebug() << "ok";
 return 0;
}


int main1(int argc, char **argv)
{
 Vec1d<int> v1d;

 v1d.push_back(7);
 v1d.push_back(9);
 v1d.push_back(17);

 v1d.each([](int& i)
 {
  qDebug() << i;
 });

 qDebug() << "ok";
 return 0;
}
