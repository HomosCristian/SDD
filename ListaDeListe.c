#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int an;
	char* model;
	float pret;
} motocicleta;

typedef struct
{
	motocicleta info;
	struct nodLS* next;
} nodLS;

typedef struct
{
	struct nodLS* info;
	struct nodLP* next;
} nodLP;

void inserareLS(nodLS** capLS, motocicleta m)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.an = m.an;
	nou->info.model = (char*)malloc((strlen(m.model) + 1) * sizeof(char));
	strcpy(nou->info.model, m.model);
	nou->info.pret = m.pret;
	nou->next = NULL;
	if (*capLS == NULL)
		*capLS = nou;
	else
	{
		nodLS* temp = *capLS;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

void inserareLP(nodLP** capLP, nodLS* capLS) {
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->info = capLS;
	nou->next = NULL;
	if (*capLP == NULL) {
		*capLP = nou;
	}
	else {
		nodLP* temp = *capLP;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next;
	}
}

void traversareLS(nodLS* capLS) {
	nodLS* temp = capLS;
	while (temp)
	{
		printf("\An = %d , Model = %s , Pret = %5.2f ",
			temp->info.an, temp->info.model, temp->info.pret);
		temp = temp->next;
	}
}

void traversareLP(nodLP* capLP) {
	nodLP* temp = capLP;
	int i = 1;
	while (temp)
	{
		printf("\nSublista: %d\n", i);
		traversareLS(temp->info);
		temp = temp->next;
		i++;
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		free(temp->info.model);
		free(temp);
		temp = temp2;
	}
}

void dezalocareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	while (temp)
	{
		nodLP* temp2 = temp->next;
		dezalocareLS(temp->info);
		free(temp);
		temp = temp2;
	}
}

void main() {
	nodLP* capLP = NULL;
	nodLS* capLSpromovati = NULL, * capLSnepromovati = NULL;

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
		if (m.pret >= 5.0)
			inserareLS(&capLSpromovati, m);
		else
			inserareLS(&capLSnepromovati, m);
		free(m.model);
	}
	fclose(f);

	inserareLP(&capLP, capLSpromovati);
	inserareLP(&capLP, capLSnepromovati);

	traversareLP(capLP);

	dezalocareLP(capLP);
}