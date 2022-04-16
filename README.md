# Proiect 2 - POO Laborator

## Clase pentru carduri bancare

Acest proiect a avut ca tematica simularea unei baze de date pentru carduri bancare ce permite
utilizatorului sa gestioneze carduri bancare (de tip Visa sau Revolut).

Programul ne permite sa adaugam carduri personalizate in baza de date si sa realizam operatii
cu acestea, precum depunerea, retragere (unei sume de bani), stergerea sau copierea datelor de pe carduri, vizualizarea detaliata a 
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

La fiecare pas, introduceti simplu cifra corespunzatoare optiunii dorite, sa zicem ca dorim sa adaugam un card in baza de date:

![image](https://user-images.githubusercontent.com/64250100/163678909-04ff3f53-bb14-4f73-915a-b7da018b1353.png)

Daca nu selectam o optiune valida sau inputul nu are sens, programul va arunca o exceptie catre utilizator:

![image](https://user-images.githubusercontent.com/64250100/163678961-644b7be0-ea5d-475b-8ad8-03fe23eb3fb5.png)



