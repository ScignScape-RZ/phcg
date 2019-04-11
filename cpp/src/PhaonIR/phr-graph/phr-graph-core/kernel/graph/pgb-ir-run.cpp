
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "pgb-ir-run.h"

#include "textio.h"

USING_KANS(TextIO)

#include "multigraph-token.h"

#include "rzns.h"

USING_RZNS(PhrGraphCore)

PGB_IR_Run::PGB_IR_Run(PHR_Graph_Build& graph_build)
 : graph_build_(graph_build)
{

}

void PGB_IR_Run::run_from_file(QString file)
{
 QString lines;
 load_file(file, lines);

 run_lines(lines);
}

void PGB_IR_Run::run_lines(QString& lines)
{
 int pos = 0;
 int end = lines.length();

 while(pos < end)
 {
  int sp = lines.indexOf("(pgb::", pos);
  if(sp == -1)
    break;
  int np = lines.indexOf(')', sp + 6);
//  if(np == -1)
//    np = lines.indexOf("\n.\n", pos);
  if(np == -1)
    break;
  QString l = lines.mid(sp + 6, np - sp - 6).simplified();
  run_line(l);
  pos = np + 1;
 }
}

void PGB_IR_Run::run_line(QString fn, QMultiMap<MG_Token_Kinds, QString>& mgts)
{

}

void PGB_IR_Run::run_line(QString line)
{
 QStringList qsl = line.split(' ');
 QString fn = qsl.takeFirst();
 QMultiMap<MG_Token_Kinds, QString> mgts;
 for(QString qs: qsl)
 {
  MG_Token mgt = MG_Token::decode_symbol(qs);
  mgts.insert(mgt.kind, mgt.raw_text);
 }
 run_line(fn, mgts);
}

