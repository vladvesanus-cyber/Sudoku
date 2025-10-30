/* Myslim ze 4/5*/
#include <stdio.h>
#include <string.h>

void v(int i, FILE *sudoku, FILE *hraci, FILE * rieseni);
void h(FILE * rieseni);
void n(FILE *sudoku, FILE *hraci, FILE * rieseni);

int main()
{
    FILE *sudoku;
    FILE *hraci;
    FILE *rieseni;
    char c;
    int i;
    sudoku = fopen("Sudoku.txt", "r");/*Open files*/
    hraci = fopen("RegisterHracov.txt", "r");
    rieseni = fopen("RegisterRieseni.txt", "r");
    scanf("%c %d", &c, &i);  /*read the which function is called*/
    if(c == 'v')
    {
        v(i, sudoku, hraci, rieseni);
    }
    else if(c == 'h')
    {
        h(rieseni);
    }
    else if(c == 'n')
    {
        n(sudoku, hraci, rieseni);
    }
    return 0;
}

void v(int i, FILE *sudoku, FILE *hraci, FILE * rieseni)
{
    if(i == 1)
    {
        char buffer[512]; /*buffer for read a hraci*/
        char *pid_raw;
        char *meno;
        char *krajina;
        char *rok;
        int i;
        char pid_copy[16];/*copy the string pid_raw because we will rewrite buffer*/
        if(!sudoku || !hraci || !rieseni)
        {
            sudoku = fopen("Sudoku.txt", "r");/*If not open then open it*/
            hraci = fopen("RegisterHracov.txt", "r");
            rieseni = fopen("RegisterRieseni.txt", "r");
        }
        if(!sudoku || !hraci || !rieseni) /*Check if every file is open*/
        {
            printf("V1: Neotvorene txt subory.\n");
            return;
        }
        while(fgets(buffer, sizeof(buffer), hraci) != NULL)/*Read a riadok*/ 
        {
            pid_raw = strtok(buffer, "#");/*variable pid is every char in buffer that is limited by first #*/
            meno = strtok(NULL, "#");/*variable the same like pid but start from where pid is ended*/
            krajina = strtok(NULL, "#");
            rok = strtok(NULL, "#");

            strcpy(pid_copy, pid_raw);

            printf("Identifikator: %s\n", pid_copy);/*print the result*/
            printf("Meno a prezvisko: %s\n", meno);
            printf("Krajina: %s\n", krajina);
            printf("Rok: %s\n", rok);
            i = 0;/*counter of vzorkov*/
            rewind(rieseni); /*Go to the start of the file*/
            printf("Vzorka:\n");
            while((fgets(buffer, sizeof(buffer), rieseni) != NULL) && i < 10)/*read from rieseni*/
            {
                char buffer_copy[512];/*Make copy of bufer because strtok cut buffer to pid to compare*/
                char *pd;

                strcpy(buffer_copy, buffer);
                strtok(buffer, "#");
                pd = strtok(NULL, "#");

                if (strcmp(pid_copy, pd) == 0)
                {
                    printf("\t%s", buffer_copy);
                    i++;          
                }
            }
            printf("\n");/*The gap between players*/
        }
    }
    else if(i == 2)
    {
        
    }
}

void h(FILE * rieseni)
{
    char s[9];
    char buffer[512];/*buffer for reading the rieseni*/
    FILE *vystup;
    scanf("%s", s);/*read SID*/
    if (s[0] != 'S' || s[1] != 'I' || s[2] != 'D' ||
    s[3] < 'A' || s[3] > 'Z' ||
    s[4] < '0' || s[4] > '9' ||
    s[5] < '0' || s[5] > '9' ||
    s[6] < '0' || s[6] > '9' ||
    s[7] < '0' || s[7] > '9')/* check if input is right*/
    {
        printf("H: Nespravny vstup.");
        return;
    }
    if (rieseni == NULL)/*check if rieseni is opened*/ 
    {
        printf("H: Neotvoreny txt subor.\n");
        return;
    }
    vystup = fopen("Vystup_H.txt", "w");/*open new file for write results*/
    if(!vystup)
    {
        printf("H: Neotvoreny txt subor.\n");
        return;
    }
    rewind(rieseni);/*go to the start of file*/
    while(fgets(buffer, sizeof(buffer), rieseni) != NULL)/*read the rieseni*/
    {
        char *sid;
        sid = strstr(buffer, s);/*search the sid in buffer(return the string which is the same(pointer))*/
        if(sid)/*check if sid isnt empty(check if this pointer != NULL)*/
        {
            fprintf(vystup, "%s", buffer);
        }
    }
    fclose(vystup);/*close file*/
    printf("H: Uspesne vytvoreny sumar.\n");
}

void n(FILE *sudoku, FILE *hraci, FILE * rieseni)
{
    if (sudoku == NULL || hraci == NULL || rieseni == NULL)
    {
        printf("N:Neotvoreny subor.\n");
        return;
    }
    
}