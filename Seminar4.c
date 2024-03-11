//Test - saptamana 8
//Assignment OBLIGATORIU peste 2 saptamani
//Liste

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	char* producator;
	int serie;

};

void afisareMasina(Masina masina) {
	printf("\nMasina %s are seria %d.", masina.producator, masina.serie);
}

Masina initMasina(const char* producator, int serie) {
	Masina masinaNoua;
	masinaNoua.serie = serie;
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

struct Nod
{
	Masina inf; //informatie utila
	Nod* next;//pointer de legatura, adresa urmatorului nod
};

//La actualizari, modificari, etc -> transmitere prin pointer
void inserareLaInceput(Nod** cap, Masina masina)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	//Aici are sens sa facem shallow copy
	nou->inf = masina;
	nou->next = *cap;
	*cap = nou;
}

void traversareLista(Nod* cap) {
	while (cap != NULL) {
		afisareMasina(cap->inf);
		cap = cap->next;
	}
}

void inserareLaFinal(Nod** cap, Masina masina)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	//Aici are sens sa facem shallow copy
	nou->inf = masina;
	nou->next = NULL;


	if (*cap != NULL) {
		//Nu il putem folosi tot pe cap pentru deplasare -> trebuie auxiliar
		Nod* aux = *cap;
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


int cautareMasina(Nod* cap, char* producator) {
	int numar = 0;
	while (cap != NULL) {
		if (strcmp(cap->inf.producator, producator) == 0) {
			numar++;
		}
		cap= cap->next;
	}
	return numar;
}

void main() {
	//definire lista goala
	Nod* Cap = NULL;

	//inserare la inceput intr-o lista simplu inlantuita
	inserareLaInceput(&Cap, initMasina("Renault", 1234));
	inserareLaInceput(&Cap, initMasina("Mercedes", 5678));
	inserareLaInceput(&Cap, initMasina("Dacia", 91011));
	inserareLaInceput(&Cap, initMasina("Audi", 121314));

	traversareLista(Cap);
	inserareLaFinal(&Cap, initMasina("Toyota", 12244));

	traversareLista(Cap);

	dezalocare(&Cap);

	int cautare = cautareMasina(Cap, "Ford");
}