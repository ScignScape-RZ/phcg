
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DYGRED_WORD_POS__H
#define DYGRED_WORD_POS__H


#include "udpipe.h"

#include "accessors.h"

class DygRed_Sentence;

class DygRed_Word_Pos
{
 QString text_;
 int index_;
 int pos_;

 DygRed_Word_Pos* parent_;
 DygRed_Word_Pos* super_;

 QPair<int, int> parent_dock_;
 typedef QPair<int, int> parent_dock_type;

 QMap<QPair<int, int>, DygRed_Word_Pos*> args_;

 QMap<DygRed_Word_Pos*, QPair<QString, QPair<int, int>>> claims_;

public:

 DygRed_Word_Pos(QString t, int i, int p);

 DygRed_Word_Pos();

 ACCESSORS(QString ,text)
 ACCESSORS(int ,index)
 ACCESSORS(int ,pos)
 ACCESSORS(DygRed_Word_Pos* ,parent)
 ACCESSORS(parent_dock_type ,parent_dock)
 ACCESSORS(DygRed_Word_Pos* ,super)

 QList<DygRed_Word_Pos*> claimed_parents();

 DygRed_Word_Pos* super_or_self()
 {
  return super_? super_->super_or_self():this;
 }

 QPair<int, int> normalized_claim_pos(DygRed_Word_Pos* c,
   int* plvl = nullptr, QString* dp = nullptr);

 QString to_string();

 int get_unfold_depth();

 void claim_parent(DygRed_Word_Pos* p, QString dp, int lvl, int pos);

 void set_parent(DygRed_Word_Pos* p, int lvl, int pos)
 {
  set_parent(p);
  set_parent_dock({lvl, pos});
 }

 void add_arg(int level, int pos, DygRed_Word_Pos* arg);
 DygRed_Word_Pos* get_arg(int level, int pos);

 void set_verb_to_subject(DygRed_Word_Pos* s, int lvl);

 void set_verb_to_direct_object(DygRed_Word_Pos* s, int lvl);
 void set_verb_to_indirect_object(DygRed_Word_Pos* s, int lvl);
 void set_modifier_to_target(DygRed_Word_Pos* s, int lvl);

 void set_modifier_to_target_chain(DygRed_Word_Pos* s,
   QList<DygRed_Word_Pos*> args, int lvl,
   QMap<DygRed_Word_Pos*, QList<DygRed_Word_Pos*>>* aa = nullptr);

 QString write_unfold_level(int lvl, DygRed_Sentence& dgs);


};


#endif
