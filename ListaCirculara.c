#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct {
    int an;
    char* model;
    float pret;
} motocicleta;

typedef struct nodLD {
    motocicleta info;
    struct nodLD* next;
    struct nodLD* prev;
} nodLD;

nodLD* initializareNod(motocicleta m) {
    nodLD* nou = (nodLD*)malloc(sizeof(nodLD));
    nou->info.an = m.an;
    nou->info.model = (char*)malloc((strlen(m.model) + 1) * sizeof(char));
    strcpy(nou->info.model, m.model);
    nou->info.pret = m.pret;
    nou->next = NULL;
    nou->prev = NULL;
    return nou;
}

nodLD* inserareNod1(nodLD* capLD, nodLD** coadaLD, motocicleta m) {
    nodLD* nou = initializareNod(m);
    if (capLD == NULL) {
        capLD = nou;
        *coadaLD = nou;
    }
    else {
        (*coadaLD)->next = nou;
        nou->prev = *coadaLD;
        *coadaLD = nou;
        (*coadaLD)->next = capLD;
        capLD->prev = *coadaLD;
    }
    return capLD;
}

void inserareNod2(nodLD** capLD, nodLD** coadaLD, motocicleta m) {
    nodLD* nou = initializareNod(m);
    if (*capLD == NULL) {
        *capLD = nou;
        *coadaLD = nou;
    }
    else {
        nodLD* temp = *capLD;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nou;
        nou->prev = temp;
        *coadaLD = nou;
        (*coadaLD)->next = *capLD;
        (*capLD)->prev = *coadaLD;
    }
}

void traversareLista(nodLD* capLD) {
    nodLD* temp = capLD;
    while (temp != capLD) {
        printf("\nAn = %d, Model = %s, Pret = %5.2f", temp->info.an, temp->info.model, temp->info.pret);
        temp = temp->next;
    }
    printf("\nAn = %d, Model = %s, Pret = %5.2f", temp->info.an, temp->info.model, temp->info.pret);
}

void traversareListaInvers(nodLD* coadaLD) {
    nodLD* temp = coadaLD;
    while (temp != coadaLD) {
        printf("\nAn = %d, Model = %s, Pret = %5.2f", temp->info.an, temp->info.model, temp->info.pret);
        temp = temp->prev;
    }
    printf("\nAn = %d, Model = %s, Pret = %5.2f", temp->info.an, temp->info.model, temp->info.pret);
}

void dezalocareLista(nodLD* capLD) {
    nodLD* temp = capLD;
    while (temp != capLD) {
        nodLD* aux = temp->next;
        free(temp->info.model);
        free(temp);
        temp = aux;
    }
    free(temp->info.model);
    free(temp);
}

void salvareStudentiVector(nodLD* capLD, motocicleta* vect, int* nrElem, float pragAn) {
    nodLD* temp = capLD;
    while (temp != capLD) {
        if (temp->info.an >= pragAn) {
            vect[*nrElem].an = temp->info.an;
            vect[*nrElem].model = (char*)malloc((strlen(temp->info.model) + 1) * sizeof(char));
            strcpy(vect[*nrElem].model, temp->info.model);
            vect[*nrElem].pret = temp->info.pret;
            (*nrElem)++;
        }
        temp = temp->next;
    }
    if (temp->info.an >= pragAn) {
        vect[*nrElem].an = temp->info.an;
        vect[*nrElem].model = (char*)malloc((strlen(temp->info.model) + 1) * sizeof(char));
        strcpy(vect[*nrElem].model, temp->info.model);
        vect[*nrElem].pret = temp->info.pret;
        (*nrElem)++;
    }
}

void stergereStudentDupaNume(nodLD** capLD, nodLD** coadaLD, char* nume) {
    if (strcmp((*capLD)->info.model, nume) == 0) {
        nodLD* temp = *capLD;
        *capLD = (*capLD)->next;
        (*capLD)->prev = *coadaLD;
        (*coadaLD)->next = *capLD;
        free(temp->info.model);
        free(temp);
        return;
    }
    else if (strcmp((*coadaLD)->info.model, nume) == 0) {
        nodLD* temp = *coadaLD;
        *coadaLD = (*coadaLD)->prev;
        (*coadaLD)->next = *capLD;
        (*capLD)->prev = *coadaLD;
        free(temp->info.model);
        free(temp);
        return;
    }
    else {
        nodLD* temp = *capLD;
        while (temp != NULL) {
            if (strcmp(temp->info.model, nume) == 0) {
                nodLD* anterior = temp->prev;
                nodLD* urmator = temp->next;
                anterior->next = urmator;
                urmator->prev = anterior;
                free(temp->info.model);
                free(temp);
                return;
            }
            else
                temp = temp->next;
        }
    }
}

void main() {
    int nrMoto;
    motocicleta m;
    nodLD* capLD = NULL, * coadaLD = NULL;
    char buffer[20];
    FILE* f = fopen("fisier.txt", "r");
    fscanf(f, "%d", &nrMoto);
    for (int i = 0; i < nrMoto; i++) {
        fscanf(f, "%d", &m.an);
        fscanf(f, "%s", buffer);
        m.model = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(m.model, buffer);
        fscanf(f, "%f", &m.pret);
        capLD = inserareNod1(capLD, &coadaLD, m);
        free(m.model);
    }
    fclose(f);
    traversareLista(capLD);
    printf("\n-------------Traversare inversa--------------\n");
    traversareListaInvers(coadaLD);
    printf("\n-------------Vector--------------\n");
    motocicleta* vect = (motocicleta*)malloc(nrMoto * sizeof(motocicleta));
    int nrElem = 0;
    salvareStudentiVector(capLD, vect, &nrElem, 9.0f);
    for (int i = 0; i < nrElem; i++)
        printf("\nVarsta = %d, Nume = %s, Medie = %5.2f", vect[i].an, vect[i].model, vect[i].pret);
    for (int i = 0; i < nrElem; i++) {
        free(vect[i].model);
    }
    free(vect);
    printf("\n-------------Stergere--------------\n");
    stergereStudentDupaNume(&capLD, &coadaLD, "Kawasaki");
    traversareLista(capLD);
    printf("\n-------------Traversare inversa--------------\n");
    traversareListaInvers(coadaLD);
    dezalocareLista(capLD);
}
