#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>


void interschimbare(int nr1, int nr2) {     //functie pt transmiterea param prin valoare
	
	int aux;
	aux = nr1;
	nr1 = nr2;
	nr2 = aux;
}

void interschimbarePointer(int* nr1, int* nr2) {     //functie pt transmiterea param prin adresa
	int aux;
	aux = *nr1;
	*nr1 = *nr2;
	*nr2 = aux;
}

void citireDeLaTastatura(int** vector, int* dimensiuneVector) {   
	//int* la dimensiune pt ca o sa se modifice dimensiunea si 2 * pt vector pt ca in main avem declarat int*
	printf("Dimensiune: ");
	scanf("&d", dimensiuneVector);   //scanf asteapta o adresa deci nu punem &dimensiune pt ca ested eja o adresa
	//alocare vector
	vector = (int*)malloc((*dimensiuneVector) * sizeof(int));

	for (int i = 0; i < (*dimensiuneVector); i++) //dereferentiere pt dimensiune
 	{
		printf("vector[%i]=", i);
		scanf("%d", &(*vector)[i]);             
		//am facut dereferentierea pt primul element din vector si dupa face & ca sa transmitem lui scanf o adresa pt ca scanf asteapta mereu o adresa
		//  scanf("%d", *vector + i);  //alta scriere mai usoara
	}

}

void afisare(int* vector, int dimensiuneVector) {
	for (int i = 0; i < dimensiuneVector; i++)
	{
		printf("\n vector[%d]=%d", i, vector[i]);
	}

}

int main() {
	
	//Tipuri de date

	int numarIntreg;
	char caracter;
	float numarReal;

	numarIntreg = 7;
	caracter = 'A';
	numarReal = 70.5f;

	//%d (desmond) sau %i (integer)
	printf("%d \n", numarIntreg);
	printf("%c \n", caracter);
	printf("%d \n", caracter);      //afiseaza codul ascii al lui 'A'
	printf("%.2f \n", numarReal);     //.2f adica afiseaza cu doua zecimale

	//Siruri de caractere (alocare dinamica/statoca)

	char sirCaractere[8];  //ultima pozitie este terminatorul de sir \0
	for (int i = 0; i < 8; i++)
	{
		sirCaractere[i] = 97 + i;
	}
	sirCaractere[7] = '\0';
	
	printf("%s \n", sirCaractere);    // %s de la string

	//Alocarea dinamica

	char* sirAlocatDinamc; //in c++ foloseam new, aici folosim malloc
	sirAlocatDinamc = (char*)malloc(6 * sizeof(char));  //nr* sizeof(tipData)
	for (int i = 0; i < 6; i++)
	{
		sirAlocatDinamc[i] = 65 + i;
	}
	sirAlocatDinamc[5] = '\0';
	printf("%s \n", sirAlocatDinamc);


	//Transmiterea parametrilor in C: prin valoare/adresa(pointer)

	//Interschimbare intre 2 nr intregi

	int var1 = 1;
	int var2 = 2;

	interschimbare(var1, var2);
	printf("\n var1=%d, var2=%d", var1, var2);

	interschimbarePointer(&var1, &var2);
	printf("\n var1=%d, var2=%d", var1, var2);

	//citire vector dinamic

	int dimensiuneVector;
	int* vector;
	citireDeLaTastatura(&vector, &dimensiuneVector);
	afisare(vector, dimensiuneVector);






}