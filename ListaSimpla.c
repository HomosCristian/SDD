#include <stdio.h>            
#include <malloc.h>           
#include <string.h>           

typedef struct {
    int an;
    char* model;
    float pret;
} motocicleta;

typedef struct nodLS {
    motocicleta info;
    struct nodLS* next;
} nodLS;

nodLS* initializareNod(motocicleta m) {
    nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
    nou->info.an = m.an;
    nou->info.model = (char*)malloc((strlen(m.model) + 1) * sizeof(char));
    strcpy(nou->info.model, m.model);
    nou->info.pret = m.pret;
    nou->next = NULL;
    return nou;
}

    nodLS* inserareNod(nodLS * capLS, motocicleta m) {
        nodLS* nou = initializareNod(m);
        if (capLS == NULL) {
            capLS = nou;
        }
        else {
            nodLS* temp = capLS;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = nou;
        }
        return capLS;
    }

    void inserareNod2(nodLS * *capLS, motocicleta m)
    {
        nodLS* nou = initializareNod(m);
        if (*capLS == NULL)
            *capLS = nou;
        else
        {
            nodLS* temp = *capLS;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = nou;
        }
    }


    void traversareLista(nodLS * capLS) {
        nodLS* temp = capLS;
        while (temp != NULL) {
            printf("\nAnul = %d, Model = %s, Pret = %5.2f", temp->info.an, temp->info.model, temp->info.pret);
            temp = temp->next;
        }
    }


    void dezalocareLista(nodLS * capLS) {
        nodLS* temp = capLS;
        while (temp != NULL) {
            nodLS* aux = temp->next;
            free(temp->info.model);
            free(temp);
            temp = aux;
        }
    }

    void main() {
        int nrMoto;
        motocicleta m;
        nodLS* capLS = NULL;
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
            capLS = inserareNod(capLS, m);
            free(m.model);
        }
        fclose(f);


        traversareLista(capLS);
    }
