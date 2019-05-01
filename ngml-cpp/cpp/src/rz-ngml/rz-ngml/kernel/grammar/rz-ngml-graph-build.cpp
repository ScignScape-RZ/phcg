
#include "rz-ngml-graph-build.h"

#include "tile/rz-ngml-tile.h"
#include "kernel/graph/rz-ngml-graph.h"
#include "tag-command/rz-ngml-tag-command.h"
#include "whitespace/rz-ngml-whitespace.h"
#include "kernel/rz-ngml-root.h"
#include "tile/rz-ngml-attribute-tile.h"
#include "tile/rz-ngml-paralex-tile.h"

#include "annotation/rz-ngml-annotation-tile.h"

#include "kernel/document/rz-ngml-document-info.h"
#include "kernel/document/rz-ngml-document-light-xml.h"

#include "rzns.h"

#include <QDebug>


USING_RZNS(NGML)

NGML_Graph_Build::NGML_Graph_Build(NGML_Graph& g, NGML_Document_Info& document_info)
 : markup_position_(g.root_node()), acc_mode_(Main_Tile), document_info_(document_info),
   current_parsing_mode_(NGML_Parsing_Modes::NGML), //?current_annotation_tile_(nullptr),
   qts_tile_acc_(&tile_acc_), qts_string_literal_acc_(&string_literal_acc_)
{

}


void NGML_Graph_Build::init()
{

}


void NGML_Graph_Build::enter_multiline_comment(QString semis, QString tildes)
{
 markup_position_.enter_multiline_comment(cutmax(semis.length()), cutmax(tildes.length()));
 parse_context_.flags.inside_multiline_comment = true;
}

void NGML_Graph_Build::check_leave_multiline_comment(QString semis, QString tildes)
{
 if(markup_position_.check_leave_multiline_comment(cutmax(tildes.length()),
  cutmax(tildes.length())));
 parse_context_.flags.inside_multiline_comment = false;
}

void NGML_Graph_Build::tile_acc(QString str)
{
 qts_tile_acc_ << str;
}


void NGML_Graph_Build::tag_command_annotation(QString annotation)
{
 //?
 // current_annotation_tile_ = new NGML_Annotation_Tile("");
 // current_annotation_tile_->set_connector(annotation);
 // caon_ptr<tNode> node = make_new_node(current_annotation_tile_);
 // markup_position_.tag_command_annotation(node);
}

void NGML_Graph_Build::annotation_entry(QString flag, QString text, QString rel, QString tile, QString follow)
{
 check_tile_acc();

 QString annotation_text = text;
 if(flag == "*")
 {
  annotation_text.prepend("*:");
 }

 caon_ptr<NGML_Tile> ntile = new NGML_Tile(annotation_text);
 caon_ptr<NGML_Annotation_Tile> atile = new NGML_Annotation_Tile;
 //atile->set_subject(text);
 caon_ptr<tNode> node = make_new_node(ntile);
 caon_ptr<tNode> anode = make_new_node(atile);
 CAON_PTR_DEBUG(tNode ,node)
 if(rel.isEmpty())
 {
  markup_position_.annotation_entry(node, anode);
  flags.active_annotation_entry = true;
  if(!tile.isEmpty())
  {
   atile->set_tile(tile);
  }
  if(follow == ";")
  {
   markup_position_.close_annotation();
   flags.active_annotation_entry = false;
  }
  else
   flags.active_annotation_tile = true;
 }
 else
 {
  atile->set_connector(rel);
  //?current_annotation_tile_->set_connector(rel);
  markup_position_.annotation_entry(node, anode);
  if(!tile.isEmpty())
  {
   atile->set_tile(tile);
   //?current_annotation_tile_->set_tile(tile);
  }
  if(follow == ";")
  {
   markup_position_.close_annotation();
   flags.active_annotation_entry = false;
  }
  else
   flags.active_annotation_tile = true;
 }
}

void NGML_Graph_Build::check_tile_acc(Acc_Mode new_mode)
{
 if(tile_acc_.isEmpty())
 {
  acc_mode_ = new_mode;
  return;
 }
 if(tile_acc_.trimmed().isEmpty())
 {
  attach_whitespace(tile_acc_);
  qts_tile_acc_.reset();
  tile_acc_.clear();
  acc_mode_ = new_mode;
  return;
 }
 switch(acc_mode_)
 {
 case Main_Tile:
  attach_left_whitespace();
  check_add_words();
  add_tile(tile_acc_.trimmed());
  attach_right_whitespace();
  qts_tile_acc_.reset();
  tile_acc_.clear();
  break;

 case Attribute:
  add_attribute_tile(tile_acc_);
  qts_tile_acc_.reset();
  tile_acc_.clear();
  break;

 default: break;
 }
 acc_mode_ = new_mode;
}

void NGML_Graph_Build::check_add_words()
{
 QStringList strings = tile_acc_.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);
 for(QString s : strings)
 {
  QRegularExpression rx_start("\\A\\$(\\w+)\\$");
  QRegularExpressionMatch rxm_start = rx_start.match(s);

  QRegularExpression rx_end("\\$(\\w+)\\$\\W*\\Z");
  QRegularExpressionMatch rxm_end = rx_end.match(s);

  if(rxm_start.hasMatch())
  {
   QString key = rxm_start.captured(1);
   s = s.mid(rxm_start.capturedEnd());
   if(key == "LDQ")
   {
    quote_acc_ += s + " ";
   }
  }
  else if(rxm_end.hasMatch())
  {
   QString key = rxm_end.captured(1);
   s = s.mid(0, rxm_end.capturedStart());
   if(key == "RDQ")
   {
    quote_acc_ += s;
    document_info_.add_quote(quote_acc_);
    quote_acc_.clear();
   }
  }
  else if(!quote_acc_.isEmpty())
  {
   quote_acc_ += s + " ";
  }


  if(s.contains('@'))
   continue;
  if(s.contains("//"))
   continue;
  if(s.count('.') > 1)
   continue;
  if(s.contains('/') && s.contains('.'))
   continue;

  if(s.contains(QRegularExpression("\\d")))
   continue;

  s.replace("&apos;", "");
  s.replace(QRegularExpression("&\\w+;"), "");
  s.replace(QRegularExpression("[^\\w']"), "");
  if(!s.isEmpty())
  {
   document_info_.add_word(s);
  }
 }
}


void NGML_Graph_Build::mark_attribute_tile()
{
 check_tile_acc(Attribute);
}



void NGML_Graph_Build::attach_left_whitespace()
{
 if(get_light_xml())
 {
  return;
 }
 int index = tile_acc_.indexOf(QRegularExpression("\\S"));
 if(index > 0)
 {
  attach_whitespace(tile_acc_.left(index));
 }
}

void NGML_Graph_Build::attach_right_whitespace()
{
 if(get_light_xml())
 {
  return;
 }

 int index = tile_acc_.lastIndexOf(QRegularExpression("\\S\\s+\\Z"));
 if(index != -1)
 {
  attach_whitespace(tile_acc_.mid(index + 1));
 }
}


void NGML_Graph_Build::attach_whitespace(QString whitespace)
{
 if(get_light_xml())
 {
  return;
 }
#ifndef NO_CAON
 if(caon_ptr<tNode> node = markup_position_.current_node())
 {
  CAON_PTR_DEBUG(tNode ,node)
  caon_ptr<NGML_Whitespace_Holder> nwh = node->as<NGML_Whitespace_Holder>();
  nwh->attach_whitespace(whitespace);
 }
#endif //NO_CAON
}

void NGML_Graph_Build::end_khif_tile(QString connector_prefix, QString connectors)
{
 end_khif_tile();

 bool string_follow = (connector_prefix.startsWith('+'));
 bool subject_claim = (connector_prefix.endsWith('['));
 markup_position_.load_khif_connectors(connectors);

 parse_context_.flags.inside_khif_tile = true;

}


void NGML_Graph_Build::attach_khif_tile()
{
 if(!khif_tile_.isEmpty())
 {
  QString kt = khif_tile_.trimmed();
  if(!kt.isEmpty())
  {
   if(markup_position_.expecting_khif_attribute_tile())
   {
    QRegularExpression rx("(\\S+)\\s*(\\S*)");
    QRegularExpressionMatch match = rx.match(kt);
    QString attribute = match.captured(1);
    QString value = match.captured(2);
    caon_ptr<NGML_Attribute_Tile> tile = make_new_attribute_tile(attribute, value);
    khif_tile_.clear();
    CAON_PTR_DEBUG(NGML_Attribute_Tile ,tile)
    caon_ptr<tNode> node = make_new_node(tile);
    markup_position_.add_khif_tile_node(node);
   }
   else
   {
    caon_ptr<NGML_Tile> tile = make_new_tile(kt);
    CAON_PTR_DEBUG(NGML_Tile ,tile)
    khif_tile_.clear();
    caon_ptr<tNode> node = make_new_node(tile);
    markup_position_.add_khif_tile_node(node);
   }
  }
 }
}

void NGML_Graph_Build::end_khif_tile()
{
 //? parse_context.flags.inside_khif_tile = false;
 attach_khif_tile();
 markup_position_.khif_tag_command_leave();
}


void NGML_Graph_Build::enter_tag_command_with_predicate_vector(QString tag_command,
 QString connector_prefix, QString connectors)
{
 bool string_follow = (connector_prefix.startsWith('+'));
 bool subject_claim = (connector_prefix.endsWith('['));

 caon_ptr<NGML_Tag_Command> ntc = make_new_tag_command(tag_command);
 caon_ptr<tNode> node = make_new_node(ntc);

 markup_position_.tag_command_entry(node);

 markup_position_.load_khif_connectors(connectors);

 parse_context_.flags.inside_khif_tile = true;

}


void NGML_Graph_Build::khif_tile_acc(QString m)
{
 khif_tile_ += m;
}

void NGML_Graph_Build::attach_predicate_vector(QString connector_prefix, QString connectors)
{
 attach_khif_tile();
 bool string_follow = (connector_prefix.startsWith('+'));
 bool subject_claim = (connector_prefix.endsWith('['));
 markup_position_.load_khif_connectors(connectors);
}


caon_ptr<NGML_Tag_Command> NGML_Graph_Build::html_tag_instruction(QString prefix,
 QString tag_command, QString argument)
{
 check_tile_acc();

 caon_ptr<NGML_Tag_Command> ntc = make_new_tag_command(tag_command);
 if(prefix == "!")
  ntc->flags.is_tag_assertion = true;
 else if(prefix == "?")
  ntc->flags.is_tag_query = true;

 ntc->flags.is_html = true;
 ntc->flags.is_understood_auto_closed = true;

 caon_ptr<tNode> node = make_new_node(ntc);

 caon_ptr<tNode> current_node = markup_position_.tag_command_instruction(node);
 tag_body_leave();
 tile_acc(argument);
 check_tile_acc();
 markup_position_.restore_current_node(current_node);

 return ntc;

}



caon_ptr<NGML_Tag_Command> NGML_Graph_Build::html_tag_command_entry(QString prefix, QString tag_command)
{
 check_tile_acc();

 if(get_light_xml())
 {
  get_light_xml()->tag_entry(tag_command);
  parse_context_.flags.inside_html_tag_body = true;
  return nullptr;
 }

 caon_ptr<NGML_Tag_Command> ntc = make_new_tag_command(tag_command);
 caon_ptr<tNode> node = make_new_node(ntc);

 markup_position_.tag_command_entry(node);
 parse_context_.flags.inside_html_tag_body = true;
 ntc->flags.is_html = true;

 return ntc;

}

caon_ptr<NGML_Tag_Command> NGML_Graph_Build::tag_command_entry(QString prefix, QString tag_command, QString parent_tag_type)
{
 check_tile_acc();
 caon_ptr<NGML_Tag_Command> ntc = make_new_tag_command(tag_command, parent_tag_type);

 if(prefix == "/")
  ntc->flags.is_environment = true;

 caon_ptr<tNode> node = make_new_node(ntc);
 markup_position_.tag_command_entry(node);
 parse_context_.flags.inside_tag_body = true;

 return ntc;
}


void NGML_Graph_Build::html_tag_command_attribute_entry(QString pre_space,
 QString attribute, QString s_or_d)
{
 current_html_attribute_ = attribute;
 if(s_or_d == "'")
  parse_context_.flags.inside_html_tag_attribute_single_quote = true;
 else if(s_or_d == "\"")
  parse_context_.flags.inside_html_tag_attribute_double_quote = true;
}

void NGML_Graph_Build::html_tag_command_attribute_acc(QString str)
{
 tile_acc_ += str;
}

caon_ptr<NGML_Attribute_Tile> NGML_Graph_Build::complete_html_tag_command_attribute()
{
 if(get_light_xml())
 {
  get_light_xml()->add_attribute_tile(current_html_attribute_, tile_acc_);
  tile_acc_.clear();
  current_html_attribute_.clear();
  document_info_.check_light_xml_href();
 }


 caon_ptr<NGML_Attribute_Tile> tile =  make_new_attribute_tile(current_html_attribute_, tile_acc_);

 CAON_PTR_DEBUG(NGML_Attribute_Tile ,tile)
 if(tile->key() == "href")
 {
  QString tag = markup_position_.current_tag_command_name();
  document_info_.add_href(tag, tile->value());
 }
 caon_ptr<tNode> node = make_new_node(tile);
 markup_position_.add_attribute_tile_node(node);

 current_html_attribute_ = QString();
 tile_acc_ = QString();

 parse_context_.flags.inside_html_tag_attribute_double_quote = false;
 parse_context_.flags.inside_html_tag_attribute_single_quote = false;
 parse_context_.flags.inside_html_tag_body = true;

 return tile;

}

NGML_Document_Light_Xml* NGML_Graph_Build::get_light_xml()
{
 return document_info_.light_xml();
}

void NGML_Graph_Build::tag_command_entry_inline(QString tag_command,
 QString tag_body_follow, QString argument)
{
 Tag_Body_Follow_Mode m = parse_tag_body_follow(tag_body_follow);
 QString prefix;
 switch(m)
 {
 case Normal:
  tag_command_entry(prefix, tag_command);
  tag_body_leave();
  tile_acc(argument);
  break;
 case Environment:
  {
   caon_ptr<NGML_Tag_Command> ntc = tag_command_entry(prefix, tag_command);
   ntc->flags.is_environment = true;
   tag_body_leave();
   tile_acc(argument);
   break;
 }
 case Empty:
  tag_command_entry(prefix, tag_command);
  tag_body_leave();
  tile_acc(argument);
  tag_command_leave(); break;

 }
}


caon_ptr<NGML_Tag_Command> NGML_Graph_Build::make_new_tag_command(QString name, QString parent_tag_type)
{
 return caon_ptr<NGML_Tag_Command>( new NGML_Tag_Command(name, parent_tag_type) );
}


caon_ptr<NGML_Tile> NGML_Graph_Build::add_tile(QString tile_str)
{
 if(get_light_xml())
 {
  get_light_xml()->add_tile(tile_str);
  return nullptr;
 }

 caon_ptr<NGML_Tile> tile = make_new_tile(tile_str);
 caon_ptr<tNode> node = make_new_node(tile);
 //?
 markup_position_.add_tile_node(node);
 return tile;
}

caon_ptr<NGML_Attribute_Tile> NGML_Graph_Build::add_attribute_tile(QString tile_str)
{
 if(get_light_xml())
 {
  get_light_xml()->add_attribute_tile(tile_str);
  return nullptr;
 }

 caon_ptr<NGML_Attribute_Tile> tile = make_new_attribute_tile(tile_str);
 CAON_PTR_DEBUG(NGML_Attribute_Tile ,tile)
 caon_ptr<tNode> node = make_new_node(tile);
 markup_position_.add_attribute_tile_node(node);
 return tile;
}


void NGML_Graph_Build::add_string_literal_tile(QString str)
{
 //? caon_ptr<NGML_Tile> tile = add_tile(str);
 //? tile->flags.is_string_literal = true;
}

void NGML_Graph_Build::tag_command_leave(QString connector_to_load, QString tag_command)
{

}

void NGML_Graph_Build::inline_tag_command_leave()
{
 if(caon_ptr<tNode> node = markup_position_.tag_command_leave())
 {
  CAON_PTR_DEBUG(tNode ,node)
  check_tile_acc();
  markup_position_.confirm_tag_command_leave(node);
 }
}

void NGML_Graph_Build::tag_command_leave()
{
 if(caon_ptr<tNode> node = markup_position_.tag_command_leave())
 {
  CAON_PTR_DEBUG(tNode ,node)
  check_tile_acc();
  markup_position_.confirm_tag_command_leave(node);
 }
}

void NGML_Graph_Build::tag_command_instruction_leave(caon_ptr<tNode> node)
{
 check_tile_acc();
 markup_position_.restore_current_node(node);
}

void NGML_Graph_Build::check_html_tag_command_leave(QString tag_command, QString match_text)
{
 check_tile_acc();

 if(get_light_xml())
 {
  get_light_xml()->tag_leave(tag_command);
  return;
 }

 markup_position_.rewind_tag_command_leave(tag_command);
}

void NGML_Graph_Build::check_tag_command_leave(QString tag_command, QString match_text)
{
 // //  If the tag command does not match the current node, treat the whole match
  //    as just text to accumulate
 if(caon_ptr<tNode> node = markup_position_.check_tag_command_leave(tag_command))
 {
  CAON_PTR_DEBUG(tNode ,node)
  check_tile_acc();
  markup_position_.confirm_tag_command_leave(node);
 }
 else
 {
  tile_acc(match_text);
 }
}

//void NGML_Graph_Build::add_string_literal_tile()
//{
// if(!tile_acc_.isEmpty())
// {
//  // //  This will happen if a string literal is preceeded by a
//  //     string without whitespace; that could be used to create
//  //     special kinds of string literals.
//  //     This could be a spot for a callback which takes the
//  //     tile_acc_ string before clearing it.
//  tile_acc_.clear();
//  qts_tile_acc_.reset();
// }
// add_string_literal_tile(string_literal_acc_);
// string_literal_acc_.clear();
// qts_string_literal_acc_.reset();
//}

caon_ptr<NGML_Attribute_Tile> NGML_Graph_Build::make_new_attribute_tile(QString tile)
{
 QRegularExpression rx("(\\S+)\\s+(.+)", QRegularExpression::DotMatchesEverythingOption);
 QRegularExpressionMatch rxm = rx.match(tile);
 if(rxm.hasMatch())
 {
  return caon_ptr<NGML_Attribute_Tile>(
   new NGML_Attribute_Tile(rxm.captured(1), rxm.captured(2)) );
 }
}

caon_ptr<NGML_Attribute_Tile> NGML_Graph_Build::make_new_attribute_tile(QString key, QString value)
{
 return caon_ptr<NGML_Attribute_Tile>(
  new NGML_Attribute_Tile(key, value) );
}

caon_ptr<NGML_Tile> NGML_Graph_Build::make_new_tile(QString tile)
{
  return caon_ptr<NGML_Tile>( new NGML_Tile(tile) );
}


caon_ptr<NGML_Paralex_Tile> NGML_Graph_Build::make_new_paralex_tile(QString tile)
{
 return caon_ptr<NGML_Paralex_Tile>( new NGML_Paralex_Tile(tile) );
}


caon_ptr<NGML_Graph_Build::tNode> NGML_Graph_Build::make_new_node(caon_ptr<NGML_Tile> tile)
{
 CAON_PTR_DEBUG(NGML_Tile ,tile)
 caon_ptr<tNode> result = caon_ptr<tNode>( new tNode(tile) );
 #ifdef RELAE_LABEL_NODES
 result->set_label(tile->thumbnail());
 #endif
 return result;
}


void NGML_Graph_Build::special_character_sequence(QString match_text)
{
 check_tile_acc();
 caon_ptr<NGML_Paralex_Tile> xtile = make_new_paralex_tile(match_text);
 caon_ptr<tNode> node = make_new_node(xtile);
 markup_position_.add_tile_node(node);
}

caon_ptr<NGML_Graph_Build::tNode> NGML_Graph_Build::make_new_node(caon_ptr<NGML_Annotation_Tile> tile)
{
 caon_ptr<tNode> result = new tNode(tile);
 result->set_label(tile->thumbnail());
 return result;
}

caon_ptr<NGML_Graph_Build::tNode> NGML_Graph_Build::make_new_node(caon_ptr<NGML_Annotation_Tile> tile, QString label)
{
 caon_ptr<tNode> result = new tNode(tile);
 result->set_label(label);
 return result;
}

caon_ptr<NGML_Graph_Build::tNode> NGML_Graph_Build::make_new_node(caon_ptr<NGML_Attribute_Tile> tile)
{
 CAON_PTR_DEBUG(NGML_Attribute_Tile ,tile)
 caon_ptr<tNode> result = caon_ptr<tNode>( new tNode(tile) );
 #ifdef RELAE_LABEL_NODES
 result->set_label(tile->thumbnail());
 #endif
 return result;
}

caon_ptr<NGML_Graph_Build::tNode> NGML_Graph_Build::make_new_node(caon_ptr<NGML_Paralex_Tile> tile)
{
 CAON_PTR_DEBUG(NGML_Paralex_Tile ,tile)
 caon_ptr<tNode> result = caon_ptr<tNode>( new tNode(tile) );
 #ifdef RELAE_LABEL_NODES
 result->set_label(tile->thumbnail());
 #endif
 return result;
}

caon_ptr<NGML_Graph_Build::tNode> NGML_Graph_Build::make_new_node(caon_ptr<NGML_Tag_Command> ntc)
{
 CAON_PTR_DEBUG(NGML_Tag_Command ,ntc)
 caon_ptr<tNode> result = caon_ptr<tNode>( new tNode(ntc) );
 #ifdef RELAE_LABEL_NODES
 result->set_label(ntc->name());
 #endif
 return result;
}


void NGML_Graph_Build::tag_body_leave(QString match)
{
 check_tile_acc();
 markup_position_.tag_body_leave();
 parse_context_.flags.inside_tag_body = false;
 if(match == "/>")
  tag_command_leave();
}

void NGML_Graph_Build::html_tag_body_leave(QString prefix)
{

 if(get_light_xml())
 {
  get_light_xml()->tag_body_leave(prefix);
  parse_context_.flags.inside_html_tag_body = false;
  return;
 }

 markup_position_.tag_body_leave();
 parse_context_.flags.inside_html_tag_body = false;
 if(prefix == "/")
  tag_command_leave();
}

