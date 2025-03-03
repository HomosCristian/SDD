#include <stdio.h>
#include<malloc.h>

typedef struct {  
	int *cod; //4 bytes  ////Acum punem o * la cod (nu trebuie doar vedem ce se intampla)
	char* denumire; //4 bytes
	float pret; //4 bytes
	float cantitate; //4 bytes
} produs; //16 bytes

void citireVectorProduse(produs* vp, int nr) {
	char buffer[20]; //ne ajuta pentru a citi sirul de caractere
	for (int i = 0; i < nr; i++) {
		printf("Cod=");
		vp[i].cod = (int*)malloc(sizeof(int));  //alocam memorie pentru cod
		scanf("%d", vp[i].cod);  //nu mai punem & pentru ca deja e un pointer

		printf("Denumire=");
		scanf("%s", buffer);
		vp[i].denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(vp[i].denumire, buffer);

		printf("Pret=");
		scanf("%f", &vp[i].pret);

		printf("Cantitate=");
		scanf("%f", &vp[i].cantitate);
	}
}

void afisareVectorProduse(produs* vp, int nr) {
	for (int i = 0; i < nr; i++) {
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f", *(vp[i].cod), vp[i].denumire, vp[i].pret, vp[i].cantitate);
	}
}

void dezalocareVectorProduse(produs* vp, int nr) {  //cate malloc-uri alocam, atatea free-uri facem
	for (int i = 0; i < nr; i++) {  //se face in oglinda, mai intai stergem ce e inauntru si apoi vectorul
		free(vp[i].cod); //Adaugam si dezalocarea pentru cod
		free(vp[i].denumire);
	}
	free(vp);
}

void citireMatrice(float** mat, char** denumiri, int nr) {  // matricce de vectori
	char buffer[20];
	for (int i = 0; i < nr; i++) {
		printf("Cod=");
		scanf("%d", &mat[i][0]);
		printf("Denumire=");
		scanf("%s", buffer);
		denumiri[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(denumiri[i], buffer);
		printf("Pret=");
		scanf("%f", &mat[i][1]);
		printf("Cantitate=");
		scanf("%f", &mat[i][2]);
	}
}

void afisareMatrice(float** mat, char** denumiri, int nr) {
	for (int i = 0; i < nr; i++) {
		printf("\nCod=%5.2f, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f", mat[i][0], denumiri[i], mat[i][1], mat[i][2]);
	}
}

void dezalocareMatrice(float** mat, char** denumiri, int nr) {
	for (int i = 0; i < nr; i++) {
		free(mat[i]);
		free(denumiri[i]);
	}
	free(denumiri);
	free(mat);
}

void main() {
	int nrProd;
	printf("Nr produse=");
	scanf("%d", &nrProd);
	//produs* vp = (produs*)malloc(nrProd * sizeof(produs));
	//citireVectorProduse(vp, nrProd);
	//afisareVectorProduse(vp, nrProd);
	//dezalocareVectorProduse(vp, nrProd);

	float** mat = (float**)malloc(nrProd * sizeof(float*));
	for  (int i = 0; i < nrProd; i++)
	{
		mat[i] = (float*)malloc(3 * sizeof(float));
	}
	char** denumiri = (char**)malloc(nrProd * sizeof(char*));
	citireMatrice(mat, denumiri, nrProd);
	afisareMatrice(mat, denumiri, nrProd);
	dezalocareMatrice(mat, denumiri, nrProd);
}