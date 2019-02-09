
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_RUNTIME_SCOPE__H
#define PHR_RUNTIME_SCOPE__H

#include <QString>
#include <QMap>


#include "phr-scope-value.h"

class PHR_Logical_Scope_Info;
class PHR_Type;


class PHR_Runtime_Scope
{
 PHR_Logical_Scope_Info* info_;
 PHR_Runtime_Scope* parent_scope_;

 QMap<QString, PHR_Scope_Value> values_;

public:

 PHR_Runtime_Scope(PHR_Runtime_Scope* parent_scope, PHR_Logical_Scope_Info* info = nullptr);

 void add_value(QString key, PHR_Type* ty, quint64 val);
 PHR_Type* find_value(QString key, quint64& val);

 void update_value(QString key, void* pv);
 void update_raw_value(QString key, quint64 val);

};

#endif // PHR_RUNTIME_SCOPE__H
