
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_COCYCLIC_TYPE__H
#define PHR_COCYCLIC_TYPE__H

#include <QString>
#include <QList>
#include <QPair>

#include "accessors.h"

class PHR_Type;

class PHR_Cocyclic_Type
{
 QString name_;
 QList<QPair<QString, PHR_Type*>> precycle_fields_;
 QList<QPair<QString, PHR_Type*>> cocycle_fields_;

public:

 PHR_Cocyclic_Type(QString name);

 void add_precycle_field(QString sym, PHR_Type* ty);
 void add_cocycle_field(QString sym, PHR_Type* ty);


};

#endif // PHR_COCYCLIC_TYPE__H
