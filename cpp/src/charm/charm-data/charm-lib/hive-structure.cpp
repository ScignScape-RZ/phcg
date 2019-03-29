
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "hive-structure.h"

#include <QVector>
#include <QString>
#include <QMap>

#include <QDebug>

Hive_Structure::Hive_Structure()
 :  block_size_(0), total_size_(0),
   value_size_(0), first_block_(nullptr)
{

}

Hive_Block* Hive_Structure::check_init_blocks(quint32 max)
{
 Hive_Block** current_block = &first_block_;
 Hive_Block* result = nullptr;
 for(int i = 0; i <= max; ++i)
 {
  if(*current_block)
  {
   result = *current_block;
   current_block = &(*current_block)->next_block;
   //last_block = *current_block;
   continue;
  }
  void* mem = malloc(block_size_ * value_size_);

//  if(!mem)
//  {
//   qDebug() << "malloc failed ...";
//  }
  (*current_block) = new Hive_Block{mem, nullptr};
  result = *current_block;
  current_block = &(result->next_block);
//  if(last_block)
//    last_block->next_block = *current_block;
//  last_block = current_block;
 }
 return result;
}


void* Hive_Structure::get_indexed_location(quint32 index)
{
 if(index >= total_size_)
   return nullptr;
 quint32 blkn = index / block_size_;
 quint16 blki = index % block_size_;
 return get_indexed_location(blkn, blki);
}

void* Hive_Structure::get_indexed_location_unchecked(quint32 index)
{
 quint32 blkn = index / block_size_;
 quint16 blki = index % block_size_;
 return get_indexed_location(blkn, blki);
}


void* Hive_Structure::get_indexed_location(quint32 blkn, quint16 blki)
{
 Hive_Block* hb = check_init_blocks(blkn);
// char loc [value_size_][block_size_] = (char*) hb->values;
// return loc[blki];

 return (unsigned char*)(hb->values)
   + (blki * value_size_);

}

void* Hive_Structure::get_back_location()
{
 if(total_size_ == 0)
   return nullptr;
 return get_indexed_location(total_size_ - 1);
}

void Hive_Structure::push_first_block()
{
 void* mem = malloc(block_size_ * value_size_);
 first_block_ = new Hive_Block{mem, first_block_};
 total_size_ += block_size_;
}

void Hive_Structure::pop_first_block()
{
 if(first_block_)
 {
  if(first_block_->next_block)
  {
   Hive_Block* hb = first_block_;
   first_block_ = first_block_->next_block;
   delete hb;
  }
  else
  {
   delete first_block_;
   first_block_ = nullptr;
  }
 }
}

void Hive_Structure::pop_back()
{
 if(total_size_ == 0)
   return;
 --total_size_;

 quint16 blki = (total_size_ % block_size_);

 if(blki == 0)
 {
  quint32 blkn = total_size_ / block_size_;
  Hive_Block* hb = check_init_blocks(blkn);
  if(hb)
  {
   if(hb->next_block)
   {
    delete hb->next_block;
    hb->next_block = nullptr;
   }
  }
 }


}

void* Hive_Structure::get_push_back_location()
{
 return get_indexed_location_unchecked(total_size_);
}

void* Hive_Structure::get_iterator_location(iterator& hit)
{
 return get_indexed_location(hit.block_index, hit.inner_index);
}

void Hive_Structure::increment_total_size()
{
 ++total_size_;
}

void Hive_Structure::check_start_iterator(iterator& hit)
{
 if(total_size_ == 0)
 {
  hit.total_index = -1;
  return;
 }
}

void Hive_Structure::reverse_iterator(iterator& hit)
{
 if(total_size_ == 0)
 {
  hit.total_index = -1;
  return;
 }
 hit.total_index = total_size_ - 1;
 hit.block_index = hit.total_index / block_size_;
 hit.inner_index = hit.total_index % block_size_;
}

void Hive_Structure::position_iterator(iterator& hit, quint32 ix)
{
 if(ix >= total_size_)
 {
  hit.total_index = -1;
  return;
 }
 hit.total_index = ix;
 hit.block_index = ix / block_size_;
 hit.inner_index = ix % block_size_;
}

void Hive_Structure::increment_iterator(iterator& hit)
{
 if(++hit.total_index == total_size_)
   hit.total_index = -1;
 if(++hit.inner_index == block_size_)
 {
  hit.inner_index = 0;
  ++hit.block_index;
 }
}


void Hive_Structure::decrement_iterator(iterator& hit)
{
 if(hit.total_index == 0)
 {
  hit.total_index = -1;
  return;
 }
 --hit.total_index;
 if(hit.inner_index == 0)
 {
  hit.inner_index = block_size_ - 1;
  --hit.block_index;
 }
 else
   --hit.inner_index;
}
