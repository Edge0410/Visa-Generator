#include <bits/stdc++.h>
#include "Card.h"
#include <chrono>
#include <thread>
using namespace std;

unsigned int Card::transactions = 0;

// cateva functii pentru meniul interactiv

void showStandardMessage()
{
    cout << "==============================================================" << '\n' << '\n';
    cout << "Alegeti operatia dorita: " << '\n' << '\n';
    cout << "1. Creati un card nou" << '\n';
    cout << "2. Afisati date despre cardurile existente" << '\n';
    cout << "3. Efectuati o tranzactie pe unul dintre cardurile existente" << '\n';
    cout << "4. Iesire" << '\n' << '\n';

    cout << "Introduceti cifra corespunzatoare optiunii dorite si apasati ENTER:" << '\n';
}

void operationSelect()
{
    cout << "==============================================================" << '\n' << '\n';
    cout << "Alegeti operatia dorita:" << '\n' << '\n';
    cout << "1. Depunere" << '\n';
    cout << "2. Retragere" << '\n';
    cout << "3. Stergere Card" << '\n';
    cout << "4. Copiere date de pe un card pe altul" << '\n';
    cout << "5. Inapoi" << '\n' << '\n';

    cout << "Introduceti cifra corespunzatoare optiunii dorite si apasati ENTER:" << '\n';
}

void showAddCardMessage()
{
    cout << "==============================================================" << '\n' << '\n';
    cout << "Selectati tipul de card dorit:" << '\n';
    cout << "1. Visa" << '\n';
    cout << "2. Revolut" << '\n';
    cout << "3. Inapoi" << '\n';
}

int main()
{
    vector<shared_ptr<Card>> Cards; // vector ce contine cardurile adaugate

    int toDo;
    string option, cardtype, disposal, cardoption, operationoption, parentcard, childcard; // variabile folosite in try catch pentru citirea datelor
    int cardIndex = 0;

    while (1)
    {
    topLabel:
        showStandardMessage();
        try 
        {
            getline(cin, option);  //selectam optiunea dorita
            if (option.length() != 1 || (option[0] < '1' || option[0] > '4')) //verificam daca avem user input corect
            {
                throw invalid_argument("Optiune invalida, incercati din nou.");
            }
            if (option[0] == '1') //daca am intrat pe cazul de adaugare card
            {
            cardLabel:
                try
                {
                    showAddCardMessage();
                    getline(cin, cardtype); //analog verificam user input
                    if (cardtype.length() != 1 || (cardtype[0] < '1' || cardtype[0] > '3'))
                    {
                        throw invalid_argument("Optiune invalida, incercati din nou.");
                    }
                    if (cardtype[0] == '3') //daca am selectat sa ne ducem inapoi facem jump inainte de try block-ul initial
                    {
                        goto topLabel; 
                    }
                    if (cardtype[0] == '1') //daca am selectat adaugarea unui card Visa
                    {
                        shared_ptr<Card> visacard(new Visa());
                        Cards.push_back(move(visacard)); //folosim smart pointer de tipul corespunzator si mutam in vectorul de carduri - upcasting implicit
                    VisaCreate:
                        try //incercam sa citim datele corespunzatoare, erorile din user input si aruncate din supraincarcarea operatorului de citire
                        {
                            cin >> *Cards[cardIndex];
                            cardIndex++;
                            cout << "Cardul a fost adaugat in baza de date locala." << '\n';
                        }
                        catch (invalid_argument &e) //erorile pomenite mai sus sunt prinse aici
                        {
                            cout << "Eroare: Datele introduse nu respecta sintaxa propusa, incercati din nou" << '\n';
                            goto VisaCreate; //ne intoarcem la primul pas 
                        }
                    }
                    if (cardtype[0] == '2')
                    {
                        shared_ptr<Card> revolutcard(new Revolut()); //analog ca mai sus doar ca citim un card de tip REVOLUT
                        Cards.push_back(move(revolutcard));
                    RevolutCreate:
                        try
                        {
                            cin >> *Cards[cardIndex];
                            cardIndex++;
                            cout << "Cardul a fost adaugat in baza de date locala." << '\n';
                        }
                        catch (invalid_argument &e)
                        {
                            cout << "Eroare: Datele introduse nu respecta sintaxa propusa, incercati din nou" << '\n';
                            goto RevolutCreate;
                        }
                    }
                }
                catch (invalid_argument &e)
                {
                    cout << e.what() << '\n'; //erorile de tip sintaxa gresita la selectarea optiunilor pentru adaugare card sunt prinse aici
                    goto cardLabel;
                }
            }
            else if (option[0] == '2') //daca dorim sa afisam date despre cardurile existente
            {
                try
                {
                    if (cardIndex == 0) //in cazul in care nu avem carduri aruncam exceptie
                        throw length_error("Lista cardurilor este goala. Cardurile adaugate vor aparea aici");
                    cout << '\n';
                    cout << "Carduri Visa:" << '\n' << '\n';
                    int indexCurent = 1;
                    for (int i = 0; i < cardIndex; i++){ //afisam cardurile Visa
                        auto cardVisa = dynamic_pointer_cast<Visa>(Cards[i]);
                        if(typeid(*cardVisa) == typeid(Visa))
                        {
                            cout<<indexCurent<<": "<<*cardVisa << '\n';
                            indexCurent++;
                        }
                    }
                    if(indexCurent == 1)
                    {
                        cout << "Lista este goala. " << '\n';
                    }
                    cout << '\n' << '\n' << "Carduri Revolut:" << '\n' << '\n';
                    indexCurent = 1;
                    for (int i = 0; i < cardIndex; i++){ //afisam cardurile Revolut
                        auto cardRevolut = dynamic_pointer_cast<Revolut>(Cards[i]);
                        if(cardRevolut != nullptr)
                        {
                            cout<<indexCurent<<": "<<*cardRevolut << '\n';
                            indexCurent++;
                        }
                    }
                    if(indexCurent == 1)
                    {
                        cout << "Lista este goala. " << '\n' << '\n';
                    }
                    cout << '\n' << "Apasati ENTER pentru a inchide vizualizarea" << '\n';
                    getline(cin, disposal);
                }
                catch (length_error &e) //prindem eroarea de lipsa carduri
                {
                    cout << e.what() << '\n';
                }
            }
            else if (option[0] == '3') //dorim sa efectuam o tranzactie pe cardurile existente
            {                          
            transactionLabel:
                try
                {
                    if (cardIndex == 0) //in cazul in care nu avem carduri aruncam o exceptie
                        throw length_error("Lista cardurilor este goala. Cardurile adaugate vor aparea aici");
                    cout << '\n';
                    for (int i = 0; i < cardIndex; i++) //afisam iar cardurile
                        cout << i + 1 << ": " << *Cards[i] << '\n'
                             << '\n'; 
                    Card::showTransactions();
                    cout << "Selectati un card pentru a efectua o tranzactie:" << '\n';
                    getline(cin, cardoption); //verificam user input apoi selectam tranzactia
                    if (cardoption[0] >= '1' && cardoption[0] - '1' < cardIndex && cardoption.length() == 1)
                    {
                        int selected = cardoption[0] - '1';
                    selectedLabel:
                        operationSelect();
                        try
                        {
                            getline(cin, operationoption);
                            if (operationoption.length() != 1 || (operationoption[0] < '1' || operationoption[0] > '5'))
                                throw invalid_argument("Optiune invalida, incercati din nou.");
                            int typeofop = operationoption[0] - '0';
                            if (typeofop == 1) //daca am selectat sa depunem bani pe un card
                            {
                                cout << "Introduceti suma dorita:" << '\n';
                                double sum = 0;
                                try
                                {
                                    getline(cin, disposal); //citim user input ca string si apoi folosim functia stod pentru a converti suma la double
                                    sum = stod(disposal); //functia arunca invalid argument daca nu poate face conversia si va fi prins de catch-ul de mai jos
                                    Cards[selected]->Deposit(sum);
                                    cout << "Operatiune efectuata cu succes." << '\n';
                                }
                                catch (exception &e)
                                {
                                    cout << "Suma introdusa este incorecta sau este mai mica decat limita minima admisa. \nIncercati din nou." << '\n';
                                    goto selectedLabel;
                                }
                            }
                            if (typeofop == 2)
                            {
                                cout << "Introduceti suma dorita" << '\n';
                                double sum = 0;
                                try
                                {
                                    getline(cin, disposal); //analog pentru retragere
                                    sum = stod(disposal);
                                    Cards[selected]->Withdraw(sum); //functia de retragere este virtuala in clasa de baza deci va fi apelata functia corespunzatoare cardului selectat
                                    cout << "Operatiune efectuata cu succes." << '\n';
                                }
                                catch (exception &e)
                                {
                                    cout << e.what() << '\n';
                                    goto selectedLabel;
                                }
                            }
                            if (typeofop == 3) //daca dorim sa stergem un card
                            {
                                Cards.erase(Cards.begin() + selected);
                                cardIndex--;
                                Card::countTransaction();
                                cout << "Operatiune efectuata cu succes." << '\n';
                                // sterge pointerul si distruge zona de memorie
                                // acelasi efect ca pop dar specific pentru un card anume
                            }
                            if (typeofop == 4) //daca dorim sa copiem datele de pe un card pe altul 
                            {
                                try
                                {
                                    if (cardIndex < 2) //trebuie sa avem macar 2 carduri pentru a realiza acest lucru
                                        throw length_error("Nu sunt suficiente carduri in baza de date pentru a efectua operatiunea.");
                                    cout << "Alegeti cardul de unde doriti sa copiati datele" << '\n';
                                    getline(cin, parentcard);
                                    if (parentcard[0] < '1' || parentcard[0] - '1' >= cardIndex)
                                        throw invalid_argument("Optiune invalida, incercati din nou.");
                                    *Cards[selected] = *Cards[parentcard[0] - '1'];  //folosim operatorul de atribuire supraincarcat
                                    cout << "Operatiune efectuata cu succes." << '\n';
                                }
                                catch (exception &e)
                                {
                                    cout << e.what() << '\n';
                                }
                            }
                            if (typeofop == 5)
                                goto topLabel;
                        }
                        catch (exception &e)
                        {
                            cout << e.what() << '\n';
                            goto selectedLabel;
                        }
                    }
                    else
                        throw invalid_argument("Cardul nu exista. Incercati din nou.");
                }
                catch (exception &e)
                {
                    cout << e.what() << '\n';
                    this_thread::sleep_for(chrono::milliseconds(1000)); //folosim sleep ca sa facem experienta mai placuta :)
                    if (cardIndex != 0)
                        goto transactionLabel;
                }
            }
            else if (option[0] == '4') //cazul in care vrem sa oprim executarea programului
            {
                break;
            }
        }
        catch (invalid_argument &e)
        {
            cout << e.what() << '\n';
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    return 0;
}