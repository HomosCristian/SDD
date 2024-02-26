#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

//definim structura

struct Produs
{
	float pret;
	int cod;
	char* denumire;
};


//Discutie fisiere si structuri (file & struct)
//Clasele pot fi private, public, protected iar structurile sunt doar publice

void citireVector(const char* numeFisier, int** vector, int* dimensiune) {
	//dereferentiere
	//citim dimensiune
	FILE* streamFisier = NULL;
	streamFisier = fopen(numeFisier, "r");   //"r" este modul citire
		if (streamFisier != NULL) {
			fscanf(streamFisier, "%d", dimensiune);  //nu facem cu & pt ca functia are adresa dimensiunii deja iar scanf asteapta o adresa
			*vector = (int*)malloc(sizeof(int) * (*dimensiune));
			//citire element cu element din fisier
			for (int i = 0; i < *dimensiune; i++) {
				fscanf(streamFisier, "%d", *vector + i);
			}
	}
		fclose(streamFisier);
		
}

//definire functie care citeste un produs din fisier

struct Produs preluareProdusDinFisier(FILE* file) {
	struct Produs produs;
	if (file != NULL) {
		//citire linie cu linie
		//functii atoi si atof (ascii to int si ascii to float)
		char buffer[20];  // care va fi format din 3 parti (strlen de sir + \0 + \n)
		fgets(buffer, 10, file);  // deci in cazul nostru (7.5) MaxCount o sa fie 5 dar punem mai mult ca sa fim siguri 
		produs.pret = atof(buffer);

		//citire a doua linie
		fgets(buffer, 10, file);
		produs.cod = atoi(buffer);

		//citire a treia linie
		fgets(buffer, 20, file);
		char* denumire = strtok(buffer, "\n");  // ca sa scapam de \n de la fgets()
		produs.denumire = malloc(sizeof(char) * (strlen(denumire)+1));
		strcpy(produs.denumire, denumire);

	}
}

void afisareProdus(struct Produs produs) {
	printf("\n Produsul %s are codul %d si pretul %.2f", produs.denumire, produs.cod, produs.pret);
}

void main(){

	int val1, val2;
	//Deschidem fisierul
	FILE* streamFisier = NULL; // (file* este ca fstream)
	streamFisier = fopen("Fisier.txt", "r");
		if (streamFisier != NULL) { //conditia ca fisierul  a fost deschis
			//fscanf citeste linia si deplaseaza mai departe
			//fgets citeste + deplasare + "\n"
			fscanf(streamFisier, "%d", &val1);
			fscanf(streamFisier, "%d", &val2);
		}
	//inchidem fisierul
		fclose(streamFisier);

		printf("\n Val1= %d, Val2=%d", val1, val2);

		//citire vector din fisier (citim prima valoare din fisier care este dimensiunea)

		int* vector = NULL;
		int dimensiune;

		citireVector("Vector.txt", &vector, &dimensiune);  // facem cu & deoarece se modifica in urma functiei valorile

			for (int i = 1; i < dimensiune; i++) {
				printf("\n vector[%i]=%d", i, vector[i]);
			}
		free(vector); //dezalocare pt apelarea functiei

		//!!!! Nu imi afiseaza n vectori, imi afiseaza n-1 vectori !!!!!  DE REPARAT ACASA
		 
		//produs din fisier
		FILE* file = NULL;
		file = fopen("Produs.txt", "r");
		struct Produs = preluareProdusDinFisier(file);

		afisareProdus(produs);
		
		//Problema si aici!!!!!
	
}

