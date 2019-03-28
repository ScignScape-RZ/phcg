
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef _EACH_HOLDERS__H
#define _EACH_HOLDERS__H

#include <functional>

template<typename _THIS_Type, typename VAL_type>
struct _each_holder
{
 _THIS_Type& _this; //typename _THIS_Type::Value_type& v
 void operator <=(std::function<void(VAL_type& v)> fn)
 {
  _this._each(fn);
 }
};

template<typename _THIS_Type, typename VAL_type>
struct _reach_holder
{
 _THIS_Type& _this;
 void operator <=(std::function<void(VAL_type& v)> fn)
 {
  _this._reach(fn);
 }
};

template<typename VEC_Type, typename VAL_Type>
struct each_holders
{
 union{
 _each_holder<VEC_Type, VAL_Type> each;
 _reach_holder<VEC_Type, VAL_Type> reach;
 };
};


#endif // _EACH_HOLDERS__H
