
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


int main8(int argc, char **argv)
{
 Que1d<int> q1d;

 q1d.set_default <= defzfn(int);

 qDebug() << q1d.head();
 qDebug() << q1d.tail();

 return 0;
}

int main7(int argc, char **argv)
{
 Deq1d<int> d1d;

 d1d.push_back(7);
 d1d.push_back(9);
 d1d.push_front(17);

 d1d._each([](int& i)
 {
  qDebug() << i;
 });

 d1d.pop_back();
 d1d.pop_front();

 d1d._each([](int& i)
 {
  qDebug() << i;
 });



 qDebug() << "ok";
 return 0;
}

int main6(int argc, char **argv)
{
 Que1d<int> q1d;

 q1d.enqueue(7);
 q1d.enqueue(9);
 q1d.enqueue(17);

 q1d._each([](int& i)
 {
  qDebug() << i;
 });

 q1d.dequeue();

 q1d._each([](int& i)
 {
  qDebug() << i;
 });

 qDebug() << "ok";
 return 0;
}


int main5(int argc, char **argv)
{
 Stk1d<int> s1d(5);

 s1d.push(7);
 s1d.push(9);
 s1d.push(27);
 s1d.push(37);
 s1d.push(39);
 s1d.push(47);
 s1d.push(9);
 s1d.push(27);
 s1d.push(37);
 s1d.push(39);
 s1d.push(47);

 s1d._each([](int& i)
 {
  qDebug() << i;
 });

 qDebug() << "...";

 for(int i  = 0; i < 6; ++i)
  s1d.pop();

 s1d._each([](int& i)
 {
  qDebug() << i;
 });

 qDebug() << "ok";
 return 0;
}


int main4(int argc, char **argv)
{
 Deq1d<int> d1d;

 d1d.push_back(7);
 d1d.push_back(9);
 d1d.push_front(17);

 d1d.each <= [](int& i)
 {
  qDebug() << i;
 };

 qDebug() << "ok";

 qDebug() << d1d.front();
 qDebug() << d1d.back();


 return 0;
}

int main3(int argc, char **argv)
{
 Que1d<int> q1d;

 q1d.enqueue(7);
 q1d.enqueue(9);
 q1d.enqueue(17);

 q1d.each <= [](int& i)
 {
  qDebug() << i;
 };

 qDebug() << "ok";

 qDebug() << q1d.head();
 qDebug() << q1d.tail();

 return 0;
}

int main2(int argc, char **argv)
{
 Stk1d<int> s1d;
 s1d.set_default <= defzfn(int);

 s1d.push(7);
 s1d.push(9);
 s1d.push(17);

 s1d.each <= [](int& i)
 {
  qDebug() << i;
 };

 qDebug() << s1d.top();
 qDebug() << s1d.bottom();

 qDebug() << "ok";
 return 0;
}


int main(int argc, char **argv)
{
 Vec1d<int> v1d;

 v1d.set_default <= defzfn(int);

 qDebug() << v1d.first();

 v1d.push_back(7);
 v1d.push_back(9);
 v1d.push_back(17);

 v1d.each <= [](int& i, quint16 index)
 {
  qDebug() << index;
  qDebug() << i;
 };

 v1d.each <<= [](int& i)
 {
  if(i == 9)
    return+0;
  qDebug() << i;
  return-1;
 };

 qDebug() << "ok";

 qDebug() << v1d.last();
 qDebug() << v1d.first();

 return 0;
}
