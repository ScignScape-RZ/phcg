
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DYGRED_DEPREL_CALLBACKS__H
#define DYGRED_DEPREL_CALLBACKS__H

#include <QMap>
#include <QString>
#include <functional>


#include "udpipe.h"

class DygRed_Sentence;
class DygRed_Word_Pos;

class DygRed_Deprel_Callbacks
{
 typedef std::function<QString(QString, DygRed_Sentence&, word&,
   DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw, DygRed_Word_Pos** rr)> fn_type;

 QMap<QString, QMap<QString, fn_type>> cbs_;

public:

 DygRed_Deprel_Callbacks();

 void add_cb(QString k, QString s, fn_type fn);

 void check_run_cb(QString k, QString s, DygRed_Sentence& dgs, word& w,
   DygRed_Word_Pos* dgw, DygRed_Word_Pos* hdgw, DygRed_Word_Pos** rr = nullptr) const;


};


#endif
