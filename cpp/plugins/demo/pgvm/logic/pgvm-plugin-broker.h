#pragma once

#include <QMap>
#include <QString>

class QTcpServer;

class PGVM_Plugin_Broker
{
 QMap<QString, QString> projects_by_xpdf_;

 QTcpServer* tcp_server_;
 quint64 current_tcp_msecs_;

public:

 PGVM_Plugin_Broker();

 QString get_project_name_from_xpdf(QString key);
 void run_msg(QString msg, QByteArray qba);
 void run_fig(const QByteArray& qba);

 void activate_server();


};


