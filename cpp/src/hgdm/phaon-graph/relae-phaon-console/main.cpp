
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QString>
#include <QDebug>


#include "hgdm/phaon-graph/phaong/phaong.h"
#include "hgdm/phaon-graph/phaong/phaong-types.h"


#include "hgdm/phaon-graph/relae-phaon/kernel/graph/relae-phaon-node.h"
#include "hgdm/phaon-graph/relae-phaon/kernel/frame/relae-phaon-frame.h"
#include "hgdm/phaon-graph/relae-phaon/kernel/query/relae-phaon-query.h"

#include "kans.h"
USING_KANS(HGDMCore)



int main(int argc, char **argv)
{
 phaong<pg_t> pg;

 QVector<phaong<pg_t>::Hypernode*> hypernodes;
 QVector<phaong<pg_t>::Hyperedge*> hyperedges;

 QPair<QVector<phaong<pg_t>::Hypernode*>&,
   QVector<phaong<pg_t>::Hyperedge*>&> graph {hypernodes, hyperedges};

 typedef QPair<QVector<phaong<pg_t>::Hypernode*>&,
   QVector<phaong<pg_t>::Hyperedge*>&> g_t;

 pg.set_user_data(&graph);

 pg.set_node_add_function([](phaong<pg_t>& _pg, phaong<pg_t>::Hypernode* hn)
 {
  QVector<phaong<pg_t>::Hypernode*>& hh = _pg.user_data_as<g_t>()->first;
  hh.push_back(hn);
 });

 pg.set_edge_add_function([](phaong<pg_t>& _pgs, phaong<pg_t>::Hyperedge* he)
 {
  QVector<phaong<pg_t>::Hyperedge*>& hv = _pgs.user_data_as<g_t>()->second;
  hv.push_back(he);
 });


 phaong<pg_t>::Hypernode* hn = pg.new_hypernode(5);
 pg.set_sf(hn, 0, {"xx", nullptr}, {"QString", nullptr});


 RPH_Node n(hn);

// //caon_ptr<QString> xx = n.as<QString>();
 caon_ptr<phaong<pg_t>::Hypernode> hn1 = n.phhn();

 pg.get_data(hn1.raw_pointer(), 0, [](QPair<QString, void*>& pr)
 {
  qDebug() << pr.first;
 });


 phaong<pg_t>::Hypernode* hn2 = pg.new_hypernode(-8);
 pg.set_af(hn2, 0, {"aa", nullptr}, {"QString", nullptr});
 pg.get_af(hn2, 0, [](QPair<QString, void*>& pr)
 {
  qDebug() << pr.first;
 });


 RPH_Node n1(hn2);

 RPH_Frame& fr = RPH_Frame::instance();
 const RPH_Query& rq = RPH_Query::instance();

 &n << fr/rq.Generic >> &n1;


 //qDebug() << *xx;

 return 0;
}


int main1(int argc, char **argv)
{
 phaong<pg_t> pg;

 QVector<phaong<pg_t>::Hypernode*> hypernodes;
 QVector<phaong<pg_t>::Hyperedge*> hyperedges;

 QPair<QVector<phaong<pg_t>::Hypernode*>&,
   QVector<phaong<pg_t>::Hyperedge*>&> graph {hypernodes, hyperedges};

 typedef QPair<QVector<phaong<pg_t>::Hypernode*>&,
   QVector<phaong<pg_t>::Hyperedge*>&> g_t;

 pg.set_user_data(&graph);

 pg.set_node_add_function([](phaong<pg_t>& _pg, phaong<pg_t>::Hypernode* hn)
 {
  QVector<phaong<pg_t>::Hypernode*>& hh = _pg.user_data_as<g_t>()->first;
  hh.push_back(hn);
 });

 pg.set_edge_add_function([](phaong<pg_t>& _pgs, phaong<pg_t>::Hyperedge* he)
 {
  QVector<phaong<pg_t>::Hyperedge*>& hv = _pgs.user_data_as<g_t>()->second;
  hv.push_back(he);
 });

 phaong<pg_t>::Hypernode* hn = pg.new_hypernode(-8);
 pg.set_data(hn, 0, {"xx", nullptr}, {"QString", nullptr});
 pg.get_data(hn, 0, [](QPair<QString, void*>& pr)
 {
  qDebug() << pr.first;
 });

// pg.set_af(hn, 0, {"aa", nullptr}, {"QString", nullptr});
// pg.get_af(hn, 0, [](QPair<QString, void*>& pr)
// {
//  qDebug() << pr.first;
// });




// pg.set_data(hn, 82, {"aa", nullptr}, {"QString", nullptr});
// pg.get_data(hn, 82, [](QPair<QString, void*>& pr)
// {
//  qDebug() << pr.first;
// });

// pg.set_data(hn, 5, {"bx", nullptr}, {"QString", nullptr});
// pg.get_data(hn, 5, [](QPair<QString, void*>& pr)
// {
//  qDebug() << pr.first;
// });

// pg.set_data(hn, 52, {"ax", nullptr}, {"QString", nullptr});
// pg.get_data(hn, 52, [](QPair<QString, void*>& pr)
// {
//  qDebug() << pr.first;
// });

// pg.set_data(hn, 5, {"bx", nullptr}, {"QString", nullptr});
// pg.get_data(hn, 5, [](QPair<QString, void*>& pr)
// {
//  qDebug() << pr.first;
// });

 phaong<pg_t>::Hypernode* hn1 = pg.new_hypernode(8);
 pg.set_data(hn1, 11, {"yy", nullptr}, {"QString", nullptr});
 pg.get_data(hn1, 3, [](QPair<QString, void*>& pr)
 {
  qDebug() << pr.first;
 });

 pg.new_hyperedge(hn, hn1);

 return 0;
}


//phaong<pg_t>::Hypernode* hn4 = pg.new_hypernode(6, 1);
//pg.set_af(hn4, 0, {"bb", nullptr}, {"QString", nullptr});
//pg.get_af(hn4, 0, [](QPair<QString, void*>& pr)
//{
// qDebug() << pr.first;
//});
//pg.set_sf(hn4, 0, {"cc", nullptr}, {"QString", nullptr});
//pg.get_sf(hn4, 0, [](QPair<QString, void*>& pr)
//{
// qDebug() << pr.first;
//});
//pg.get_data(hn4, 1, [](QPair<QString, void*>& pr)
//{
// qDebug() << pr.first;
//});
