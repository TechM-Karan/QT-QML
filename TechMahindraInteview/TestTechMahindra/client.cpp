#include "client.h"
#include <qmutex.h>

client::client(QByteArray data)
{
    inputData = data;
    QString fileName = getUserNameFromInput();
    if (fileName.isEmpty())
        fileName = "DummyUser";
    file.setFileName(fileName.append(".TXT"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    qDebug() << "Error in Opening the client file";

    QTextStream writeToFile(&file);
    QString msg(data);
    writeToFile << msg<< "\n";
    connection();
}

client::~client()
{
    disconnect();
    socket.close();
}

void client::sendDataToServer()
{
    QString msg = socket.readAll();

    if ( msg.isEmpty())
        return;

    if (msg.contains("Welcome"))
        printWelcomeMessage(msg);


    delay(3);

    socket.write(QByteArray(inputData));
    if ( msg.contains("Response"))
    {
        processServerResponse(msg);
    }
}

void client::connection()
{
    QTextStream writeToFile(&file);


    socket.connectToHost(QHostAddress::LocalHost,12345);
    if(socket.waitForConnected(-1))
    {
       writeToFile << "Client connected to server" << "\n";
    }
    else
    {
       writeToFile << "Client not connected to server" << "\n";
       return;
    }
   connect(&socket, SIGNAL(readyRead()), this, SLOT(sendDataToServer()));
}

void client::printWelcomeMessage(QString msg)
{
    QTextStream writeToFile(&file);
    writeToFile << msg<< "\n";
}

QString client::getUserNameFromInput()
{
    if ( inputData.isNull())
        return QString("");

    QString data(inputData);
    QStringList parseData = data.split(QRegularExpression(" "));
    QString parsedData = parseData.at(0).toLocal8Bit().constData();
    parseData.clear();
    parseData = data.split(QRegularExpression(">"));
    parsedData = parseData.at(1).toLocal8Bit().constData();
    parseData = parsedData.split(QRegularExpression("<"));
    parsedData = parseData.at(0).toLocal8Bit().constData();
    QString userName = parsedData.trimmed();
    return (userName);
}

void client::delay(int sec)
{
    QTime dieTime = QTime::currentTime().addSecs(sec);
    while( QTime::currentTime() < dieTime ) { }
}

void client::processServerResponse(QString msg)
{
    socket.close();
    QStringList parseData = msg.split(QRegularExpression(" "));
    QString parsedData = parseData.at(1).toLocal8Bit().constData();
    responsefromServer = parsedData;

    QTextStream writeToFile(&file);
    writeToFile << msg<< "\n";
    file.close();
}

void client::showServerResponse()
{
    qDebug()<< "SERVER RESPONSE "<<responsefromServer<<"\n";
}
