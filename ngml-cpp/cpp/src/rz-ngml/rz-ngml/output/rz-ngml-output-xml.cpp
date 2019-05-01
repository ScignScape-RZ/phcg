
#include "rz-ngml-output-xml.h"

#include "rz-ngml-output-event-generator.h"
#include "kernel/document/rz-ngml-document.h"
#include "kernel/output/rz-ngml-output-bundle.h"
#include "tile/rz-ngml-token.h"
#include "kernel/graph/rz-ngml-node.h"
#include "tag-command/rz-ngml-tag-command.h"
#include "kernel/rz-ngml-root.h"
#include "tag-command/rz-ngml-command-callback.h"

#include <QFile>
#include <QFileInfo>

#include "rzns.h"

USING_RZNS(NGML)


NGML_Output_Xml::NGML_Output_Xml(NGML_Document& document)
 : NGML_Output_Base(document), NGML_Output_Event_Handler()
{
 init_callbacks();
}

void NGML_Output_Xml::init_callbacks()
{
#define RENAME_(name, tag, style_class) \
 callbacks_[#name] = caon_ptr<NGML_Command_Callback>( new NGML_Command_Callback(#name, #tag, #style_class) ); \


#define RENAME_TAG(name, tag) \
 callbacks_[#name] = caon_ptr<NGML_Command_Callback>( new NGML_Command_Callback(#name, #tag) ); \


#define NGML_CALLBACK_(name) \
 callbacks_[#name] = caon_ptr<NGML_Command_Callback>( new NGML_Command_Callback(#name, \
  NGML_Command_Callback::Callback_Map_type{{ \

#define WHEN_(kind) \
 {#kind, [this](QTextStream& qts, caon_ptr<tNode> node, caon_ptr<NGML_Command_Callback> cb)

#define _WHEN },

#define _WHEN_(kind) _WHEN WHEN_(kind)

#define _NGML_CALLBACK }}) );

 #include "rz-ngml-output-xml.callbacks.h"

}

void NGML_Output_Xml::write_xml_output(QString& xml_output)
{
 QTextStream qts(&xml_output);
 generate(qts);
 xml_output.replace("$OP$", "(");
 xml_output.replace("$CP$", ")");
 xml_output.replace("$EQ$", "=");
}

void NGML_Output_Xml::generate(QTextStream& qts)
{
 NGML_Output_Event_Generator events(*this, *this);
 events.generate(qts);
}

void NGML_Output_Xml::generate_root(const NGML_Output_Bundle& b, caon_ptr<NGML_Root> nr)
{
 nr->write_whitespace(b.qts);
}


void NGML_Output_Xml::export_xml(QString path)
{
 if(path.startsWith(".."))
 {
  path.remove(0, 1);
  path.prepend(document_.local_path());
 }
 else if(path.startsWith('.'))
 {
  QFileInfo qfi(document_.local_path());
  path.prepend(qfi.absolutePath() + '/' + qfi.completeBaseName());
 }
 QString xml_output;
 write_xml_output(xml_output);

 QFile outfile(path);
 if(outfile.open(QFile::WriteOnly | QIODevice::Text))
 {
  outfile.write(xml_output.toLatin1());
  outfile.close();
 }
}

caon_ptr<NGML_Command_Callback> NGML_Output_Xml::check_command_callback(caon_ptr<NGML_Tag_Command> ntc)
{
 QString name = ntc->name();
 return callbacks_.value(name, caon_ptr<NGML_Command_Callback>( nullptr ));
}


//caon_ptr<NGML_Command_Callback> NGML_Output_Xml::check_callback
// (QTextStream& qts, caon_ptr<NGML_Tag_Command> ntc, caon_ptr<tNode> node)
//{
// caon_ptr<NGML_Command_Callback> result = nullptr;
// QString name = ntc->name();
// if(callbacks_.contains(name))
// {
//  result = callbacks_[name];
//  if(result->flags.has_pre_callback)
//  {
//   result->pre_callback(qts, node, result);
//  }
// }
// return result;
//}

void NGML_Output_Xml::check_post_callback
 (QTextStream& qts, caon_ptr<NGML_Command_Callback> cb, caon_ptr<tNode> node)
{
 if(cb->flags.has_post_callback)
 {
  cb->post_callback(qts, node, cb);
 }
}

void NGML_Output_Xml::generate_tag_command_auto_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 b.qts << "/>";
}



void NGML_Output_Xml::generate_tag_command_entry(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 CAON_PTR_B_DEBUG(NGML_Node ,node)
 chiefs_.push(b.node);
 switch(b.connection_descriptor)
 {
 case NGML_Connection_Descriptor::Tag_Command_Cross:
  //?
 case NGML_Connection_Descriptor::Tag_Command_Entry:

  caon_ptr<NGML_Command_Callback> cb = b.cb;

  if(cb)
  {
   CAON_PTR_DEBUG(NGML_Command_Callback ,cb)

   if(cb->flags.has_around_callback)
   {
    cb->around_callback(b.qts, b.node, b.cb);
    break;
   }

   if(cb->flags.has_pre_callback)
    cb->pre_callback(b.qts, b.node, b.cb);
   if(!cb->flags.pre_fallthrough)
    break;

  }

  QString command_print_name;
  if(cb && cb->flags.has_rename)
   command_print_name = cb->rename_tag();
  else
   command_print_name = ntc->name();

  QString style_class_name;
  if(cb && cb->flags.has_rename_style_class)
   style_class_name = cb->rename_style_class();

  b.qts << '\n' << '<' << command_print_name;
  if(!style_class_name.isEmpty())
   b.qts << " class='" << style_class_name << '\'';
  break;
 }
}

void NGML_Output_Xml::generate_tag_command_leave(const NGML_Output_Bundle& b,
 caon_ptr<NGML_Tag_Command> ntc)
{
 if(b.cb)
 {
  if(b.cb->flags.has_post_callback)
  {
   b.cb->post_callback(b.qts, b.node, b.cb);
  }
  if(!b.cb->flags.post_fallthrough)
   return;
 }

 QString command_print_name;
 if(b.cb && b.cb->flags.has_rename)
  command_print_name = b.cb->rename_tag();
 else
  command_print_name = ntc->name();
 b.qts << "</" << ntc->name() << '>';
}

void NGML_Output_Xml::generate_tag_body_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 b.qts << '>';
 ntc->write_whitespace(b.qts);
}


//void NGML_Output_Xml::generate_token(const NGML_Output_Bundle& b, caon_ptr<NGML_Token> token)
//{
// CAON_PTR_DEBUG(NGML_Token ,token)
// b.qts << token->to_string() << '>';
//}

//void NGML_Output_Xml::generate_space_following_token(const NGML_Output_Bundle& b)
//{
// b.qts << "\n ";
//}


//void NGML_Output_Xml::generate_call_leave(const NGML_Output_Bundle& b)
//{
// caon_ptr<NGML_Node> chief = chiefs_.top();
// chiefs_.pop();
// CAON_PTR_DEBUG(NGML_Node ,chief)
// b.qts << "<cs/";
// if(caon_ptr<NGML_Token> token = chief->ngml_token())
// {
//  b.qts << token->to_string();
// }
// b.qts << ">\n";
//}

//void NGML_Output_Xml::generate_token_connection_descriptor(const NGML_Output_Bundle& b)
//{
// switch(b.connection_descriptor)
// {
// case NGML_Connection_Descriptor::Call_Sequence:
//  b.qts << " <& |cs| ";
//  break;
// case NGML_Connection_Descriptor::Call_Continue:
//  b.qts << " <& |cc| ";
//  break;

// }
//}
