
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "txh-udp-corpus.h"

//#include "dygred/dygred-deprel-callbacks.h"

#include <QDebug>

#include <QTextStream>

#include "textio.h"
USING_KANS(TextIO)

#include "ds-relae-phaon/rph-document.h"

#include "kans.h"
USING_KANS(HGDMCore)

TXH_UDP_Corpus::TXH_UDP_Corpus(QString root_folder)
  :  QRing_File_Structure(root_folder)
{


}

void TXH_UDP_Corpus::check_comments()
{
 for(TXH_UDP_Sentence& dgs : *this)
 {
  dgs.check_comments();
 }
}

void TXH_UDP_Corpus::check_write_latex()
{
 for(TXH_UDP_Sentence& dgs : *this)
 {
  if(dgs.latex_out_file().isEmpty())
    continue;
  QString latex;
  QTextStream qts(&latex);
  dgs.write_latex(qts);
  QString f = expand_external_file(dgs.latex_out_file());
  save_file(f, latex);
 }
}

void TXH_UDP_Corpus::init_sentences()
{
 QString f = files_.first();
 QString xf = expand_file(f);

 RPH_Document doc(xf);

 doc.parse();

 typedef RPH_Graph::hypernode_type hypernode_type;

// QVector<hypernode_type*> v = doc.graph()->hypernodes();

 RPH_Graph& g = *doc.graph();
 const QVector<hypernode_type*>& v = g.hypernodes();

 QString udp_text;
 QTextStream qts(&udp_text);

 resize(v.size());

 int i = 0;

 for(hypernode_type* h : v)
 {
  TXH_UDP_Sentence& sent = (*this)[i];
  ++i;
  g.get_sf(h, 1, [&sent](QPair<QString, void*>& pr)
  {
   sent.set_id(pr.first.toInt());
  });

  g.get_sf(h, 2, [&sent](QPair<QString, void*>& pr)
  {
   sent.set_corpus_name(pr.first);
  });

  g.get_sf(h, 3, [&sent](QPair<QString, void*>& pr)
  {
   sent.set_sxp_text(pr.first);
  });

  g.get_sf(h, 4, [&sent](QPair<QString, void*>& pr)
  {
   sent.set_latex_out_file(pr.first);
  });

  g.get_sf(h, 5, [&qts](QPair<QString, void*>& pr)
  {
   qts << pr.first << "\n\n";
  });
 }

 qDebug() << xf;
 save_file(xf + ".conllu", udp_text);

// for(TXH_UDP_Sentence& dgs : *this)
// {
//  QMap<QString, QList<TXH_UDP_Word_Pos*>> m;// = new QMap<QString, QList<TXH_UDP_Word_Pos*>> ;

//  TXH_UDP_Word_Pos* rvb = dgs.normalize_deps(m);

//  TXH_UDP_Deprel_Callbacks cbs;// = new TXH_UDP_Deprel_Callbacks;
//  TXH_UDP_Sentence::init_callbacks(cbs);


//  dgs.init_pairs();
//  dgs.init_groups(cbs);
//  dgs.init_group_reps();

//  dgs.resolve_internal_group_parents();
// }
}

void TXH_UDP_Corpus::report_sentence_texts(QTextStream& qts)
{
 for(TXH_UDP_Sentence& dgs : *this)
 {
  dgs.report_text(qts);
  qts << '\n';
 }
}


void TXH_UDP_Corpus::report_sentence_texts()
{
 for(TXH_UDP_Sentence& dgs : *this)
 {
  dgs.report_text();
 }
}

int TXH_UDP_Corpus::detokenize(QString outfile)
{
 QVector<sentence*> sv;

 QStringList infiles;
 expand_files(infiles);

 int result = main_detokenize(infiles,
   expand_file(outfile), &sv);

 for(sentence* s : sv)
 {
  push_back(TXH_UDP_Sentence(s));
 }

 return result;
}
