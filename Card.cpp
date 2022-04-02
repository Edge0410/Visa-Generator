#include <bits/stdc++.h>
#include "Card.h"
#include <random>
using namespace std;

// clasa de baza

Card::Card(string name)
{
    balance = 0;
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed1); // gen(time(NULL));
    uniform_int_distribution<long long> dist(1000000000000000, 9999999999999999);

    // distr(generator) are randomul
    cardNumber = to_string(dist(gen));
    cardHolder = name;
    expDate = "05/2026";

    unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen2(seed2); // gen(time(NULL));
    uniform_int_distribution<int> distt(100, 999);
    CVV = to_string(distt(gen2));

    cout << "Card creat cu succes!" << '\n';
}

Card::Card(Card &ob)
{
    balance = 0;

    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed1); // gen(time(NULL));
    uniform_int_distribution<long long> dist(1000000000000000, 9999999999999999);

    // distr(generator) are randomul
    cardNumber = to_string(dist(gen));
    cardHolder = ob.cardHolder;
    expDate = "05/2026";

    unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen2(seed2); // gen(time(NULL));
    uniform_int_distribution<int> distt(100, 999);
    CVV = to_string(distt(gen2));

    cout << "Card copiat cu succes!" << '\n';
}

Card::~Card()
{
}

void Card::Deposit(double x)
{
    this->balance += x;
}

void Card::showDetails(ostream &stream)
{
    stream << "Numele Posesorului de card: " << this->cardHolder << '\n';
    stream << "Numar card: " << this->cardNumber << '\n';
    stream << "Balanta: " << this->balance << '\n';
}

// clasa de card visa

Visa::Visa(string nume, double tlimit, double wlimit, double cms)
    : Card(nume)
{
    transactionLimit = tlimit;
    withdrawLimit = wlimit;
    comission = cms;
}

Visa::~Visa()
{
}

void Visa::showDetails(ostream &stream)
{
    Card::showDetails(stream);
    stream << "Comision la retragere: " << this->comission <<'\n';
}

void Visa::Withdraw(double x)
{
    try
    {
        if (x + x * (comission / 100) > withdrawLimit)
        {
            throw runtime_error(string("Nu s-a putut efectua retragerea - Limita maxima atinsa"));
        }
        else if (balance - (x + x * (comission / 100)) < 0)
        {
            throw runtime_error(string("Nu s-a putut efectua retragerea - Fonduri insuficiente"));
        }
        else
        {
            balance -= x + x * (comission / 100);
            transactions++;
        }
    }
    catch (runtime_error e)
    {
        cout << e.what() << '\n';
    }
}

// clasa de card revolut

Revolut::Revolut(string nume, double tlimit, double wlimit, double cbk)
    : Visa(nume, tlimit, wlimit)
{
    cashback = cbk;
}

Revolut::~Revolut()
{
    
}

void Revolut::Withdraw(double x)
{
    try
    {
        if (x > withdrawLimit)
        {
            throw runtime_error(string("Nu s-a putut efectua retragerea - Limita maxima atinsa"));
        }
        else if (balance - x < 0)
        {
            throw runtime_error(string("Nu s-a putut efectua retragerea - Fonduri insuficiente"));
        }
        else
        {
            if (transactions == 0)
            {
                balance -= x;
                balance += x * (cashback / 100);
            }
            else
                balance -= x;
            transactions++;
        }
    }
    catch (runtime_error e)
    {
        cout << e.what() << '\n';
    }
}

void Revolut::showDetails(ostream &stream)
{
    Card::showDetails(stream);
    stream << "Cashback: " << this->cashback <<'\n';
}

//operatori supraincarcati
