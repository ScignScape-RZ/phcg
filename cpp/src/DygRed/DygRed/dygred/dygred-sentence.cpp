
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dygred-sentence.h"

#include "dygred-deprel-callbacks.h"

#include "dygred-word-pair.h"

#include <QDebug>
#include <QTextStream>

#include "dygred-word-group.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QStack>

DygRed_Sentence::DygRed_Sentence(sentence* udp_sentence)
  : udp_sentence_(udp_sentence)
{

}

void DygRed_Sentence::report_text(QTextStream& qts)
{
 QString rep;
 for(word w : udp_sentence_->words)
 {
  DygRed_Word_Pos& wp = word_poss_[w.id];
  rep += wp.text() + ' ';
 }
 qts << rep << "\n";
}

void DygRed_Sentence::write_sxp_edges(QTextStream& qts,
  QMap<QPair<QString, int>, QVector<const DygRed_SXP_Rel_Pair*>>& qmap,
  QString templat, QString rtemplat, int root_num)
{
// int i = 0;
// for(QPair<QString, int>& pr : sxp_texts_)
// {
//  ++i;
//  if(i == root_num)
//  {
//   qts << rtemplat.arg(i).arg("root");
//  }
//  auto it = qmap.find(pr);
//  if(it != qmap.end())
//  {
//   for(const DygRed_SXP_Rel_Pair* rp : *it)
//   {
//    QString rel = QString("%1%2").arg(rp->rel.unw).arg(rp->rel.unw);
//    qts << templat.arg(rp->rel.sxp_index).arg(i).arg(rel);
//   }
//  }
// }

 qts << rtemplat.arg(1).arg("root");

 for(DygRed_SXP_Rel_Pair& pr : sxp_vector_)
 {
  QString rel = QString("%1%2").arg(pr.rel.unw).arg(pr.rel.pos);
  qts << templat.arg(pr.rel.sxp_index).arg(pr.sxp_index).arg(rel);

//  int i1 = get_id_by_word(pr.text, pr.which);
//  int i2 = get_id_by_word(pr.rel.chief, pr.rel.which);
//  pr.index = i1;
//  pr.rel.index = i2;
 }
}


void DygRed_Sentence::write_edges(QTextStream& qts, QString templat, QString rtemplat)
{
 for(word w : udp_sentence_->words)
 {
  if(w.id == 0)
    continue;

  int h = w.head;

  if(h > 0)
    qts << templat.arg(w.id).arg(h).arg(QString::fromStdString(w.deprel));
  else if(h == 0)
    qts << rtemplat.arg(w.id).arg(QString::fromStdString(w.deprel));
 }
}

void DygRed_Sentence::scan_sxp(const QVector<DygRed_SXP_Rel_Pair>& qvec,
  QMap<QPair<QString, int>, QVector<const DygRed_SXP_Rel_Pair*>>& qmap)
{
 for(const DygRed_SXP_Rel_Pair& pr : qvec)
 {
  //const DygRed_SXP_Rel* rel = &pr.rel;
  QString text = pr.rel.chief;
  if(pr.rel.which > 0)
    text += QString("->%1").arg(pr.rel.which);
  qmap[{text, pr.rel.index}].push_back(&pr);
 }
}



void DygRed_Sentence::join_sxp_text(QTextStream& qts,
  QMap<QPair<QString, int>, QVector<const DygRed_SXP_Rel_Pair*>>& qmap,
  QString sep, QString end, Join_Field_Codes j)
{
 int i = 0;
 int max = sxp_texts_.size();
 for(QPair<QString, int>& pr : sxp_texts_)
 {
  ++i;
  word w = udp_sentence_->words[pr.second];

  QString text;

  switch (j)
  {
  case Join_Field_Codes::Text:
   text = pr.first;
   break;
  case Join_Field_Codes::UPOS:
   text = QString::fromStdString(w.upostag);
   break;
  case Join_Field_Codes::XPOS:
   text = QString::fromStdString(w.xpostag);
   break;
  }

  text.replace("$", "\\$");

  if(i == max)
    qts << text << end;
  else
    qts << text << sep;
 }
}

void DygRed_Sentence::join_text(QTextStream& qts, QString sep, QString end, Join_Field_Codes j)
{
 //QString result;
 int max = udp_sentence_->words.size() - 1;
 for(word w : udp_sentence_->words)
 {
  if(w.id == 0)
    continue;
  DygRed_Word_Pos& wp = word_poss_[w.id];

  QString text;

  switch (j)
  {
  case Join_Field_Codes::Text:
   text = wp.text();
   break;
  case Join_Field_Codes::UPOS:
   text = QString::fromStdString(w.upostag);
   break;
  case Join_Field_Codes::XPOS:
   text = QString::fromStdString(w.xpostag);
   break;
  }

  text.replace("$", "\\$");

  if(w.id == max)
    qts << text << end;
  else
    qts << text << sep;
 }
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

int DygRed_Sentence::get_id_by_word(QString qw, int which)
{
 int count = 0;
 for(word w : udp_sentence_->words)
 {
  if(w.form == qw.toStdString())
  {
   if(which == 0)
     return w.id;
   ++count;
   if(count == which)
     return w.id;
  }
 }
 return 0;
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

void DygRed_Sentence::check_comments()
{
 for(std::string c : udp_sentence_->comments)
 {
  QString qs = QString::fromStdString(c);
  if(qs.startsWith("#sxp:"))
  {
   sxp_text_ = qs.mid(5).trimmed();
   parse_sxp(sxp_text_);
  }
 }
}

//struct sxprel
//{
// QString hint;
// int ch_id;
// int unw;
// int max_unw;
// int pos;
//};

void DygRed_Sentence::parse_sxp(QString sxp, QVector<DygRed_SXP_Rel_Pair>& qvec,
  QVector<QPair<QString, int>>& sxp_texts)
{
 QRegularExpression rx = QRegularExpression("(\\(|\\)|[^()\\s]+|\\s+)");
 int pos = 0;

 int opc = 0;
 int cpc = 0;

 QMap<QString, int> counts;

 QStack<int> pos_stack;
// int current_pos = 0;

 DygRed_SXP_Rel current_ch = {QString(), 0, 0, 0, 0, 0, 0};
 QStack<DygRed_SXP_Rel> ch_stack;

 while(pos < sxp.length())
 {
  QRegularExpressionMatch rxm = rx.match(sxp, pos);
  if(!rxm.hasMatch())
   break;
  QString qs = rxm.captured();
  pos += qs.length();
  qs = qs.trimmed();
  if(!qs.isEmpty())
  {
   if(qs == '(')
   {
    ++opc;
    continue;
   }
   else if(qs == ')')
   {
    ++cpc;
    continue;
   }
   else if(qs.trimmed().isEmpty())
     continue;

   int which = 0;
   if(qs.endsWith("->@"))
   {
    qs.chop(3);
    which = ++counts[qs];
   }
   else
   {
    ++counts[qs];
   }

   sxp_texts.push_back({qs, which});

   //QString cc = current_ch.chief;
   if(cpc > 0)
   {
    int unw = current_ch.unw;
    int max = current_ch.max_unw;
    for(int i = 0; i < cpc; ++i)
    {
     current_ch = ch_stack.pop();
    }
    //current_pos = current_ch.pos;
    unw = current_ch.unw;
    ++current_ch.pos;
    if(opc == 0)
    {
     qDebug() << QString("\n%1 : %2 (%3-%4)").
        arg(current_ch.chief).arg(qs).arg(current_ch.unw).arg(current_ch.pos);
     qvec.push_back({qs, which, 0, sxp_texts.size(), current_ch});
     ++current_ch.pos;
    }
   }
   if(opc > 0)
   {
    if(!current_ch.chief.isEmpty())
    {
     qDebug() << QString("\n%1 : %2 (%3-%4)").
        arg(current_ch.chief).arg(qs).arg(current_ch.unw).arg(current_ch.pos);
     qvec.push_back({qs, which, 0, sxp_texts.size(), current_ch});
    }
    ch_stack.push(current_ch);
    if(opc > 1)
    {
     for(int i = opc; i > 1; --i)
     {
      ch_stack.push({qs, which, 0, i, opc, 0, sxp_texts.size()});
     }
    }
    current_ch = {qs, which, 0, 1, opc, 1, sxp_texts.size()};
    opc = 0;
    cpc = 0;
//    current_pos = 0;
   }
   else if(cpc > 0)
   {
    cpc = 0;
    continue;
   }
   else
   {
    qDebug() << QString("\n%1 : %2 (%3-%4)").
       arg(current_ch.chief).arg(qs).arg(current_ch.unw).arg(current_ch.pos);
    qvec.push_back({qs, which, 0, sxp_texts.size(), current_ch});
    ++current_ch.pos;// = current_pos;
   }
  }
 }
}

void DygRed_Sentence::parse_sxp(QString sxp)
{
 parse_sxp(sxp, sxp_vector_, sxp_texts_);
 for(DygRed_SXP_Rel_Pair& pr : sxp_vector_)
 {
  int i1 = get_id_by_word(pr.text, pr.which);
  int i2 = get_id_by_word(pr.rel.chief, pr.rel.which);
  pr.index = i1;
  pr.rel.index = i2;
 }

 for(QPair<QString, int>& pr : sxp_texts_)
 {
  int id = get_id_by_word(pr.first, pr.second);
  if(pr.second > 0)
    pr.first += QString("->%1").arg(pr.second);
  pr.second = id;
 }
}

#ifdef HIDE
 QRegularExpression rx = QRegularExpression("(\\(|\\)|[^()\\s]+|\\s+)");
 int pos = 0;

 QMap<QString, int> counts;

 QMap<int, sxprel> ws;

 int opc = 0;
 int cpc = 0;

 QStack<int> pos_stack;
 int current_pos = 0;

 sxprel current_ch = {0, 0, 0, 0};
 QStack<sxprel> ch_stack;

 QMap<int, sxprel> w_ch;

 while(pos < sxp.length())
 {
  QRegularExpressionMatch rxm = rx.match(sxp, pos);
  if(!rxm.hasMatch())
   break;
  QString qs = rxm.captured();
  pos += qs.length();
  qs = qs.trimmed();
  if(!qs.isEmpty())
  {
//   bool is_word = false;
//   bool is_space = false;
//   bool is_open_paren = false;
//   bool is_close_paren = false;
   if(qs == '(')
   {
    ++opc;
    continue;
   }
   else if(qs == ')')
   {
    ++cpc;
    continue;
   }
   else if(qs.trimmed().isEmpty())
     continue;

   int rank = 0;
   if(qs.endsWith("->@"))
   {
    qs.chop(3);
    rank = ++counts[qs];
   }
   else
   {
    ++counts[qs];
   }

   int id = get_id_by_word(qs, rank);

   QString cc;
   if(current_ch.ch_id > 0)
   {
    cc = QString::fromStdString(udp_sentence_->words[current_ch.ch_id].form);
   }

   if(opc > 0)
   {
    if(current_ch.ch_id > 0)
    {
     qDebug() << QString("\n%1 : %2 [%3:%4] (%5-%6)").arg(qs).
        arg(cc).arg(id).arg(current_ch.ch_id).arg(current_ch.unw).arg(current_ch.pos);
     w_ch[id] = current_ch;
    }
    ch_stack.push(current_ch);
    current_ch = {qs, id, 1, opc, 1};

//(and (is ((The (city s)) ambiance) colonial) (is->@ (the climate) tropical))

//    for(int i = 0; i < opc; ++i)
//      pos_stack.push(0);
    opc = 0;
    current_pos = 0;
//    ws[id] = {current_pos, {opc, cpc}};
   }
   else if(cpc > 0)
   {
    int unw = current_ch.unw;
    int max = current_ch.max_unw;
    for(int i = 0; i < cpc; ++i)
    {
     if(unw == max)
     {
      current_ch = ch_stack.pop();
      current_pos = current_ch.pos;
      unw = current_ch.unw;
      max = current_ch.max_unw;


      if(current_ch.ch_id > 0)
      {
       cc = QString::fromStdString(udp_sentence_->words[current_ch.ch_id].form);
      }

     }
     ++unw;
    }
    ++current_pos;
    current_ch.pos = current_pos;
    qDebug() << QString("\n%1 : %2 [%3:%4] (%5-%6)").arg(qs).
       arg(cc).arg(id).arg(current_ch.ch_id).arg(current_ch.unw).arg(current_ch.pos);
    w_ch[id] = current_ch;

//    for(int i = 0; i < cpc; ++i)
//      current_pos = pos_stack.pop();
    cpc = 0;
//    ws[id] = {current_pos, {opc, cpc}};
   }
   else
   {
    ++current_pos;
    current_ch.pos = current_pos;
    qDebug() << QString("\n%1 : %2 [%3:%4] (%5-%6)").arg(qs).
       arg(cc).arg(id).arg(current_ch.ch_id).arg(current_ch.unw).arg(current_ch.pos);
    w_ch[id] = current_ch; //.first, {current_ch.second}

//    ws[id] = {current_pos, {opc, cpc}};
   }
  }
 }

 QString summary;

  qDebug() << "\n";

 QMapIterator<int, sxprel> it(w_ch);
 while (it.hasNext())
 {
  it.next();
  int id = it.key();
  int ch = it.value().ch_id;
  int unw = it.value().unw;
  int pos = it.value().pos;
  word w = udp_sentence_->words[id];
  word chw = udp_sentence_->words[ch];

  qDebug() << QString("\n%1 : %2 [%3:%4] (%5-%6)").arg(QString::fromStdString(w.form)).
    arg(QString::fromStdString(chw.form)).arg(id).arg(ch).arg(unw).arg(pos);
 }

// for(int id = 1; id <= udp_sentence_->words.size(); ++id)
// {
//  if(!ws.contains(id))
//    return;
//  int pos = ws[id].first;
//  int opc = ws[id].second.first;
//  int cpc = ws[id].second.second;

//  summary += QString(opc, QChar('('));
//  summary += QString(cpc, QChar(')'));
//  word w = udp_sentence_->words[id];
//  summary += QString::fromStdString(w.form);
// }

// qDebug() << "summary: " << summary;


}
#endif

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
  DygRed_Word_Group* wg = groups_map_[dgw].value(k);
  if(wg)
    return wg->rep();
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
