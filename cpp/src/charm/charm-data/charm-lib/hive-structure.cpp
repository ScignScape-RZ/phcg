
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "hive-structure.h"

#include <QVector>
#include <QString>
#include <QMap>

Hive_Structure::Hive_Structure()
 :  block_size_(0), total_size_(0),
   value_size_(0), first_block_(nullptr)
{

}

void Hive_Structure::check_init_blocks(quint32 max)
{
 Hive_Block* current_block = first_block_;
 Hive_Block* last_block = nullptr;
 for(int i = 0; i <= max; ++i)
 {
  if(current_block)
  {
   current_block = current_block->next_block;
   last_block = current_block;
   continue;
  }
  void* mem = malloc(block_size_ * total_size_);
  current_block = new Hive_Block{mem, nullptr};
  if(last_block)
    last_block->next_block = current_block;
  last_block = current_block;
 }
}

void* Hive_Structure::get_indexed_location(quint32 index)
{
 quint32 blkn = index / block_size_;
 quint16 blki = index % block_size_;

 check_init_blocks(blkn);

}

void* Hive_Structure::get_push_back_location()
{
 return get_indexed_location(total_size_ + 1);

}
