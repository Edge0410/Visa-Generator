#include <bits/stdc++.h>
#include "Card.h"
#include <random>
using namespace std;

// clasa de baza

Card::Card(string name) //constructor cu valoare implicita
{
    balance = 0;
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count(); //generez un numar de card 
    default_random_engine gen(seed1); // gen(time(NULL));
    uniform_int_distribution<long long> dist(1000000000000000, 9999999999999999);

    // distr(generator) are randomul
    cardNumber = to_string(dist(gen));

    unsigned seedpin = std::chrono::system_clock::now().time_since_epoch().count(); //generez un pin 
    default_random_engine genpin(seedpin); // gen(time(NULL));
    uniform_int_distribution<int> distpin(1000, 9999);

    PIN = to_string(distpin(genpin));

    cardHolder = name; //atribui numele si o data de expirare

    expDate = "05/2026";

    unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen2(seed2); // gen(time(NULL));
    uniform_int_distribution<int> distt(100, 999);
    CVV = to_string(distt(gen2));

    cout << "Card creat cu succes!" << '\n';
}

Card::Card(Card &ob) //constructor de copiere
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

Card& Card::operator= (Card& card) //operator de atribuire pentru continutul de baza al clasei, va fi apelat in operatorul pentru clasele derivate
{
    this->cardHolder = card.cardHolder; //atribuie numele si pinul cardului dat ca parametru, asta facem cand copiem datele de pe un card pe altul
    this->PIN = card.PIN;
    return *this;
}

Card::~Card()
{
    // nu am date alocate dinamic, se ocupa smart pointer de restul
}

void Card::showTransactions() //functie care afiseaza numarul de tranzactii de pe o sesiune
{
    cout << "Ati efectuat pana acum " << transactions << " tranzactii" << '\n';
    cout << "Puteti efectua maxim 10 tranzactii per sesiune!" << '\n';
}

void Card::showDetails(ostream &stream) //functie de afisare apelata de operatorul << , este virtuala si apelata de clasele derivate prin functiile lor
{
    stream << "Numele Posesorului de card: " << this->cardHolder << '\n';
    stream << "Numar card: " << this->cardNumber << '\n';
    stream << fixed << setprecision(2) << "Balanta: " << this->balance << '\n';
    stream << "Data de expirare: " << this->expDate << '\n';
    stream << "Codul PIN: " << this->PIN << '\n';
}

void Card::readDetails(istream &stream) //functie de citire apelata de operatorul >> , functioneaza pe acelasi principiu
{
    cout<<"Introduceti numele posesorului de card (maxim 50 de caractere): \n";
    getline(stream, this->cardHolder);
    if(this->cardHolder.length() > 50 || this->cardHolder == "")
    {
        throw invalid_argument("");
    }
}

// clasa de card visa

Visa::Visa(double tlimit, double wlimit, string name, double cms) //constructor cu valori implicite si lista de initializare
    : Card(name)
{
    depositLimit = tlimit;
    withdrawLimit = wlimit;
    comission = cms;
}

Visa::~Visa()
{
    // nu am date alocate dinamic, se ocupa smart pointer de ele  
}

Visa::Visa(Visa& ob) //constructor de copiere
    :Card(ob)
{
    depositLimit = ob.depositLimit;
    withdrawLimit = ob.withdrawLimit;
    comission = ob.comission;
}

Visa& Visa::operator= (Visa& card) //operator de atribuire pentru clasa derivata
{
    Card::operator=(card); //apeleaza si operatorul pentru partea din baza
    depositLimit = card.depositLimit;
    withdrawLimit = card.withdrawLimit;
    comission = card.comission;
    return *this;
}

void Visa::showDetails(ostream &stream) //functie de afisare
{
    this->showType();
    Card::showDetails(stream); //apeleaza functia de afisare pentru partea de baza
    stream << "Limita inferioara la deposit: " << this->depositLimit << '\n';
    stream << "Limita de retragere: " << this->withdrawLimit << '\n';
    stream << "Comision la retragere: " << this->comission <<'\n';
}

void Visa::Deposit(double x) //functie pentru depunere
{
    if(x < depositLimit)
        throw invalid_argument("Suma depozitata este prea mica");
    this->balance += x;
    transactions++;
}

void Visa::showType()
{
    cout<<"Tipul cardului: VISA"<<'\n';
}

void Visa::readDetails(istream &stream) //functie de citire apelata de operatorul >>
{
    string disposal;
    Card::readDetails(stream); //apeleaza aceeasi functie pt partea de baza
    cout << "Introduceti limita inferioara la depozit (numar): \n";
    getline(stream, disposal);
    this->depositLimit = stod(disposal);
    cout << "Introduceti limita de retragere (numar): \n";
    getline(stream, disposal);
    this->withdrawLimit = stod(disposal);
    cout << "Introduceti comisionul per retragere: (numar) \n";
    getline(stream, disposal);
    this->comission = stod(disposal);
    if(comission < 0)
        throw invalid_argument("");
}

void Visa::Withdraw(double x) //functie pentru retragere
{
    if(transactions > 10) //daca depasim limita de tranzactii
        throw runtime_error("Nu s-a putut efectua retragerea - Limita zilnica de tranzactii a fost atinsa.");

    if (x + x * (comission / 100) > withdrawLimit) //daca depasim limita de retragere
        throw runtime_error("Nu s-a putut efectua retragerea - Limita maxima de retragere depasita.");

    if (balance - (x + x * (comission / 100)) < 0) //daca avem bani pe card
        throw runtime_error("Nu s-a putut efectua retragerea - Fonduri insuficiente.");

    balance -= x + x * (comission / 100);
    transactions++;
}

// clasa de card revolut

Revolut::Revolut(double tlimit, double wlimit, string name, double cbk) //constructor cu valori implicite
    : Visa(tlimit, wlimit, name)
{
    cashback = cbk;
}

Revolut::~Revolut()
{
    // nu am date alocate dinamic, se ocupa smart pointer de ele
}

Revolut::Revolut(Revolut& ob)
    :Visa(ob)
{
    cashback = ob.cashback;
}

Revolut& Revolut::operator= (Revolut& card) //operator de atribuire
{
    Visa::operator=(card); //apeleaza operatorul pentru bucata din clasa derivata parinte care la randul ei apeleaza operatorul pentru clasa de baza
    cashback = card.cashback;
    return *this;
}

void Revolut::Deposit(double x)
{
    if(x < depositLimit) 
        throw invalid_argument("Suma depozitata este prea mica");
    this->balance += x;
    transactions++;
}

void Revolut::Withdraw(double x) //functie pentru retragere, nu mai avem comision dar avem cashback
{
    if(transactions > 10)
        throw invalid_argument("Nu s-a putut efectua retragerea - Limita zilnica de tranzactii a fost atinsa.");
    if (x > withdrawLimit)
        throw invalid_argument("Nu s-a putut efectua retragerea - Limita maxima de retragere depasita.");
    if (balance - x < 0)
        throw invalid_argument("Nu s-a putut efectua retragerea - Fonduri insuficiente.");
    if (transactions == 0) //aplicam cashback la prima tranzactie a zilei
    {
        balance -= x;
        balance += x * (cashback / 100);
    }
    else
        balance -= x;
    transactions++;
}

void Revolut::showDetails(ostream &stream) //functie de afisare apelata de operatorul <<, urca in ierarhie si apeleaza pe rand cele doua functii de afisare
{
    Visa::showDetails(stream);
    stream << "Cashback: " << this->cashback <<'\n';
}

void Revolut::showType()
{
    cout<<"Tipul cardului: REVOLUT"<<'\n';
}

void Revolut::readDetails(istream &stream) //functie de citire, apelam functia de citire din baza nu din derivata parinte ca sa nu mai citim si comisionul
{
    string disposal;
    Card::readDetails(stream);
    cout << "Introduceti limita inferioara la depozit (numar): \n";
    getline(stream, disposal);
    this->depositLimit = stod(disposal);
    cout << "Introduceti limita de retragere (numar): \n";
    getline(stream, disposal);
    this->withdrawLimit = stod(disposal);
    cout << "Introduceti valoarea de cashback (numar): \n";
    getline(stream, disposal);
    this->cashback = stod(disposal);
}

//operatori supraincarcati

ostream& operator <<(ostream &stream, Card& card)
{
    card.showDetails(stream);
    return stream;
}

istream& operator >>(istream &stream, Card& card)
{
    card.readDetails(stream);
    return stream;
}