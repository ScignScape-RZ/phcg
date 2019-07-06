
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "udpipe.h"

#include <QDebug>
#include <QFile>


#include "dygred/dygred-sentence.h"
#include "dygred/dygred-corpus.h"
#include "dygred/dygred-word-pos.h"

#include "dygred/dygred-deprel-callbacks.h"

#include <QDir>

#include "textio.h"

USING_KANS(TextIO)


int main(int argc, char* argv[])
{
// QString sent = "(and (is ((The (city 's)) ambiance) colonial) (is->@ (the climate) tropical))";

// QString sent = "(and (is (The city) colonial) (xis (the climate) tropical))";
// QString sent = "(and (is city colonial) (xis (the climate) tropical))";
// QString sent = "(and (is city colonial) (xis tropical))";
//
// QString sent = "(and (is colonial) (xis tropical))";
 // QString sent = "(and (is colonial) tropical)";

// (and (is (The city) colonial) (xis (the climate) tropical))
// QString sent = "(is ((The (city 's)) ambiance) colonial)";
// QString sent = "(is (The city) colonial)";
// QString sent = "(is ((The city) ambiance) colonial)";

// QVector<DygRed_SXP_Rel_Pair> qvec;
// DygRed_Sentence::parse_sxp(sent, qvec);

// return 0;

 QString root = "&" CONLLU_DIR ;
// parse_corpus(root, qs);
 DygRed_Corpus dgc(root);

 int result = 0;

 QStringList infiles{"@/joint/j.conllu"};
 QString outfile = "@/joint/j.txt";

 dgc.add_files(infiles);
 result = dgc.detokenize(outfile);

 dgc.init_sentences();
 dgc.check_comments();

// return 0;

 QString latex;
 QTextStream qts(&latex);

 for(DygRed_Sentence& dgs : dgc)
 {
  qts << "\n\\begin{dependency}\n\\begin{deptext}\n";

  dgs.join_text(qts, " \\& ", " \\\\");
  qts << "\n";
  dgs.join_text(qts, " \\& ", " \\\\", DygRed_Sentence::Join_Field_Codes::UPOS);
  qts << "\n";
  dgs.join_text(qts, " \\& ", " \\\\", DygRed_Sentence::Join_Field_Codes::XPOS);
//  qts << "\n";
  qts << "\n\\end{deptext}\n\n";

  dgs.write_edges(qts, "\\depedge{%1}{%2}{%3}\n", "\\deproot{%1}{%2}\n");

//  \depedge{1}{2}{det}

  qts << "\n\n\\end{dependency}\n";

  QString sx = dgs.sxp_text();
  if(!sx.isEmpty())
  {
   QMap<QPair<QString, int>, QVector<const DygRed_SXP_Rel_Pair*>> qmap;

   DygRed_Sentence::scan_sxp(dgs.sxp_vector(), qmap);

   qts << "\n" << sx << "\n";
   qts << "\n\\begin{dependency}\n\\begin{deptext}\n";

   dgs.join_sxp_text(qts, qmap, " \\& ", " \\\\");
   qts << "\n";
   dgs.join_sxp_text(qts, qmap, " \\& ", " \\\\", DygRed_Sentence::Join_Field_Codes::UPOS);
   qts << "\n";
   dgs.join_sxp_text(qts, qmap, " \\& ", " \\\\", DygRed_Sentence::Join_Field_Codes::XPOS);
 //  qts << "\n";
   qts << "\n\\end{deptext}\n\n";

   dgs.write_sxp_edges(qts, qmap, "\\depedge[edge below]{%1}{%2}{%3}\n",
     "\\deproot[edge below]{%1}{%2}\n");
   qts << "\n\n\\end{dependency}\n";

  }

 }

 save_file(dgc.expand_external_file("@/joint/j.tex"), latex);

 return 0;

}

#ifdef HIDE
QString parse_to_outfile(int argc, char* argv[], DygRed_Corpus& dgc, QString model_file)
{
 QString root = dgc.root_folder();

 QStringList infiles{ root + "/t1.txt" };

 QString outfile = "@t2.txt";
 QString outf = root + "/t2.txt";

 int result = main_parse(argc, argv,
   model_file,
   infiles, outf);
 if(result != 0)
 {
  qDebug() << "Error code: " << result;
 }
 return outfile;
}

QString parse_to_outfile(DygRed_Corpus& dgc, QString model_file)
{
 QString root = dgc.root_folder();

 QStringList infiles{ root + "/t1.txt" };

 QString outfile = "@t2.txt";
 QString outf = root + "/t2.txt";

 int result = main_parse(model_file,
   infiles, outf);
 if(result != 0)
 {
  qDebug() << "Error code: " << result;
 }
 return outfile;
}

int main(int argc, char* argv[])
{
 //QString root = "C:/repos/kauv-rz/data/udpipe/examples";

//? QString root = "&" RZ_DIR "/../../udpipe/examples";
 QString root = "&" CONLLU_DIR ;

 DygRed_Corpus dgc(root);

 QString model_file = dgc.expand_external_file("@en_pud.conllu");

 //"C:/repos/kauv-rz/data/udpipe/eng/udpipe-ud-2.0-170801/english-lines-ud-2.0-170801.udpipe";

 //
 //
 QString parsefile = parse_to_outfile(dgc, model_file);
 //QString parsefile = "@t2.txt";

 int result = 0;

 QStringList infiles{parsefile};
 QString outfile = "@out/t1.txt";

 dgc.add_files(infiles);
 result = dgc.detokenize(outfile);

 DygRed_Deprel_Callbacks cbs;
 DygRed_Sentence::init_callcacks(cbs);


 DygRed_Sentence& dgs = dgc.first();

 QMap<QString, QList<DygRed_Word_Pos*>> m;

 DygRed_Word_Pos* rvb = dgs.normalize_deps(m);

 dgs.init_pairs();
 dgs.init_groups(cbs);
 dgs.init_group_reps();

 dgs.resolve_internal_group_parents();

 DygRed_Word_Pos* rr = dgs.get_adv_rep(rvb);

 //DygRed_Word_Pos* rr = dgs.guess_dock_parents(cbs);

// DygRed_Word_Pos* rr = dgs.guess_dock_parents(cbs);
// dgs.resolve_parent_claims();
//
 qDebug() << dgs.to_vstring(rr);

 return 0;
}
#endif //def HIDE

#ifdef HIDE


void save_file(QString path, DygRed_Corpus& dgc)
{
 QFile outfile(path);
 if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text))
   return;
 QTextStream outstream(&outfile);
 dgc.report_sentence_texts(outstream);
 outfile.close();
}

void parse_corpus(QString root, QString f)
{
 DygRed_Corpus dgc(root);


 int result = 0;

 QStringList infiles{QString("@%1").arg(f)};
 QString outfile = QString("@out/%1.txt").arg(f);

 dgc.add_files(infiles);
 result = dgc.detokenize(outfile);

 dgc.init_sentences();

// QTextStream qts;
 save_file(dgc.expand_external_file(outfile), dgc);
}

int main(int argc, char* argv[])
{
 QString root = "&" CONLLU_DIR ;

 QDir cdir(CONLLU_DIR);
 QStringList filters = {"*.conllu"};
 cdir.setNameFilters(filters);
 QStringList qsl = cdir.entryList();

 for(QString qs : qsl)
 {
  qDebug()<< qs;

  parse_corpus(root, qs);
 }
 //dgc.report_sentence_texts(qts);

 return 0;//result;
}

#endif //def HIDE

#ifdef HIDE


QString parse_to_outfile(int argc, char* argv[], DygRed_Corpus& dgc, QString model_file)
{
 QString root = dgc.root_folder();

 QStringList infiles{ root + "/t1.txt" };

 QString outfile = "@t2.txt";
 QString outf = root + "/t2.txt";

 int result = main_parse(argc, argv,
   model_file,
   infiles, outf);
 if(result != 0)
 {
  qDebug() << "Error code: " << result;
 }
 return outfile;
}

QString parse_to_outfile(DygRed_Corpus& dgc, QString model_file)
{
 QString root = dgc.root_folder();

 QStringList infiles{ root + "/t1.txt" };

 QString outfile = "@t2.txt";
 QString outf = root + "/t2.txt";

 int result = main_parse(model_file,
   infiles, outf);
 if(result != 0)
 {
  qDebug() << "Error code: " << result;
 }
 return outfile;
}

int main(int argc, char* argv[])
{
 //QString root = "C:/repos/kauv-rz/data/udpipe/examples";

//? QString root = "&" RZ_DIR "/../../udpipe/examples";
 QString root = "&" CONLLU_DIR ;

 DygRed_Corpus dgc(root);

 QString model_file = dgc.expand_external_file("@en_pud.conllu");

 //"C:/repos/kauv-rz/data/udpipe/eng/udpipe-ud-2.0-170801/english-lines-ud-2.0-170801.udpipe";

 //
 //
 QString parsefile = parse_to_outfile(dgc, model_file);
 //QString parsefile = "@t2.txt";

 int result = 0;

 QStringList infiles{parsefile};
 QString outfile = "@out/t1.txt";

 dgc.add_files(infiles);
 result = dgc.detokenize(outfile);

 DygRed_Deprel_Callbacks cbs;
 DygRed_Sentence::init_callcacks(cbs);


 DygRed_Sentence& dgs = dgc.first();

 QMap<QString, QList<DygRed_Word_Pos*>> m;

 DygRed_Word_Pos* rvb = dgs.normalize_deps(m);

 dgs.init_pairs();
 dgs.init_groups(cbs);
 dgs.init_group_reps();

 dgs.resolve_internal_group_parents();

 DygRed_Word_Pos* rr = dgs.get_adv_rep(rvb);

 //DygRed_Word_Pos* rr = dgs.guess_dock_parents(cbs);

// DygRed_Word_Pos* rr = dgs.guess_dock_parents(cbs);
// dgs.resolve_parent_claims();
//
 qDebug() << dgs.to_vstring(rr);

 return 0;
}

int main1(int argc, char* argv[])
{
 QString root = "C:/repos/kauv-rz/data/udpipe/set1";
 DygRed_Corpus dgc(root);

 int result = 0;

 QStringList infiles{"@t1.txt"};
 QString outfile = "@out/t1.txt";

 dgc.add_files(infiles);
 result = dgc.detokenize(outfile);




// {
//  QStringList infiles{"C:/udpipe/eng/t1.txt"};
//  QString outfile = "C:/udpipe/eng/t2.txt";
//  result = main_parse(argc, argv,
//    "C:/udpipe/eng/udpipe-ud-2.0-170801/english-lines-ud-2.0-170801.udpipe",
//    infiles, outfile);
//  if(result != 0)
//  {
//   return result;
//  }
// }
// {


//  QStringList infiles{"C:/udpipe/eng/t2.txt"};
//  QString outfile = "C:/udpipe/eng/t3.txt";

//  QVector<sentence*> sv;

//  result = main_detokenize(infiles, outfile, &sv);

//  QVector<DygRed_Sentence> dgrs;

//  for(sentence* s : sv)
//  {
//   dgrs.push_back(DygRed_Sentence(s));
//  }

//  qDebug() << sv.size();


// }
 return result;
 //
 //return main_with_qmap(argc, argv, qm, "C:/udpipe/eng/udpipe-ud-2.0-170801/english-lines-ud-2.0-170801.udpipe", files);
}



//if(rr = dgs.get_uadv(rvb, advs))
//{
// if(advs.isEmpty())
// {
//  rr->set_modifier_to_target(rvb, rlvl);
//  ++rlvl;
// }
// else
// {
//  DygRed_Word_Pos* adv = rr;
//  rr = advs.first();
//  rr->set_modifier_to_target(adv, rlvl);
//  rr->set_modifier_to_target(rvb, rlvl + 1);
//  rlvl += 2;
// }
//}
//else
//{
// rr = rvb;
//}




//int rlvl = 0;

//DygRed_Word_Pos* rr;
//QMap<DygRed_Word_Pos*, QList<DygRed_Word_Pos*>> aa;
//QList<DygRed_Word_Pos*> advs = dgs.get_uadv(rvb, aa);
//if(advs.isEmpty())
//{
// rr = rvb;
//}
//else
//{
// rr = advs.takeFirst();
// rr->set_modifier_to_target_chain(rvb, advs, rlvl, &aa);
// if(advs.isEmpty())
//   ++rlvl;
// else
//   rlvl += advs.size();
//}

//qDebug() << "Root: " << rvb->to_string();

//if(DygRed_Word_Pos* subj = dgs.get_usubject(rvb))
//{
// QList<DygRed_Word_Pos*> adjs = dgs.get_uadj(subj);
// if(adjs.isEmpty())
// {
//  rr->set_verb_to_subject(subj, rlvl);
// }
// else
// {
//  DygRed_Word_Pos* adj = adjs.takeFirst();
//  rr->set_verb_to_subject(adj, rlvl);
//  adj->set_modifier_to_target_chain(subj, adjs, 0);
// }
//}

//qDebug() << dgs.to_vstring(rr);

////QString dep = dgs.get_dep_by_word("runs");

#endif // HIDE
