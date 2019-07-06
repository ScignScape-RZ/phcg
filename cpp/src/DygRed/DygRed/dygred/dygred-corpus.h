
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DYGRED_CORPUS__H
#define DYGRED_CORPUS__H


#include "dygred-sentence.h"

#include <QVector>

#include "qring/qring-file-structure.h"

class QTextStream;

class DygRed_Corpus : public QVector<DygRed_Sentence>,
  public QRing_File_Structure
{

public:

 DygRed_Corpus(QString root_folder);

 int detokenize(QString outfile);

 void report_sentence_texts();

 void report_sentence_texts(QTextStream& qts);

 void init_sentences();
 void check_comments();


};


#endif
