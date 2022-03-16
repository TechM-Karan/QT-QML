#ifndef SERVER_H
#define SERVER_H


#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QRegularExpression>
#include <bank.h>
#include <QString>
#include <QFile>
#include <QTime>

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QObject *parent=0);
    ~Server();
signals:

public slots:
    void connection();
    void readData();
    void processClientData(QByteArray data);
    void processRequestOperation();
    QString responseServer();
    void startServer();
    void delay(int sec);

private:
    QTcpServer *tcpServer;
    QTcpSocket* tcpSocket;
    Bank bankData;
    QFile file;
};

#endif // SERVER_H
