
#include "rz-ngml-output-khif.h"

#include "rz-ngml-output-event-generator.h"
#include "kernel/document/rz-ngml-document.h"
#include "kernel/output/rz-ngml-output-bundle.h"
#include "tile/rz-ngml-token.h"
#include "kernel/graph/rz-ngml-node.h"
#include "tag-command/rz-ngml-tag-command.h"
#include "kernel/rz-ngml-root.h"
#include "tag-command/rz-ngml-command-callback.h"

#include "tile/rz-ngml-attribute-tile.h"
#include "tile/rz-ngml-tile.h"
#include "tile/rz-ngml-paralex-tile.h"

#include <QTextStream>
#include <QDebug>

#include <QRegExp>
#include <QRegularExpression>

#include <QFileInfo>

#include "rzns.h"
USING_RZNS(NGML)


NGML_Output_Khif::NGML_Output_Khif(NGML_Document& ngd)
 : NGML_Output_Base(ngd), NGML_Output_Event_Handler()
{
 init_callbacks();
}

void NGML_Output_Khif::init_callbacks()
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

 #include "rz-ngml-output-khif.callbacks.h"

}

void NGML_Output_Khif::write_khif_output(QString& khif_output)
{
 QTextStream qts(&khif_output);
 generate(qts);

 khif_output.replace(QRegularExpression("\\+\\[\\w+\\]\\s+\\$NOSTAG\\$"), "");
 khif_output.replace(QRegularExpression("\\$NOETAG\\$\\s+\\+\\[\\w+\\]"), "");
 khif_output.replace(QRegularExpression("(&\\w+;)\\s+([,:!?.;])"), "\\1\\2");

}

void NGML_Output_Khif::insert_khif_link(QTextStream& qts)
{
 QString file = document_.local_path();
 QFileInfo qfi(file);
 QString file_name = qfi.baseName();

 qts << QString("(khif-link \"%1\")").arg(file_name);

 // should translate to, something like ...
 // qts << QString("(div +[@] class kf-link +[e] (span +[e] (span +[m] "
 //  "View as:) +[x] (a +[@] href %1 +[m] ngml) +[x] "
 //                "(a +[@] href %2 +[m] khif)) +[x] (hr +[s]))"
 // ).arg(ngml_link).arg(khif_link);



}


void NGML_Output_Khif::process_khi_file_info(QTextStream& qts, caon_ptr<NGML_Node> node)
{
 CAON_PTR_DEBUG(NGML_Node ,node)

 if(caon_ptr<NGML_Node> n = qry_.Tag_Command_Main_Tile(node))
 {
  if(caon_ptr<NGML_Tile> tile = n->ngml_tile())
  {
   CAON_PTR_DEBUG(NGML_Tile ,tile)
   QString s = tile->raw_text();
   document_.set_khi_info(s);
  }
 }
}


void NGML_Output_Khif::generate(QTextStream& qts)
{
 NGML_Output_Event_Generator events(*this, *this);
 events.generate(qts);
}

void NGML_Output_Khif::generate_root(const NGML_Output_Bundle& b, caon_ptr<NGML_Root> nr)
{
 nr->write_whitespace(b.qts);
}


caon_ptr<NGML_Command_Callback> NGML_Output_Khif::check_command_callback(caon_ptr<NGML_Tag_Command> ntc)
{
 QString name = ntc->name();
 return callbacks_.value(name, caon_ptr<NGML_Command_Callback>( nullptr ) );
}


void NGML_Output_Khif::generate_tag_command_entry(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 CAON_PTR_B_DEBUG(NGML_Node ,node)
 chiefs_.push(b.node);
 switch(b.connection_descriptor)
 {
 case NGML_Connection_Descriptor::Tag_Command_Cross:
  b.qts << " +[x] ";
  // fallthrough...

 case NGML_Connection_Descriptor::Tag_Command_Cross_From_Blank:

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

  b.qts << '(' << command_print_name;
  if(!style_class_name.isEmpty())
   b.qts << " +[@] class " << style_class_name << ' ';
  break;
 }

}

void NGML_Output_Khif::generate_tag_command_auto_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 b.qts << " +[s] ";
 generate_tag_command_leave(b, ntc);
}


void NGML_Output_Khif::generate_tag_command_leave(const NGML_Output_Bundle& b,
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
 b.qts << " )";
}

void NGML_Output_Khif::generate_tag_command_entry_connector(const NGML_Output_Bundle& b)
{
 b.qts << " +[h] ";
}

void NGML_Output_Khif::generate_tag_body_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 CAON_PTR_DEBUG(NGML_Tag_Command ,ntc)
 if(ntc->flags.has_main_tile)
 {
  b.qts << " +[m] ";
 }
 else if(ntc->flags.has_entry)
 {
  b.qts << " +[e] ";
 }
 else if(!ntc->flags.has_attribute_tile)
 {
  b.qts << " +[s] ";
 }
 ntc->write_whitespace(b.qts);
}

void NGML_Output_Khif::export_khif(QString path, QString surround)
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
 QString khif_output;
 write_khif_output(khif_output);

 if(!surround.isEmpty())
 {
  khif_output.prepend(QString("(%1\n").arg(surround));
  khif_output.append("\n)");
 }

 QFile outfile(path);
 if(outfile.open(QFile::WriteOnly | QIODevice::Text))
 {
  outfile.write(khif_output.toLatin1());
  outfile.close();
 }
}

void NGML_Output_Khif::export_mhix(QString path)
{
 export_khif(path, "RZ_MHIX +[e]");
}


void NGML_Output_Khif::check_mark_continue(const NGML_Output_Bundle& b)
{
 // but not  Tag_Command_Continue_From_Blank ...
 if(b.connection_descriptor == NGML_Connection_Descriptor::Tag_Command_Continue)
  b.qts << " +[c] ";

 //?
 else if(b.connection_descriptor == NGML_Connection_Descriptor::Tag_Command_Continue_From_Blank)
  b.qts << " +[c] ";

 else if(b.connection_descriptor == NGML_Connection_Descriptor::Closed_Tag_Command_Main_Tile)
  b.qts << " +[c] ";

}


void NGML_Output_Khif::generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Tile> tile)
{
 CAON_PTR_DEBUG(NGML_Tile ,tile)
 check_mark_continue(b);
 QStringList rt = tile->raw_text().split('\n');
 QStringListIterator it(rt);
 int lines = 0;
 while(it.hasNext())
 {
  QString s = it.next();
  if(s.startsWith("@@"))
  {
   b.qts << "\n(khi-forms::read-khi-insert :" << s << ')';
     // is there a way to tell if a tile ends the file?
   b.qts << " +[c]";
  }
  else
  {
   s.replace(QRegularExpression("(?=[\\[\\{\\(\\)])"), ".");
   if(lines > 0)
    b.qts << '\n';
   b.qts << s;
  }
  ++lines;
 }

 check_generate_whitespace(b, tile);
}

void NGML_Output_Khif::generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Attribute_Tile> tile)
{
 tile->write_khif(b.qts);
}

void NGML_Output_Khif::generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Paralex_Tile> tile)
{
 b.qts << ' ';
 tile->write_khif(b.qts);
 b.qts << ' ';
 check_generate_whitespace(b, tile);
}


