
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_SYMBOL_SCOPE__H
#define PHR_SYMBOL_SCOPE__H


#include "kans.h"

#include <QString>
#include <QMap>

#include "accessors.h"

#include "phr-function-vector.h"


//KANS_(PhaonLib)

class PHR_Namespace;

class PHR_Symbol_Scope : public QMap<QString, PHR_Function_Vector>
{

public:

 PHR_Symbol_Scope();



};


//_KANS(PhaonLib)


#endif //PHR_SYMBOL_SCOPE__H
