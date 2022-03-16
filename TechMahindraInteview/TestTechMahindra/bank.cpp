#include "bank.h"

Bank::Bank()
{
    userName.clear();
    operation.clear();
    totalBalanceAmount = 0;
    depositAmount = 0;
}

Bank::Bank(QByteArray clientData)
{
    data = clientData;
    userName.clear();
    operation.clear();
    totalBalanceAmount = 0;
    depositAmount = 0;
}

QString Bank::parseInputdata(int field)
{
    QByteArray data1(data);
    QString clientData(data1);
    QStringList parseData = clientData.split(QRegularExpression(" "));
    QString parsedData = parseData.at(field).toLocal8Bit().constData();
    parseData.clear();
    parseData = parsedData.split(QRegularExpression(">"));
    parsedData = parseData.at(1).toLocal8Bit().constData();
    parseData = parsedData.split(QRegularExpression("<"));
    parsedData = parseData.at(0).toLocal8Bit().constData();
    QString str = parsedData.trimmed();
    return (str);
}

void Bank::getUserName()
{
    userName = parseInputdata(USERNAME);
}

void Bank::getOperation()
{
    operation = parseInputdata(OPERATION);
}

void Bank::getTotalBalanceAmount()
{
    totalBalanceAmount = parseInputdata(BALANCE).toInt();
}

void Bank::getDepositAmount()
{
    depositAmount = parseInputdata(DEPOSIT).toInt();
}

int Bank::bankProcessing()
{
    if ( operation == QString("D") )
    {
        totalBalanceAmount = totalBalanceAmount + depositAmount;
    }
    return totalBalanceAmount;
}
