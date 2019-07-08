
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef TXH_UDP_SENTENCE__H
#define TXH_UDP_SENTENCE__H


#include "udpipe.h"

//#include "dygred-word-pos.h"

#include <QVector>

#include "accessors.h"

//class TXH_UDP_Deprel_Callbacks;
//class TXH_UDP_Word_Pair;
//class TXH_UDP_Word_Group;

class QTextStream;

struct TXH_UDP_SXP_Rel
{
 QString chief;
 int which;
 int index;
 int unw;
 int max_unw;
 int pos;
 int sxp_index;
};

struct TXH_UDP_SXP_Rel_Pair
{
 QString text;
 int which;
 int index;
 int sxp_index;
 TXH_UDP_SXP_Rel rel;
};

class TXH_UDP_Sentence
{
 quint16 id_;

 sentence* udp_sentence_;

// QVector<TXH_UDP_Word_Pos> word_poss_;
// QList<TXH_UDP_Word_Pair*> pairs_;
// QMap<TXH_UDP_Word_Pos*, QMap<QString, TXH_UDP_Word_Group*>> groups_map_;
// QMap<QPair<QString, TXH_UDP_Word_Pos*>, TXH_UDP_Word_Group*> dwg_groups_map_;
// QVector<TXH_UDP_Word_Group*> dwg_groups_;

 QVector<TXH_UDP_SXP_Rel_Pair> sxp_vector_;
 QVector<QPair<QString, int>> sxp_texts_;
 QString sxp_text_;

 QString latex_out_file_;
 QString corpus_name_;

// TXH_UDP_Word_Group* get_group(QString k, TXH_UDP_Word_Pos* dgw);

public:

 enum Join_Field_Codes {
   Text, UPOS, XPOS
 };

 explicit TXH_UDP_Sentence(sentence* udp_sentence = nullptr);


 ACCESSORS__RGET(QVector<TXH_UDP_SXP_Rel_Pair> ,sxp_vector)
 ACCESSORS(QString ,sxp_text)
 ACCESSORS(QString ,latex_out_file)
 ACCESSORS(QString ,corpus_name)
 ACCESSORS(quint16 ,id)
 ACCESSORS(sentence* ,udp_sentence)

 //?static void init_callbacks(TXH_UDP_Deprel_Callbacks& cbs);

 void init_pairs();
//? void init_groups(const TXH_UDP_Deprel_Callbacks& cbs);

 QString get_dep_by_word(QString qw, int which = 0);
 int get_id_by_word(QString qw, int which = 0);

// TXH_UDP_Word_Pos* normalize_deps(QMap<QString, QList<TXH_UDP_Word_Pos*>>& m);
// TXH_UDP_Word_Pos* guess_dock_parents(const TXH_UDP_Deprel_Callbacks& cbs);
// void resolve_parent_claims();
// TXH_UDP_Word_Pos* get_usubject(TXH_UDP_Word_Pos* dgw);
// QList<TXH_UDP_Word_Pos*> get_uadv(TXH_UDP_Word_Pos* dgw,
//    QMap<TXH_UDP_Word_Pos*, QList<TXH_UDP_Word_Pos*>>& advs);
// QList<TXH_UDP_Word_Pos*> get_uadj(TXH_UDP_Word_Pos* dgw);
// TXH_UDP_Word_Pos* get_udeprel(TXH_UDP_Word_Pos* dgw, QString dp);
// TXH_UDP_Word_Pos* get_udeprel(TXH_UDP_Word_Pos* dgw, const QSet<QString>& dps);
// QList<TXH_UDP_Word_Pos*> get_udeprels(TXH_UDP_Word_Pos* dgw, const QSet<QString>& dps);

// QString to_vstring(TXH_UDP_Word_Pos* dgw);
// QString get_pos_tag(TXH_UDP_Word_Pos* dgw);
// QString get_udeprel(TXH_UDP_Word_Pos* dgw);

// TXH_UDP_Word_Pos* get_uhead(TXH_UDP_Word_Pos* dgw);

// TXH_UDP_Word_Group* check_init_group(QString k, TXH_UDP_Word_Pos* dgw, TXH_UDP_Word_Pos* hdgw);

// TXH_UDP_Word_Group* check_init_adv_group(TXH_UDP_Word_Pos* dgw, TXH_UDP_Word_Pos* hdgw);
// TXH_UDP_Word_Group* check_init_adj_group(TXH_UDP_Word_Pos* dgw, TXH_UDP_Word_Pos* hdgw);
// TXH_UDP_Word_Group* check_init_verb_group(TXH_UDP_Word_Pos* dgw, TXH_UDP_Word_Pos* hdgw);

// void init_adj_group_rep(TXH_UDP_Word_Group& dwgg);
// void init_adv_group_rep(TXH_UDP_Word_Group& dwgg);
// void init_verb_group_rep(TXH_UDP_Word_Group& dwgg);
// TXH_UDP_Word_Pos* check_default_init_group_rep(TXH_UDP_Word_Group& dwgg);

// TXH_UDP_Word_Pos* get_adv_rep(TXH_UDP_Word_Pos* dgw);
// TXH_UDP_Word_Pos* get_rep(QString k, TXH_UDP_Word_Pos* dgw);

 void init_group_reps();

// TXH_UDP_Word_Pos* find_group_rep_not_of_kind(QString k, TXH_UDP_Word_Pos* dgw);
// TXH_UDP_Word_Group* find_group_of_kind(QString k, TXH_UDP_Word_Pos* dgw);
// TXH_UDP_Word_Pos* find_group_rep_of_kind(QString k, TXH_UDP_Word_Pos* dgw);

// void internal_resolve_adj_group(TXH_UDP_Word_Pos* dgw, TXH_UDP_Word_Pos* hdgw);
// void resolve_internal_group_parents();
// void resolve_internal_group_parents(TXH_UDP_Word_Group& dwgg);
// void default_resolve_internal_group_parents(TXH_UDP_Word_Group& dwgg, bool left_assoc);
// void verb_resolve_internal_group_parents(TXH_UDP_Word_Group& dwgg);
// void set_as_parent(TXH_UDP_Word_Pos* c, TXH_UDP_Word_Pos* p,
//   int lvl, int pos);

// void set_as_group_indirect_parent(QString ck, TXH_UDP_Word_Pos* c, QString pk, TXH_UDP_Word_Pos* p,
//   int lvl, int pos);

 void report_text();
 void report_text(QTextStream& qts);

 void join_text(QTextStream& qts, QString sep, QString end, Join_Field_Codes j = Join_Field_Codes::Text);
 void join_sxp_text(QTextStream& qts,
   QString sep, QString end, Join_Field_Codes j = Join_Field_Codes::Text);

 void write_edges(QTextStream& qts, QString templat, QString rtemplat);
 void write_sxp_edges(QTextStream& qts,
   QString templat, QString rtemplat, int root_num = 1);

 void check_comments();

 void write_latex(QTextStream& qts);

 void parse_sxp(QString sxp);
 void check_parse_sxp();

// static void scan_sxp(const QVector<TXH_UDP_SXP_Rel_Pair>& qvec);

 static void parse_sxp(QString sxp, QVector<TXH_UDP_SXP_Rel_Pair>& qvec,
   QVector<QPair<QString, int>>& sxp_texts);

// void set_verb_to_subject(int v, int s, int lvl);
// int get_adj(int n);


};


#endif
