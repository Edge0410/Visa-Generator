#include <bits/stdc++.h>
#include "Card.h"
using namespace std;

unsigned int Card::transactions = 0;

ostream& operator <<(ostream &stream, Card& card)
{
    card.showDetails(stream);
    return stream;
}

int main()
{
    Visa card1("Eduard", 20, 200, 10);
    card1.Deposit(500);
    card1.Withdraw(50);
    cout<<card1;

    Revolut card2("Dobrin", 20, 2500, 5);
    card2.Deposit(1500);
    card2.Withdraw(1000);
    cout<<card2;
}