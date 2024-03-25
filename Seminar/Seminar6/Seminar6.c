#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

//Test - saptamana 8
//Assignment OBLIGATORIU peste 2 saptamani
//Liste

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	long id;
	char* producator;
	int serie;
};

struct Nod {
	Masina inf; //informatie utila
	Nod* next; //pointer de legatura, adresa urmatorului nod
};

void afisareMasina(Masina masina) {
	printf("\n %ld. Masina %s are seria %d.",masina.id, masina.producator, masina.serie);
}

Masina initMasina(long id, const char* producator, int serie) {
	Masina masinaNoua;
	masinaNoua.id = id;
	masinaNoua.serie = serie;
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

//La actualizari, modificari, etc -> transmitere prin pointer
void push(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod)); //Aici are sens sa facem shallow copy
	nou->inf = masina;
	nou->next = *cap;
	*cap = nou;
}


void put(Nod** cap, Masina masina) {
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

// Discutie Stiva si Coada

//Structura Stiva (LIFO - Last IN, First OUT)

//Structua Coada (FIFO - First IN, First OUT)

Masina pop(Nod** varf) {  // Functia Pop - Extragere informatie utila si dezalocare
	Masina masina;
	masina.id = -1;
	masina.producator = NULL;
	masina.serie = -1;

	if (*varf) {
		masina = (*varf)->inf;  // Dezalocare pt inf utila nu se face in functia pop
		Nod* tmp = *varf;
		(*varf) = (*varf)->next;
		free(tmp);
	}


	return masina;
}

Masina cautareDupaId(Nod** stiva, long id) {
	Masina masina;
	masina.id = -1;
	masina.serie = -1;
	masina.producator = NULL;
	Nod* stivaAuxiliara = NULL;
	while ((*stiva)!=NULL && (*stiva)->inf.id != id) {
		push(&stivaAuxiliara, pop(stiva));
	}
	if (*stiva) {
		masina = pop(stiva);
	}
	while (stivaAuxiliara) {
		push(stiva, pop(&stivaAuxiliara));
	}

	return masina;
}

void main() {

	Nod* stiva = NULL; //Definire lista goala
	Masina masina1;
	//Inserare la inceput intr-o lista simplu inlantuita:
	push(&stiva, initMasina(1, "Renault", 1234));
	push(&stiva, initMasina(2, "Ford", 5678));
	push(&stiva, initMasina(3, "Ford", 5679));
	push(&stiva, initMasina(4, "Peugeot", 9101));
	push(&stiva, initMasina(5, "Bmw", 1213));
	printf("\n Cautare in Stiva:");

	Masina masinaCautata = cautareDupaId(&stiva, 3);
	afisareMasina(masinaCautata);
	free(masinaCautata.producator);

	printf("\n \n Stiva: ");

	while (stiva) {
		masina1 = pop(&stiva);
		afisareMasina(masina1);
		free(masina1.producator);
	}

	printf("\n");

	Nod* coada = NULL; //Definire lista goala
	Masina masina2;
	//Inserare la inceput intr-o lista simplu inlantuita:
	put(&coada, initMasina(1, "Renault", 1234));
	put(&coada, initMasina(2, "Ford", 5678));
	put(&coada, initMasina(3, "Ford", 5679));
	put(&coada, initMasina(4, "Peugeot", 9101));
	put(&coada, initMasina(5, "Bmw", 1213));
	printf("\n Coada:");
	while (coada) {
		masina2 = pop(&coada);  // Pop ar trebui sa se numeasa get la coada!
		afisareMasina(masina2);
		free(masina2.producator);
	}
	
}