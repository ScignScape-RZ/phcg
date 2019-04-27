
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PCM_REPORT_SYNTAX__H
#define PCM_REPORT_SYNTAX__H


#include "kans.h"

#include "accessors.h"
#include "flags.h"

#include <QVector>
#include <QTextStream>
#include <QMap>

//#include "pcm-channel.h"



class PCM_Report_Syntax
{
public:

 flags_(3)
  bool compress_fground_channel:1;
  bool identify_channel_names:1;
  bool identify_types:1;
  bool merge_fground_and_lambda:1;
  bool surround_carriers:1;
  bool types_after_values:1;
  bool types_colon_separator:1;
  bool use_block_statement_syntax:1;
  bool use_block_braces:1;
  bool use_keyword_for_function_types:1;
  bool write_empty_lambda_channel:1;
  bool write_empty_result_channel:1;
  bool arrow_before_result_channel:1;
  bool use_statement_annotations:1;
  bool comma_separate_channel_carriers:1;
  bool cast_after_expression:1;
  bool expand_array_indicators:1;
  bool surround_type_expressions:1;
 _flags

private:

// QMap<KCM_Channel::Kinds, QString> channel_kind_codes_;

// typedef QMap<KCM_Channel::Kinds, QString> channel_kind_codes_type;


public:

 PCM_Report_Syntax();


// ACCESSORS__RGET(channel_kind_codes_type ,channel_kind_codes)

// QString get_channel_kind_code(KCM_Channel::Kinds kind);

};




#endif //PCM_REPORT_SYNTAX__H
