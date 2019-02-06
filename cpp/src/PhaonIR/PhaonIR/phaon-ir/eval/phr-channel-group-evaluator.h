
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_CHANNEL_GROUP_EVALUATOR__H
#define PHR_CHANNEL_GROUP_EVALUATOR__H


#include <QMap>

class PHR_Channel_Group;
class PhaonIR;
class PHR_Channel;

class PHR_Channel_Group_Evaluator
{
 PhaonIR& phr_;

protected:

 PHR_Channel_Group& channel_group_;

 PHR_Channel* get_channel_by_sp_name(QString sp_name, PHR_Channel_Group& pcg);

 qint32 phr_get_s4_symbol_value(QString sym);


public:

 PHR_Channel_Group_Evaluator(PhaonIR& phr, PHR_Channel_Group& channel_group);

 virtual void run_eval() = 0;
 virtual void debug_report() = 0;
 virtual void* get_result_value();
 virtual QString get_result_string();

 template<typename T>
 T get_result_value_as()
 {
  return *(T*)get_result_value();
 }


};

#endif // PHR_CHANNEL_GROUP_EVALUATOR__H
