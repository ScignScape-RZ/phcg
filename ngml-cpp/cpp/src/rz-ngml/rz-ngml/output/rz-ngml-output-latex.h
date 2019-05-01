
#ifndef RZ_NGML_OUTPUT_LATEX__H
#define RZ_NGML_OUTPUT_LATEX__H


#include "rz-ngml-output-base.h"
#include "rz-ngml-output-event-handler.h"

#include "rzns.h"

RZNS_(NGML)

class NGML_Graph;
class NGML_Document;


class NGML_Output_Latex : public NGML_Output_Base, private NGML_Output_Event_Handler
{
 QMap<QString, caon_ptr<NGML_Command_Callback>> callbacks_;
 void init_callbacks();


public:


 NGML_Output_Latex(NGML_Document& document);

 void export_latex(QString path = "..tex");
 void write_latex_output(QString& latex_output);

 void generate(QTextStream& qts);

 void generate_tag_command_entry(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;
 void generate_tag_command_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;
 void generate_tag_body_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;

 void generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Paralex_Tile> tile) Q_DECL_OVERRIDE;
 void generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Attribute_Tile> tile) Q_DECL_OVERRIDE;

 void handle_annotation(caon_ptr<NGML_Tile> tile, caon_ptr<NGML_Annotation_Tile> atile) Q_DECL_OVERRIDE;

 caon_ptr<NGML_Command_Callback> check_command_callback(caon_ptr<NGML_Tag_Command> ntc)  Q_DECL_OVERRIDE;

};

_RZNS(NGML)


#endif
