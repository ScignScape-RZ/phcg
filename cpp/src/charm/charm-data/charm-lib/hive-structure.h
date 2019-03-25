
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef HIVE_STRUCTURE__H
#define HIVE_STRUCTURE__H


#include "accessors.h"

#include <QVector>
#include <QString>
#include <QMap>

struct Hive_Block
{
 void* values;
 Hive_Block* next_block;
};


class Hive_Structure
{
 quint8 block_size_;
 quint32 total_size_;
 quint16 value_size_;

 Hive_Block* first_block_;

public:

 Hive_Structure();


 ACCESSORS(quint16, block_size)
 ACCESSORS(quint32, total_size)
 ACCESSORS(quint16, value_size)

 ACCESSORS(Hive_Block*, first_block)

 void* get_push_back_location();
 void* get_indexed_location(quint32 index);

 void check_init_blocks(quint32 max);
};




#endif // HIVE_STRUCTURE__H
