#include <QDebug>
#include <QApplication>

#include <QDateTime>
#include <QTcpSocket>
#include <QNetworkReply>
#include <QNetworkAccessManager>

void init_qba(QByteArray& qba)
{
 qba.append("Fig1");

 qba.append("<//>");

 QByteArray pre = "<<>>run-fig@";
 quint64 ms = QDateTime::currentMSecsSinceEpoch();
 pre.append(QByteArray::number(ms));
 pre.append(':');
 qba.prepend(pre);

}

int main_via_socket(int argc, char* argv[])
{
 QCoreApplication app(argc, argv);
 QByteArray qba;

 init_qba(qba);

 QTcpSocket* tcpSocket = new QTcpSocket;
 int port = 18269; // // r z 9

 tcpSocket->connectToHost("Localhost", port);

 QObject::connect(tcpSocket, &QNetworkReply::readyRead,
  [tcpSocket, &app, &qba]()
 {
  QString result = QString::fromLatin1( tcpSocket->readAll() );
  if(result == "OK")
  {
   tcpSocket->write(qba);
  }
  else if(result == "END")
  {
   qDebug() << "OK\n";
   tcpSocket->disconnectFromHost();
   tcpSocket->deleteLater();
   app.exit();
  }
  else
  {
   qDebug() << "Unexpected response: " << result << "\n";
   tcpSocket->disconnectFromHost();
   tcpSocket->deleteLater();
   app.exit();
  }
 });

 return app.exec();
}

int main_via_qnam(int argc, char* argv[])
{
 QCoreApplication app(argc, argv);
 QByteArray qba;

 init_qba(qba);

 QNetworkAccessManager qnam;

 int port = 18261; // // r z 1
 QString addr = QString("http://localhost:%1/").arg(port);

 QNetworkRequest req;

 req.setUrl( QUrl(addr) );
 req.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

 QNetworkReply* reply = qnam.post(req, qba);

 QObject::connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
  [reply, &app](QNetworkReply::NetworkError code)
 {
  if(code != QNetworkReply::RemoteHostClosedError)
  {
   qDebug() << "Unexpected error: " << code << "\n";
  }
  else
  {
   qDebug() << "OK\n";
  }
  reply->deleteLater();
  app.exit();
 });

 return app.exec();
}


int main(int argc, char* argv[])
{
 // choose one ...
 // //
 return main_via_socket(argc, argv);
 //?return main_via_qnam(argc, argv);
}

