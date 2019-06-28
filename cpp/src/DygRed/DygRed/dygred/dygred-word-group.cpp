
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dygred-word-group.h"

//#include "dygred-sentence.h"

DygRed_Word_Group::DygRed_Word_Group(QString kind)
 : kind_(kind), urep_(nullptr), rep_(nullptr), leaf_(nullptr)
{

}


QList<DygRed_Word_Pos*> DygRed_Word_Group::inner_list()
{
 QSet<DygRed_Word_Pos*> r = poss_;
 if(rep_)
   r.remove(rep_);
 if(leaf_)
   r.remove(leaf_);
 return r.toList();
}

DygRed_Word_Pos* DygRed_Word_Group::urep_to_rep()
{
 rep_ = urep_;
 return rep_;
}


DygRed_Word_Pos* DygRed_Word_Group::non_urep_to_rep()
{
 QSetIterator<DygRed_Word_Pos*> it(poss_);
 while(it.hasNext())
 {
  DygRed_Word_Pos* dgw = it.next();
  if(dgw != urep_)
  {
   rep_ = dgw;
   return rep_;
  }
 }
 return nullptr;
}

DygRed_Word_Pos* DygRed_Word_Group::non_urep()
{
 QSetIterator<DygRed_Word_Pos*> it(poss_);
 while(it.hasNext())
 {
  DygRed_Word_Pos* dgw = it.next();
  if(dgw != urep_)
  {
   return dgw;
  }
 }
 return nullptr;
}

DygRed_Word_Pos* DygRed_Word_Group::non_rep()
{
 QSetIterator<DygRed_Word_Pos*> it(poss_);
 while(it.hasNext())
 {
  DygRed_Word_Pos* dgw = it.next();
  if(dgw != rep_)
  {
   return dgw;
  }
 }
 return nullptr;
}


void DygRed_Word_Group::check_add(DygRed_Word_Pos* dgw)
{
 poss_.insert(dgw);
}

void DygRed_Word_Group::check_add(DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw)
{
 check_add(dgw);
 check_add(hdgw);
}

