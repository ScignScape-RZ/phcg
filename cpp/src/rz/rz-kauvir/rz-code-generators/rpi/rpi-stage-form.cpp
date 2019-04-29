
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rpi-stage-form.h"
#include "rpi-block.h"

#include "rz-graph-core/code/rz-re-block-entry.h"

#include "rz-graph-valuer/scope/rz-lisp-graph-block-info.h"

#include "rpi-type-declaration.h"
#include "rpi-expression.h"

#include "rpi-stage-form-annotation.h"
#include "rpi-stage-element.h"

#include "rz-code-elements/rz-code-statement.h"
#include "rz-code-elements/rz-expression-review.h"

#include "phr-graph-core/kernel/graph/pgb-ir-build.h"

#include <functional>

#include "rzns.h"

#define ANNOTATION_FLAG(x) \
  (annotation_ && annotation_->flags.x)

USING_RZNS(GVal)

RPI_Stage_Form::RPI_Stage_Form(PGB_IR_Build& pgb, caon_ptr<RPI_Stage_Form> parent)
  :  Flags(0), pgb_(pgb), parent_(parent), parent_lambda_position_(-1),
     first_nested_block_(nullptr), implicit_added_depth_(0),
     nesting_level_(0),
     type_declaration_(nullptr), expression_(nullptr),
     assignment_info_(),
     annotation_(nullptr),
     code_statement_(nullptr),
     expression_review_(nullptr), hdcode_(0)
{

}

RPI_Stage_Form::RPI_Stage_Form(PGB_IR_Build& pgb, caon_ptr<RPI_Block> block)
  :  pgb_(pgb), parent_(nullptr), plene_block_(block),
     first_nested_block_(nullptr), implicit_added_depth_(0),
     type_declaration_(nullptr), expression_(nullptr),
     assignment_info_()
{

}

QString RPI_Stage_Form::get_assignment_target()
{
 return assignment_info_.text();
}


caon_ptr<RPI_Type_Declaration> RPI_Stage_Form::type_declaration_on_block_entry()
{
 //if(ANNOTATION_FLAG(is_block_entry_statment))
 if(flags.is_block_entry_statment || flags.is_nested_block_entry_statment)
   return type_declaration_;
 return nullptr;
}


void RPI_Stage_Form::write_fdef_entry()
{
 if(inner_elements_.size() < 2)
   return;

 // is it always here ([0] is the type-binding instruction?)
 RPI_Stage_Element& rse = inner_elements_[1];

 pgb_(step_forms_).comment("Signature");
 pgb_(step_forms_).make_token_node(rse.text().prepend('@'), "&sig-fground-node")
  = Purpose_Codes::Make_Token_Node_FSym;

 write_statement_entry("&sig-fground-node",
   "!last_statement_entry_node", "!last_statement_entry_node");

 pgb_(step_forms_).make_signature_node("&sig-fground-node", "&sig-node");



}

void RPI_Stage_Form::write_assignment_initialization_via_expression(
  QTextStream& qts, caon_ptr<RPI_Stage_Form> prior)
{
 RPI_Stage_Element& rse = inner_elements_.first();
 caon_ptr<RPI_Stage_Form> f = rse.form();

 caon_ptr<RPI_Type_Declaration> td = nullptr;
 if(prior)
 {
  td = prior->type_declaration_on_block_entry();
 }
 if(td)
   f->flags.is_block_entry_statment = true;// mark_as_block_entry_statment();

 f->mark_as_assignment_expression();

 f->write_unmediated(qts, prior);
 step_forms_.append(f->step_forms());

//? pgb_(step_forms_).add_channel_anchor(assignment_info_.text())


 //pgb_(step_forms_).add_channel_anchor()

// pgb_(step_forms_).make_statement_info_node(assignment_info_.text().prepend('@'),
//   ":parse-literal", assignment_info_.encode_ikind().prepend(':'),
//   "&si-node");

#ifdef HIDE
 QString ty;

 caon_ptr<RPI_Type_Declaration> prior_type_declaration_ben = nullptr;
 if(prior)
 {
  prior_type_declaration_ben = prior->type_declaration_on_block_entry();
 }

 for(RPI_Stage_Element& rse: inner_elements_)
 {
  if(rse.kind() == RPI_Stage_Element_Kinds::Kernel_Type_Symbol)
    ty = rse.text();
  else if(rse.kind() == RPI_Stage_Element_Kinds::Literal)
  {
   if(prior_type_declaration_ben)
     pgb_(step_forms_).add_block_entry_token("!last_block_pre_entry_node",
     rse.text().prepend('$'), "&si-node", "!last_statement_entry_node");
   else
     pgb_(step_forms_).add_statement_sequence_token("!last_statement_entry_node",
     rse.text().prepend('$'), "&si-node", "!last_statement_entry_node");
   break;
  }
 }
#endif // HIDE
}

void RPI_Stage_Form::write_assignment_initialization_via_token(
  QString key, caon_ptr<RPI_Stage_Form> prior)
{
 pgb_(step_forms_).make_statement_info_node(assignment_info_.text().prepend('@'),
   key.prepend(':'), assignment_info_.encode_ikind().prepend(':'),
   "&si-node");

 QString ty;

 caon_ptr<RPI_Type_Declaration> prior_type_declaration_ben = nullptr;
 if(prior)
 {
  prior_type_declaration_ben = prior->type_declaration_on_block_entry();
 }

 for(RPI_Stage_Element& rse: inner_elements_)
 {
  if(rse.kind() == RPI_Stage_Element_Kinds::Kernel_Type_Symbol)
    ty = rse.text();
  else if(rse.kind() == RPI_Stage_Element_Kinds::Literal)
  {
   if(prior_type_declaration_ben)
     pgb_(step_forms_).add_block_entry_token("!last_block_pre_entry_node",
     rse.text().prepend('$'), "&si-node", "!last_statement_entry_node");
   else
     pgb_(step_forms_).add_statement_sequence_token("!last_statement_entry_node",
     rse.text().prepend('$'), "&si-node", "!last_statement_entry_node");
   break;
  }
  else if(rse.kind() == RPI_Stage_Element_Kinds::Type_Default_Marker)
  {
   if(prior_type_declaration_ben)
     pgb_(step_forms_).add_block_entry_token("!last_block_pre_entry_node",
     rse.text().prepend('@'), "&si-node", "!last_statement_entry_node");
   else
     pgb_(step_forms_).add_statement_sequence_token("!last_statement_entry_node",
     rse.text().prepend('@'), "&si-node", "!last_statement_entry_node");
   break;
  }
 }
}

void RPI_Stage_Form::write_as_statement(QTextStream& qts, caon_ptr<RPI_Stage_Form> prior)
{
 if(code_statement_)
 {
  qts << "\n\n ;; Identified as code statement kind: "
      << code_statement_->kind_to_string();

  if(!code_statement_->annotation().isEmpty())
  {
   qts << " " << code_statement_->annotation();
  }
  qts << "\n";
 }
 if(expression_review_)
 {
  qts << "\n\n ;; Expression Review: "
      << expression_review_->text() << "\n";
 }

 if(type_declaration_)
 {
  CAON_PTR_DEBUG(RPI_Type_Declaration ,type_declaration_)
  type_declaration_->write(qts);
 }
 else if(expression_)
 {
  expression_->write_as_statement(qts, prior);
 }
 else
 {
  write(qts, prior);
 }

}

//void RPI_Stage_Form::add_prin1_quoted_form(QString text, RPI_Stage_Element_Kinds kind, QString text)
//{
// check_init_annotation();
// annotation_->flags.has_prin1_quoted_form = true;

// RPI_Stage_Form* new_form = new RPI_Stage_Form(this);

// new_form->set_raw_text(QString("\n\n(prin1-to-string '(%1))\n\n").arg(text));

// inner_elements_.push_back({new_form, mt});

//}

void RPI_Stage_Form::init_type_declaration(QString cmd)
{
 if(type_declaration_)
 {
  CAON_PTR_DEBUG(RPI_Type_Declaration ,type_declaration_)
  // // this is an error ...
  return;
 }
 // // should distinguish cmd == "my" and "our" ...
 type_declaration_ = new RPI_Type_Declaration(*this);
 type_declaration_->set_cmd(cmd);

 //check_init_annotation();
 flags.write_type_declaration = true;
}

void RPI_Stage_Form::init_expression()
{
 expression_ = new RPI_Expression(*this);
}

void RPI_Stage_Form::init_assignment_expression(QString tok)
{
 init_expression();
 expression_->set_assignment_token(tok);
}

void RPI_Stage_Form::init_formula_expression(QString tok)
{
 init_expression();
 expression_->set_assignment_token(tok);
}

void RPI_Stage_Form::write(QTextStream& qts, caon_ptr<RPI_Stage_Form> prior)
{
 check_init_annotation_flags();
 CAON_PTR_DEBUG(RPI_Stage_Form_Annotation ,annotation_)
 if(type_declaration_)
 {
  CAON_PTR_DEBUG(RPI_Type_Declaration ,type_declaration_)
  type_declaration_->write(qts);
 }
 else if(expression_)
 {
  if(ANNOTATION_FLAG(is_deferred))
  {
   qts << "kb::hold-deferred " << hdcode_ << " '(progn (;; annotation_flag_ deferred ...\n";
   expression_->write(qts, prior);
   qts << "\n)) ;; ... annotation_flag_ deferred\n";
  }
  else
  {
   expression_->write(qts, prior);
  }
 }
 else if(!raw_text_.isEmpty())
 {
  qts << raw_text_;
 }
 else
 {
  write_unmediated(qts, prior);
 }
}

QString RPI_Stage_Form::instruction()
{
 if(inner_elements_.isEmpty())
   return QString();
 if(inner_elements_.first().kind() != RPI_Stage_Element_Kinds::Instruction_Symbol)
   return QString();
 return inner_elements_.first().text();
}



void RPI_Stage_Form::add_expression_wrapper(caon_ptr<RPI_Stage_Form> form,
  QString text, int hdcode)
{
 wrapped_inner_elements_[form] = {text, hdcode};
}

void RPI_Stage_Form::set_prior_sibling_flags(caon_ptr<RPI_Stage_Form> prior)
{
 CAON_PTR_DEBUG(RPI_Stage_Form ,prior)
 if(!prior)
   return;
 RPI_Stage_Element_Kinds k = prior->last_element_kind();
 switch(k)
 {
 case RPI_Stage_Element_Kinds::Form:
  if(prior->last_element_form_instruction("kb::write-anon-fdef"))
    flags.prior_sibling_is_block = true;
  else
    flags.prior_sibling_is_expression = true;
  break;
 case RPI_Stage_Element_Kinds::FGround_Symbol:
  flags.prior_sibling_is_fground_token = true;
  break;
 case RPI_Stage_Element_Kinds::Token:
 case RPI_Stage_Element_Kinds::Literal:
 case RPI_Stage_Element_Kinds::String_Literal:
  flags.prior_sibling_is_token = true;

 case RPI_Stage_Element_Kinds::Instruction_Symbol:
  if(prior->instruction("kb::write-anon-fdef"))
  {
   // // here the prior is basically a wrapper for this form
   flags.prior_sibling_is_block = prior->flags.prior_sibling_is_block;
   flags.prior_sibling_is_expression = prior->flags.prior_sibling_is_expression;
   flags.prior_sibling_is_fground_token = prior->flags.prior_sibling_is_fground_token;
   flags.prior_sibling_is_token = prior->flags.prior_sibling_is_token;
  }
  break;
 default:
  break;
 }
 init_prior_description();
}

void RPI_Stage_Form::init_prior_description()
{
 if(flags.prior_sibling_is_block)
   prior_description_ = "prior_sibling_is_block";
 if(flags.prior_sibling_is_expression)
   prior_description_ = "prior_sibling_is_expression";
 if(flags.prior_sibling_is_fground_token)
   prior_description_ = "prior_sibling_is_fground_token";
 if(flags.prior_sibling_is_token)
   prior_description_ = "prior_sibling_is_token";
}

RPI_Stage_Element_Kinds RPI_Stage_Form::last_element_kind()
{
 if(inner_elements_.isEmpty())
   return RPI_Stage_Element_Kinds::N_A;
 return inner_elements_.last().kind();
}

QString RPI_Stage_Form::last_element_form_instruction()
{
 RPI_Stage_Element_Kinds k = last_element_kind();
 if(k == RPI_Stage_Element_Kinds::Form)
   return inner_elements_.last().form()->instruction();
 return QString();
}

void RPI_Stage_Form::add_expression(caon_ptr<RPI_Stage_Form> form)
{
 inner_elements_.push_back(RPI_Stage_Element(form));
}

void RPI_Stage_Form::add_nested_block(caon_ptr<RPI_Block> block)
{
 if(!first_nested_block_)
 {
  first_nested_block_ = block;
 }
 caon_ptr<RPI_Stage_Form> form = new RPI_Stage_Form(pgb_, block);
 inner_elements_.push_back(form);
}

void RPI_Stage_Form::mark_as_fn_no_block()
{
 check_init_annotation();
 annotation_->flags.is_fn_no_block = true;
 CAON_PTR_DEBUG(RPI_Stage_Form_Annotation ,annotation_)
}

void RPI_Stage_Form::mark_as_s1_assignment_preempts_s0()
{
 check_init_annotation();
 annotation_->flags.s1_assignment_preempts_s0 = true;
}

void RPI_Stage_Form::mark_as_parent_s1_assignment_preempts_s0()
{
 check_init_annotation();
 annotation_->flags.parent_s1_assignment_preempts_s0 = true;
}

//void RPI_Stage_Form::mark_as_inferred_block_entry_statment()
//{
// check_init_annotation();
// annotation_->flags.is_inferred_block_entry_statment = true;
//}

//void RPI_Stage_Form::mark_preceder_token()
//{
// check_init_annotation();
// annotation_->flags.has_preceder_token = true;
//}

//void RPI_Stage_Form::mark_as_statement()
//{
// check_init_annotation();
// annotation_->flags.is_statement = true;
//}

//void RPI_Stage_Form::mark_as_block_entry_statment()
//{
// check_init_annotation();
// annotation_->flags.is_block_entry_statment = true;
// //CAON_PTR_DEBUG(RPI_Stage_Form_Annotation ,annotation_)
//}

//void RPI_Stage_Form::mark_as_nested_block_entry_statment()
//{
// check_init_annotation();
// annotation_->flags.is_nested_block_entry_statment = true;
// //CAON_PTR_DEBUG(RPI_Stage_Form_Annotation ,annotation_)
//}

bool RPI_Stage_Form::is_effective_block_entry_statment()
{
 bool result = flags.is_block_entry_statment;

 if(!result)
   result = flags.is_nested_block_entry_statment;

 if(!result)
 {
  if(inner_elements_.isEmpty())
    return false;
  if(inner_elements_[0].kind() == RPI_Stage_Element_Kinds::Form)
    result = inner_elements_[0].form()->is_effective_block_entry_statment();
 }
 return result;

 //CAON_PTR_DEBUG(RPI_Stage_Form_Annotation ,annotation_)
}

//void RPI_Stage_Form::mark_as_initialization_expression()
//{
// check_init_annotation();
// annotation_->flags.is_block_entry_statment = true;
// //CAON_PTR_DEBUG(RPI_Stage_Form_Annotation ,annotation_)
//}

void RPI_Stage_Form::mark_as_assignment_expression()
{
 check_init_annotation();
 annotation_->flags.is_nested_as_assignment = true;
 CAON_PTR_DEBUG(RPI_Stage_Form_Annotation ,annotation_)
}

void RPI_Stage_Form::check_init_annotation()
{
 if(!annotation_)
 {
  annotation_ = new RPI_Stage_Form_Annotation();
 }
}

bool RPI_Stage_Form::s1_assignment_preempts_s0()
{
 return ANNOTATION_FLAG(s1_assignment_preempts_s0);
}


void RPI_Stage_Form::check_init_annotation(QString fn)
{
 typedef std::function<void(RPI_Stage_Form*)> fn_type;
 static QMap<QString, fn_type> static_map {{
  {"kb::if-without-elsif", [](RPI_Stage_Form* _this)
   {
    _this->check_init_annotation();
    _this->annotation_->flags.is_general_if = true;
    _this->annotation_->flags.is_if = true;
   }
  },
  {"kb::if-with-else", [](RPI_Stage_Form* _this)
   {
    _this->check_init_annotation();
    _this->annotation_->flags.is_general_if = true;
    _this->annotation_->flags.is_if_with_else = true;
   }
  },
  {"kb::if-with-elsif", [](RPI_Stage_Form* _this)
   {
    _this->check_init_annotation();
    _this->annotation_->flags.is_general_if = true;
    _this->annotation_->flags.is_if_with_elsif = true;
   }
  },
 }};
 if(static_map.contains(fn))
 {
  static_map[fn](this);
 }
}

bool RPI_Stage_Form::implict_end_form_before_nested_written()
{
 if(annotation_)
 {
  return annotation_->flags.implict_end_form_before_nested_written;
 }
 return false;
}

void RPI_Stage_Form::check_init_annotation_flags()
{
 if(annotation_)
 {
  if(!annotation_->flags.checked)
  {
   annotation_->flags.checked = true;
   if(annotation_->flags.is_general_if)
   {
    annotation_->flags.end_form_before_nested = true;
    annotation_->flags.surround_nested_secondary = true;
    annotation_->flags.write_pull_nested_form_group = true;
    annotation_->flags.write_push_nested_form_group = true;
    annotation_->flags.skip_write_command_package = true;
   }
  }
 }
}

void RPI_Stage_Form::write_statement_entry(
  QString node_name, QString prior_node_name, QString copy)
{
 pgb_(step_forms_).add_statement_sequence_node(prior_node_name, node_name);
 if(!copy.isEmpty())
   pgb_(step_forms_).copy_value(node_name, copy);
}

void RPI_Stage_Form::write_statement_entry_qts()
{

}

void RPI_Stage_Form::write_statement_entry_qts(QTextStream& qts)
{
 qts << "\n;statement_\n";
 qts << "\n( ; from write_statement_entry\n";
}

void RPI_Stage_Form::write_statement_leave_qts(QTextStream& qts)
{
 if(ANNOTATION_FLAG(skip_write_command_package))
 {

 }
 else
 {
  if(!ANNOTATION_FLAG(statement_form_closed_before_nested))
  {
   qts << "\n);_statement\n";
  }
  qts << "\n(kb::write-promote-expression)";
  qts << "\n(kb::write-cmd-eval)";
  qts << "\n(kb::write-statement-clear)";
 }
}

QString RPI_Stage_Form::get_s1_assignment_check()
{
 QString result = s1_assignment_check_;
 return result;
}

void RPI_Stage_Form::check_write_first_nested_is_assignment_leave(QTextStream& qts)
{
 CAON_PTR_DEBUG(RPI_Stage_Form_Annotation ,annotation_)
 if(ANNOTATION_FLAG(first_nested_is_assignment))
 {
  if(!annotation_->flags.child_implict_end_form_before_nested_written)
  {
   qts << "\n ) ; end nested assignment expression ... \n ";
  }
 }
}


void RPI_Stage_Form::write_checked_unmediated(QTextStream& qts, caon_ptr<RPI_Stage_Form> prior)
{
 qts << "( ; write_unmediated_ \n";
 write_unmediated(qts, prior);
 if(ANNOTATION_FLAG(has_prin1_quoted_form))
 {
  if(annotation_->flags.is_fn_no_block)
  {
   qts << ") ; _write_unmediated (with prin1; no block) \n";
  }
  else
  {
   qts << " ; _write_unmediated (with prin1) \n";
  }
 }
 else
 {
  qts << ") ; _write_unmediated \n";
 }
}

bool RPI_Stage_Form::is_non_block_expression()
{
 // for now ...
 return !plene_block_;
}

RPI_Assignment_Info* RPI_Stage_Form::get_parent_assignmnt_info()
{
 RPI_Assignment_Info* rai = nullptr;
 RPI_Assignment_Info* result = nullptr;
 if(parent_)
 {
  rai = &parent_->assignment_info();
  if(rai->has_text())
    result = rai;
 }
 return result;
}

//bool RPI_Stage_Form::has_preceder_token()
//{
// return ANNOTATION_FLAG(has_preceder_token);
//}

void RPI_Stage_Form::write_signature_type_declaration(QTextStream& qts)
{

}

void RPI_Stage_Form::write_type_declaration(QTextStream& qts)
{
 RPI_Stage_Element& rse1 = inner_elements_[1];
 RPI_Stage_Element& rse2 = inner_elements_[2];

 pgb_(step_forms_).add_type_declaration(rse1.text().prepend('@'),
   rse2.text().prepend('@'));
}


void RPI_Stage_Form::write_unmediated(QTextStream& qts, caon_ptr<RPI_Stage_Form> prior)
{
 CAON_PTR_DEBUG(RPI_Stage_Form ,prior)
 check_init_annotation_flags();
 QString icd = QString(implicit_added_depth_, '(');

 qts << icd;

 if(type_declaration_)
 {
  if(!flags.write_type_declaration)
  {
   qts << "skipping type declaration ...";
   return;
  }
  if(ANNOTATION_FLAG(is_fn_no_block))
  {
   if(inner_elements_.size() >= 2)
     write_signature_type_declaration(qts);
  }
  if(inner_elements_.size() >= 3)
    write_type_declaration(qts);
  return;
 }

 RPI_Assignment_Info* rai = get_parent_assignmnt_info();

// if(ANNOTATION_FLAG(is_block_entry_statment))
// {
 int channel_count = 0;
 RPI_Stage_Element_Kinds last_kind = RPI_Stage_Element_Kinds::N_A;

 // // note that prior_form is not always reset, so
  //   last_form will actually be the prior element only if
  //   last_kind is Form.
 caon_ptr<RPI_Stage_Form> prior_form = nullptr;

 //QString
 for(RPI_Stage_Element& rse : inner_elements_)
 {
  QString rset = rse.text();
  switch (rse.kind())
  {
  case RPI_Stage_Element_Kinds::Instruction_Symbol:
   {// for now
   }
   break;
  case RPI_Stage_Element_Kinds::S1_FGround_Symbol:
  case RPI_Stage_Element_Kinds::FGround_Symbol:
   if(rset.startsWith('#'))
     pgb_(step_forms_).make_token_node(rset.prepend('$'), "&fsym-node")
     = Purpose_Codes::Make_Token_Node_FSym;
   else
     pgb_(step_forms_).make_token_node(rset.prepend('@'), "&fsym-node")
     = Purpose_Codes::Make_Token_Node_FSym;

   if( flags.is_block_entry_statment
      || flags.is_inferred_block_entry_statment )
   {
    if(rai)
    {
     pgb_(step_forms_).make_statement_info_node(
       rai->text().prepend('@'), ":result",
       assignment_info_.encode_ikind().prepend(':'), "&si-node");
       //   ":parse-literal", assignment_info_.encode_ikind().prepend(':'));   rai->text()
     pgb_(step_forms_).add_block_entry_node("!last_block_pre_entry_node",
       "&fsym-node", "!last_block_entry_node", "&si-node");
    }
    else
      pgb_(step_forms_).add_block_entry_node("!last_block_pre_entry_node",
      "&fsym-node", "!last_block_entry_node");
   }
   else if(flags.is_inferred_block_entry_statment)
   {
    if(rai)
    {
     pgb_(step_forms_).make_statement_info_node(
       rai->text().prepend('@'), ":result",
       rai->encode_ikind().prepend(':'), "&si-node");
//?
// // which  assignment_info_.encode_ikind()?
//     pgb_(step_forms_).make_statement_info_node(
//       rai->text().prepend('@'), ":result",
//       assignment_info_.encode_ikind().prepend(':'), "&si-node");
     pgb_(step_forms_).add_statement_sequence_node("!last_statement_entry_node",
       "&fsym-node", "&si-node");
    }
    else
      pgb_(step_forms_).add_statement_sequence_node("!last_statement_entry_node", "&fsym-node");
   }
   // non block entry handled in the block ...

   if(flags.is_statement || ANNOTATION_FLAG(is_nested_as_assignment))
     pgb_(step_forms_).copy_value("&fsym-node", "!last_statement_entry_node")
     = Purpose_Codes::Copy_To_Last_Statement_Entry_Node;

//?
   pgb_(step_forms_).copy_value("&fsym-node", "!last_expression_entry_node");
   pgb_(step_forms_).copy_value("&fsym-node", "&channel-seq");
   break;

  case RPI_Stage_Element_Kinds::Literal:
   if(channel_count == 0)
     pgb_(step_forms_).add_channel_entry_token("&channel-seq", "lambda",
       rset.prepend('$'), "&channel-seq");
   else if(last_kind == RPI_Stage_Element_Kinds::Form)
   {
    QString srcn;
    if(prior_form)
    {
     if(prior_form->instruction("kb::write-anon-fdef"))
       srcn = "!prior_block_entry_node";
     else
       srcn = "!prior_expression_entry_node";
    }
    else
      srcn = "!prior_expression_entry_node";
    pgb_(step_forms_).add_channel_continue_token(srcn,
      rset.prepend('$'), "&channel-seq");
   }
   else
     pgb_(step_forms_).add_channel_token("&channel-seq",
       rset.prepend('$'), "&channel-seq");
   ++channel_count;
   break;

  case RPI_Stage_Element_Kinds::S1_Symbol:
    pgb_(step_forms_).add_channel_xentry_token("!last_expression_entry_node",
      "sigma", rset.prepend('@'), "&xchannel");
   break;

  case RPI_Stage_Element_Kinds::String_Literal:
   if(channel_count == 0)
     pgb_(step_forms_).add_channel_entry_token("&channel-seq", "lambda",
       rset.prepend('$'), "&channel-seq");
   else
     pgb_(step_forms_).add_channel_token("&channel-seq",
       rset.prepend('$'), "&channel-seq");
   ++channel_count;
   break;
  case RPI_Stage_Element_Kinds::Raw_Symbol:
   if(channel_count == 0)
     pgb_(step_forms_).add_channel_entry_token("&channel-seq", "lambda",
       rset.prepend('@'), "&channel-seq");
   else
     pgb_(step_forms_).add_channel_token("&channel-seq",
       rset.prepend('@'), "&channel-seq");
   ++channel_count;
   break;

  case RPI_Stage_Element_Kinds::Form:
   {
    caon_ptr<RPI_Stage_Form> f = rse.form();
    CAON_PTR_DEBUG(RPI_Stage_Form ,f)

    CAON_PTR_DEBUG(RPI_Stage_Form ,prior_form)

    if(f->instruction("kb::write-anon-fdef"))
    {
     f->write_unmediated(qts, nullptr);
     if(!f->step_forms().isEmpty())
     {
      pgb_(step_forms_).make_block_info_node("&bin");

      if(f->flags.prior_sibling_is_fground_token)
        pgb_.insert_after_purpose(f->step_forms(), Purpose_Codes::Make_Token_Node_FSym)
        .add_channel_entry_block_node("!last_expression_entry_node", "lambda",
        "&fsym-node", "&bin", "!last_block_entry_node");
      else if(f->flags.prior_sibling_is_token)
        pgb_.insert_after_purpose(f->step_forms(), Purpose_Codes::Make_Token_Node_FSym)
        .add_channel_sequence_block_node("&channel-seq",
        "&fsym-node", "&bin", "!last_block_entry_node");
      else if(f->flags.prior_sibling_is_expression)
        pgb_.insert_after_purpose(f->step_forms(), Purpose_Codes::Make_Token_Node_FSym)
        .add_channel_continue_block_node("!prior_expression_entry_node",
        "&fsym-node", "&bin",  "!last_block_entry_node");
      else if(f->flags.prior_sibling_is_block)
        pgb_.insert_after_purpose(f->step_forms(), Purpose_Codes::Make_Token_Node_FSym)
        .add_channel_cross_block_node("!prior_block_entry_node",
        "&fsym-node", "&bin",  "!last_block_entry_node");
//      pgb_.insert_after_purpose(f->step_forms(), Purpose_Codes::Make_Token_Node_FSym)
//      .add_channel_fground_cross_node("!prior_block_entry_node",
//      "&fsym-node", "&bin",  "!last_block_entry_node");


//         pgb_.insert_after_purpose(f->step_forms(), Purpose_Codes::Make_Token_Node_FGround_Sumbol)
//         .add_channel_continue_block_node("!last_expression_entry_node",
//         "&fsym-node", "&bin",  "!last_block_entry_node");

      pgb_(step_forms_).push_block_entry();

      step_forms_.append(f->step_forms());

      pgb_(step_forms_).pop_block_entry();
     }
    }
    else
    {
     f->write_unmediated(qts, nullptr);
     if(!f->step_forms().isEmpty())
     {
      if(f->is_non_block_expression())
      {
       QString ty = "u4"; //?

       if(f->is_deferred())
         pgb_(step_forms_).make_fsym_ground_node(
         ":?result", ty.prepend(':'),  "&fsym-ground-node");
       else
         pgb_(step_forms_).make_fsym_ground_node(
         ":result", ty.prepend(':'),  "&fsym-ground-node");

       if(f->flags.write_push_expression)
         pgb_(step_forms_).push_expression_entry();

//       if(f->flags.has_preceder_token)
//         pgb_.insert_after_purpose(f->step_forms(), Purpose_Codes::Make_Token_Node_FSym)
//         .add_fsym_ground_node(
//         "&channel-seq",
//         "&fsym-node", ":lambda", "&fsym-ground-node");

       if(f->flags.prior_sibling_is_token)
         pgb_.insert_after_purpose(f->step_forms(), Purpose_Codes::Make_Token_Node_FSym)
         .add_fsym_ground_node(
         "&channel-seq",
         "&fsym-node", ":lambda", "&fsym-ground-node");
       else if(f->flags.prior_sibling_is_expression)
         pgb_.insert_after_purpose(f->step_forms(), Purpose_Codes::Make_Token_Node_FSym)
         .add_channel_fground_cross_node(
         "!prior_expression_entry_node",
         "&fsym-node", ":lambda", "&fsym-ground-node");
       else if(f->flags.prior_sibling_is_fground_token)
         pgb_.insert_after_purpose(f->step_forms(), Purpose_Codes::Make_Token_Node_FSym)
         .add_channel_fground_coentry_node(
         "!last_expression_entry_node",
         "&fsym-node", ":lambda", "&fsym-ground-node");
       else if(f->flags.prior_sibling_is_block)
         pgb_.insert_after_purpose(f->step_forms(), Purpose_Codes::Make_Token_Node_FSym)
         .add_channel_fground_cross_node(
         "!prior_block_entry_node",
         "&fsym-node", ":lambda", "&fsym-ground-node");

//       else if(last_kind == RPI_Stage_Element_Kinds::Form)
//       {
//        if(f->flags.prior_sibling_is_expression)
//        {
//         pgb_.insert_after_purpose(f->step_forms(), Purpose_Codes::Make_Token_Node_FSym)
//         .add_channel_fground_cross_node(
//         "!prior_expression_entry_node",
//         "&fsym-node", ":lambda", "&fsym-ground-node");
//        }
//       }
//       else
//         pgb_.insert_after_purpose(f->step_forms(), Purpose_Codes::Make_Token_Node_FSym)
//         .add_channel_fground_coentry_node(
//         "!last_expression_entry_node",
//         "&fsym-node", ":lambda", "&fsym-ground-node");


      }
      step_forms_.append(f->step_forms());

      if(f->flags.write_push_expression)
        pgb_(step_forms_).pop_expression_entry();

//?
//      pgb_(step_forms_).copy_value( "!last_expression_entry_node",
//        "&channel-seq");
     }
    }
    ++channel_count;
    prior_form = f;
   }
   break;
  default:
   continue; // skip last_kind assignment ...
  }
  last_kind = rse.kind();
 }

 //?return;

 //}


 if(!ANNOTATION_FLAG(has_instruction_token))
 {
  if(ANNOTATION_FLAG(infer_write_s0_statement))
  {
   qts << "kb::write-s0-expression ";

   MS_Token askt = MS_Token {MS_Token_Kinds::Assignment_Kind, "none"};
   qts << askt.encode();
   qts << ' ';

  }
  else if(ANNOTATION_FLAG(unsurrounded_nested))
  {
   MS_Token mst {MS_Token_Kinds::Paren_Entry, QString::number(nesting_level_)};
   QString mste = mst.encode();
   qts << "\n " << mste << ' ';
  }
  else if(ANNOTATION_FLAG(first_nested_is_assignment))
  {
   qts << " ; for assignment ... \n ";
  }
  else if(ANNOTATION_FLAG(is_nested_as_assignment))
  {
   qts << " ; nested for assignment ... \n ";
  }
  else if(plene_block_)
  {
   qts << "kb::write-plene-block ";
  }
  else
  {
   MS_Token lisp_call_mode_token {MS_Token_Kinds::Note_Symbol, ":lc-f"};
   qts << "kb::prepare-expression " << lisp_call_mode_token.encode();
  }
 }

 if(plene_block_)
 {
  qts << "\n;block_\n";

  if(caon_ptr<RE_Block_Entry> rbe = plene_block_->get_block_entry())
  {
   if(rbe->flags.if_block)
   {
   }
  }
  else
  {
   // so get info plene_block_ mode ...
   qts << "\n;; fn body"
     "\n(kb::write-enter-plebod)";

  }

  qts << "\n(kb::write-enter-plene-block)\n";
  plene_block_->write(step_forms_, qts);
  qts << "\n(kb::write-leave-plene-block)\n";
 }
 else
 {
 }

 QList<caon_ptr<RPI_Stage_Form>> nested_forms;
 int nf_count = 0;
 int count = 0;

 int skip = -1;
 int pseudo_first = -1;

 for(RPI_Stage_Element element : inner_elements_)
 {
  if(count == skip)
  {
   ++count;
   continue;
  }

  if(element.form())
  {
   caon_ptr<RPI_Stage_Form> ef = element.form();
   CAON_PTR_DEBUG(RPI_Stage_Form ,ef)

   QString note = element.text();

#ifdef HIDE
   // //  would this only apply to tokens?
   if( (count == pseudo_first) && (assignment_token_.has_text() ) )
   {
    if(ANNOTATION_FLAG(first_nested_is_assignment))
    {
     // // should I set this here or elsewhere?
     element.first->mark_as_assignment_expression();
    }
    element.first->write(qts);
    ++count;
    continue;
   }
#endif // HIDE
   if( (count == 0) && (assignment_info_.has_text() ) )
   {
#ifdef HIDE
   // //  again, would this only apply to tokens?

    CAON_PTR_DEBUG(RPI_Stage_Form_Annotation ,annotation_)
    if(parent_ && parent_->s1_assignment_preempts_s0())
    {
     skip = 1;
    }
    else if(ANNOTATION_FLAG(first_inner_element_is_s1_assignment_preempts_s0))
    {
     pseudo_first = 1;
     ++count;
     continue;
    }
#endif // HIDE

    if(ANNOTATION_FLAG(first_nested_is_assignment))
    {
     // // should I set this here or elsewhere?
     element.form()->mark_as_assignment_expression();
    }

    element.form()->write(qts, prior);
   }
   else if(note.isEmpty())
   {
    // //  these are deferred to after ...
    nested_forms.push_back(ef);
    ++nf_count;

    MS_Token mst {MS_Token_Kinds::Nested_Forward,
      QString("%1-%2").arg(nesting_level_).arg(nf_count)};
    qts << ' ' << mst.encode() << ' ';
   }
   else
   {
    //?qts << ' ' << element.second.encode() << ' ';
    element.form()->write(qts, prior);
    qts << ' ';
   }
  }
  else
  {
   CAON_PTR_DEBUG(RPI_Stage_Form_Annotation ,annotation_)
   if(count == 0)
   {
    if(parent_ && parent_->s1_assignment_preempts_s0())
    {
     skip = 1;
    }
    else if(ANNOTATION_FLAG(first_inner_element_is_s1_assignment_preempts_s0))
    {
     pseudo_first = 1;
     ++count;
     continue;
    }
   }

//   QString rt = element.second.raw_text;
//   MS_Token_Kinds mstk = element.second.kind;

//?   QString str = element.second.encode();

 //?  qts << ' ' << str << ' ';
  }
  ++count;
 }

 if(chief_.startsWith('.'))
 {
  qts << "\n;;instruction\n)\n";
 }

 if(plene_block_)
 {
  qts << "\n;_plene_block";
 }
 else
 {
 }

 // ?? always end ...?
 if(!nested_forms.isEmpty())
 {
  check_init_annotation();
  annotation_->flags.surround_nested = true;
 }

 if(ANNOTATION_FLAG(end_form_before_nested))
 {
  qts << "\n) ;end form before nested...\n";
 }
 //?
 else if(nested_forms.isEmpty())
 {
  qts << "\n ; nothing nested...\n";
 }
 else if(!ANNOTATION_FLAG(skip_implicit_end_form_before_nested))
 {
  annotation_->flags.statement_form_closed_before_nested = true;
  annotation_->flags.implict_end_form_before_nested_written = true;

  CAON_PTR_DEBUG(RPI_Stage_Form_Annotation ,annotation_)

  qts << "\n) ;implicit end form before nested...\n";

 }

 if(ANNOTATION_FLAG(write_push_nested_form_group))
 {
  qts << "\n(kb::push-nested-form-group)\n";
 }

 if(ANNOTATION_FLAG(unsurrounded_nested))
 {
  MS_Token mst {MS_Token_Kinds::Paren_Leave, QString::number(nesting_level_)};
  qts << "\n " << mst.encode() << ' ';
 }

 int nfb_count = 0;

 for(caon_ptr<RPI_Stage_Form> nf: nested_forms)
 {
  CAON_PTR_DEBUG(RPI_Stage_Form_Annotation ,annotation_)
  ++nfb_count;

  if(ANNOTATION_FLAG(implict_end_form_before_nested_written))
  {
   nf->mark_parent_implict_end_form_before_nested_written();
   if(parent_)
   {
    parent_->mark_child_implict_end_form_before_nested_written();
   }
  }

  if(ANNOTATION_FLAG(surround_nested_secondary))
  {
   MS_Token mst {MS_Token_Kinds::Nested_Back,
     QString("%1-%2").arg(nesting_level_).arg(nfb_count)};
   qts << "\n(kb::enter-secondary-nested-form " << mst.encode() << ")\n";

   qts << "( ; secondary-nested-form-body_ \n";
  }
  else if(ANNOTATION_FLAG(surround_nested))
  {
   MS_Token mst {MS_Token_Kinds::Nested_Back,
     QString("%1-%2").arg(nesting_level_).arg(nfb_count)};

   auto fnd = wrapped_inner_elements_.find(nf);
   if(fnd == wrapped_inner_elements_.end())
   {
    qts << "\n(kb::enter-nested-form " << mst.encode() << ")\n";
    qts << "( ; nested-form-body_ \n";
   }
   else
   {
    QString note = fnd.value().first;
    int hdcode = fnd.value().second;
    MS_Token cmst {MS_Token_Kinds::Literal, QString::number(hdcode)};
    if(note.endsWith('\''))
    {
     note.chop(1);
     MS_Token nmst{MS_Token_Kinds::Note_Symbol, note};
     qts << "\n(kb::enter-nested-form " << nmst.encode() << " "
          << cmst.encode() << " "<< mst.encode() << ")\n";
     qts << "( ; nested-form-body_ \n";
     nf->mark_deferred(hdcode);
    }
    else
    {
     MS_Token nmst{MS_Token_Kinds::Note_Symbol, note};
     qts << "\n(kb::enter-nested-form " << nmst.encode() << " "
          << cmst.encode() << " "<< mst.encode() << ")\n";
     qts << "( ; nested-form-body_ \n";
    }
   }
  }
  else
  {
   nf->mark_unsurrounded_nested();
  }
  nf->set_nesting_level(nesting_level_ + 1);
  qts << ' ';
  nf->write(qts, prior);
  qts << ' ';
  if(ANNOTATION_FLAG(surround_nested_secondary))
  {
   qts << "\n) ; _nested-form-body \n";
   qts << "\n(kb::leave-secondary-nested-form)\n";
  }
  else if(ANNOTATION_FLAG(surround_nested))
  {

   CAON_PTR_DEBUG(RPI_Stage_Form_Annotation ,annotation_)

   if(annotation_->flags.parent_implict_end_form_before_nested_written)
   {
    if(annotation_->flags.skip_close_paren_on_parent_written)
    {
     qts << "\n ; _nested-form-body (lisp form already closed; parent) \n";
    }
    else if(nf->implict_end_form_before_nested_written())
    {
     qts << "\n ; _nested-form-body (nested form already closed; parent closed) \n";
    }
    else
    {
     qts << "\n) ; _nested-form-body (despite parent closed) \n";
    }
   }
   else
   {
    // // make sure this is always kosher
    if(nf->implict_end_form_before_nested_written())
    {
     qts << "\n ; _nested-form-body (lisp form already closed) \n";
    }
    else
    {
     qts << "\n) ; _nested-form-body \n";
    }
   }


   qts << "\n(kb::leave-nested-form)\n";
  }
 }

 if(ANNOTATION_FLAG(write_pull_nested_form_group))
 {
  qts << "\n(kb::pull-nested-form-group)\n";
 }

}

void RPI_Stage_Form::mark_unsurrounded_nested()
{
 check_init_annotation();
 annotation_->flags.unsurrounded_nested = true;
}

bool RPI_Stage_Form::is_deferred()
{
 return ANNOTATION_FLAG(is_deferred);
}

void RPI_Stage_Form::mark_deferred(int hdcode)
{
 check_init_annotation();
 annotation_->flags.is_deferred = true;
 hdcode_ = hdcode;
}

void RPI_Stage_Form::mark_parent_implict_end_form_before_nested_written()
{
 check_init_annotation();
 annotation_->flags.parent_implict_end_form_before_nested_written = true;
}

void RPI_Stage_Form::mark_child_implict_end_form_before_nested_written()
{
 check_init_annotation();
 annotation_->flags.child_implict_end_form_before_nested_written = true;
}

void RPI_Stage_Form::set_assignment_info(RPI_Assignment_Info& assignment_info)
{
 // always?
 check_init_annotation();
 annotation_->flags.first_nested_is_assignment = true;

 CAON_PTR_DEBUG(RPI_Stage_Form_Annotation ,annotation_)

 assignment_info_ = assignment_info;
}

void RPI_Stage_Form::add_s1_fn_element(QString fn, QString obj)
{
 check_init_annotation();
 annotation_->flags.has_instruction_token = true;

 inner_elements_.push_back(RPI_Stage_Element(
   RPI_Stage_Element_Kinds::S1_FGround_Symbol, fn));

 inner_elements_.push_back(RPI_Stage_Element(
   RPI_Stage_Element_Kinds::S1_Symbol, obj));
}


void RPI_Stage_Form::add_assignment_initialization_element(RPI_Stage_Element_Kinds kind, QString text)
{
 inner_elements_.push_back(RPI_Stage_Element(kind, text));
}

void RPI_Stage_Form::add_literal_element(RPI_Stage_Element_Kinds kind, QString text)
{
 inner_elements_.push_back(RPI_Stage_Element(kind, text));
}

void RPI_Stage_Form::add_insert_element(RPI_Stage_Element_Kinds kind, QString text)
{
 inner_elements_.push_back(RPI_Stage_Element(kind, text));
}

void RPI_Stage_Form::add_carrier_element(RPI_Stage_Element_Kinds kind, QString text)
{
 inner_elements_.push_back(RPI_Stage_Element(kind, text));
}

void RPI_Stage_Form::add_kauvir_element(RPI_Stage_Element_Kinds kind, QString text)
{
 inner_elements_.push_back(RPI_Stage_Element(kind, text));
}

void RPI_Stage_Form::init_inferred_s0_statement()
{
 check_init_annotation();
 annotation_->flags.infer_write_s0_statement = true;
}

void RPI_Stage_Form::add_fn_element(RPI_Stage_Element_Kinds kind, QString text)
{
 inner_elements_.push_back(RPI_Stage_Element(kind, text));
}

void RPI_Stage_Form::add_bridge_element(RPI_Stage_Element_Kinds kind, QString text)
{
 inner_elements_.push_back(RPI_Stage_Element(kind, text));
}

void RPI_Stage_Form::add_instruction_element(RPI_Stage_Element_Kinds kind, QString text)
{
 check_init_annotation();
 annotation_->flags.has_instruction_token = true;

 if(annotation_->flags.parent_s1_assignment_preempts_s0)
 {
  QString ch = parent_->s1_assignment_check();
//  MS_Token mt1 = {MS_Token_Kinds::Preempted_Instruction_Symbol, ch};
//  inner_elements_.push_back({nullptr, mt1});
  annotation_->flags.first_inner_element_is_s1_assignment_preempts_s0 = true;
 }

 inner_elements_.push_back(RPI_Stage_Element(kind, text));
}

void RPI_Stage_Form::add_argument_element(RPI_Stage_Element_Kinds kind, QString text)
{
 inner_elements_.push_back(RPI_Stage_Element(kind, text));
}
