
#ifndef QY_SCRIPT_DOCUMENT__H
#define QY_SCRIPT_DOCUMENT__H

//?#include "relae-graph/relae-node-ptr.h"

//?#include "kernel/sy-dominion.h"

#include "accessors.h"

#include "qyns.h"

#include <QFile>
#include <QTextStream>

#include "qhyp/qhyp-graph/qy-ptr.h"


QYNS_(QYSGraph)

class QY_Script_Parser;
class QY_Script_Grammar;
class QY_Script_Graph_Builder;
//?class SY_Script_Word_Entry_List;
class QY_Script_Graph;
//class SY_Graph;


class QY_Script_Document
{
 qy_ptr<QY_Script_Graph> graph_;
 qy_ptr<QY_Script_Parser> parser_;
 qy_ptr<QY_Script_Graph_Builder> graph_builder_;
 qy_ptr<QY_Script_Grammar> grammar_;

 QString local_path_;
 QString raw_text_;

 QString local_directory_;

 void resolve_report_path(QString& path);

 int number_of_lines_;

 void preprocess_raw_text();
 static QString insert_block_map_signatures(QString original_source, QString sig);

public:


 ACCESSORS(QString ,local_path)
 ACCESSORS(QString ,raw_text)
 ACCESSORS(QString ,local_directory)
 ACCESSORS(qy_ptr<QY_Script_Graph> ,graph)
 ACCESSORS__GET(qy_ptr<QY_Script_Grammar> ,grammar)

 ACCESSORS(qy_ptr<QY_Script_Graph_Builder> ,graph_builder)

 QY_Script_Document(QString path);

 ~QY_Script_Document();

 void load_file(QString path);
 void report_graph(QString path);

 QString qy_path_handlers();

 void write_report(QString path);

 void set_grammar(QY_Script_Grammar* grammar = nullptr);

 void parse(int start_position = 0, int end_position = -1);

 template<typename T>
 void write_report(QString path, T& report)
 {
  resolve_report_path(path);
  QFile file(path);
  if(file.open(QFile::WriteOnly | QIODevice::Text))
  {
   QTextStream qts(&file);
   report.write_report(qts);
  }
 }



};

_QYNS(QYSGraph)


#endif

