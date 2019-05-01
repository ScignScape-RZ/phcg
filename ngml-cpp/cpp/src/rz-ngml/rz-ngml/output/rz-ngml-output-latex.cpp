
#include "rz-ngml-output-latex.h"

#include "rz-ngml-output-event-generator.h"
#include "kernel/document/rz-ngml-document.h"
#include "kernel/output/rz-ngml-output-bundle.h"
#include "tag-command/rz-ngml-tag-command.h"
#include "tile/rz-ngml-paralex-tile.h"

#include "tag-command/rz-ngml-command-callback.h"

#include "kernel/graph/rz-ngml-node.h"


#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>

#include "rzns.h"
USING_RZNS(NGML)


NGML_Output_Latex::NGML_Output_Latex(NGML_Document& document)
 : NGML_Output_Base(document)
{
 init_callbacks();
}

void NGML_Output_Latex::init_callbacks()
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

 #include "rz-ngml-output-latex.callbacks.h"

}

void NGML_Output_Latex::generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Attribute_Tile> tile)
{
}


void NGML_Output_Latex::write_latex_output(QString& latex_output)
{
 QTextStream qts(&latex_output);
 generate(qts);
 latex_output.replace(QRegularExpression("\\n+"), "\n");
}

void NGML_Output_Latex::generate(QTextStream& qts)
{
 NGML_Output_Event_Generator events(*this, *this);
 events.generate(qts);
}

void NGML_Output_Latex::export_latex(QString path)
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
 QString latex_output;
 write_latex_output(latex_output);

 // //temp
 latex_output.replace("@@", "%%");
 latex_output.replace("#{", "\\scaps{");
 latex_output.replace("}#", "}");

 QFile outfile(path);
 if(outfile.open(QFile::WriteOnly | QIODevice::Text))
 {
  outfile.write(latex_output.toLatin1());
  outfile.close();
 }
}

void NGML_Output_Latex::handle_annotation(caon_ptr<NGML_Tile> tile, caon_ptr<NGML_Annotation_Tile> atile)
{
 document_.tag_command_annotation(tile, atile);
}


void NGML_Output_Latex::generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Paralex_Tile> tile)
{
 tile->write_latex(b.qts);
 check_generate_whitespace(b, tile);
}


void NGML_Output_Latex::generate_tag_command_entry(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 CAON_PTR_B_DEBUG(NGML_Node ,node)
 CAON_PTR_DEBUG(NGML_Tag_Command ,ntc)

 caon_ptr<NGML_Command_Callback> cb = b.cb;

 switch(b.connection_descriptor)
 {
 case NGML_Connection_Descriptor::Tag_Command_Cross:
 case NGML_Connection_Descriptor::Tag_Command_Entry:
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
  if(ntc->flags.is_environment)
  {
   b.qts << "\\begin{" << ntc->latex_name();// << '}';
  }
  else
   b.qts << '\\' << ntc->latex_name();// << '{';
  break;
 }
 if(caon_ptr<tNode> n = qry_.Tag_Command_Annotation(b.node))
 {
  if(caon_ptr<tNode> mt = qry_.Tag_Command_Main_Tile(b.node))
  {
   if(caon_ptr<NGML_Tile> nt = mt->ngml_tile())
    tag_command_annotation(nt, n);
  }
 }

}

void NGML_Output_Latex::generate_tag_command_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
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

 if(ntc->flags.is_environment)
 {
  b.qts << "\\end{" << ntc->latex_name() << '}';
 }
 else
  b.qts << '}';
}

void NGML_Output_Latex::generate_tag_body_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 if(ntc->flags.is_environment)
 {
  b.qts << '}';
 }
 else
  b.qts << '{';
}

caon_ptr<NGML_Command_Callback> NGML_Output_Latex::check_command_callback(caon_ptr<NGML_Tag_Command> ntc)
{
 QString name = ntc->name();
 return callbacks_.value(name, caon_ptr<NGML_Command_Callback> ( nullptr ));
}

