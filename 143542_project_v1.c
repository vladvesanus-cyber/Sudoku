// Myslim ze 4/5
#include <stdio.h>
#include <string.h>

void v(int n, FILE *sudoku, FILE *hraci, FILE * rieseni);
void h(FILE * rieseni);

int main()
{
    FILE *sudoku = fopen("Sudoku.txt", "r");// Open files
    FILE *hraci = fopen("RegisterHracov.txt", "r");
    FILE *rieseni = fopen("RegisterRieseni.txt", "r");
    char c;
    int n;
    scanf("%c %d", &c, &n);  //read the which function is called
    if(c == 'v')
    {
        v(n, sudoku, hraci, rieseni);
    }
    else if(c == 'h')
    {
        h(rieseni);
    }
}

void v(int n, FILE *sudoku, FILE *hraci, FILE * rieseni)
{
    if(n == 1)
    {
        if(!sudoku || !hraci || !rieseni)
        {
            sudoku = fopen("Sudoku.txt", "r");// If not open then open it
            hraci = fopen("RegisterHracov.txt", "r");
            rieseni = fopen("RegisterRieseni.txt", "r");
        }
        if(!sudoku || !hraci || !rieseni) // Check if every file is open
        {
            printf("V1: Neotvorene txt subory.\n");
            return;
        }
        char buffer[512]; //buffer for read a hraci
        while(fgets(buffer, sizeof(buffer), hraci) != NULL)//Read a riadok 
        {
            char *pid_raw = strtok(buffer, "#");//variable pid is every char in buffer that is limited by first #
            char *meno = strtok(NULL, "#");//variable the same like pid but start from where pid is ended
            char *krajina = strtok(NULL, "#");
            char *rok = strtok(NULL, "#");

            char pid_copy[16];//copy the string pid_raw because we will rewrite buffer
            strcpy(pid_copy, pid_raw);

            printf("Identifikator: %s\n", pid_copy);//print the result
            printf("Meno a prezvisko: %s\n", meno);
            printf("Krajina: %s\n", krajina);
            printf("Rok: %s\n", rok);
            int i = 0;//counter of vzorkov
            rewind(rieseni); //Go to the start of the file
            printf("Vzorka:\n");
            while((fgets(buffer, sizeof(buffer), rieseni) != NULL) && i < 10)//read from rieseni
            {
                char buffer_copy[512];//Make copy of bufer because strtok cut buffer to pid to compare 
                strcpy(buffer_copy, buffer);
                char *gid = strtok(buffer, "#");
                char *pd = strtok(NULL, "#");

                if (strcmp(pid_copy, pd) == 0)
                {
                    printf("\t%s", buffer_copy);
                    i++;          
                }
            }
            printf("\n");//The gap between players
        }
    }
    else if(n == 2)
    {
        
    }
}

void h(FILE * rieseni)
{
    char s[9];
    scanf("%s", s);//read SID
    if (s[0] != 'S' || s[1] != 'I' || s[2] != 'D' ||
    s[3] < 'A' || s[3] > 'Z' ||
    s[4] < '0' || s[4] > '9' ||
    s[5] < '0' || s[5] > '9' ||
    s[6] < '0' || s[6] > '9' ||
    s[7] < '0' || s[7] > '9')// check if input is right
    {
        printf("H: Nespravny vstup.");
        return;
    }
    if (rieseni == NULL)//check if rieseni is opened 
    {
        printf("H: Neotvoreny txt subor.\n");
        return;
    }
    FILE *vystup = fopen("Vystup_H.txt", "w");//open new file for write results
    if(!vystup)
    {
        printf("H: Neotvoreny txt subor.\n");
        return;
    }
    rewind(rieseni);//go to the start of file
    char buffer[512];//buffer for reading the rieseni
    while(fgets(buffer, sizeof(buffer), rieseni) != NULL)//read the rieseni
    {
        char *sid = strstr(buffer, s);//search the sid in buffer(return the string which is the same(pointer))
        if(sid)//check if sid isnt empty(check if this pointer != NULL)
        {
            fprintf(vystup, "%s", buffer);
        }
    }
    fclose(vystup);//close file
    printf("H: Uspesne vytvoreny sumar.\n");
}