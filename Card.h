#ifndef CARD_H
#define CARD_H

#include<bits/stdc++.h>

class Card
{
public:
    static unsigned int transactions; //singurele chestii publice sunt functiile folosite la citire, afisare, depunere, retragere
    static void showTransactions();
    virtual void showDetails(std::ostream&);
    virtual void readDetails(std::istream&);
    virtual void showType() = 0;
    Card& operator= (Card&); //si bineinteles, constructorii;
    Card(std::string name= "");
    Card(Card&);
    virtual ~Card();
    virtual void Withdraw(double) = 0;
    virtual void Deposit(double x = 0) = 0; 
protected:
    double balance; //orice card trebuie sa aiba acces la balanta
private:
    std::string PIN;
    std::string cardNumber;
    std::string cardHolder;
    std::string expDate;
    std::string CVV;
};

class Visa : public Card
{
public:
    Visa(double tlimit = 0, double wlimit = 0, std::string name = "", double cms = 0);
    virtual ~Visa();
    Visa(Visa&);
    Visa& operator= (Visa&);
    void Withdraw(double);
    void showDetails(std::ostream&);
    void readDetails(std::istream&);
    void Deposit(double x);
    void showType();
protected:
    double depositLimit; // am nevoie sa fie protected pentru ca fiecare card are regulile lui de retragere
    double withdrawLimit; // totodata, cardul REVOLUT este un caz particular de card VISA, cu mici imbunatatiri, deci se comporta la fel
private:
    double comission;
};

class Revolut : public Visa
{
public:
    Revolut(double tlimit = 0, double wlimit = 0, std::string name = "", double cbk = 0);
    virtual ~Revolut();
    Revolut(Revolut&);
    Revolut& operator= (Revolut&);
    void showDetails(std::ostream&);
    void readDetails(std::istream&);
    void showType();
    void Deposit(double x);
    void Withdraw(double);
private:
    double cashback;
};

std::ostream& operator <<(std::ostream&, Card&);

std::istream& operator >>(std::istream&, Card&);



#endif