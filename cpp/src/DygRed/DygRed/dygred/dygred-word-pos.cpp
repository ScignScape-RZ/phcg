
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dygred-word-pos.h"

#include "dygred-sentence.h"

DygRed_Word_Pos::DygRed_Word_Pos(QString t, int i, int p)
 : text_(t), index_(i), pos_(p), parent_(nullptr), super_(nullptr),
   parent_dock_({0,0})
{

}

DygRed_Word_Pos::DygRed_Word_Pos()
  : index_(-1), pos_(-1), parent_(nullptr), super_(nullptr), parent_dock_({0,0})
{

}

void DygRed_Word_Pos::claim_parent(DygRed_Word_Pos* p, QString dp, int lvl, int pos)
{
 claims_[p] = {dp, {lvl, pos}};
}

QPair<int, int> DygRed_Word_Pos::normalized_claim_pos(DygRed_Word_Pos* c, int* plvl, QString* dp)
{
 auto it = claims_.find(c);
 if(it == claims_.end())
 {
  return {-1, -1};
 }
 if(dp)
   *dp = it.value().first;

 int lvl = it.value().second.first;

 if(lvl == -1)
 {
  if(plvl)
    lvl = *plvl;
  else
    lvl = 0;
 }

 return {lvl, it.value().second.second};
}


QList<DygRed_Word_Pos*> DygRed_Word_Pos::claimed_parents()
{
 return claims_.keys();
}


void DygRed_Word_Pos::add_arg(int level, int pos, DygRed_Word_Pos* arg)
{
 args_[{level, pos}] = arg;
}

DygRed_Word_Pos* DygRed_Word_Pos::get_arg(int level, int pos)
{
 return args_.value({level, pos});
}

QString DygRed_Word_Pos::to_string()
{
 return QString("%1 [%2]: %3").arg(text_).arg(index_).arg(pos_);
}

void DygRed_Word_Pos::set_verb_to_subject(DygRed_Word_Pos* s, int lvl)
{
 add_arg(lvl, 0, s);
 s->set_parent(this);
}


void DygRed_Word_Pos::set_verb_to_direct_object(DygRed_Word_Pos* s, int lvl)
{
 add_arg(lvl, 1, s);
 s->set_parent(this);
}

void DygRed_Word_Pos::set_verb_to_indirect_object(DygRed_Word_Pos* s, int lvl)
{
 add_arg(lvl, 2, s);
 s->set_parent(this);
}

void DygRed_Word_Pos::set_modifier_to_target(DygRed_Word_Pos* s, int lvl)
{
 add_arg(lvl, 0, s);
 s->set_parent(this);
}

int DygRed_Word_Pos::get_unfold_depth()
{
 if(args_.isEmpty())
   return 0;
 int result = 0;
 for(QPair<int, int> pr : args_.keys())
 {
  if(result < pr.first)
    result = pr.first;
 }
 return result + 1;
}


void DygRed_Word_Pos::set_modifier_to_target_chain(DygRed_Word_Pos* s,
  QList<DygRed_Word_Pos*> args, int lvl,
  QMap<DygRed_Word_Pos*, QList<DygRed_Word_Pos*>>* aa)
{
 if(args.isEmpty())
 {
  set_modifier_to_target(s, lvl);
  return;
 }
 DygRed_Word_Pos* prior = this;
 int effective_lvl = lvl;
 for(DygRed_Word_Pos* a : args)
 {
  QList<DygRed_Word_Pos*>* aas = nullptr;
  if(aa)
  {
   auto it = aa->find(a);
   if(it != aa->end())
   {
    aas = &it.value();
   }
  }
  if(aas)
  {
   // aas known to be nonempty
   prior->set_modifier_to_target(aas->first(), 0);
   aas->first()->set_modifier_to_target(a, 0);
   effective_lvl = lvl + 1;
   prior = aas->first();
//   prior->set_modifier_to_target(a, 0);
//   prior = a;
  }
  else
  {
   prior->set_modifier_to_target(a, 0);
   prior = a;
  }
 }
 prior->set_modifier_to_target(s, effective_lvl);
}

QString DygRed_Word_Pos::write_unfold_level(int lvl, DygRed_Sentence& dgs)
{
 QMap<int, DygRed_Word_Pos*> largs;
 QMapIterator<QPair<int, int>, DygRed_Word_Pos*> it(args_);
 int max = 0;
 while(it.hasNext())
 {
  it.next();
  if(it.key().first == lvl)
  {
   largs[it.key().second] = it.value();
   ++max;
  }
 }
 QString result;
 for(int i = 0; i < max; ++i)
 {
  DygRed_Word_Pos* dgw = largs.value(i);
  if(dgw)
  {
   result += dgs.to_vstring(dgw);
  }
  else
  {
   result += "??";
  }
  result += ' ';
 }
 if(result.endsWith(' '))
   result.chop(1);
 return result;
}
