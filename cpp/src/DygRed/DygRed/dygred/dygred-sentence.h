
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DYGRED_SENTENCE__H
#define DYGRED_SENTENCE__H


#include "udpipe.h"

#include "dygred-word-pos.h"

#include <QSet>

class DygRed_Deprel_Callbacks;
class DygRed_Word_Pair;
class DygRed_Word_Group;

class QTextStream;

struct DygRed_SXP_Rel
{
 QString chief;
 int which;
 int index;
 int unw;
 int max_unw;
 int pos;
 int sxp_index;
};

struct DygRed_SXP_Rel_Pair
{
 QString text;
 int which;
 int index;
 int sxp_index;
 DygRed_SXP_Rel rel;
};

class DygRed_Sentence
{
 sentence* udp_sentence_;

 QVector<DygRed_Word_Pos> word_poss_;

 QList<DygRed_Word_Pair*> pairs_;
 QMap<DygRed_Word_Pos*, QMap<QString, DygRed_Word_Group*>> groups_map_;

 QMap<QPair<QString, DygRed_Word_Pos*>, DygRed_Word_Group*> dwg_groups_map_;
 QVector<DygRed_Word_Group*> dwg_groups_;

 QVector<DygRed_SXP_Rel_Pair> sxp_vector_;
 QVector<QPair<QString, int>> sxp_texts_;
 QString sxp_text_;

 DygRed_Word_Group* get_group(QString k, DygRed_Word_Pos* dgw);

public:

 enum Join_Field_Codes {
   Text, UPOS, XPOS
 };

 explicit DygRed_Sentence(sentence* udp_sentence = nullptr);


 ACCESSORS__RGET(QVector<DygRed_SXP_Rel_Pair> ,sxp_vector)
 ACCESSORS(QString ,sxp_text)


 static void init_callbacks(DygRed_Deprel_Callbacks& cbs);

 void init_pairs();
 void init_groups(const DygRed_Deprel_Callbacks& cbs);

 QString get_dep_by_word(QString qw, int which = 0);
 int get_id_by_word(QString qw, int which = 0);

 DygRed_Word_Pos* normalize_deps(QMap<QString, QList<DygRed_Word_Pos*>>& m);

 DygRed_Word_Pos* guess_dock_parents(const DygRed_Deprel_Callbacks& cbs);
 void resolve_parent_claims();
 DygRed_Word_Pos* get_usubject(DygRed_Word_Pos* dgw);

 QList<DygRed_Word_Pos*> get_uadv(DygRed_Word_Pos* dgw,
    QMap<DygRed_Word_Pos*, QList<DygRed_Word_Pos*>>& advs);

 QList<DygRed_Word_Pos*> get_uadj(DygRed_Word_Pos* dgw);

 DygRed_Word_Pos* get_udeprel(DygRed_Word_Pos* dgw, QString dp);

 DygRed_Word_Pos* get_udeprel(DygRed_Word_Pos* dgw, const QSet<QString>& dps);
 QList<DygRed_Word_Pos*> get_udeprels(DygRed_Word_Pos* dgw, const QSet<QString>& dps);

 QString to_vstring(DygRed_Word_Pos* dgw);

 QString get_pos_tag(DygRed_Word_Pos* dgw);
 QString get_udeprel(DygRed_Word_Pos* dgw);

 DygRed_Word_Pos* get_uhead(DygRed_Word_Pos* dgw);

 DygRed_Word_Group* check_init_group(QString k, DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw);

 DygRed_Word_Group* check_init_adv_group(DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw);
 DygRed_Word_Group* check_init_adj_group(DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw);
 DygRed_Word_Group* check_init_verb_group(DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw);

 void init_adj_group_rep(DygRed_Word_Group& dwgg);
 void init_adv_group_rep(DygRed_Word_Group& dwgg);
 void init_verb_group_rep(DygRed_Word_Group& dwgg);
 DygRed_Word_Pos* check_default_init_group_rep(DygRed_Word_Group& dwgg);

 DygRed_Word_Pos* get_adv_rep(DygRed_Word_Pos* dgw);
 DygRed_Word_Pos* get_rep(QString k, DygRed_Word_Pos* dgw);

 void init_group_reps();

 DygRed_Word_Pos* find_group_rep_not_of_kind(QString k, DygRed_Word_Pos* dgw);
 DygRed_Word_Group* find_group_of_kind(QString k, DygRed_Word_Pos* dgw);
 DygRed_Word_Pos* find_group_rep_of_kind(QString k, DygRed_Word_Pos* dgw);

 void internal_resolve_adj_group(DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw);
 void resolve_internal_group_parents();
 void resolve_internal_group_parents(DygRed_Word_Group& dwgg);
 void default_resolve_internal_group_parents(DygRed_Word_Group& dwgg, bool left_assoc);
 void verb_resolve_internal_group_parents(DygRed_Word_Group& dwgg);
 void set_as_parent(DygRed_Word_Pos* c, DygRed_Word_Pos* p,
   int lvl, int pos);

 void set_as_group_indirect_parent(QString ck, DygRed_Word_Pos* c, QString pk, DygRed_Word_Pos* p,
   int lvl, int pos);

 void report_text();
 void report_text(QTextStream& qts);

 void join_text(QTextStream& qts, QString sep, QString end, Join_Field_Codes j = Join_Field_Codes::Text);
 void join_sxp_text(QTextStream& qts,
   QString sep, QString end, Join_Field_Codes j = Join_Field_Codes::Text);

 void write_edges(QTextStream& qts, QString templat, QString rtemplat);
 void write_sxp_edges(QTextStream& qts,
   QString templat, QString rtemplat, int root_num = 1);

 void check_comments();

 void parse_sxp(QString sxp);

// static void scan_sxp(const QVector<DygRed_SXP_Rel_Pair>& qvec);

 static void parse_sxp(QString sxp, QVector<DygRed_SXP_Rel_Pair>& qvec,
   QVector<QPair<QString, int>>& sxp_texts);

// void set_verb_to_subject(int v, int s, int lvl);
// int get_adj(int n);


};


#endif
