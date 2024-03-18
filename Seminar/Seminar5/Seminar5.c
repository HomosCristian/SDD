#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>`


typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct LDI LDI;

struct Masina {
	char* producator;
	int serie;
};

struct Nod {
	Masina inf;
	Nod* next;
	Nod* prev;
};

struct LDI {
	Nod* prim;
	Nod* ultim;
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

//Discutie liste duble inlantuite (LDI)



void inserareLaInceput(Masina masina, LDI* ldi) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->prev = NULL;
	nou->next = ldi->prim;
	if (ldi->prim != NULL) {  //conditie ca sa avem noduri in lista

		ldi->prim->prev = nou;
		ldi->prim = nou;
	}
	else {
		ldi->ultim = nou;
		ldi->prim = NULL;
	}
}

void inserareLaFinal(Masina masina, LDI* ldi) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->prev = ldi->ultim;
	nou->next = NULL;
	if (ldi->ultim != NULL) {  //conditie ca sa avem noduri in lista

		ldi->ultim->next = nou;
		ldi->ultim = nou;
	}
	else {
		ldi->ultim = nou;
		ldi->prim = NULL;
	}
}

void dezalocare(LDI* lista) {
	Nod* copie = lista->prim;
	while (copie) {
		free(copie->inf.producator);
		copie = copie->next;
		if (copie) {
			free(copie->prev);
		}
	}
	free(lista->ultim);
	lista->prim = lista->ultim = NULL;
}

void traversareLista(LDI lista, int* nrMasini) {   //traversare de la stanga la dreapta
	while (lista.prim!=NULL)
	{
		afisareMasina(lista.prim->inf);
		(*nrMasini)++;
		lista.prim = lista.prim->next;
	}
}

//Conversie de la LDI la vector

//Am adaugat un contor la fct traversareLista

void conversieLaVector(LDI lista, Masina** vectorMasini) {
	int nrMasini = 0;
	while (lista.prim) {
		(*vectorMasini)[nrMasini] = initMasina(lista.prim->inf.producator, lista.prim->inf.serie);
		nrMasini++;
		lista.prim = lista.prim->next;
	}
}
//Lista circulara

void traversareListaCirculara(LDI lista) {

	Nod* aux = lista.prim;
	do {
		afisareMasina(aux->inf);
		aux = aux->next;
	} while (aux != lista.prim);
}

void main() {
	LDI lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareLaInceput(initMasina("Ford", 1234), &lista);
	inserareLaInceput(initMasina("Audi", 3453), &lista);
	inserareLaInceput(initMasina("Renault", 4345), &lista);
	inserareLaInceput(initMasina("Mercedes", 5344), &lista);

	int nrMasini = 0;
	traversareLista(lista, &nrMasini);
	
	Masina* vectorMasini = (Masina*)malloc(sizeof(Masina) * nrMasini);
	conversieLaVector(lista, &vectorMasini);
	printf("\n Afisare masini din vecotri:");
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(vectorMasini[i]);
		free(vectorMasini[i].producator);
	}
	free(vectorMasini);

	lista.ultim->next = lista.prim;
	lista.prim->prev = lista.ultim;

	traversareListaCirculara(lista);

	//dezalocare(&lista);  ////Nu are sens pt lista circulara
}