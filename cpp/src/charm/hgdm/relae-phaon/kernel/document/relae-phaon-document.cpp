
#include "qyscript-document.h"

//?#include "relae-graph/relae-parser.templates.h"

#include "kernel/graph/qyscript-graph.h"
#include "kernel/grammar/qyscript-grammar.h"
#include "kernel/grammar/qyscript-parser.h"
#include "kernel/grammar/qyscript-graph-builder.h"

#include "qy-relae/qy-relae-grammar/qy-relae-parser.templates.h"

#include <QFileInfo>
#include <QDir>

USING_QYNS(QYSGraph)


QY_Script_Document::QY_Script_Document(QString path)
 : graph_(nullptr), grammar_(nullptr), number_of_lines_(0)
{
 if(!path.isEmpty())
  load_file(path);
}

void QY_Script_Document::load_file(QString path)
{
 QFile file(path);
 if(file.open(QFile::ReadOnly | QIODevice::Text))
 {
  raw_text_ = file.readAll();
  local_path_ = path;
  QFileInfo qfi(local_path_);
  local_directory_ = qfi.absoluteDir().absolutePath();
 }
}


void QY_Script_Document::resolve_report_path(QString& path)
{
 if(path.startsWith('.'))
 {
  path = path.mid(1);
  if(path.startsWith('.'))
  {
   path = local_path_ + path;
  }
  else
  {
//   QFileInfo qfi(local_path_);
  }
 }
}

void QY_Script_Document::report_graph(QString path)
{
 resolve_report_path(path);
 QFile file(path);
 if(file.open(QFile::WriteOnly | QIODevice::Text))
 {
  QTextStream qts(&file);
  if(graph_)
   graph_->report(qts);
 }
}


void QY_Script_Document::set_grammar(QY_Script_Grammar* grammar)
{
 if(grammar)
  grammar_ = grammar;
 else
  grammar_ = new QY_Script_Grammar();
}



void QY_Script_Document::parse(int start_position, int end_position)
{
//? preprocess_raw_text();



// caon_ptr<SY_Root> root = new SY_Root(this);
// caon_ptr<SY_Node> node = new SY_Node(root);
// RELAE_SET_NODE_LABEL(node, "<root>");
 graph_ = new QY_Script_Graph();
// graph_->set_document(this);
 parser_ = new QY_Script_Parser(graph_);
 parser_->set_raw_text(raw_text_);
// graph_build.reset_graph();

 graph_builder_ = new QY_Script_Graph_Builder(this, *parser_, *graph_);
 graph_builder_->init();

 grammar_ = new QY_Script_Grammar;

 grammar_->init(*parser_, *graph_, *graph_builder_);

// grammar_->activate_context(print);

 grammar_->compile(*parser_, *graph_, raw_text_, start_position);
}

QY_Script_Document::~QY_Script_Document()
{

}


