#include <QDebug>
#include <QApplication>

#include "../pgvm-plugin-broker.h"

int main(int argc, char *argv[])
{
 QApplication qapp(argc, argv);
 PGVM_Plugin_Broker ppb;

 ppb.activate_server();

 //qDebug() << ppb.get_project_name_from_xpdf("Fig1");

 return qapp.exec();
}

