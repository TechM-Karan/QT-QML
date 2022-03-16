#ifndef BANK_H
#define BANK_H
#include<QByteArray>
#include<QString>
#include<QStringList>
#include<QRegularExpression>

#define USERNAME 0
#define BALANCE 1
#define OPERATION 2
#define DEPOSIT 3

class Bank
{
public:
    Bank();
    Bank(QByteArray data);

    QString userName;
    int totalBalanceAmount;
    QString operation;
    int depositAmount;
    QByteArray data;


    QString parseInputdata(int field);
    void getUserName();
    void getOperation();
    void getTotalBalanceAmount();
    void getDepositAmount();
    int bankProcessing();

};

#endif // BANK_H
