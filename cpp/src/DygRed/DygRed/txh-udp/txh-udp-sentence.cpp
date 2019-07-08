
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "txh-udp-sentence.h"

#include <QDebug>
#include <QTextStream>

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QStack>

TXH_UDP_Sentence::TXH_UDP_Sentence(sentence* udp_sentence)
  : udp_sentence_(udp_sentence)
{

}

void TXH_UDP_Sentence::report_text(QTextStream& qts)
{
 QString rep;
 for(word w : udp_sentence_->words)
 {
//  TXH_UDP_Word_Pos& wp = word_poss_[w.id];
//  rep += wp.text() + ' ';
 }
 qts << rep << "\n";
}

void TXH_UDP_Sentence::write_sxp_edges(QTextStream& qts,
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
//   for(const TXH_UDP_SXP_Rel_Pair* rp : *it)
//   {
//    QString rel = QString("%1%2").arg(rp->rel.unw).arg(rp->rel.unw);
//    qts << templat.arg(rp->rel.sxp_index).arg(i).arg(rel);
//   }
//  }
// }

 qts << rtemplat.arg(root_num).arg("root");

 for(TXH_UDP_SXP_Rel_Pair& pr : sxp_vector_)
 {
  QString rel = QString("%1%2").arg(pr.rel.unw).arg(pr.rel.pos);
  qts << templat.arg(pr.rel.sxp_index).arg(pr.sxp_index).arg(rel);

//  int i1 = get_id_by_word(pr.text, pr.which);
//  int i2 = get_id_by_word(pr.rel.chief, pr.rel.which);
//  pr.index = i1;
//  pr.rel.index = i2;
 }
}


void TXH_UDP_Sentence::write_edges(QTextStream& qts, QString templat, QString rtemplat)
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

//void TXH_UDP_Sentence::scan_sxp(const QVector<TXH_UDP_SXP_Rel_Pair>& qvec)//,
////  QMap<QPair<QString, int>, QVector<const TXH_UDP_SXP_Rel_Pair*>>& qmap)
//{
//// for(const TXH_UDP_SXP_Rel_Pair& pr : qvec)
//// {
////  //const TXH_UDP_SXP_Rel* rel = &pr.rel;
////  QString text = pr.rel.chief;
////  if(pr.rel.which > 0)
////    text += QString("->%1").arg(pr.rel.which);
////  qmap[{text, pr.rel.index}].push_back(&pr);
//// }
//}

void TXH_UDP_Sentence::join_sxp_text(QTextStream& qts,
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
  text.replace("->", "{\\arrwhich}");

  if(i == max)
    qts << text << end;
  else
    qts << text << sep;
 }
}

void TXH_UDP_Sentence::join_text(QTextStream& qts, QString sep, QString end, Join_Field_Codes j)
{
 //QString result;
 int max = udp_sentence_->words.size() - 1;
 for(word w : udp_sentence_->words)
 {
  if(w.id == 0)
    continue;
//?  TXH_UDP_Word_Pos& wp = word_poss_[w.id];

  QString text;

  switch (j)
  {
  case Join_Field_Codes::Text:
   //?text = wp.text();
   text = QString::fromStdString(w.form);
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


void TXH_UDP_Sentence::report_text()
{
 QString rep;
 for(word w : udp_sentence_->words)
 {
//  TXH_UDP_Word_Pos& wp = word_poss_[w.id];
//  rep += wp.text() + ' ';
 }
 qDebug() << rep;
}

int TXH_UDP_Sentence::get_id_by_word(QString qw, int which)
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

QString TXH_UDP_Sentence::get_dep_by_word(QString qw, int which)
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


void TXH_UDP_Sentence::write_latex(QTextStream& qts)
{
 qts << "\n\\begin{dependency}\n\\begin{deptext}\n";

 join_text(qts, " \\& ", " \\\\");
 qts << "\n";
 join_text(qts, " \\& ", " \\\\", TXH_UDP_Sentence::Join_Field_Codes::UPOS);
 qts << "\n";
 join_text(qts, " \\& ", " \\\\", TXH_UDP_Sentence::Join_Field_Codes::XPOS);
 qts << "\n\\end{deptext}\n\n";

 write_edges(qts, "\\depedge{%1}{%2}{%3}\n", "\\deproot{%1}{%2}\n");

//  \depedge{1}{2}{det}

 qts << "\n\n\\end{dependency}\n";

 QString sx = sxp_text_;
 if(!sx.isEmpty())
 {
//   QMap<QPair<QString, int>, QVector<const TXH_UDP_SXP_Rel_Pair*>> qmap;
//   TXH_UDP_Sentence::scan_sxp(dgs.sxp_vector() );

  sx.replace("$", "\\$");
  sx.replace("->", "{\\arrwhich}");

  qts << "\n" << sx << "\n";


  qts << "\n\\begin{dependency}\n\\begin{deptext}\n";

  join_sxp_text(qts, " \\& ", " \\\\");
  qts << "\n";
  join_sxp_text(qts, " \\& ", " \\\\", TXH_UDP_Sentence::Join_Field_Codes::UPOS);
  qts << "\n";
  join_sxp_text(qts, " \\& ", " \\\\", TXH_UDP_Sentence::Join_Field_Codes::XPOS);
//  qts << "\n";
  qts << "\n\\end{deptext}\n\n";

  write_sxp_edges(qts, "\\depedge[edge below]{%1}{%2}{%3}\n",
    "\\deproot[edge below]{%1}{%2}\n");
  qts << "\n\n\\end{dependency}\n";

 }
}

void TXH_UDP_Sentence::check_comments()
{
 for(std::string c : udp_sentence_->comments)
 {
  QString qs = QString::fromStdString(c);
  if(qs.startsWith("#sxp:"))
  {
   sxp_text_ = qs.mid(5).trimmed();
   parse_sxp(sxp_text_);
  }
  if(qs.startsWith("#ltx:"))
  {
   latex_out_file_ = qs.mid(5).trimmed();
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

void TXH_UDP_Sentence::parse_sxp(QString sxp, QVector<TXH_UDP_SXP_Rel_Pair>& qvec,
  QVector<QPair<QString, int>>& sxp_texts)
{
 QRegularExpression rx = QRegularExpression("(\\(|\\)|[^()\\s]+|\\s+)");
 int pos = 0;

 int opc = 0;
 int cpc = 0;

 QMap<QString, int> counts;

 QStack<int> pos_stack;
// int current_pos = 0;

 TXH_UDP_SXP_Rel current_ch = {QString(), 0, 0, 0, 0, 0, 0};
 QStack<TXH_UDP_SXP_Rel> ch_stack;

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

void TXH_UDP_Sentence::parse_sxp(QString sxp)
{
 parse_sxp(sxp, sxp_vector_, sxp_texts_);
 for(TXH_UDP_SXP_Rel_Pair& pr : sxp_vector_)
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

