#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>

typedef struct Motocicleta Motocicleta;
typedef struct Nod Nod;

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

Motocicleta pop(Nod** varf)
{
	Motocicleta motocicleta;
	motocicleta.capacitate = -1;
	motocicleta.putere = -1;
	motocicleta.producator = NULL;
	motocicleta.model = NULL;
	if (*varf) {
		motocicleta = (*varf)->inf;
		Nod* temp = *varf;
		(*varf) = (*varf)->next;
		free(temp);
	}
	return motocicleta;
}

Motocicleta cautareDupaCapacitate(Nod** stiva, int capacitate) {
	Motocicleta motocicleta;
	motocicleta.putere = -1;
	motocicleta.capacitate = -1;
	motocicleta.producator = NULL;
	motocicleta.model = NULL;
	Nod* stivaAuxiliara = NULL;
	while ((*stiva) != NULL && (*stiva)->inf.capacitate != capacitate) {
		push(&stivaAuxiliara, pop(stiva));
	}
	if (*stiva) {
		motocicleta = pop(stiva);
	}
	while (stivaAuxiliara) {
		push(stiva, pop(&stivaAuxiliara));
	}
	return motocicleta;
}

void main()
{
	Nod* stiva = NULL;
	Motocicleta motocicleta;
	push(&stiva, initMotocicleta("Kawasaki", 649, "Ninja 650", 67));
	push(&stiva, initMotocicleta("Kawasaki", 399, "Ninja 400", 45));
	push(&stiva, initMotocicleta("Kawasaki", 636, "Ninja ZX6R", 125));
	push(&stiva, initMotocicleta("Kawasaki", 998, "Ninja ZX10R", 200));

	Motocicleta motocicletaCautata = cautareDupaCapacitate(&stiva, 649);
	afisareMotocicleta(motocicletaCautata);
	free(motocicletaCautata.producator);
	free(motocicletaCautata.model);

	printf("\n\n Stiva:");
	while (stiva) 
	{
		motocicleta = pop(&stiva);
		afisareMotocicleta(motocicleta);
		free(motocicleta.producator);
		free(motocicleta.model);
	}

	Nod* coada = NULL;
	put(&coada, initMotocicleta("Kawasaki", 649, "Ninja 650", 67));
	put(&coada, initMotocicleta("Kawasaki", 399, "Ninja 400", 45));
	put(&coada, initMotocicleta("Kawasaki", 636, "Ninja ZX6R", 125));
	put(&coada, initMotocicleta("Kawasaki", 998, "Ninja ZX10R", 200));

	printf("\n\n Coada:");
	while (coada)
	{
		motocicleta = pop(&coada);
		afisareMotocicleta(motocicleta);
		free(motocicleta.producator);
		free(motocicleta.model);
	}
}

