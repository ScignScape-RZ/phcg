
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dygred-corpus.h"

#include "dygred/dygred-deprel-callbacks.h"

#include <QTextStream>


DygRed_Corpus::DygRed_Corpus(QString root_folder)
  :  QRing_File_Structure(root_folder)
{


}

void DygRed_Corpus::init_sentences()
{
 for(DygRed_Sentence& dgs : *this)
 {
  QMap<QString, QList<DygRed_Word_Pos*>> m;// = new QMap<QString, QList<DygRed_Word_Pos*>> ;

  DygRed_Word_Pos* rvb = dgs.normalize_deps(m);

  DygRed_Deprel_Callbacks cbs;// = new DygRed_Deprel_Callbacks;
  DygRed_Sentence::init_callbacks(cbs);


  dgs.init_pairs();
  dgs.init_groups(cbs);
  dgs.init_group_reps();

  dgs.resolve_internal_group_parents();
 }
}

void DygRed_Corpus::report_sentence_texts(QTextStream& qts)
{
 for(DygRed_Sentence& dgs : *this)
 {
  dgs.report_text(qts);
  qts << '\n';
 }
}


void DygRed_Corpus::report_sentence_texts()
{
 for(DygRed_Sentence& dgs : *this)
 {
  dgs.report_text();
 }
}

int DygRed_Corpus::detokenize(QString outfile)
{
 QVector<sentence*> sv;

 QStringList infiles;
 expand_files(infiles);

 int result = main_detokenize(infiles,
   expand_file(outfile), &sv);

 for(sentence* s : sv)
 {
  push_back(DygRed_Sentence(s));
 }

 return result;
}
