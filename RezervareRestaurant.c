#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int capacitate;
    int disponibilitate;
} Masa;

Masa *mese = NULL;
int numarMese = 0;

void red(){
    printf("\033[0;31m");
}

void green(){
    printf("\033[0;32m");
}

void yellow() {
    printf("\033[0;33m");
}

void blue(){
    printf("\033[0;34m");
}

void purple(){
    printf("\033[0;35m");
}

void white(){
    printf("\033[0;37m");
}

void citire_fisier_mese() 
{
    FILE *f = fopen("mese.txt", "r");
    if (f == NULL) 
    {
        printf("Fisierul nu exista sau nu poate fi deschis.\n");
        return;
    }

    numarMese = 0;
    int c, d;
    while (fscanf(f, "%d %d", &c, &d) == 2) {
        mese = (Masa*)realloc(mese, (numarMese + 1) * sizeof(Masa));
        if (mese == NULL)
        {
            printf("Eroare la realocarea memoriei!\n");
            fclose(f);
        }
        mese[numarMese].capacitate = c;
        mese[numarMese].disponibilitate = d;
        numarMese++;
    }
    fclose(f);
}

void scrie_mese_in_fisier() 
{
    FILE *f = fopen("mese.txt", "w");
    if (f == NULL) 
    {
        printf("Eroare la deschiderea fisierului pentru scriere!\n");
        return;
    }
    for (int i = 0; i < numarMese; i++)
        fprintf(f, "%d %d\n", mese[i].capacitate, mese[i].disponibilitate);
    fclose(f);
}

void sterge_ecran() 
{
    system("cls || clear");
}

void revenire()
{
    int comanda;
    printf("\nApasati 0 pentru a reveni la meniul principal: ");
    scanf("%d", &comanda);
    if (comanda == 0) 
        sterge_ecran();
    else revenire();
}

void meniu_principal() 
{
    purple();
    printf("\n===");
    white();
    printf(" Meniu Principal ");
    purple();
    printf("===\n");
    white();
    printf("1. Adauga masa\n");
    printf("2. Sterge masa\n");
    printf("3. Afiseaza toate mesele\n");
    printf("4. Cauta masa libera\n");
    printf("5. Rezerva masa\n");
    printf("6. Sterge rezervare\n");
    printf("7. Inchide aplicatia\n");
}

void adauga_masa() 
{
    int capacitate;
    printf("Introduceti capacitatea mesei (1-20): ");
    scanf("%d", &capacitate);
    if (capacitate < 1 || capacitate > 20) 
    {
        printf("Capacitatea ");
        red();
        printf("trebuie ");
        white();
        printf("sa fie intre 1 si 20!\n");
        return;
    }

    mese = (Masa*)realloc(mese, (numarMese + 1) * sizeof(Masa));
    if (mese == NULL) 
        printf("Eroare la realocare memorie!\n");

    mese[numarMese].capacitate = capacitate;
    mese[numarMese].disponibilitate = 0;  // Noua masa e libera
    numarMese++;
    scrie_mese_in_fisier();
    printf("Masa adaugata cu ");
    green();
    printf("succes!\n");
    white();
}

void sterge_masa() 
{
    int nr;
    printf("Introduceti numarul mesei de sters (1-%d): ", numarMese);
    scanf("%d", &nr);
    if (nr < 1 || nr > numarMese) 
    {
        printf("Masa ");
        red();
        printf("nu ");
        white();
        printf("exista!\n");
        return;
    }

    for (int i = nr - 1; i < numarMese - 1; i++) 
        mese[i] = mese[i + 1];
    numarMese--;
    mese = (Masa*)realloc(mese, numarMese * sizeof(Masa));
    scrie_mese_in_fisier();
    printf("Masa ");
    blue();
    printf("stearsa ");
    white();
    printf("cu succes!\n");
}

void lista_mese() 
{
    printf("\n--- Mesele restaurantului ---\n");
    for (int i = 0; i < numarMese; i++) 
    {
        //printf("Masa %d - Capacitate: %d, %s\n", i + 1, mese[i].capacitate, mese[i].disponibilitate ? "Rezervata" : "Libera");
        yellow();
        printf("Masa %d", i + 1);
        white();
        printf(" - ");
        blue();
        printf("Capacitate");
        white();
        printf(": %d,",  mese[i].capacitate);
        if (mese[i].disponibilitate==1)
        {
            red();
            printf("Rezervata\n");
            white();
        }
        else
        {
            green();
            printf("Libera\n");
            white();
        }
    }
    
}

void cauta_masa_libera() 
{
    int c, ok=0;
    printf("Introduceti capacitatea dorita: ");
    scanf("%d", &c);

    for (int i = 0; i < numarMese; i++) 
    {
        if (mese[i].capacitate == c && mese[i].disponibilitate == 0) 
        {
            ok=1;
            printf("Masa %d este ", i + 1);
            green();
            printf("libera.\n");
            white();
            return;
        }
    }
    if (ok==0)
        red();
        printf("Nu exista ");
        white();
        printf("mese libere pentru capacitatea ceruta.\n");
}

void rezervare() 
{
    int c;
    printf("Introduceti capacitatea mesei pe care doriti sa o rezervati: ");
    scanf("%d", &c);

    for (int i = 0; i < numarMese; i++) 
    {
        if (mese[i].capacitate == c && mese[i].disponibilitate == 0) 
        {
            mese[i].disponibilitate = 1;
            scrie_mese_in_fisier();
            printf("Masa %d a fost ", i + 1);
            green();
            printf("rezervata!\n");
            white();
            return;
        }
    }
    red();
    printf("Nu exista ");
    white();
    printf("masa disponibila pentru capacitatea ceruta.\n");
}

void sterge_rezervare() 
{
    int c;
    printf("Introduceti capacitatea pentru a sterge rezervarea: ");
    scanf("%d", &c);

    for (int i = 0; i < numarMese; i++) 
    {
        if (mese[i].capacitate == c && mese[i].disponibilitate == 1) 
        {
            mese[i].disponibilitate = 0;
            scrie_mese_in_fisier();
            printf("Rezervarea la masa %d a fost ", i + 1);
            red();
            printf("anulata!\n");
            white();
            return;
        }
    }
    blue();
    printf("Nu exista ");
    white();
    printf("rezervari pentru aceasta capacitate.\n");
}

int main() {
    int optiune;
    citire_fisier_mese();
    
    do {
        meniu_principal();
        printf("\nAlegeti ");
        purple();
        printf("optiunea");
        white();
        printf(": ");
        scanf("%d", &optiune);
        sterge_ecran();

        switch (optiune) {
            case 1:
                adauga_masa();
                revenire();
                break;
            case 2:
                sterge_masa();
                revenire();
                break;
            case 3:
                lista_mese();
                revenire();
                break;
            case 4:
                cauta_masa_libera();
                revenire();
                break;
            case 5:
                rezervare();
                revenire();
                break;
            case 6:
                sterge_rezervare();
                revenire();
                break;
            case 7:
                printf("Multumim ca ati utilizat aplicatia noasta!\nO zi ");
                yellow();
                printf("frumoasa!\n");
                white();
                break;
            default:
                printf("Optiune invalida!\n");
        }
    } while (optiune != 7);

    free(mese);
    return 0;
}
