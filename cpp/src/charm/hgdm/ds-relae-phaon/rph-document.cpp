
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "rph-document.h"

#include "relae-graph/relae-parser.templates.h"

#include "kernel/graph/relae-phaon-graph.h"
#include "grammar/rph-grammar.h"
#include "grammar/rph-parser.h"
#include "grammar/rph-graph-build.h"

#include <QFileInfo>
#include <QDir>

USING_KANS(HGDMCore)


RPH_Document::RPH_Document(QString path)
 : graph_(nullptr), grammar_(nullptr)
{
 if(!path.isEmpty())
  load_file(path);
}

QVector<RPH_Graph::hypernode_type*>& RPH_Document::top_level_hypernodes()
{
 static QVector<RPH_Graph::hypernode_type*> static_default;
 if(graph_build_)
   return graph_build_->top_level_hypernodes();
 return static_default;
}

void RPH_Document::load_file(QString path)
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


void RPH_Document::resolve_report_path(QString& path)
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

void RPH_Document::report_graph(QString path)
{
 resolve_report_path(path);
 QFile file(path);
 if(file.open(QFile::WriteOnly | QIODevice::Text))
 {
  QTextStream qts(&file);
//  if(graph_)
//   graph_->report(qts);
 }
}


void RPH_Document::set_grammar(RPH_Grammar* grammar)
{
 if(grammar)
  grammar_ = grammar;
 else
  grammar_ = new RPH_Grammar();
}



void RPH_Document::parse(int start_position, int end_position)
{
//? preprocess_raw_text();



// caon_ptr<RPH_Root> root = new RPH_Root(this);
// caon_ptr<RPH_Node> node = new RPH_Node(root);
// RELAE_SET_NODE_LABEL(node, "<root>");
 graph_ = new RPH_Graph();
// graph_->set_document(this);
 parser_ = new RPH_Parser(graph_);
 parser_->set_raw_text(raw_text_);
// graph_build.reset_graph();

 graph_build_ = new RPH_Graph_Build(this, *parser_, *graph_);
 graph_build_->init();

 grammar_ = new RPH_Grammar;

 grammar_->init(*parser_, *graph_, *graph_build_);

// grammar_->activate_context(print);

 grammar_->compile(*parser_, *graph_, raw_text_, start_position);
}

RPH_Document::~RPH_Document()
{

}


