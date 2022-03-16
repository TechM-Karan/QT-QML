#include "server.h"
#include <qmutex.h>

Server::Server(QObject *parent):QObject(parent)
{
    file.setFileName("SERVER.TXT");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    qDebug() << "Error in Opening the client file";
    startServer();
}

void Server::startServer()
{
    tcpServer = new QTcpServer(this);
    if ( tcpServer == NULL) return;

    QTextStream writeToFile(&file);

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(connection()));

    if (!tcpServer->listen(QHostAddress::LocalHost,12345))
    {
        writeToFile << "Server not Started Banking"<<"\n";
    }
    else
    {
        writeToFile << "Server started"<<"\n";
    }
}

void Server::connection()
{
    if (tcpServer )
    {
        tcpSocket = tcpServer->nextPendingConnection();
        connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
        QTextStream tstream(tcpSocket);
        if ( tcpSocket != NULL )
            tcpSocket->write("Welcome to Banking Software");
    }
}
void Server::readData()
{
    if ( tcpSocket )
    {
    QByteArray msg = tcpSocket->readAll();
    if (msg.isEmpty())
        return;
    QTextStream writeToFile(&file);
    writeToFile << "Client Data" << "\n";
    writeToFile << QString(msg) <<"\n";

    delay(3);

    processClientData(msg);
    processRequestOperation();

    QString response = responseServer();
    QByteArray sevData(response.toUtf8());
    writeToFile << QString(sevData) <<"\n";
    tcpSocket->write(sevData);
    tcpSocket->disconnect();
    }
}

Server::~Server()
{
    disconnect();
    file.close();
    if (tcpServer )
        delete tcpServer;
}

void Server::processClientData(QByteArray clientData)
{
    bankData.data = clientData;
    bankData.getUserName();
    bankData.getOperation();
    bankData.getTotalBalanceAmount();
    bankData.getDepositAmount();
}

void Server::processRequestOperation()
{
    bankData.bankProcessing();
}


QString Server::responseServer()
{
    QString serverData = QString::number(bankData.totalBalanceAmount);
    QString serverResponse = QString("Response <TotalBalanceAmount>%1</TotalBalanceAmount>").arg(serverData);
    return serverResponse;
}


void Server::delay(int sec)
{
    QTime dieTime = QTime::currentTime().addSecs(sec);
    while( QTime::currentTime() < dieTime ) { }
}
