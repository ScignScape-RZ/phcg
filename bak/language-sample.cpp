
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "language-sample.h"

#include "language-sample-group.h"

#include "phaong/phaong-types.h"

#include <QDebug>

#include "textio.h"


USING_KANS(DSM)
USING_KANS(TextIO)

Language_Sample::Language_Sample(QString text, phaong<pg_t>& phg)
  :  text_(text), index_(0), chapter_(0), page_(0), group_(nullptr)
{
 phg.new_hypernode(this, 6, {"Language_Sample", nullptr});

 {
  int phaong_data_index = 0;
  phg.PHAONG_DATA(QString ,text);
  phg.PHAONG_DATA(QString ,source_title);
  phg.PHAONG_DATA(int ,index);
  phg.PHAONG_DATA(QString ,sub_index);
  phg.PHAONG_DATA(int ,chapter);
  phg.PHAONG_DATA(int ,page);
 }

}

int Language_Sample::get_group_id()
{
 if(group_)
 {
  return group_->id();
 }
 return 0;
}

Language_Sample_Group* Language_Sample::get_ref_group()
{
 if(group_)
 {
  if(group_->ref_group())
    return group_->ref_group();
  return group_;
 }
 return nullptr;
}

QString Language_Sample::get_serialization()
{
 QString result = QString("%1 %2 %3 %4\n").arg(index_)
   .arg(sub_index_).arg(chapter_).arg(page_);

 int gid = get_group_id();
 if(gid)
 {
  result += QString("# %1\n").arg(gid);
 }

 result += text_;
 return result;
}

void Language_Sample::read_samples_from_file
(phaong<pg_t>& phg, QString path, QVector<Language_Sample*>& result,
 QVector<Language_Sample_Group*>& groups)
{
 QString text = load_file(path);
 QStringList qsl = text.split('\n');
 QString loc_code;

 QString speaker;

 Language_Sample_Group* current_ref_group = nullptr;
 bool awaiting_ref_group = false;
 int ref_group_id = 0;

 int group_count = 0;
 int gid = 0;

 for(QString qs : qsl)
 {
  if(qs.isEmpty())
    continue;

  if(qs.startsWith('#'))
  {
   gid = qs.mid(2).simplified().toInt();

   qDebug() << "Loc code: " << loc_code;

   if(loc_code.isEmpty())
   {
    qDebug() << "No Loc code!";
   }

   if(gid == 11)
     continue;

   continue;
  }

  if(qs.startsWith(':'))
  {
   speaker = qs.mid(2).simplified();
   continue;
  }

  if(qs.startsWith('/'))
  {
   //?
   continue;
  }

  if(qs == "++")
  {
   //?
   continue;
  }
  if(qs == "--")
  {
   //?
   continue;
  }
  if(qs.startsWith('?'))
  {
   //?
   continue;
  }

  if(loc_code.isEmpty())
  {
   loc_code = qs.simplified();
   continue;
  }

  QString pre;
  QString post;

  int index = loc_code.indexOf('<');
  if(index != -1)
  {
   QString pp = loc_code.mid(index + 1);
   loc_code = loc_code.left(index).simplified();
   int i1 = pp.indexOf('>');
   if(i1 == -1)
   {
    pre = pp;
   }
   else
   {
    pre = pp.left(i1);
    post = pp.mid(i1 + 1);
   }
  }

//  // // temp...
//  if(pre.startsWith('A'))
//  {
//   speaker = "A";
//   pre = pre.mid(1).simplified();
//  }
//  else if(pre.startsWith('B'))
//  {
//   speaker = "B";
//   pre = pre.mid(1).simplified();
//  }
//  else if(pre.startsWith("I1"))
//  {
//   speaker = "I1";
//   pre = pre.mid(2).simplified();
//  }
//  else if(pre.startsWith("I2"))
//  {
//   speaker = "I2";
//   pre = pre.mid(2).simplified();
//  }

//  qDebug() << loc_code;

//    // // temp...
//  if(pre.startsWith("??/*"))
//  {
//   amark = "??/*";
//   pre = pre.mid(4).simplified();
//  }
//   else if(pre.startsWith("??"))
//    {
//     amark = "??";
//     pre = pre.mid(2).simplified();
//    }
//    else if(pre.startsWith("?*"))
//    {
//     amark = "?*";
//     pre = pre.mid(2).simplified();
//    }
//    else if(pre.startsWith("*?"))
//    {
//     amark = "*?";
//     pre = pre.mid(2).simplified();
//    }
//    else if(pre.startsWith('?'))
//    {
//     amark = "?";
//     pre = pre.mid(1).simplified();
//    }
//    else if(pre.startsWith("#"))
//    {
//     amark = "#";
//     pre = pre.mid(1).simplified();
//    }
//    else if(pre.startsWith("*"))
//    {
//     amark = "*";
//     pre = pre.mid(1).simplified();
//    }

//    if(pre.startsWith('X'))
//    {
//     speaker = "X";
//     pre = pre.mid(1).simplified();
//    }
//    else if(pre.startsWith('Y'))
//    {
//     speaker = "Y";
//     pre = pre.mid(1).simplified();
//    }


  //qDebug() << "lc: " << loc_code;
  QStringList ls = loc_code.split(' ');

  Language_Sample* samp = new Language_Sample(qs, phg);

  samp->set_index(ls[0].toInt());
  samp->set_sub_index(ls[1]);
  samp->set_chapter(ls[2].toInt());
  samp->set_page(ls[3].toInt());

  if(!speaker.isEmpty())
  {
   samp->set_speaker(speaker);
   speaker.clear();
  }

  if(gid)
  {
   Language_Sample_Group* g = groups[gid - 1];
   samp->set_group(g);

   if(awaiting_ref_group)
   {
    current_ref_group = g;
    awaiting_ref_group = false;
   }
   else if(ref_group_id)
   {
    g->set_ref_group(groups[ref_group_id - 1]);
    ref_group_id = 0;
   }
   else if(current_ref_group)
   {
    g->set_ref_group(current_ref_group);
   }
  }
  else
  {
   QString tid = QString("%1-%2-%3")
        .arg(samp->chapter()).arg(samp->page())
        .arg(samp->index());
   qDebug() << "group missing: " << tid;
//   QString tid = QString("%1-%2-%3")
//     .arg(samp->chapter()).arg(samp->page())
//     .arg(samp->index());
//   Language_Sample_Group* g = groups.value(tid);
//   if(!g)
//   {
//    ++group_count;
//    g = new Language_Sample_Group(group_count, tid);
//    groups[tid] = g;
//    g->set_chapter(samp->chapter());
//    g->set_page(samp->page());
//   }
//   samp->set_group(g);
  }

  samp->get_ref_group()->push_back(samp);

  loc_code.clear();
  result.push_back(samp);
 }
}

