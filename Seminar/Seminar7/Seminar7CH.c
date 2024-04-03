#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Masina {
	char* producator;
	int serie;
};

struct Nod {
	Masina inf; //informatie utila
	Nod* next; //pointer de legatura, adresa urmatorului nod
};

struct HashTable {
	Nod** vector;
	int dimensiune;
};

void afisareMasina(Masina masina) {
	printf("\n Masina %s are seria %d.", masina.producator, masina.serie);
}

Masina initMasina(const char* producator, int serie) {
	Masina masinaNoua;
	masinaNoua.serie = serie;
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

void inserareLaFinal(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod)); //Aici are sens sa facem shallow copy
	nou->inf = masina;
	nou->next = NULL;
	if ((*cap) != NULL) {
		Nod* aux = *cap; //Nu il putem folosi tot pe cap pentru deplasare -> trebuie auxiliar
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

HashTable initHashTable(int dim) {  //initializare hashTable cu NULL
	HashTable hashTable;
	hashTable.dimensiune = dim;
	hashTable.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; i++) {
		hashTable.vector[i] = NULL;
	}
	return hashTable;
}

int hash(int serie, int dim) {   //functia hash ne da pozitia unde inseram/cautam
	return serie % dim;
}

void inserareInHT(HashTable ht, Masina masina) {  // inserare in tabela de dispersie (chaining)
	if (ht.dimensiune > 0) {
		int pozitie = hash(masina.serie, ht.dimensiune);
		if (pozitie >= 0 && pozitie < ht.dimensiune) {
			inserareLaFinal(&(ht.vector[pozitie]), masina);
		}
	}
}

void traversareHT(HashTable hashT) {
	for (int i = 0; i < hashT.dimensiune; i++) {
		printf("\n Pozitie: %d", i);
		Nod* copie = hashT.vector[i];
		while (copie != NULL) {
			afisareMasina(copie->inf);
			copie = copie->next;
		}
	}
}

void main() {
	HashTable hashT = initHashTable(10);  //initializare hashTable
	inserareInHT(hashT, initMasina("Renault", 1234));   //transmitem prin valoare hasht deoarece nun se modifica adresa. Ea se modifica la initHT
	inserareInHT(hashT, initMasina("Ford", 5678));
	inserareInHT(hashT, initMasina("Ford", 5679));
	inserareInHT(hashT, initMasina("Ford", 5677));  // coliziune pt ca seria%10 da 7 deci avem 3 masini pe pozitia 7 intr o lista
	inserareInHT(hashT, initMasina("Ford", 5677));
	inserareInHT(hashT, initMasina("Peugeot", 9101));
	inserareInHT(hashT, initMasina("Ford", 5677));
	inserareInHT(hashT, initMasina("Bmw", 1213));

	traversareHT(hashT);
}
