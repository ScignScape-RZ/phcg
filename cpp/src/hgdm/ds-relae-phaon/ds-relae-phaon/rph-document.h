
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RPH_DOCUMENT__H
#define RPH_DOCUMENT__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/relae-phaon-dominion.h"

#include "accessors.h"

#include "kans.h"

#include <QFile>
#include <QTextStream>



KANS_(HGDMCore)

class RPH_Parser;
class RPH_Grammar;
class RPH_Graph_Build;
class RPH_Word_Entry_List;
class RPH_Graph;
//class RPH_Graph;


class RPH_Document
{
 RPH_Graph* graph_;
 RPH_Parser* parser_;
 RPH_Graph_Build* graph_build_;
 RPH_Grammar* grammar_;

 QString local_path_;
 QString raw_text_;

 QString local_directory_;


 void preprocess_raw_text();

public:

 ACCESSORS(QString ,local_path)
 ACCESSORS(QString ,raw_text)
 ACCESSORS(QString ,local_directory)
 ACCESSORS(RPH_Graph* ,graph)
 ACCESSORS__GET(RPH_Grammar* ,grammar)

 ACCESSORS(RPH_Graph_Build* ,graph_build)

 RPH_Document(QString path);

 ~RPH_Document();

 void load_file(QString path);
 void report_graph(QString path);

 QString rph_path_handlers();

 void resolve_report_path(QString& path);

 void write_report(QString path);

 void set_grammar(RPH_Grammar* grammar = nullptr);

 void parse(int start_position = 0, int end_position = -1);

// template<typename T>
// void write_report(QString path, T& report)
// {
//  resolve_report_path(path);
//  QFile file(path);
//  if(file.open(QFile::WriteOnly | QIODevice::Text))
//  {
//   QTextStream qts(&file);
//   report.write_report(qts);
//  }
// }



};

_KANS(HGDMCore)


#endif

