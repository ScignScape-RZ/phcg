
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rpi-block.h"
#include "rpi-stage-form.h"

#include "rz-graph-core/kernel/graph/rz-re-node.h"
#include "rz-graph-core/code/rz-re-block-entry.h"

#include "rz-graph-visit/rz-graph-visitor-phaon.h"
#include "rz-graph-token/token/rz-lisp-token.h"

#include "rz-graph-valuer/scope/rz-lisp-graph-lexical-scope.h"
#include "rz-graph-valuer/valuer/rz-lisp-graph-valuer.h"

#include "rz-graph-core/code/rz-re-function-def-entry.h"

#include "rz-graph-core/code/rz-re-call-entry.h"


#include "rz-graph-core/token/rz-re-token.h"

#include "rz-graph-valuer/scope/rz-lisp-graph-block-info.h"

#include "rz-function-def/rz-function-def-syntax.h"
#include "rz-function-def/rz-function-def-info.h"

#include "phr-graph-core/kernel/graph/pgb-ir-build.h"

#include "multistep-token.h"

#include "rzns.h"

USING_RZNS(RECore)


USING_RZNS(GVal)

RPI_Block::RPI_Block(PGB_IR_Build& pgb, caon_ptr<RPI_Block> parent_block)
  :  pgb_(pgb),
     parent_block_(parent_block), block_sequence_mode_(Block_Sequence_Modes::N_A),
     current_form_(nullptr), last_form_(nullptr), continue_block_(nullptr),
     block_info_(nullptr), pending_block_info_(nullptr),
     lexical_scope_(nullptr),
     parent_lambda_position_(-1)
{

}

void RPI_Block::build_phaon_graph()
{

}

int RPI_Block::get_new_hd_code()
{
 static int result = 0;
 return ++result;
}

void RPI_Block::scan_top_level(RZ_Graph_Visitor_Phaon& visitor_phaon)
{
 caon_ptr<RE_Node> rn = visitor_phaon.visitor().graph_root_node();

 scan(visitor_phaon, *rn);
}

void RPI_Block::scan(RZ_Graph_Visitor_Phaon& visitor_phaon,
  RE_Node& start_node)
{
 caon_ptr<RZ_Lisp_Graph_Block_Info> rbi;
 if(caon_ptr<RE_Node> ben = visitor_phaon.visitor().find_block_entry_node(&start_node, rbi))
 {
  CAON_PTR_DEBUG(RE_Node ,ben)

  caon_ptr<RE_Node> cen = visitor_phaon.visitor().find_run_call_entry(ben);

  // // does this need to be more fine-grained?

  caon_ptr<RE_Block_Entry> rbe = ben->re_block_entry();

  if(rbe)
  {
   CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
   lexical_scope_ = rbe->lexical_scope();
  }

  CAON_PTR_DEBUG(RE_Node ,cen)

  if(cen)
  {
   add_form_from_call_entry_node(visitor_phaon, *cen, rbe);
  }

  caon_ptr<RE_Node> current_node = cen;
  while(current_node)
  {
   if(current_node = visitor_phaon.find_statement_cross_sequence_node(current_node) )
   {
    CAON_PTR_DEBUG(RE_Node, current_node)
    last_form_ = current_form_;
    current_form_ = nullptr;
    add_form_from_call_entry_node(visitor_phaon, *current_node);
   }
  }
  CAON_DEBUG_NOOP
 }

}


void RPI_Block::add_form_from_call_entry_node(RZ_Graph_Visitor_Phaon& visitor_phaon,
  RE_Node& entry_node, caon_ptr<RE_Block_Entry> rbe)
{
 if(current_form_)
 {
  // i.e., an expression inside a form

 }
 else
 {
  current_form_ = new RPI_Stage_Form(pgb_);


  if(rbe)
  {
   current_form_->mark_as_block_entry_statment();
  }

  forms_.push_back(current_form_);
  if(caon_ptr<RE_Node> start_node = visitor_phaon.start_node_from_call_entry_node(&entry_node))
  {
   CAON_PTR_DEBUG(RE_Node ,start_node)

   if(caon_ptr<RZ_Expression_Review> rer = visitor_phaon.get_expression_review_from_entry_node(start_node))
   {
    CAON_PTR_DEBUG(RZ_Expression_Review ,rer)
    current_form_->set_expression_review(rer);
   }

   if(caon_ptr<RZ_Code_Statement> st = visitor_phaon.get_code_statement_from_statement_entry_node(start_node))
   {
    CAON_PTR_DEBUG(RZ_Code_Statement ,st)
    code_statements_.push_back(st);
    current_form_->set_code_statement(st);

    visitor_phaon.check_assignment_annotation(start_node, st);


   }
   else
   {
    code_statements_.push_back(nullptr);
   }
   scan_form_from_start_node(visitor_phaon, *start_node);
  }
 }

}


void RPI_Block::scan_form_from_start_node(RZ_Graph_Visitor_Phaon& visitor_phaon,
  RE_Node& start_node)
{
 scan_form_from_statement_entry_node(visitor_phaon, start_node);
 current_form_ = nullptr;
}

caon_ptr<RE_Block_Entry> RPI_Block::get_block_entry()
{
 if(block_info_)
 {
  if(caon_ptr<RE_Node> ben = block_info_->block_entry_node())
  {
   return ben->re_block_entry();
  }
 }
 return nullptr;
}

void RPI_Block::scan_form_from_statement_entry_node(RZ_Graph_Visitor_Phaon& visitor_phaon,
  RE_Node& start_node)
{
 int lambda_count = 0;
 int implicit_added_depth = 0;

 if(pending_block_info_)
 {
  //  this assumes there will never be "nested" pending block info ...
 }
 else
 {
  pending_block_info_ = visitor_phaon.check_pending_block_info(&start_node);
 }

 if(caon_ptr<RZ_Lisp_Token> tok = start_node.lisp_token())
 {
  CAON_PTR_DEBUG(RZ_Lisp_Token ,tok)

  QString fn;
  RZ_Graph_Visitor_Phaon::Special_Form_Flags sff =
    RZ_Graph_Visitor_Phaon::parse_special_form_flag(tok->raw_text());

  switch(sff)
  {
  case RZ_Graph_Visitor_Phaon::Special_Form_Flags::Type_Declare:
   {
    current_form_->init_type_declaration(tok->raw_text());
    fn = visitor_phaon.function_name_from_token_text(tok->raw_text());
    current_form_->add_instruction_element(RPI_Stage_Element_Kinds::Instruction_Symbol, fn);
   }
   break;
  case RZ_Graph_Visitor_Phaon::Special_Form_Flags::Formula:
   {
    current_form_->init_formula_expression(tok->raw_text());
    //?
   }
   break;
  case RZ_Graph_Visitor_Phaon::Special_Form_Flags::Assignment:
   {
    current_form_->init_assignment_expression(tok->raw_text());
    //?
   }
   break;
  case RZ_Graph_Visitor_Phaon::Special_Form_Flags::N_A:
   {
    if(tok->flags.is_if_with_elsif)
    {
     current_form_->init_expression();
     fn = "kb::if-with-elsif";
    }
    else if(tok->flags.is_if_with_else)
    {
     current_form_->init_expression();
     fn = "kb::if-with-else";
    }
    else
    {
     current_form_->init_expression();
     fn = visitor_phaon.function_name_from_token_text(tok->raw_text());
     if(tok->raw_text() == "/->")
     {
      if(caon_ptr<RPI_Stage_Form> parent = current_form_->parent())
      {
       parent->set_s1_assignment_check("/->");
       current_form_->mark_as_parent_s1_assignment_preempts_s0();
      }
     }
    }
    current_form_->check_init_annotation(fn);
    if(fn.startsWith("kb::"))
    {
     current_form_->add_instruction_element(RPI_Stage_Element_Kinds::Instruction_Symbol, fn);
     if(fn == "kb::write-overloadable-fdef")
     {
      current_form_->init_type_declaration("kb::write-overloadable-fdef");
     }
    }
    else
    {
     if(fn.startsWith('&'))
     {
      current_form_->init_inferred_s0_statement();
      //?fn = fn.mid(1);
     }
     else if(lexical_scope_->contains_function_symbol(fn))
     {
      current_form_->init_inferred_s0_statement();
     }
     else if(lexical_scope_->contains_symbol(fn))
     {
      current_form_->init_inferred_s0_statement();
     }
     current_form_->add_fn_element(RPI_Stage_Element_Kinds::Fuxe_Symbol, fn);
    }

    // should be a flag ...
    if(tok->raw_text() == "do")
    {
     if(current_form_->parent_lambda_position() != -1)
     {
     }
     // this is now handled later ...
     //current_form_->add_string_token(":|W|");
    }
   }
   break;
  }
 }
 caon_ptr<RE_Node> current_node = &start_node;

 RZ_Lisp_Graph_Visitor::Next_Node_Premise nnp = RZ_Lisp_Graph_Visitor::Next_Node_Premise::N_A;

 while(current_node)
 {
  // nnp is read-write in visitor_phaon.get_next_node(...)
  caon_ptr<RE_Node> next_node = visitor_phaon.get_next_node(current_node, nnp);

  CAON_PTR_DEBUG(RE_Node ,current_node)
  CAON_PTR_DEBUG(RE_Node ,next_node)

  bool skip_increase_lambda_count = false;

  MS_Token_Kinds mstk = MS_Token_Kinds::N_A;

  switch(nnp)
  {

  case RZ_Lisp_Graph_Visitor::Next_Node_Premise::Normal:
   {
    if(caon_ptr<RZ_Lisp_Token> next_tok = next_node->lisp_token())
    {
     CAON_PTR_DEBUG(RZ_Lisp_Token ,next_tok)

     if(next_tok->flags.is_dep_marker)
     {
      current_node = next_node;
      continue;
     }
     QString bridge_code;

     MS_Token mst = visitor_phaon.lisp_token_from_token_text(next_tok->raw_text(), bridge_code);

     QString lt = mst.raw_text;
     if(mst.kind != MS_Token_Kinds::N_A)
     {
      mstk = mst.kind;
     }

     if(next_tok->flags.is_assign_to_default_ctor)
     {
      skip_increase_lambda_count = true;
      lt.clear();
      //  currently this just ignores the token.
     }
     else if(next_tok->flags.precedes_call_arrow)
     {
      skip_increase_lambda_count = true;
      QString ht = lt;

      // // do we need this?
      //ht.prepend(":|s,");
      //ht.append('|');

      held_token_ = {MS_Token_Kinds::Sigma_Symbol, ht};
      lt.clear();
     }
     else if(next_tok->flags.follows_call_arrow)
     {
      skip_increase_lambda_count = true;

      // // do we need this?
      //lt.replace('-', '_');

      // // do we need this?
      //lt.prepend(":|&,");
      //lt.append('|');
     }

     else if(next_tok->flags.is_symbol_declaration ||
        next_tok->flags.is_symbol_matched_to_declaration)
     {
      mstk = MS_Token_Kinds::Scoped_Symbol;
     }
     else if(next_tok->flags.is_string_literal)
     {
      lt.prepend("\\\"");
      lt.append("\\\"");
     }
     else if(lexical_scope_ && lexical_scope_->contains_symbol(lt))
     {
      mstk = MS_Token_Kinds::Scoped_Symbol;
     }

     else if(next_tok->flags.is_type_symbol_in_declaration)
     {
      skip_increase_lambda_count = true;
      mstk = MS_Token_Kinds::Type_Symbol;
     }
     if(!lt.isEmpty())
     {
      if(bridge_code.isEmpty())
      {
       if(next_tok->flags.is_numeric_literal)
       {
        current_form_->add_insert_element(RPI_Stage_Element_Kinds::Kernel_Type_Symbol, "u32");
        current_form_->add_literal_element(RPI_Stage_Element_Kinds::Literal, lt);
         //?current_form_->add_literal_token(MS_Token::check_as(mstk, MS_Token_Kinds::Literal, lt));//{MS_Token_Kinds::Literal, lt});
       }
       else if(next_tok->flags.is_string_literal)
       {
        current_form_->add_insert_element(RPI_Stage_Element_Kinds::Kernel_Type_Symbol, "str");
        current_form_->add_literal_element(RPI_Stage_Element_Kinds::String_Literal, lt);
        //current_form_->add_literal_token(MS_Token::check_as(mstk, MS_Token_Kinds::String_Literal, lt));
       }
       else if(next_tok->flags.has_assignment_initialization_expression)
       {
        current_form_->set_assignment_info(RPI_Assignment_Info(
          RPI_Assignment_Value_Kinds::Expression, //Scoped_Symbol,
          RPI_Assignment_Initialization_Kinds::Init, lt));
//?        current_form_->set_assignment_token(MS_Token::check_as(mstk, MS_Token_Kinds::Scoped_Symbol, lt));
       }
       else if(next_tok->flags.has_assignment_initialization_token)
       {
        current_form_->set_assignment_info(RPI_Assignment_Info(
          RPI_Assignment_Value_Kinds::Literal,
          RPI_Assignment_Initialization_Kinds::Init, lt));
//?        current_form_->set_assignment_token({MS_Token_Kinds::Scoped_Symbol_Literal_Init, lt});
       }
       else if(next_tok->flags.is_assignment_initialization_entry)
       {
        current_form_->add_assignment_initialization_element(RPI_Stage_Element_Kinds::Instruction_Symbol, lt);
           //MS_Token::check_as(mstk, MS_Token_Kinds::Instruction_Symbol, lt));
       }
       else if(mstk == MS_Token_Kinds::Skipped_Flag_Symbol)
       {
        if(lt == "FN-NO-BLOCK")
        {
         current_form_->mark_as_fn_no_block();
        }
       }
       else
       {
        current_form_->add_argument_element(RPI_Stage_Element_Kinds::Raw_Symbol, lt);
           //MS_Token::check_as(mstk, MS_Token_Kinds::Raw_Symbol, lt));
       }
      }
      else
      {
       QString code = visitor_phaon.wrap_token_with_bridge_code(lt, bridge_code, es_argument_);
       current_form_->add_bridge_element(RPI_Stage_Element_Kinds::Bridge_Symbol, code);

          //MS_Token::check_as(mstk, MS_Token_Kinds::Bridge_Symbol, code));
      }
      if(!skip_increase_lambda_count)
      {
       ++lambda_count;
      }
      if(!held_token_.raw_text.isEmpty())
      {
       current_form_->add_carrier_element(RPI_Stage_Element_Kinds::N_A, held_token_.raw_text);
       held_token_.clear();
      }
     }
    }
    current_node = next_node;
   }
   break;

  case RZ_Lisp_Graph_Visitor::Next_Node_Premise::Expression:
   {
    RPI_Stage_Form* new_form = new RPI_Stage_Form(pgb_, current_form_);
    new_form->set_parent_lambda_position(lambda_count);
    new_form->set_implicit_added_depth(implicit_added_depth);
    current_form_->add_expression(new_form);
    caon_ptr<RE_Call_Entry> rce = next_node->re_call_entry();
    CAON_PTR_DEBUG(RE_Call_Entry ,rce)
    if(rce->flags.is_deferred)
    {
     current_form_->add_expression_wrapper(new_form, "defer'", get_new_hd_code());
    }
    current_form_ = new_form;
    caon_ptr<RE_Node> en = visitor_phaon.visitor().entry_from_call_entry(next_node);
    CAON_PTR_DEBUG(RE_Node ,en)
    scan_form_from_statement_entry_node(visitor_phaon, *en);
    current_form_ = new_form->parent();

    if(pending_block_info_)
    {
     visitor_phaon.set_pending_block_info(pending_block_info_);
     pending_block_info_ = nullptr;
    }
    else
    {
     current_node = next_node;
    }
   }
   break;

  case RZ_Lisp_Graph_Visitor::Next_Node_Premise::Block_Entry:
   {
    // "hand-off" the pending_block_info_ from visitor_phaon to this
    caon_ptr<RZ_Lisp_Graph_Block_Info> rbi = visitor_phaon.clear_pending_block_info();

    caon_ptr<RPI_Block> new_block = new RPI_Block(pgb_, this);
    caon_ptr<RPI_Block> current_block = new_block;

    new_block->set_block_info(rbi);
    if(caon_ptr<RE_Node> cen = visitor_phaon.call_entry_node_from_block_entry_node(next_node))
    {
     CAON_PTR_DEBUG(RZ_Lisp_Graph_Block_Info ,rbi)
     CAON_PTR_DEBUG(RE_Node ,cen)
     if(caon_ptr<RE_Node> nben = rbi->block_entry_node())
     {
      if(caon_ptr<RE_Block_Entry> rbe = nben->re_block_entry())
      {
       new_block->set_lexical_scope(rbe->lexical_scope());
      }
     }
     new_block->add_form_from_call_entry_node(visitor_phaon, *cen);
     current_form_->add_nested_block(new_block);


     caon_ptr<RZ_Lisp_Graph_Block_Info> nn_bi;
     caon_ptr<RE_Node> continue_node = visitor_phaon.leave_nested_block(rbi, nn_bi);
     while(continue_node)
     {
      caon_ptr<RE_Node> nben = nn_bi->block_entry_node();
      CAON_PTR_DEBUG(RE_Node ,continue_node)
      CAON_PTR_DEBUG(RZ_Lisp_Graph_Block_Info ,nn_bi)
      CAON_PTR_DEBUG(RE_Node ,nben)
      caon_ptr<RE_Block_Entry> nrbe = nben->re_block_entry();
      CAON_PTR_DEBUG(RE_Block_Entry ,nrbe)

      caon_ptr<RPI_Stage_Form> expression_form = nullptr;

      if(nrbe->flags.elsif_block)
      {
       if(caon_ptr<RE_Node> sen = nrbe->statement_entry_node())
       {
        CAON_PTR_DEBUG(RE_Node ,sen)
        caon_ptr<RE_Node> en = visitor_phaon.visitor().entry_from_call_entry(sen);
        CAON_PTR_DEBUG(RE_Node ,en)

        if(en)
        {
         caon_ptr<RE_Node> nen = visitor_phaon.visitor().entry_from_call_entry(en);
         CAON_PTR_DEBUG(RE_Node ,nen)
         if(nen)
         {
          expression_form = new RPI_Stage_Form(pgb_, current_form_);
          current_form_ = expression_form;

          caon_ptr<RE_Node> nene = visitor_phaon.visitor().entry_from_call_entry(nen);
          CAON_PTR_DEBUG(RE_Node ,nene)

          scan_form_from_statement_entry_node(visitor_phaon, *nene);

          current_form_ = expression_form->parent();

          current_form_->add_expression(expression_form);
         }
        }

        caon_ptr<RZ_Lisp_Graph_Block_Info> new_rbi;

        caon_ptr<RE_Node> new_ben = visitor_phaon.visitor().find_block_entry_node(en, new_rbi);
        CAON_PTR_DEBUG(RE_Node ,new_ben)
        CAON_PTR_DEBUG(RZ_Lisp_Graph_Block_Info ,new_rbi)
        if(!new_ben)
        {
         // should this be handled in find_block_entry_node()? ...
         if(new_rbi)
         {
          new_ben = new_rbi->block_entry_node();
         }
        }
        if(new_ben)
        {
         caon_ptr<RPI_Block> new_block = new RPI_Block(pgb_, this);
         new_block->set_block_info(new_rbi);

         if(caon_ptr<RE_Node> new_cen = visitor_phaon.call_entry_node_from_block_entry_node(new_ben))
         {
          CAON_PTR_DEBUG(RE_Node ,new_cen)
          new_block->add_form_from_call_entry_node(visitor_phaon, *new_cen);
          current_form_->add_nested_block(new_block);
         }
        }
       }

      }

      else if(nrbe->flags.else_block)
      {
       if(caon_ptr<RE_Node> sen = nrbe->statement_entry_node())
       {
        CAON_PTR_DEBUG(RE_Node ,sen)
        caon_ptr<RE_Node> en = visitor_phaon.visitor().entry_from_call_entry(sen);
        CAON_PTR_DEBUG(RE_Node ,en)

        caon_ptr<RZ_Lisp_Graph_Block_Info> new_rbi;

        caon_ptr<RE_Node> new_ben = visitor_phaon.visitor().find_block_entry_node(en, new_rbi);
        CAON_PTR_DEBUG(RE_Node ,new_ben)
        CAON_PTR_DEBUG(RZ_Lisp_Graph_Block_Info ,new_rbi)

        if(new_ben)
        {
         caon_ptr<RPI_Block> new_block = new RPI_Block(pgb_, this);
         new_block->set_block_info(new_rbi);

         if(caon_ptr<RE_Node> new_cen = visitor_phaon.call_entry_node_from_block_entry_node(new_ben))
         {
          CAON_PTR_DEBUG(RE_Node ,new_cen)
          new_block->add_form_from_call_entry_node(visitor_phaon, *new_cen);
          current_form_->add_nested_block(new_block);
         }
        }


        // handle the expression ...
       }
      }

      caon_ptr<RPI_Block> nb = new RPI_Block(pgb_, this);
      nb->set_block_info(nn_bi);
      nb->set_preceding_expression_form(expression_form);
      current_block->set_continue_block(nb);
      current_block = nb;

      if(caon_ptr<RE_Node> cen = visitor_phaon.call_entry_node_from_block_entry_node(nben))
      {
       nb->add_form_from_call_entry_node(visitor_phaon, *cen);
      }
      continue_node = visitor_phaon.leave_nested_block(nn_bi, nn_bi);
      //
     }
    }
    current_node = nullptr;
   }
   break;
  case RZ_Lisp_Graph_Visitor::Next_Node_Premise::Function_Def_Entry:
   {
    QString entry_code;
    CAON_PTR_DEBUG(RE_Node ,next_node)
    if(caon_ptr<RE_Function_Def_Entry> fde = next_node->re_function_def_entry())
    {
     CAON_PTR_DEBUG(RE_Function_Def_Entry ,fde)

     if(fde->kind() == RE_Function_Def_Kinds::Call_Arrow_Note)
     {
      caon_ptr<RE_Node> note_node = fde->note_node();
      QString note = note_node->re_token()->raw_text();
      QString signature_code;

      if(caon_ptr<RZ_Function_Def_Info> function_def_info =
        visitor_phaon.get_function_def_info_from_entry(fde))
      {
       signature_code  = function_def_info->dynamo_signature_code_string();
       MS_Token note {MS_Token_Kinds::Note_Symbol, ":fdef"};
       //?current_form_->add_prin1_quoted_form(signature_code, note);
      }


     }
     else if(fde->kind() == RE_Function_Def_Kinds::Call_Arrow_Async)
     {
      //?current_form_->add_kauvir_token(":|Wa|");
     }
     else
     {
      if(caon_ptr<RZ_Function_Def_Info> function_def_info =
        visitor_phaon.get_function_def_info_from_entry(fde))
      {
       QString signature_code = function_def_info->dynamo_signature_code_string();
       MS_Token note {MS_Token_Kinds::Note_Symbol, ":fdef"};
       //?current_form_->add_prin1_quoted_form(signature_code, note);
      }
     }

     caon_ptr<RE_Node> prior_node = fde->prior_node();
     CAON_PTR_DEBUG(RE_Node ,prior_node)

     caon_ptr<RE_Node> fdi_node = fde->node();
     CAON_PTR_DEBUG(RE_Node ,fdi_node)

     if(caon_ptr<RE_Node> ben = visitor_phaon.block_entry_node_from_function_def_entry_node(prior_node))
     {
      CAON_PTR_DEBUG(RE_Node ,ben)
      CAON_DEBUG_NOOP
      caon_ptr<RPI_Block> new_block = new RPI_Block(pgb_, this);

      // //  does this need to depend on the function def info somehow?
      new_block->set_es_argument("ks");

      if(caon_ptr<RE_Block_Entry> rbe = ben->re_block_entry())
      {
       caon_ptr<RZ_Lisp_Graph_Lexical_Scope> ls = rbe->lexical_scope();

       if(caon_ptr<RZ_Function_Def_Info> function_def_info =
         visitor_phaon.get_function_def_info_from_entry(fde))
       {
        CAON_PTR_DEBUG(RZ_Function_Def_Info ,function_def_info)
        entry_code = function_def_info->kauvir_entry_code_string(*ls);
       }


       CAON_PTR_DEBUG(RZ_Lisp_Graph_Lexical_Scope ,ls)
       new_block->set_lexical_scope(ls);
       new_block->set_entry_lisp_code(entry_code);
      }


      new_block->set_parent_lambda_position(parent_lambda_position_);
      ++lambda_count;
      if(caon_ptr<RE_Node> cen = visitor_phaon.call_entry_node_from_block_entry_node(ben))
      {
       new_block->add_form_from_call_entry_node(visitor_phaon, *cen);

       caon_ptr<RE_Node> next_statement_node = cen;
       while(next_statement_node = visitor_phaon.get_next_statement_node(next_statement_node))
       {
        CAON_PTR_DEBUG(RE_Node ,next_statement_node)
        new_block->add_form_from_call_entry_node(visitor_phaon, *next_statement_node);
       }

       current_form_->add_nested_block(new_block);
      }
     }
    }

    current_node = nullptr;

   }
   break;

  case RZ_Lisp_Graph_Visitor::Next_Node_Premise::Token_To_Block_Entry:
   {
    caon_ptr<RPI_Block> new_block = new RPI_Block(pgb_, this);

    caon_ptr<RE_Block_Entry> rbe = next_node->re_block_entry();

    if(rbe->flags.ghost_block)
    {
     new_block->set_block_sequence_mode(Block_Sequence_Modes::Ghost);
    }

    ++lambda_count;
    if(caon_ptr<RE_Node> cen = visitor_phaon.call_entry_node_from_block_entry_node(next_node))
    {
     new_block->add_form_from_call_entry_node(visitor_phaon, *cen);
     current_form_->add_nested_block(new_block);
    }

    current_node = nullptr;
   }
   break;

  case RZ_Lisp_Graph_Visitor::Next_Node_Premise::N_A:
   current_node = nullptr;
   break;
  }
 }
}

void RPI_Block::write_top_level(QList<PGB_IR_Build::Text_With_Purpose>& tps, QTextStream& qts)
{
 pgb_(tps).make_root_node("!last_block_pre_entry_node");

// _PGB_IR_Build _pgb = pgb_(qsl);
// _pgb.make_root_node("!last_last_block_pre_entry_node");
 write(tps, qts);
}


void RPI_Block::write(QList<PGB_IR_Build::Text_With_Purpose>& tps, QTextStream& qts)
{
 if(parent_block_)
 {
  if(es_argument_.isEmpty())
  {
   qts << "\n(kb::write-enter-scope)\n";
  }
  else
  {
   // // same ?
   // ... qts << "\n(kb::write-enter-scope)\n";
  }
 }
 else
 {
  // ... qts << "\n(kb::write-file-start)\n";
 }


 qts << entry_lisp_code_;

 caon_ptr<RPI_Stage_Form> prior = nullptr;
 for(caon_ptr<RPI_Stage_Form> rsf : forms_)
 {
  rsf->write_as_statement(qts, prior);

  tps.append(rsf->step_forms());
  prior = rsf;
 }

 if(parent_block())
 {
  qts << "\n(kb::write-leave-scope)\n";
 }
 else
 {
  qts << "\n\n(kb::write-file-end)\n";
 }

 caon_ptr<RE_Block_Entry> rbe = get_block_entry();


 if(continue_block_)
 {

 }
 else if(rbe)
 {
  CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
  if(rbe->flags.if_block)
  {
  }
  else if(rbe->flags.elsif_block)
  {

  }
 }

}
