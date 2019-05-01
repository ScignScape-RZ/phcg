
#ifndef RZ_NGML_OUTPUT_KHIF__H
#define RZ_NGML_OUTPUT_KHIF__H

#include <QString>

#include "accessors.h"

#include "flags.h"

#include "rz-ngml-output-base.h"
#include "rz-ngml-output-event-handler.h"

class QTextStream;

#include <QMap>
#include <QStack>

#include "rzns.h"
RZNS_(NGML)

class NGML_Document;
class NGML_Node;
class NGML_Tile;
class NGML_Tag_Command;
class NGML_Paralexeme;
class NGML_Command_Callback;
class NGML_Paralexical_Segment;
class NGML_Sentence;
class NGML_Sentence_Part;
class NGML_Punctuation;


class NGML_Output_Khif : NGML_Output_Base, NGML_Output_Event_Handler
{
 typedef NGML_Node tNode;

 QStack<caon_ptr<NGML_Node>> chiefs_;
 QMap<QString, caon_ptr<NGML_Command_Callback>> callbacks_;

 void init_callbacks();

public:

 NGML_Output_Khif(NGML_Document& ngd);

 void generate(QTextStream& qts);

 void export_khif(QString path = "..khif", QString surround = QString());
 void export_mhix(QString path = "..mhix");

 void generate_tag_command_auto_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc);


 static QString escaped_raw_text(NGML_Tile& tile);

 static void escape(QString& str);

 void generate_tile(QTextStream& qts, tNode& node, NGML_Tile& tile,
  NGML_Connection_Descriptor& cd);


 void clear_attribute_tile();

 void write_khif_output(QString& khif_output);


 void generate_root(const NGML_Output_Bundle& b, caon_ptr<NGML_Root> nr) Q_DECL_OVERRIDE;

 void generate_tag_command_entry(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;

 void generate_tag_command_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;

 void generate_tag_body_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;

 void generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Tile> tile) Q_DECL_OVERRIDE;
 void generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Attribute_Tile> tile) Q_DECL_OVERRIDE;
 void generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Paralex_Tile> tile) Q_DECL_OVERRIDE;

 void generate_tag_command_entry_connector(const NGML_Output_Bundle& b);


 void check_mark_continue(const NGML_Output_Bundle& b);
 void process_khi_file_info(QTextStream& qts, caon_ptr<NGML_Node> node);
 caon_ptr<NGML_Command_Callback> check_command_callback(caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;

 void insert_khif_link(QTextStream& qts);

};

_RZNS(NGML)

#endif

