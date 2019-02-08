
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_TYPE_SYSTEM__H
#define PHR_TYPE_SYSTEM__H


#include <QMap>
#include <QString>

class PHR_Type;

class PHR_Type_System
{
 QMap<QString, PHR_Type*> types_;

public:

 PHR_Type_System();

 void check_add_type_by_name(QString name, quint8 byte_code);

 PHR_Type* get_type_by_name(QString name);


};

#endif //  PHR_TYPE_SYSTEM__H
