#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTime>
#include <QFile>
#include <QRegularExpression>

class client: public QObject
{
    Q_OBJECT
public:
    client(QByteArray);
   ~client();
    void printWelcomeMessage(QString msg);
    void processServerResponse(QString msg);
    QString getUserNameFromInput();
    void showServerResponse();
    void delay(int);

    void connection();
    QTcpSocket socket;
    QByteArray inputData;
    QString responsefromServer;
    QFile file;
signals:

public slots:
    void sendDataToServer();
};

#endif // CLIENT_H
