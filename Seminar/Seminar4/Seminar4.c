#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

//Test - saptamana 8
//Assignment OBLIGATORIU peste 2 saptamani
//Liste

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	char* producator;
	int serie;
};

struct Nod {
	Masina inf; //informatie utila
	Nod* next; //pointer de legatura, adresa urmatorului nod
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

//La actualizari, modificari, etc -> transmitere prin pointer
void inserareLaInceput(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod)); //Aici are sens sa facem shallow copy
	nou->inf = masina;
	nou->next = *cap;
	*cap = nou;
}

void traversareLista(Nod* cap) {
	while (cap) {
		afisareMasina(cap->inf);
		cap = cap->next;
	}
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

void dezalocare(Nod** cap) {
	while ((*cap) != NULL) {
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie->inf.producator);
		free(copie);
	}
}

int numarAparitiiFord(Nod* cap, char* producator) {
	int numar = 0;
	while (cap)
	{
		if (strcmp(cap->inf.producator, producator) == 0)
		{
			numar++;
		}
		cap = cap->next;
	}
	return numar;
}

void main() {
	Nod* cap = NULL; //Definire lista goala

	//Inserare la inceput intr-o lista simplu inlantuita:
	inserareLaInceput(&cap, initMasina("Renault", 1234));
	inserareLaInceput(&cap, initMasina("Ford", 5678));
	inserareLaInceput(&cap, initMasina("Ford", 5679));
	inserareLaInceput(&cap, initMasina("Peugeot", 9101));
	inserareLaInceput(&cap, initMasina("Bmw", 1213));

	traversareLista(cap);

	printf("\n");

	inserareLaFinal(&cap, initMasina("Toyota", 1415));

	traversareLista(cap);

	int nr = numarAparitiiFord(cap, "Ford");

	printf("Masina Ford apare de %d ori", nr);

	dezalocare(&cap);
}