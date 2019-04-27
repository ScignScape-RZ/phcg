
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

 QList<PGB_IR_Build::Text_With_Purpose> tps;

 pgb(tps).make_root_node("!last_block_pre_entry_node");

// make_statement_info_node(QString anchor_name,
//    QString channel_name, QString anchor_kind)

 pgb(tps).make_statement_info_node("@x", ":parse-literal", ":\\=", "&si-node");
 pgb(tps).add_block_entry_token("!last_block_pre_entry_node",
   "$64", "&si-node", "!last_statement_entry_node");

 pgb(tps).make_token_node("@&prn", "&fsym-node");
 pgb(tps).add_statement_sequence_node("!last_statement_entry_node", "&fsym-node");
 pgb(tps).copy_value("&fsym-node", "!last_statement_entry_node");
 pgb(tps).add_channel_entry_token("&fsym-node",
   "lambda", "@x", "&current-channel-node");

 pgb.generate_file(tps);

 qDebug() << "ok";
 return 0;
}


int main1(int argc, char **argv)
{
 PGB_IR_Build pgb(DEFAULT_PHR_FOLDER "/pgb/t1.gen.pgb");

 QList<PGB_IR_Build::Text_With_Purpose> tps;

 pgb(tps).make_root_node("!last_block_pre_entry_node");
 pgb(tps).make_token_node("@&prn", "&fsym-node");
 pgb(tps).add_block_entry_node("!last_block_pre_entry_node", "&fsym-node", "!last_block_entry_node");
 pgb(tps).copy_value("&fsym-node", "!last_statement_entry_node");
 pgb(tps).add_channel_entry_token("&fsym-node",
   "lambda", "$44", "&current-channel-node");

// pgb(tps).make_token_node("@&prn", "&fsym-node");
// pgb(tps).add_statement_sequence_node("!last_statement_entry_node", "&fsym-node");

// pgb(tps).add_channel_entry_token("&fsym-node",
//   "lambda", "$55", "&fsym-node");



// pgb.make_root_node("current_node", MG_Token_Subgroups::Known);
// pgb.make_token_node("&prn", MG_Token_Subgroups::Symbol,
//   "fsym-node", MG_Token_Subgroups::Ledger);
// pgb.add_block_entry_node("current_node",
//   MG_Token_Subgroups::Known, "fsym-node", MG_Token_Subgroups::Ledger);
// pgb.add_channel_token("fsym-node", MG_Token_Subgroups::Ledger,
//   "lambda", "44", MG_Token_Subgroups::Value,
//   "current-channel-node", MG_Token_Subgroups::Ledger);

 pgb.generate_file(tps);

 qDebug() << "ok";
 return 0;
}
