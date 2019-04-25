
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-code-model.h"

#include "types/phr-type.h"
#include "types/phr-type-object.h"

#include "types/phr-type-system.h"

#include <QMetaType>


PHR_Code_Model::PHR_Code_Model()
  :  type_system_(nullptr), scopes_(nullptr),
     //?current_symbol_scope_(nullptr),
     table_(nullptr)
{

}

PHR_Type_Object* PHR_Code_Model::create_and_register_type_object(QString name)
{
 if(name.endsWith('*'))
 {
  return create_and_register_type_object(name, DEFAULT_PTR_BYTE_CODE);
 }
 else
 {
  return create_and_register_type_object(name, 8);
 }
}

PHR_Type_Object* PHR_Code_Model::create_and_register_type_object(QString name, int bc)
{
 PHR_Type* pt = type_system_->check_add_type_by_name(name, bc);
 PHR_Type_Object* pto = new PHR_Type_Object(pt);
// KCM_Type_Object* result = new KCM_Type_Object(kto);

 if(name.endsWith('*'))
 {
  int pid = QMetaType::type(name.toLatin1());
  if(pid != QMetaType::UnknownType)
  {
   const QMetaObject* pqmo = QMetaType::metaObjectForType(pid);
   if(pqmo)
   {
    pt->set_pqmo(pqmo);
   }
  }
  name.chop(1);
  int id = QMetaType::type(name.toLatin1());
  if(id != QMetaType::UnknownType)
  {
   pt->set_qmetatype_ptr_code(id);
   const QMetaObject* qmo = QMetaType::metaObjectForType(id);
   if(qmo)
   {
    pt->set_qmo(qmo);
   }
  }
 }
 else
 {
  int id = QMetaType::type(name.toLatin1());
  if(id != QMetaType::UnknownType)
  {
   pt->set_qmetatype_ptr_code(id);
   const QMetaObject* qmo = QMetaType::metaObjectForType(id);
   if(qmo)
   {
    pt->set_qmo(qmo);
   }
  }
  int pid = QMetaType::type( (name + "*").toLatin1() );
  if(pid != QMetaType::UnknownType)
  {
   const QMetaObject* pqmo = QMetaType::metaObjectForType(pid);
   if(pqmo)
   {
    pt->set_pqmo(pqmo);
    pt->set_qmetatype_ptr_code(pid);
    // // kto->check_register_variant_and_metatype_info(QVariant::UserType, pid);
   }
  }
 }
 return pto;
}

void PHR_Code_Model::direct_eval(PHR_Command_Package* pcp, PHR_Symbol_Scope* current_symbol_scope)
{
 if(direct_eval_fn_)
 {
  //?current_symbol_scope_ = current_symbol_scope;
  direct_eval_fn_(this, pcp, current_symbol_scope);
 }
}

void PHR_Code_Model::init_scope_system()
{
 //scope_system_->join_lexical_scope(current_lexical_scope_);
}
