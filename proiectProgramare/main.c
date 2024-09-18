#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct disponibil{
    char disponibil_data[50];
    char disponibil_ora_min[50];
    char disponibil_ora_max[50];
}disponibil[100];

struct program{
    char tip_consultatie[50];
}program[100];

struct istoric{
    char istoric_ora[50];
    char istoric_data[50];
    char istoric_optiune[50];
}istoric[100];

int citireNrIstoric(int a){
    FILE* fi = fopen("istoric.txt", "r");
    fscanf(fi, "%d", &a);
    fclose(fi);
    return a;
}

int verificareData(int zi, int luna, int an){
    if(an != 2023 || luna < 1 || luna > 12 || (luna%2 == 0 && zi > 30 && luna != 2) || (luna%2 == 1 && zi > 31) || zi < 1 || (luna == 2 && zi > 28))
        return 0;
    else
        return 1;
}

int citireNrDisponibilitate(int nr){
    FILE* fp = fopen("disponibil.txt", "r");
    fscanf(fp, "%d", &nr);
    fgetc(fp);
    fclose(fp);
    return nr;
}

int verificareIstoric(char* a, char* b, char* c, int nr_program){
    int ok = 1;
    for (int i = 1; i < nr_program; i++){
        if(strcmp(a, istoric[i].istoric_data) == 0 && strcmp(b, istoric[i].istoric_ora) == 0 && strcmp(c, istoric[i].istoric_optiune) == 0)
            ok = 0;
    }
    return ok;
}


void citireDisponibilitate(){
    int nr_disponibil;
    FILE* fp = fopen("disponibil.txt", "r");
    fscanf(fp, "%d", &nr_disponibil);
    fgetc(fp);
    for (int i = 1; i <= nr_disponibil; ++i){
        fgets(disponibil[i].disponibil_data, 50, fp);
        disponibil[i].disponibil_data[strlen(disponibil[i].disponibil_data) - 1] = '\0';
        fgets(disponibil[i].disponibil_ora_min, 50, fp);
        disponibil[i].disponibil_ora_min[strlen(disponibil[i].disponibil_ora_min) - 1] = '\0';
        fgets(disponibil[i].disponibil_ora_max, 50, fp);
        disponibil[i].disponibil_ora_max[strlen(disponibil[i].disponibil_ora_max) - 1] = '\0';
    }
    fclose(fp);
}

void citireOferte(){
    int nr_oferte;
    FILE* fi = fopen("program.txt", "r");
    fscanf(fi, "%d", &nr_oferte);
    fgetc(fi);
    for (int i = 1; i <= nr_oferte; ++i){
        fgets(program[i].tip_consultatie, 50, fi);
        program[i].tip_consultatie[strlen(program[i].tip_consultatie) - 1] = '\0';
    }
    for (int i = 1; i <= nr_oferte; ++i) {
        printf("%s\n", program[i].tip_consultatie);
    }
    fclose(fi);
}

void citireIstoric1(){
    int nr_istoric;
    FILE* fp = fopen("istoric.txt", "r");
    fscanf(fp, "%d", &nr_istoric);
    fgetc(fp);
    for (int i = 1; i <= nr_istoric; ++i){
        fgets(istoric[i].istoric_data, 50, fp);
        istoric[i].istoric_data[strlen(istoric[i].istoric_data) - 1] = '\0';
        fgets(istoric[i].istoric_ora, 50, fp);
        istoric[i].istoric_ora[strlen(istoric[i].istoric_ora) - 1] = '\0';
        fgets(istoric[i].istoric_optiune, 50, fp);
        istoric[i].istoric_optiune[strlen(istoric[i].istoric_optiune) - 1] = '\0';
    }
    fclose(fp);
}

void citireIstoric(){
    int nr_istoric;
    FILE* fp = fopen("istoric.txt", "r");
    fscanf(fp, "%d", &nr_istoric);
    printf("-= ISTORIC =- \n");
    fgetc(fp);
    for (int i = 1; i <= nr_istoric; ++i){
        fgets(istoric[i].istoric_data, 50, fp);
        fgets(istoric[i].istoric_ora, 50, fp);
        fgets(istoric[i].istoric_optiune, 50, fp);
    }
    for (int i = 1; i <= nr_istoric; ++i) {
        printf("%d. %s %s %s\n", i, istoric[i].istoric_data, istoric[i].istoric_ora, istoric[i].istoric_optiune);
    }
    fclose(fp);
}


void writeInFile(int zi, int luna, int an, int nr_program) {
    FILE* fp = fopen("istoric.txt", "w");
    fprintf(fp, "%d\n", nr_program);
    for (int i = 1; i <= nr_program; ++i) {
        fprintf(fp, "%s\n", istoric[i].istoric_data);
        fprintf(fp, "%s\n", istoric[i].istoric_ora);
        fprintf(fp, "%s\n", istoric[i].istoric_optiune);
    }
    fclose(fp);
}


int main()
{

    while (1 == 1) {
        system("cls");
        printf("-= MENIU =-\n");
        printf("1. Oferte\n");
        printf("2. Program\n");
        printf("3. Istoric\n");
        printf("4. Exit\n");

        int choice;
        do {
            printf("Introdu varianta dorita: ");
            scanf("%d", &choice);
        } while (choice < 1 || choice > 4);

        system("cls");

        if (choice == 1) {

            printf("-= OFERTE =-\n");
            citireOferte();
            system("pause");

        } else if (choice == 2) {

            int i = 0;

            while (i == 0) {

                int zi, luna, an;
                int nr = 0;
                char data1[50];
                system("cls");
                printf("Introduceti data(zi.luna.an): ");
                scanf("%d.%d.%d", &zi, &luna, &an);
                sprintf(data1, "%d.%d.%d", zi, luna, an);
                citireDisponibilitate();
                nr = citireNrDisponibilitate(nr);
                int ok = 0, k = 0;
                for (int i = 1; i <= nr; i++){
                    k++;
                    if(strcmp(data1, disponibil[i].disponibil_data) == 0){
                        ok = 1;
                        break;
                    }
                }
                if(verificareData(zi, luna, an) == 0)
                do{
                    system("cls");
                    printf("Data introdusa este incorecta. Introduceti data(zi.luna.an): ");
                    scanf("%d.%d.%d", &zi, &luna, &an);

                } while(verificareData(zi, luna, an) == 0);

                if(verificareData(zi, luna, an) == 1 && ok == 1)
                {
                    system("cls");
                    printf("-=Oferte=- \n");
                    citireOferte();
                    printf("\nInterval orar: %s - %s\n", disponibil[k].disponibil_ora_min, disponibil[k].disponibil_ora_max);
                    printf("0. Back\n");
                    printf("1. Programare\n");
                    int choice2;
                    do {
                    printf("Introdu varianta dorita: ");
                    scanf("%d", &choice2);
                    } while (choice2 < 0 || choice2 > 1);
                    if (choice2 == 0)
                        i = 1;
                    else if (choice2 == 1)
                    {
                        citireIstoric1();
                        int nr_program = 0, a = 0, nr_2;
                        nr_program = citireNrIstoric(a) + 1;
                        printf("Introduceti ora la care doriti sa va programati: ");
                        scanf("%s", istoric[nr_program].istoric_ora);
                        if(strcmp(istoric[nr_program].istoric_ora, disponibil[k].disponibil_ora_min) == -1 && strcmp(istoric[nr_program].istoric_ora, disponibil[k].disponibil_ora_max) == -1){
                            printf("Introduceti tipul de operatie dorit: ");
                            scanf("%s", istoric[nr_program].istoric_optiune);
                            sprintf(istoric[nr_program].istoric_data, "%d.%d.%d", zi, luna, an);
                            //writeInFile(zi, luna, an, nr_program);
                            //printf("Programare realizata cu succes!");
                            int ok_3;
                            ok_3 = verificareIstoric(istoric[nr_program].istoric_data, istoric[nr_program].istoric_ora, istoric[nr_program].istoric_optiune, nr_program);
                            if (ok_3 == 1){
                                writeInFile(zi, luna, an, nr_program);
                                printf("Programare realizata cu succes!");
                            }
                            else
                            printf("Eroare! Programare deja realizata");
                        }
                        else{
                            do{
                                printf("Ora introdusa se afla inafara intervalului orar! Introduceti o alta data:");
                                scanf("%s", istoric[nr_program].istoric_optiune);
                            }while (strcmp(istoric[nr_program].istoric_ora, disponibil[k].disponibil_ora_min) != -1 && strcmp(istoric[nr_program].istoric_ora, disponibil[k].disponibil_ora_max) != -1);
                            printf("Introduceti tipul de operatie dorit: ");
                            scanf("%s", istoric[nr_program].istoric_optiune);
                            sprintf(istoric[nr_program].istoric_data, "%d.%d.%d", zi, luna, an);
                            //writeInFile(zi, luna, an, nr_program);
                            //printf("Programare realizata cu succes!");
                            int ok_3;
                            ok_3 = verificareIstoric(istoric[nr_program].istoric_data, istoric[nr_program].istoric_ora, istoric[nr_program].istoric_optiune, nr_program);
                            if (ok_3 == 1){
                                writeInFile(zi, luna, an, nr_program);
                                printf("Programare realizata cu succes!");
                            }
                            else
                            printf("Eroare! Programare deja realizata");
                        }
                    }

                  }
                  else
                    printf("Cabinetul nu este disponibil in data de %s\n", data1);
                    system("pause");

                i = 1;
            }

        } else if (choice == 3){
            citireIstoric();
            system("pause");

        } else if(choice == 4)
            return 0;
}
    return 0;
}
