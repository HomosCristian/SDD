#include <malloc.h>
#include <stdio.h>

typedef struct {
	int an;
	char* model;
	float pret;
} motocicleta;

typedef struct {
	motocicleta info;
	struct nodLS* next;
} nodLS;

typedef struct {
	struct nodLS** vect;
	int nrElem;
} hashT;

int functieHash1(int cheie, hashT tabela) {
	return cheie % tabela.nrElem;
}

int functieHash2(char* model, hashT tabela) {
	return  model[0] % tabela.nrElem;
}

void inserareLS(nodLS** capLS, motocicleta m) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.an = m.an;
	nou->info.model = (char*)malloc((strlen(m.model) + 1) * sizeof(char));
	strcpy(nou->info.model, m.model);
	nou->info.pret = m.pret;
	nou->next = NULL;
	if (*capLS == NULL) {
		*capLS = nou;
	}
	else {
		nodLS* temp = *capLS;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void inserareHash(hashT tabela, motocicleta m) {
	int poz = functieHash1(m.model, tabela);
	inserareLS(&tabela.vect[poz], m);
}

void traversareLS(nodLS* capLS) {
	nodLS* temp = capLS;
	while (temp != NULL) { 
		printf("\nAnul = %d, Model = %s, Pret = %5.2f", temp->info.an, temp->info.model, temp->info.pret); 
		temp = temp->next; 
	}
}

traversareHash(hashT tabela) {
	for (int i = 0; i < tabela.nrElem; i++) {
		if (tabela.vect[i] != NULL) {
			printf("\nPozitia = %d", i);
			traversareLS(tabela.vect[i]);
		}
	}
}

void dezalocareLS(nodLS* capLS) {
	nodLS* temp = capLS;
	while (temp != NULL) { 
		nodLS* aux = temp->next; 
		free(temp->info.model); 
		free(temp); 
		temp = aux; 
	}
}

void dezalocareHash(hashT tabela) {
	for (int i = 0; i < tabela.nrElem; i++) {
		if (tabela.vect[i] != NULL) {
			dezalocareLS(tabela.vect[i]);
		}
	}
	free(tabela.vect);
}

void main() {
	hashT tabela;
	tabela.nrElem = 23;
	tabela.vect = (nodLS**)malloc(tabela.nrElem * sizeof(nodLS*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	motocicleta m;
	int nrMoto;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrMoto);
	for (int i = 0; i < nrMoto; i++)
	{
		fscanf(f, "%d", &m.an);
		fscanf(f, "%s", buffer);
		m.model = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(m.model, buffer);
		fscanf(f, "%f", &m.pret);
		inserareHash(tabela, m);
		free(m.model);
	}
	fclose(f);

	traversareHash(tabela);

	dezalocareHash(tabela);
}