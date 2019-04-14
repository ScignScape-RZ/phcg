
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-graph-core/kernel/graph/phr-graph.h"

#include "phr-graph-core/kernel/graph/pgb-ir-build.h"


#include "rzns.h"

USING_RZNS(PhrGraphCore)

#include <QDebug>

int main(int argc, char **argv)
{
 PGB_IR_Build pgb(DEFAULT_PHR_FOLDER "/pgb/t1.gen.pgb");

 QStringList qsl;

 pgb(qsl).make_root_node("!last_block_pre_entry_node");
 pgb(qsl).make_token_node("@&prn", "&entry-node");
 pgb(qsl).add_block_entry_node("!last_block_pre_entry_node", "&entry-node");
 pgb(qsl).copy_value("&entry-node", "!last_statement_entry_node");
 pgb(qsl).add_channel_entry_token("&entry-node",
   "lambda", "$44", "&current-channel-node");

// pgb(qsl).make_token_node("@&prn", "&entry-node");
// pgb(qsl).add_statement_sequence_node("!last_statement_entry_node", "&entry-node");

// pgb(qsl).add_channel_entry_token("&entry-node",
//   "lambda", "$55", "&entry-node");



// pgb.make_root_node("current_node", MG_Token_Subgroups::Known);
// pgb.make_token_node("&prn", MG_Token_Subgroups::Symbol,
//   "entry-node", MG_Token_Subgroups::Ledger);
// pgb.add_block_entry_node("current_node",
//   MG_Token_Subgroups::Known, "entry-node", MG_Token_Subgroups::Ledger);
// pgb.add_channel_token("entry-node", MG_Token_Subgroups::Ledger,
//   "lambda", "44", MG_Token_Subgroups::Value,
//   "current-channel-node", MG_Token_Subgroups::Ledger);

 pgb.generate_file(qsl);

 qDebug() << "ok";
 return 0;
}
