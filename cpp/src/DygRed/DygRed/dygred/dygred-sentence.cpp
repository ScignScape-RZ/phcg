
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dygred-sentence.h"

#include "dygred-deprel-callbacks.h"

#include "dygred-word-pair.h"

#include <QDebug>


#include "dygred-word-group.h"


DygRed_Sentence::DygRed_Sentence(sentence* udp_sentence)
  : udp_sentence_(udp_sentence)
{

}

void DygRed_Sentence::report_text()
{
 QString rep;
 for(word w : udp_sentence_->words)
 {
  DygRed_Word_Pos& wp = word_poss_[w.id];
  rep += wp.text() + ' ';
 }
 qDebug() << rep;
}

QString DygRed_Sentence::get_dep_by_word(QString qw, int which)
{
 int count = 0;
 for(word w : udp_sentence_->words)
 {
  if(w.form == qw.toStdString())
  {
   if(count == which)
     return QString::fromStdString(w.deprel);
   ++count;
  }
 }
 return QString();
}

QString DygRed_Sentence::get_udeprel(DygRed_Word_Pos* dgw)
{
 return QString::fromStdString(
   udp_sentence_->words[dgw->pos()].deprel);
}

DygRed_Word_Pos* DygRed_Sentence::get_uhead(DygRed_Word_Pos* dgw)
{
 return &word_poss_[udp_sentence_->words[dgw->pos()].head];
}

QString DygRed_Sentence::get_pos_tag(DygRed_Word_Pos* dgw)
{
 return QString::fromStdString(
   udp_sentence_->words[dgw->pos()].upostag);
}

DygRed_Word_Pos* DygRed_Sentence::normalize_deps(QMap<QString, QList<DygRed_Word_Pos*>>& m)
{
 QMap<QString, int> counts;

 word_poss_.resize(udp_sentence_->words.size());

 for(word w : udp_sentence_->words)
 {
  QString qw = QString::fromStdString(w.form);
  word_poss_[w.id] = DygRed_Word_Pos(qw, counts[qw]++, w.id);
  m[QString::fromStdString(w.deprel)].push_back(&word_poss_[w.id]);
 }
 return m.value("root").isEmpty() ?
   nullptr : m.value("root").first();
}

void DygRed_Sentence::resolve_parent_claims()
{
 for(DygRed_Word_Pos& dgw : word_poss_)
 {
  QList<DygRed_Word_Pos*> cps = dgw.claimed_parents();
  if(cps.isEmpty())
    continue;
  if(cps.size() == 1)
  {
   DygRed_Word_Pos* cp = cps.first();
   QPair<int, int> pr = dgw.normalized_claim_pos(cp);
   dgw.set_parent(cp, pr.first, pr.second);
   cp->add_arg(pr.first, pr.second, &dgw);
   continue;
  }
  int lvl = 0;
  DygRed_Word_Pos* prior = &dgw;
  for(DygRed_Word_Pos* cp : cps)
  {
   DygRed_Word_Pos* sos = cp->super_or_self();
   QPair<int, int> pr = dgw.normalized_claim_pos(cp, &lvl);
   prior->set_parent(sos, pr.first, pr.second);
   sos->add_arg(pr.first, pr.second, prior);
   prior = cp;
   ++lvl;
  }
 }
}


void DygRed_Sentence::init_pairs()
{
 for(word w : udp_sentence_->words)
 {
  if(w.head == -1)
  {
   continue;
  }
  DygRed_Word_Pair* pr = new DygRed_Word_Pair(&word_poss_[w.head], &word_poss_[w.id]);
  pairs_.push_back(pr);
 }
}


void DygRed_Sentence::init_groups(const DygRed_Deprel_Callbacks& cbs)
{
 for(word w : udp_sentence_->words)
 {
  if(w.head == -1)
  {
   continue;
  }
  QString qw = QString::fromStdString(w.form);
  QString dp = QString::fromStdString(w.deprel);
  cbs.check_run_cb("groups", dp, *this, w, &word_poss_[w.id], &word_poss_[w.head]);
 }
}


DygRed_Word_Group* DygRed_Sentence::check_init_adj_group(
  DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw)
{
 DygRed_Word_Group* result = check_init_group("adj", dgw, hdgw);
 QString postag = get_pos_tag(hdgw);
 if(postag == "NOUN")
 {
  result->set_urep(hdgw);
 }
 return result;
}

DygRed_Word_Group* DygRed_Sentence::check_init_verb_group(
  DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw)
{
 DygRed_Word_Group* result = check_init_group("verb", dgw, hdgw);
 QString postag = get_pos_tag(hdgw);
 if(postag == "VERB")
 {
  result->set_urep(hdgw);
 }
 return result;
}

DygRed_Word_Pos* DygRed_Sentence::check_default_init_group_rep(DygRed_Word_Group& dwgg)
{
 switch(dwgg.size())
 {
 case 0: return nullptr;
 case 1: return dwgg.urep_to_rep();
 case 2: return dwgg.non_urep_to_rep();
 default: return nullptr;

 }
}

void DygRed_Sentence::init_adj_group_rep(DygRed_Word_Group& dwgg)
{
 if(check_default_init_group_rep(dwgg))
   return;
 QSet<DygRed_Word_Pos*>& poss = dwgg.poss();
 DygRed_Word_Pos* prior = nullptr;
 for(DygRed_Word_Pos* dgw : poss)
 {
  QString postag = get_pos_tag(dgw);
  if(postag == "NOUN")
  {
   dwgg.set_leaf(dgw);
   continue;
  }
  QString udeprel = get_udeprel(dgw);
  if(udeprel == "det")
  {
   dwgg.set_rep(dgw);
   return;
  }
  prior = dgw;
 }
 if(prior)
 {
  dwgg.set_rep(prior);
 }
}

void DygRed_Sentence::init_adv_group_rep(DygRed_Word_Group& dwgg)
{
 if(check_default_init_group_rep(dwgg))
   return;
 QSet<DygRed_Word_Pos*>& poss = dwgg.poss();
 DygRed_Word_Pos* prior = nullptr;
 DygRed_Word_Pos* leaf = nullptr;
 for(DygRed_Word_Pos* dgw : poss)
 {
  QString postag = get_pos_tag(dgw);
  if(postag == "VERB")
  {
   dwgg.set_leaf(dgw);
   leaf = dgw;
   continue;
  }
 }
 for(DygRed_Word_Pos* dgw : poss)
 {
  if(dgw == leaf)
    continue;
  QString udeprel = get_udeprel(dgw);
  if(udeprel == "advmod")
  {
   DygRed_Word_Pos* h = get_uhead(dgw);
   if(h != leaf)
   {
    dwgg.set_rep(dgw);
    return;
   }
  }
  prior = dgw;
 }
 if(prior)
   dwgg.set_rep(prior);
}

void DygRed_Sentence::init_verb_group_rep(DygRed_Word_Group& dwgg)
{
 dwgg.urep_to_rep();
}

void DygRed_Sentence::resolve_internal_group_parents()
{
 for(DygRed_Word_Group* dwgg : dwg_groups_)
 {
  resolve_internal_group_parents(*dwgg);
 }
}

void DygRed_Sentence::set_as_group_indirect_parent(QString ck, DygRed_Word_Pos* c,
  QString pk, DygRed_Word_Pos* p,
  int lvl, int pos)
{
 DygRed_Word_Group* cg = dwg_groups_map_.value({ck,c});
 DygRed_Word_Group* pg = dwg_groups_map_.value({pk,p});

 if(cg)
 {
  DygRed_Word_Pos* cr = cg->rep();
  int elvl = lvl + 1;
  if(pg)
  {
   DygRed_Word_Pos* pr = pg->rep();
   set_as_parent(cr, pr, elvl, pos);
  }
  else
    set_as_parent(cr, p, elvl, pos);
 }
 else
 {
  if(pg)
  {
   DygRed_Word_Pos* pr = pg->rep();
   set_as_parent(c, pr, lvl, pos);
  }
  else
    set_as_parent(c, p, lvl, pos);
 }

}

DygRed_Word_Pos* DygRed_Sentence::get_rep(QString k, DygRed_Word_Pos* dgw)
{
 if(DygRed_Word_Group* dwgg = dwg_groups_map_.value({k,dgw}))
 {
  return dwgg->rep();
 }
 return dgw;
}

DygRed_Word_Pos* DygRed_Sentence::get_adv_rep(DygRed_Word_Pos* dgw)
{
 return get_rep("adv", dgw);
}

void DygRed_Sentence::set_as_parent(DygRed_Word_Pos* c, DygRed_Word_Pos* p,
    int lvl, int pos)
{
 if(c)
 {
  c->set_parent(p);
  c->set_parent_dock({lvl, pos});
 }

 if(p)
   p->add_arg(lvl, pos, c);
}

void DygRed_Sentence::resolve_internal_group_parents(DygRed_Word_Group& dwgg)
{
 QString k = dwgg.kind();
 static QSet<QString> lassocs {"adv"};
 if(k == "verb")
 {
  verb_resolve_internal_group_parents(dwgg);
 }
 else
 {
  default_resolve_internal_group_parents(dwgg, lassocs.contains(k));
 }
}

void DygRed_Sentence::verb_resolve_internal_group_parents(DygRed_Word_Group& dwgg)
{
 DygRed_Word_Pos* rdgw = dwgg.rep();
 DygRed_Word_Pos* udgw = dwgg.urep();
 int s = dwgg.size();
 DygRed_Word_Pos* odgw = dwgg.non_urep();
 set_as_group_indirect_parent("adj", odgw, "adv", udgw, 0, 0);
}

void DygRed_Sentence::default_resolve_internal_group_parents(
  DygRed_Word_Group& dwgg, bool left_assoc)
{
 switch(dwgg.size())
 {
 case 2:
  {
   DygRed_Word_Pos* rdgw = dwgg.rep();
   DygRed_Word_Pos* udgw = dwgg.urep();
   if(rdgw == udgw)
   {
    DygRed_Word_Pos* odgw = dwgg.non_urep();
    set_as_parent(odgw, udgw, 0, 0);
   }
   else
   {
    set_as_parent(udgw, rdgw, 0, 0);
   }
  }
  break;
 case 3:
  {
   DygRed_Word_Pos* rdgw = dwgg.rep();
   DygRed_Word_Pos* ldgw = dwgg.leaf();
   QList<DygRed_Word_Pos*> inn = dwgg.inner_list();
   DygRed_Word_Pos* idgw = inn.first();
   if(left_assoc)
   {
    set_as_parent(idgw, rdgw, 0, 0);
    set_as_parent(ldgw, rdgw, 1, 0);
//    if(DygRed_Word_Pos* ndgw =
//      find_group_rep_not_of_kind(dwgg.kind(), ldgw))
    if(DygRed_Word_Group* vdwgg =
      find_group_of_kind("verb", ldgw))
    {
     DygRed_Word_Pos* ndgw = vdwgg->non_rep();
     if(DygRed_Word_Pos* adgw =
       find_group_rep_of_kind("adj", ndgw))
     {
      set_as_parent(adgw, rdgw, 2, 0);
     }
     else
     {
      set_as_parent(ndgw, rdgw, 2, 0);
     }
     //set_as_parent(ndgw, rdgw, 2, 0);
    }
   }
   else
   {
    set_as_parent(ldgw, idgw, 0, 0);
    set_as_parent(idgw, rdgw, 0, 0);
   }
  }
  break;
 default: break;
 }
}

DygRed_Word_Pos* DygRed_Sentence::find_group_rep_not_of_kind(QString k, DygRed_Word_Pos* dgw)
{
 if(groups_map_.contains(dgw))
 {
  QMapIterator<QString, DygRed_Word_Group*> it(groups_map_[dgw]);
  while(it.hasNext())
  {
   it.next();
   if(it.key() != k)
     return it.value()->rep();
  }
 }
 return nullptr;
}

DygRed_Word_Pos* DygRed_Sentence::find_group_rep_of_kind(QString k, DygRed_Word_Pos* dgw)
{
 if(groups_map_.contains(dgw))
 {
  return groups_map_[dgw].value(k)->rep();
 }
 return nullptr;
}

DygRed_Word_Group* DygRed_Sentence::find_group_of_kind(QString k, DygRed_Word_Pos* dgw)
{
 if(groups_map_.contains(dgw))
 {
  return groups_map_[dgw].value(k);
 }
 return nullptr;
}


void DygRed_Sentence::init_group_reps()
{
 for(DygRed_Word_Group* dwgg : dwg_groups_)
 {
  QString k = dwgg->kind();
  if(k == "adv")
    init_adv_group_rep(*dwgg);
  else if(k == "adj")
    init_adj_group_rep(*dwgg);
  else if(k == "verb")
    init_verb_group_rep(*dwgg);
 }
}





DygRed_Word_Group*  DygRed_Sentence::check_init_adv_group(DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw)
{
 DygRed_Word_Group* result = check_init_group("adv", dgw, hdgw);
 QString postag = get_pos_tag(hdgw);
 if(postag == "VERB")
 {
  result->set_urep(hdgw);
 }
 return result;
}


DygRed_Word_Group* DygRed_Sentence::get_group(QString k, DygRed_Word_Pos* dgw)
{
 if(groups_map_.contains(dgw))
 {
  return groups_map_[dgw].value(k);
 }
 return nullptr;
}

DygRed_Word_Group* DygRed_Sentence::check_init_group(QString k, DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw)
{
 DygRed_Word_Group* result = dwg_groups_map_.value({k, hdgw});
 if(result)
 {
  dwg_groups_map_[{k, dgw}] = result;
  groups_map_[dgw][k] = result;
 }
 else if(result = dwg_groups_map_.value({k, dgw}))
 {
  dwg_groups_map_[{k, hdgw}] = result;
  groups_map_[hdgw][k] = result;
 }
 else
 {
  result = new DygRed_Word_Group(k);
  dwg_groups_map_[{k, dgw}] = result;
  dwg_groups_map_[{k, hdgw}] = result;
  groups_map_[dgw][k] = result;
  groups_map_[hdgw][k] = result;
  dwg_groups_.push_back(result);
 }
 result->check_add(dgw, hdgw);
 return result;
}


void DygRed_Sentence::internal_resolve_adj_group(DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw)
{

}


DygRed_Word_Pos* DygRed_Sentence::guess_dock_parents(const DygRed_Deprel_Callbacks& cbs)
{
 DygRed_Word_Pos* result = nullptr;
 for(word w : udp_sentence_->words)
 {
  if(w.head == -1)
  {
   result = &word_poss_[w.children[0]];
   continue;
  }
  QString qw = QString::fromStdString(w.form);
  QString dp = QString::fromStdString(w.deprel);
  cbs.check_run_cb("claims", dp, *this, w, &word_poss_[w.id], &word_poss_[w.head], &result);
 }
 return result;
}

void DygRed_Sentence::init_callbacks(DygRed_Deprel_Callbacks& cbs)
{
#define DYGRED_CBS_EMBED_INCLUDE
#include "_cbs/_groups/_det.cpp"
#include "_cbs/_groups/_advmod.cpp"
#include "_cbs/_groups/_amod.cpp"
#include "_cbs/_groups/_nsubj.cpp"
#include "_cbs/_groups/_root.cpp"

#include "_cbs/_claims/_det.cpp"
#include "_cbs/_claims/_advmod.cpp"
#include "_cbs/_claims/_amod.cpp"
#include "_cbs/_claims/_nsubj.cpp"
#include "_cbs/_claims/_root.cpp"
#undef DYGRED_CBS_EMBED_INCLUDE
}













//int DygRed_Sentence::get_adj(int n)
//{

//}

QList<DygRed_Word_Pos*> DygRed_Sentence::get_udeprels(DygRed_Word_Pos* dgw, const QSet<QString>& dps)
{
 word w = udp_sentence_->words[dgw->pos()];
 QList<DygRed_Word_Pos*> result;
 for(int i : w.children)
 {
  word ch = udp_sentence_->words[i];
  QString dp = QString::fromStdString(ch.deprel);
  if(dps.contains(dp))
    result.push_back(&word_poss_[ch.id]);
 }
 return result;
}

DygRed_Word_Pos* DygRed_Sentence::get_udeprel(DygRed_Word_Pos* dgw, const QSet<QString>& dps)
{
 word w = udp_sentence_->words[dgw->pos()];
 for(int i : w.children)
 {
  word ch = udp_sentence_->words[i];
  QString dp = QString::fromStdString(ch.deprel);
  if(dps.contains(dp))
    return &word_poss_[ch.id];
 }
 return nullptr;
}

DygRed_Word_Pos* DygRed_Sentence::get_udeprel(DygRed_Word_Pos* dgw, QString dp)
{
 word w = udp_sentence_->words[dgw->pos()];
 for(int i : w.children)
 {
  word ch = udp_sentence_->words[i];
  if(ch.deprel == dp.toStdString())
    return &word_poss_[ch.id];
 }
 return nullptr;
}

QString DygRed_Sentence::to_vstring(DygRed_Word_Pos* dgw)
{
 int d = dgw->get_unfold_depth();
 if(d == 0)
 {
  return dgw->text();
 }
 QString result = QString(d, '(') + dgw->text() + ' ';
 for(int i = 0; i < d; ++i)
 {
  result += dgw->write_unfold_level(i, *this) + ") ";
 }
 if(result.endsWith(' '))
   result.chop(1);
 return result;
}

DygRed_Word_Pos* DygRed_Sentence::get_usubject(DygRed_Word_Pos* dgw)
{
 return get_udeprel(dgw, "nsubj");
}

QList<DygRed_Word_Pos*> DygRed_Sentence::get_uadv(DygRed_Word_Pos* dgw,
  QMap<DygRed_Word_Pos*, QList<DygRed_Word_Pos*>>& advs)
{
 QList<DygRed_Word_Pos*> result = get_udeprels(dgw, {"advmod"});
 for(DygRed_Word_Pos* r: result)
 {
  QList<DygRed_Word_Pos*> aa = get_udeprels(r, {"advmod"});
  if(!aa.isEmpty())
  {
   advs[r] = aa;
  }
 }
// if(!result.isEmpty())
// {
//  DygRed_Word_Pos* aa = get_udeprel(result.first(), "advmod");
//  while(aa)
//  {
//   advs.push_back(aa);
//   aa = get_udeprel(aa, "advmod");
//  }
// }
 return result;
}

QList<DygRed_Word_Pos*> DygRed_Sentence::get_uadj(DygRed_Word_Pos* dgw)
{
 return get_udeprels(dgw, {"amod", "nmod:poss", "det"});
}

//QString DygRed_Sentence::get_dep_by_word(QString qw, int which)
//{
// int count = 0;
// for(word w : udp_sentence_->words)
// {
//  if(w.form == qw.toStdString())
//  {
//   if(count == which)
//     return QString::fromStdString(w.deprel);
//   ++count;
//  }
// }
// return QString();
//}
