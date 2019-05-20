#pragma once

#include <QMap>
#include <QString>

#include <functional>

class QTcpServer;

class PGVM_Plugin_Broker
{
 QMap<QString, QString> projects_by_xpdf_;
 QMap<QString, QStringList> files_by_project_;

 QTcpServer* tcp_server_;
 quint64 current_tcp_msecs_;

public:

 PGVM_Plugin_Broker();

 std::function<void(QString, QStringList&)> cbfn;

 QString get_project_name_from_xpdf(QString key);
 void get_files_from_project_name(QString fn, QStringList& qsl);

 void run_msg(QString msg, QByteArray qba);
 void run_fig(const QByteArray& qba);

 void activate_server();


};


