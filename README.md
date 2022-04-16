# Proiect 2 - POO Laborator

## Clase pentru carduri bancare

Acest proiect a avut ca tematica simularea unei baze de date pentru carduri bancare ce permite
utilizatorului sa gestioneze carduri bancare (de tip Visa sau Revolut).

Programul ne permite sa adaugam carduri personalizate in baza de date si sa realizam operatii
cu acestea, precum depunerea, retragerea (unei sume de bani), stergerea sau copierea datelor de pe carduri, vizualizarea detaliata a 
cardurilor, etc.

### Pentru a rula programul, rulati urmatoarele comenzi in terminal:

```
g++ Card.cpp main.cpp -o main
.\main
```

### Meniu interactiv

Programul dispune de un meniu interactiv la rularea programului:

![image](https://user-images.githubusercontent.com/64250100/163678927-b8a7e0ee-0e5b-4645-844d-c10708e6b542.png)

### How it works

** Intro **

La fiecare pas, introduceti simplu cifra corespunzatoare optiunii dorite, sa zicem ca dorim sa adaugam un card in baza de date:

![image](https://user-images.githubusercontent.com/64250100/163678909-04ff3f53-bb14-4f73-915a-b7da018b1353.png)

Daca nu selectam o optiune valida sau inputul nu are sens, programul va arunca o exceptie catre utilizator:

![image](https://user-images.githubusercontent.com/64250100/163678961-644b7be0-ea5d-475b-8ad8-03fe23eb3fb5.png)

** Features **

### 1. Adauga un card

Aceasta reprezinta prima optiune din meniu, cuprinzand crearea obiectelor (apelarea constructorilor si folosirea smart pointers) si stocarea acestora.
La adaugarea unui card, se cer mai multe informatii de la utilizator, ce se introduc de la tastatura, fiind completate de date random generate in constructori (numarul de card, CVV, etc) - un exemplu este urmatorul:

![image](https://user-images.githubusercontent.com/64250100/163690044-0b4b3cd7-189e-4fb8-b7b3-5151fe27a756.png)

### 2. Vizualizarea cardurilor existente

Acum ca am adaugat mai multe carduri in baza de date, vom dori sa le listam pentru a vedea toate datele corespunzatoare. Acest lucru se realizeaza cu a doua optiune din meniu, ce va afisa pe ecran toate cardurile in ordinea adaugarii lor.

![image](https://user-images.githubusercontent.com/64250100/163690175-f76b261e-156e-4629-8f96-414229254527.png)

### 3. Efectuarea unei tranzactii 

In momentul in care vom dori sa efectuam tranzactii pe cardurile adaugate, functiile virtuale au rolul de a particulariza operatiunile in functie de tipul cardului. Spre exemplu, daca retragem bani de pe un card VISA vom avea un comision de retragere la fiecare operatiune, pe cand la un card REVOLUT comisionul este implicit 0 iar la prima tranzactie din sesiune (din ziua curenta) vom primi un cashback.

Pentru a efectua operatiuni trebuie sa selectam optiunea 3 din meniu apoi indicele de ordine al cardului pe care dorim sa efectuam o operatiune, un exemplu este urmatorul:

![image](https://user-images.githubusercontent.com/64250100/163690339-a9aee461-2299-4a15-8b62-36cdb6306050.png)

Din acest moment putem selecta una dintre urmatoarele operatiuni/tranzactii:

![image](https://user-images.githubusercontent.com/64250100/163690383-d6b161b0-31f7-4f43-983a-6c915c605297.png)

### 4. Buton de iesire

La selectarea optiunii 4 din meniu, programul isi incheie executia.

## Cateva constrangeri cu privire la datele introduse de utilizator:

- Numele unei persoane nu trebuie sa depaseasca 50 de caractere
- Comisionul trebuie sa fie o valoare pozitiva
- Comisionul implicit pentru cardurile REVOLUT este 0.




