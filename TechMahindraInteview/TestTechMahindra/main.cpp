#include <QCoreApplication>
#include <server.h>
#include <client.h>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server myserver;

    client client1("<user>NANJESH</user> <bal>1000</bal> <oper>D</oper> <DepAmt>100</DepAmt>");

    return a.exec();
}
