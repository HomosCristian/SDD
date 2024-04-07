#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>

typedef struct Motocicleta Motocicleta;
typedef struct NodLsi NodLsi;
typedef struct NodLdi NodLdi;
typedef struct LDI LDI;

struct Motocicleta 
{
	char* producator;
	int capacitate;
	char* model;
	int putere;
};

struct NodLsi  // Lista simplu inlantuita
{
	Motocicleta inf;
	NodLsi* next;
};

struct NodLdi
{
	Motocicleta inf;
	NodLdi* next;
	NodLdi* prev;
};

struct LDI
{
	NodLdi* prim;
	NodLdi* ultim;
};

void afisareMotocicleta(Motocicleta motocicleta)
{
	printf("\n Motocicleta %s %s are capacitatea de %dcc si o putere de %d cai putere", motocicleta.producator, motocicleta.model, motocicleta.capacitate, motocicleta.putere);
}

Motocicleta initMotocicleta(const char* producator, int capacitate,const char* model, int putere) 
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

// LISTA SIMPLA INLANTUITA

void inserareLaInceputLsi(NodLsi** cap, Motocicleta motocicleta)
{
	NodLsi* nou = (NodLsi*)malloc(sizeof(NodLsi));  // Alocam memorie unui nod
	nou->inf = motocicleta;  // Informatia utila
	nou->next = *cap;  

	*cap = nou;
}

void inserareLaFinalLsi(NodLsi** cap, Motocicleta motocicleta)
{
	NodLsi* nou = (NodLsi*)malloc(sizeof(NodLsi));  // Alocam memorie unui nod
	nou->inf = motocicleta;  // Informatia utila
	nou->next = NULL;

	if (*cap)  // Parcuregem lista pana la final
	{
		NodLsi* aux = *cap;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
	{
		*cap = nou;
	}
}

void traversareLsi(NodLsi* cap)
{
	while (cap)  // Conditie cat timp avem ceva in lista
	{
		afisareMotocicleta(cap->inf);  // Afisam informatia utila
		cap = cap->next;  // Trecem la urmatorul nod
	}
}

void dezalocareLsi(NodLsi** cap) // Folosim pointer la pointer pentru ca modificam lista
{
	while (*cap)
	{
		NodLsi* copie = *cap;  // Facem o copie a adresei primului nod
		free(copie->inf.producator);
		free(copie->inf.model);
		free(copie);
		*cap = (*cap)->next;  // Trecem la urmaotrul nod
	}
}

int numarAparitiiModel(NodLsi* cap, const char* model)  // Functie care numara cate motociclete de acelasi model sunt in lista
{
	int nr = 0;
	while (cap)
	{
		if (strcmp(cap->inf.model, model) == 0)
		{
			nr++;
		}
		cap = cap->next;
	}
	return nr;
}

void stergereUltimulNod(NodLdi** cap)  // Functie care sterge ultimul nod din lsita
{
	if ((*cap)!=NULL)  // Parcuregem lista pana la final
	{
		NodLsi* copie = *cap;  // Cream o copie pentru ca modificam lista
		while (copie->next->next)
		{
			copie = copie->next;
		}
		free(copie->next->inf.producator);
		free(copie->next->inf.model);
		free(copie->next);
		copie->next = NULL;
	}

}

void stergerePrimulNod(NodLsi** cap)
{
	NodLsi* copie = *cap;
	*cap = (*cap)->next;
	free(copie);
}

void stergeNodDupaModel(NodLsi** cap, const char* model) {
	if (*cap == NULL) {
		printf("Lista este goala.\n");
		return;
	}

	NodLsi* anterior = NULL;
	NodLsi* curent = *cap;

	while (curent != NULL) {
		if (strcmp(curent->inf.model, model) == 0) {
			if (anterior == NULL) {
				*cap = curent->next; // dacă nodul care trebuie șters este primul nod
			}
			else {
				anterior->next = curent->next;
			}
			free(curent->inf.producator);
			free(curent->inf.model);
			free(curent);
			printf(" Nodul cu modelul % s a fost sters.\n", model);
			return;
		}
		anterior = curent;
		curent = curent->next;
	}

	printf("Nu s-a gasit niciun nod cu modelul %s.\n", model);
}



// LISTA DUBLA INLANTUITA

void inserareLaInceputLdi(LDI* ldi, Motocicleta motocicleta)
{
	NodLdi* nou = (NodLdi*)malloc(sizeof(NodLdi));  // Alocam memorie unui nod
	nou->inf = motocicleta;  // Ii dam informatia utila
	nou->prev = NULL;  // Setam nodul din inainte ca NULL pentru ca nu exista
	nou->next = ldi->prim;  
	if (ldi->prim)   // Conditie ca sa avem noduri in lista
	{  
		ldi->prim->prev = nou;
		ldi->prim = nou;
	}
	else
	{
		ldi->ultim = nou;
		ldi->prim = nou;
	}
}

void inserareLaFinalLdi(LDI* ldi, Motocicleta motocicleta)
{
	NodLdi* nou = (NodLdi*)malloc(sizeof(NodLdi));
	nou->inf = motocicleta;
	nou->prev = ldi->ultim;
	nou->next = NULL;
	if (ldi->ultim) // Conditie sa avem ceva in lista
	{
		ldi->ultim->next = nou;
		ldi->ultim = nou;
	}
	else
	{
		ldi->ultim = nou;
		ldi->prim = nou;
	}
}

void traversareLdi(LDI ldi)  
{
	while (ldi.prim) // Traversare de la stanga la dreapta
	{
		afisareMotocicleta(ldi.prim->inf);
		ldi.prim = ldi.prim->next;
	}

	//while (ldi.ultim) // Traversare de la dreapta la stanga
	//{
	//	afisareMotocicleta(ldi.ultim->inf);
	//	ldi.ultim = ldi.ultim->prev;
	//}
}

void dezalocareLdi(LDI* ldi) 
{
	NodLdi* copie = ldi->prim;
	while (copie) {
		free(copie->inf.producator);
		copie = copie->next;
		if (copie) {
			free(copie->prev);
		}
	}
	free(ldi->ultim);
	ldi->prim = ldi->ultim = NULL;
}


void main()
{
	Motocicleta m1, m2;

	m1 = initMotocicleta("Kawasaki", 649, "Ninja 650", 67);
	m2 = initMotocicleta("Kawasaki", 399, "Ninja 400", 45);

	afisareMotocicleta(m1);
	afisareMotocicleta(m2);

	printf("\n\n\n Lista simpla inlantuita:\n");

	NodLsi* cap = NULL;
	inserareLaInceputLsi(&cap, initMotocicleta("Kawasaki", 649, "Ninja 650", 67));
	inserareLaInceputLsi(&cap, initMotocicleta("Kawasaki", 399, "Ninja 400", 45));
	inserareLaFinalLsi(&cap, initMotocicleta("Kawasaki", 636, "Ninja ZX6R", 125));
	inserareLaFinalLsi(&cap, initMotocicleta("Kawasaki", 998, "Ninja ZX10R", 200));
	inserareLaFinalLsi(&cap, initMotocicleta("Kawasaki", 636, "Ninja ZX6R", 125));

	traversareLsi(cap);

	int nr = numarAparitiiModel(cap, "Ninja ZX6R");
	printf("\n\n Exista %d modele de motociclete identice in lista", nr);

	stergereUltimulNod(&cap);
	printf("\n\n Afisare dupa stergerea ultimului nod din lista:\n");
	traversareLsi(cap);

	inserareLaInceputLsi(&cap, initMotocicleta("Kawasaki", 636, "Ninja ZX6R", 125));
	printf("\n\n Am mai introdus o motociclieta la inceputul liste:");
	traversareLsi(cap);
	stergerePrimulNod(&cap);
	printf("\n\n Afisare dupa stergerea primului nod din lista:\n");
	traversareLsi(cap);

	printf("\n\n");
	stergeNodDupaModel(&cap, "Ninja 650");
	traversareLsi(cap);

	printf("\n\n\n Lista dubla inlantuita:\n");

	LDI lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareLaInceputLdi(&lista, initMotocicleta("Kawasaki", 649, "Ninja 650", 67));
	inserareLaInceputLdi(&lista, initMotocicleta("Kawasaki", 399, "Ninja 400", 45));
	inserareLaFinalLdi(&lista, initMotocicleta("Kawasaki", 636, "Ninja ZX6R", 125));
	inserareLaFinalLdi(&lista, initMotocicleta("Kawasaki", 998, "Ninja ZX10R", 200));

	traversareLdi(lista);



}

