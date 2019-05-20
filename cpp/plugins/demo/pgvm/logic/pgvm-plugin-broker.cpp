#include "pgvm-plugin-broker.h"

#include <QMessageBox>
#include <QTcpServer>
#include <QObject>
#include <QTcpSocket>

PGVM_Plugin_Broker::PGVM_Plugin_Broker()
 : projects_by_xpdf_{
    {"Fig1", "rz-graph-phaon-console"},
    {"Fig2", "rz-pgbir-console"},
   },
   files_by_project_{
     {"rz-graph-phaon-console",
     {
      "/home/nlevisrael/hypergr/pgvm-demo/ar/cpp/src/PhaonIR/PhaonIR/phaon-ir/phaon-ir.cpp",
      "/home/nlevisrael/hypergr/pgvm-demo/ar/cpp/src/PhaonIR/PhaonIR/phaon-ir/phaon-ir.h",
     }},
   },
  tcp_server_(nullptr), current_tcp_msecs_(0), cbfn(nullptr)
{

}

void PGVM_Plugin_Broker::activate_server()
{
 if(tcp_server_)
 {
  return;
 }
 QString waiting_message;

 if(tcp_server_)
 {
  waiting_message = QString("TCP is already started, using IP: %1\nport: %2\n\n")
    .arg(tcp_server_->serverAddress().toString()).arg(tcp_server_->serverPort());
  QMessageBox::information(nullptr, "Already Activated", waiting_message);
  return;
 }
 tcp_server_ = new QTcpServer();
 QMap<qintptr, QByteArray>* temps = new QMap<qintptr, QByteArray>();

 int port = 18269; // // r z 9

 if (!tcp_server_->listen(QHostAddress::LocalHost, port))
 {
  QMessageBox::critical(nullptr, "TCP Initialization Failed",
                         QString("Could not use port: %1.")
                         .arg(tcp_server_->errorString()));
 }
 else
 {
  waiting_message = QString("Using IP: %1\nport: %2\n\n")
     .arg(tcp_server_->serverAddress().toString()).arg(tcp_server_->serverPort());

  QMessageBox::information(nullptr, "TCP is Started",
                            QString(waiting_message));
 }

 QObject::connect(tcp_server_, &QTcpServer::newConnection, [this, temps]
 {
  QTcpSocket* clientConnection = tcp_server_->nextPendingConnection();
  QObject::connect(clientConnection, &QAbstractSocket::disconnected,
    clientConnection, &QObject::deleteLater);
  clientConnection->write("OK");
  QObject::connect(clientConnection, &QTcpSocket::readyRead, [clientConnection, this, temps]
  {
   qintptr sd = clientConnection->socketDescriptor();
   QByteArray received;
   while(clientConnection->bytesAvailable())
   {
    received.append(clientConnection->readAll());
   }
   if(received.endsWith("<//>"))
   {
    received.chop(4);
    QByteArray qba = (*temps)[sd];
    qba.append(received);
    temps->remove(sd);

    int index = qba.indexOf("<<>>");

    if(index != -1)
    {
     int i1 = qba.indexOf('@', index);
     int i2 = qba.indexOf(':', i1);
     QString msg = QString::fromLatin1(qba.mid(index + 4, i1 - index - 4));
     QByteArray ms = qba.mid(i1 + 1, i2 - i1 - 2);
     quint64 msecs = ms.toLongLong();
     if(msecs != current_tcp_msecs_)
     {
      current_tcp_msecs_ = msecs;
      run_msg( msg, qba.mid(i2 + 1) );
     }
    }
    clientConnection->write("END");
   }
   else
   {
    (*temps)[sd] += received;
   }
  });
 });
}

void PGVM_Plugin_Broker::run_msg(QString msg, QByteArray qba)
{
 qDebug() << QString("received: %1").arg(msg);

 if(msg == "run-fig")
 {
  run_fig(qba);
 }
}

void PGVM_Plugin_Broker::run_fig(const QByteArray& qba)
{
 QString fig = QString::fromLatin1(qba);
 //qDebug() <<
 QString pn = get_project_name_from_xpdf(fig);

 QStringList qsl;
 get_files_from_project_name(pn, qsl);

 qDebug() << qsl;

 QMessageBox::information(nullptr, "Activating Project",
   QString("The project %1 will be activated and source files "
     "opened to examine the functionality depicted in %2.").arg(pn).arg(fig));

 if(cbfn)
   cbfn(pn, qsl);
}

void PGVM_Plugin_Broker::get_files_from_project_name(QString pn, QStringList& qsl)
{
 qsl = files_by_project_.value(pn);
}



QString PGVM_Plugin_Broker::get_project_name_from_xpdf(QString key)
{
 return projects_by_xpdf_.value(key);
}


