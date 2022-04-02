#ifndef CARD_H
#define CARD_H

#include<bits/stdc++.h>

class Card
{
public:
    static unsigned int transactions;
    virtual void showDetails(std::ostream&);
    Card(std::string);
    Card(Card&);
    ~Card();
    virtual void Withdraw(double) = 0;
    void Deposit(double x = 0); 
protected:
    double balance;
private:
    std::string cardNumber;
    std::string cardHolder;
    std::string expDate;
    std::string CVV;
};

class Visa : public Card
{
public:
    Visa(std::string, double, double, double cms = 0);
    ~Visa();
    void Withdraw(double);
    void showDetails(std::ostream&);
protected:
    double transactionLimit;
    double withdrawLimit;
private:
    double comission;
};

class Revolut : public Visa
{
public:
    Revolut(std::string, double, double, double);
    ~Revolut();
    void showDetails(std::ostream&);
    void Withdraw(double);
private:
    double cashback;
};


#endif