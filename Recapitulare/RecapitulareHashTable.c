#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>

typedef struct Motocicleta Motocicleta;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Motocicleta
{
	char* producator;
	int capacitate;
	char* model;
	int putere;
};

struct Nod
{
	Motocicleta inf;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int dimensiune;
};

void afisareMotocicleta(Motocicleta motocicleta)
{
	printf("\n Motocicleta %s %s are capacitatea de %dcc si o putere de %d cai putere", motocicleta.producator, motocicleta.model, motocicleta.capacitate, motocicleta.putere);
}

Motocicleta initMotocicleta(const char* producator, int capacitate, const char* model, int putere)
{
	Motocicleta motocicletaNoua;
	motocicletaNoua.capacitate = capacitate;
	motocicletaNoua.putere = putere;
	motocicletaNoua.producator = (char*)malloc(sizeof(char) * strlen(producator) + 1);
	strcpy(motocicletaNoua.producator, producator);
	motocicletaNoua.model = (char*)malloc(sizeof(char) * (strlen(model) + 1));
	strcpy(motocicletaNoua.model, model);

	return motocicletaNoua;
}

void push(Nod** cap, Motocicleta motocicleta)  // Acelasi lucru ca inserarea la inceput
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = motocicleta;
	nou->next = *cap;
	*cap = nou;
}

void put(Nod** cap, Motocicleta motocicleta)  // Acelasi lucru ca inserarea la final
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = motocicleta;
	nou->next = NULL;
	if (*cap)
	{
		Nod* aux = *cap;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
		*cap = nou;
}

HashTable initHashTable(int dim) 
{
	HashTable hashTable;
	hashTable.dimensiune = dim;
	hashTable.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; i++) {
		hashTable.vector[i] = NULL;
	}
	return hashTable;
}

int hash(int capacitate, int dim)
{
	return capacitate / dim / dim %dim;
}

void inserareInHT(HashTable ht, Motocicleta motocicleta)  // Inserare in tabela de dispersie (chaining)
{ 
	if (ht.dimensiune > 0) {
		int pozitie = hash(motocicleta.capacitate, ht.dimensiune);
		if (pozitie >= 0 && pozitie < ht.dimensiune) {
			put(&(ht.vector[pozitie]), motocicleta);
		}
	}
}

void traversareHT(HashTable hashT) {
	for (int i = 0; i < hashT.dimensiune; i++) {
		printf("\n Pozitie: %d", i);
		Nod* copie = hashT.vector[i];
		while (copie != NULL) {
			afisareMotocicleta(copie->inf);
			copie = copie->next;
		}
	}
}

void main()
{
	HashTable hashT = initHashTable(10);  //  Initializare HashTable
	inserareInHT(hashT, initMotocicleta("Kawasaki", 649, "Ninja 650", 67));  //transmitem prin valoare hasht deoarece nun se modifica adresa. Ea se modifica la initHT
	inserareInHT(hashT, initMotocicleta("Kawasaki", 399, "Ninja 400", 45));
	inserareInHT(hashT, initMotocicleta("Kawasaki", 636, "Ninja ZX6R", 125));
	inserareInHT(hashT, initMotocicleta("Kawasaki", 998, "Ninja ZX10R", 200));
	inserareInHT(hashT, initMotocicleta("Kawasaki", 636, "Ninja ZX6R", 125)); // coliziune pt ca capacitate%10 da 6 deci avem 2 motociclete pe pozitia 6 intr o lista

	traversareHT(hashT);
}

