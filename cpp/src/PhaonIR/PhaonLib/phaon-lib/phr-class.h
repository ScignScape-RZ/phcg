
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CLASS__H
#define PHR_CLASS__H


#include "kans.h"

#include <QString>

#include "accessors.h"


//KANS_(PhaonLib)

class PHR_Namespace;

class PHR_Class
{
 PHR_Namespace* phaon_namespace_;
 QString name_;

public:

 PHR_Class(QString name, PHR_Namespace* phaon_namespace);

 ACCESSORS(QString ,name)
 ACCESSORS(PHR_Namespace* ,phaon_namespace)


};


//_KANS(PhaonLib)


#endif //PHR_CLASS__H
