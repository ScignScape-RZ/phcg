
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RTXH_DOCUMENT__H
#define RTXH_DOCUMENT__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/relae-txh-dominion.h"

#include "accessors.h"

#include "kans.h"

#include <QFile>
#include <QTextStream>

#include "kernel/graph/relae-txh-graph.h"

KANS_(HGDMCore)

class RTXH_Parser;
class RTXH_Grammar;
class RTXH_Graph_Build;
class RTXH_Word_Entry_List;
class RTXH_Graph;
//class RTXH_Graph;


class RTXH_Document
{
 RTXH_Graph* graph_;
 RTXH_Parser* parser_;
 RTXH_Graph_Build* graph_build_;
 RTXH_Grammar* grammar_;

 QString local_path_;
 QString raw_text_;

 QString local_directory_;


 void preprocess_raw_text();

public:

 ACCESSORS(QString ,local_path)
 ACCESSORS(QString ,raw_text)
 ACCESSORS(QString ,local_directory)
 ACCESSORS(RTXH_Graph* ,graph)
 ACCESSORS__GET(RTXH_Grammar* ,grammar)

 ACCESSORS(RTXH_Graph_Build* ,graph_build)

 RTXH_Document(QString path);

 ~RTXH_Document();

 QVector<RTXH_Graph::hypernode_type*>& top_level_hypernodes();

 void load_file(QString path);
 void report_graph(QString path);

 QString rtxh_path_handlers();

 void resolve_report_path(QString& path);

 void write_report(QString path);

 void set_grammar(RTXH_Grammar* grammar = nullptr);

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

