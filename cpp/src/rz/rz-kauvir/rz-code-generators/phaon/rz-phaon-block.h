
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_PHAON_BLOCK__H
#define RZ_PHAON_BLOCK__H

#include "accessors.h"
#include "flags.h"

#include <QString>
#include <QMap>

#include <QVector>

#include <QTextStream>

#include "rzns.h"

#include "relae-graph/relae-caon-ptr.h"

#include "multistep-token.h"

RZNS_(RECore)
 class RE_Node;
 class RE_Block_Entry;
_RZNS(RECore)

USING_RZNS(RECore)

RZNS_(GBuild)
 class RZ_Lisp_Graph_Visitor;
 class RZ_Graph_Visitor_Phaon;
_RZNS(GBuild)

USING_RZNS(GBuild)

RZNS_(PhrGraphCore)
 class PGB_IR_Build;
_RZNS(PhrGraphCore)

USING_RZNS(PhrGraphCore)

RZNS_(GVal)

class RZ_Dynamo_Form;
class RZ_Lisp_Graph_Lexical_Scope;

class RZ_Function_Def_Syntax;
class RZ_Lisp_Graph_Block_Info;
class RZ_Code_Statement;

class RZ_Phaon_Block
{
public:

 enum class Block_Sequence_Modes {
  N_A, If_Else, If_Elsif, Map, Ghost
 };

private:


 caon_ptr<RZ_Lisp_Graph_Lexical_Scope> lexical_scope_;


 caon_ptr<RZ_Phaon_Block> parent_block_;
 caon_ptr<RZ_Phaon_Block> continue_block_;

 QVector<caon_ptr<RZ_Dynamo_Form>> forms_;

 caon_ptr<RZ_Dynamo_Form> current_form_;
 caon_ptr<RZ_Dynamo_Form> last_form_;

 caon_ptr<RZ_Lisp_Graph_Block_Info> pending_block_info_;
 caon_ptr<RZ_Lisp_Graph_Block_Info> block_info_;
 caon_ptr<RZ_Dynamo_Form> preceding_expression_form_;

 MS_Token held_token_;

 QString entry_lisp_code_;

 int parent_lambda_position_;

 void add_form_from_call_entry_node(RZ_Graph_Visitor_Phaon& visitor_phaon,
   RE_Node& entry_node);

 void add_statement_from_call_entry_node(PGB_IR_Build& pgb, RZ_Graph_Visitor_Phaon& visitor_phaon,
   RE_Node& entry_node, QString pgbs, caon_ptr<RE_Block_Entry> rbe = nullptr);

 QString es_argument_;

 Block_Sequence_Modes block_sequence_mode_;

 QVector<caon_ptr<RZ_Code_Statement>> code_statements_;

 static int get_new_hd_code();

public:

 RZ_Phaon_Block(caon_ptr<RZ_Phaon_Block> parent_block = nullptr);

 ACCESSORS(caon_ptr<RZ_Phaon_Block> ,parent_block)
 ACCESSORS(caon_ptr<RZ_Phaon_Block> ,continue_block)

 ACCESSORS(QVector<caon_ptr<RZ_Dynamo_Form>> ,forms)
 ACCESSORS(int ,parent_lambda_position)
 ACCESSORS(QString ,entry_lisp_code)

 ACCESSORS(caon_ptr<RZ_Lisp_Graph_Block_Info> ,pending_block_info)
 ACCESSORS(caon_ptr<RZ_Lisp_Graph_Block_Info> ,block_info)
 ACCESSORS(caon_ptr<RZ_Dynamo_Form> ,preceding_expression_form)

 ACCESSORS(Block_Sequence_Modes ,block_sequence_mode)

 ACCESSORS(caon_ptr<RZ_Lisp_Graph_Lexical_Scope> ,lexical_scope)




 ACCESSORS(QString ,es_argument)

 caon_ptr<RE_Block_Entry> get_block_entry();

 RZ_Lisp_Graph_Visitor& visitor();

 void build_phaon_graph(PGB_IR_Build& pgb);

 void scan_top_level(PGB_IR_Build& pgb, RZ_Graph_Visitor_Phaon& visitor_phaon);

 void scan(PGB_IR_Build& pgb, RZ_Graph_Visitor_Phaon& visitor_phaon, RE_Node& start_node);

 void scan_form_from_start_node(RZ_Graph_Visitor_Phaon& visitor_phaon,
   RE_Node& start_node);

 void scan_form_from_statement_entry_node(RZ_Graph_Visitor_Phaon& visitor_phaon,
   RE_Node& start_node);

};

_RZNS(GVal)

#endif //RZ_PHAON_BLOCK__H
