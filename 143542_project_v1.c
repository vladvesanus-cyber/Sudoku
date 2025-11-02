/* Myslim ze 4/5*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void v(int i, FILE *sudoku, FILE *hraci, FILE * rieseni);
void h(FILE * rieseni);
void n(FILE *sudoku, FILE *hraci, FILE * rieseni);
void q(int i);

char **sid_s;
char **riesen_s;
char **pid_h;
char **meno_h;
char **krajina_h;
char **rok_h;
char **gid_r;
char **pid_r;
char **sid_r;
char **date_r;
int *trvanie_r;
int count_s;
int count_h;
int count_r;

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
    else if(c == 'q')
    {
        q(i);
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
    char buffer[512];
    int i;
    if (sudoku == NULL || hraci == NULL || rieseni == NULL)
    {
        printf("N:Neotvoreny subor.\n");
        return;
    }
    if (sid_s != NULL) {
        int j;
        for (j = 0; j < count_s; j++) {
            free(sid_s[j]);
            free(riesen_s[j]);
        }
        free(sid_s);
        free(riesen_s);
        sid_s = NULL;
        riesen_s = NULL;
    }

    if (pid_h != NULL) {
        int j;
        for (j = 0; j < count_h; j++) {
            free(pid_h[j]);
            free(meno_h[j]);
            free(krajina_h[j]);
            free(rok_h[j]);
        }
        free(pid_h);
        free(meno_h);
        free(krajina_h);
        free(rok_h);
        pid_h = NULL;
        meno_h = NULL;
        krajina_h = NULL;
        rok_h = NULL;
    }

    if (gid_r != NULL) {
        int j;
        for (j = 0; j < count_r; j++) {
            free(gid_r[j]);
            free(pid_r[j]);
            free(sid_r[j]);
            free(date_r[j]);
        }
        free(gid_r);
        free(pid_r);
        free(sid_r);
        free(date_r);
        free(trvanie_r);
        gid_r = NULL;
        pid_r = NULL;
        sid_r = NULL;
        date_r = NULL;
        trvanie_r = NULL;
    }  
    /*Start read files from the start*/
    rewind(sudoku);
    rewind(hraci);
    rewind(rieseni);
    i = 0;
    while(fgets(buffer, sizeof(buffer), sudoku) != NULL)
    {
        char *raw_sid;
        char *raw_reseni;

        raw_sid = strtok(buffer, "#");
        raw_reseni = strtok(NULL, "#"); 
        
        sid_s = realloc(sid_s, (i + 1) * sizeof(char *));
        riesen_s = realloc(riesen_s, (i + 1) * sizeof(char *));
        
        sid_s[i] = malloc(strlen(raw_sid) + 1);
        strcpy(sid_s[i], raw_sid);
        
        riesen_s[i] = malloc(strlen(raw_reseni) + 1);
        strcpy(riesen_s[i], raw_reseni);
        i++;
    }
    count_s = i;
    i = 0;
    while(fgets(buffer, sizeof(buffer), hraci) != NULL)
    {
        char *pid_raw;
        char *meno_raw;
        char *krajina_raw;
        char *rok_raw;
        
        pid_raw = strtok(buffer, "#");/*variable pid is every char in buffer that is limited by first #*/
        meno_raw = strtok(NULL, "#");/*variable the same like pid but start from where pid is ended*/
        krajina_raw = strtok(NULL, "#");
        rok_raw = strtok(NULL, "#");
        
        pid_h = realloc(pid_h, (i + 1) * sizeof(char*));
        meno_h = realloc(meno_h, (i + 1) * sizeof(char*));
        krajina_h = realloc(krajina_h, (i + 1) * sizeof(char*));
        rok_h = realloc(rok_h, (i + 1) * sizeof(char*));

        pid_h[i] = malloc(strlen(pid_raw) + 1);
        strcpy(pid_h[i], pid_raw);

        meno_h[i] = malloc(strlen(meno_raw) + 1);
        strcpy(meno_h[i], meno_raw);
        
        krajina_h[i] = malloc(strlen(krajina_raw) + 1);
        strcpy(krajina_h[i], krajina_raw);

        rok_h[i] = malloc(strlen(rok_raw) + 1);
        strcpy(rok_h[i], rok_raw);
        i++;
    }
    count_h = i;
    i = 0;
    while(fgets(buffer, sizeof(buffer), rieseni) != NULL)
    {
        char *gid_raw;
        char *pid_raw;
        char *sid_raw;
        char *date_raw;
        char *m_raw;
        char *s_raw;
        int m, s;
        
        gid_raw = strtok(buffer, "#");/*variable pid is every char in buffer that is limited by first #*/
        pid_raw = strtok(NULL, "#");/*variable the same like pid but start from where pid is ended*/
        sid_raw = strtok(NULL, "#");
        date_raw = strtok(NULL, "#");
        m_raw = strtok(NULL, "#");
        s_raw = strtok(NULL, "#");
        
        gid_r = realloc(gid_r, (i + 1) * sizeof(char*));
        pid_r = realloc(pid_r, (i + 1) * sizeof(char*));
        sid_r = realloc(sid_r, (i + 1) * sizeof(char*));
        date_r = realloc(date_r, (i + 1) * sizeof(char*));
        trvanie_r = realloc(trvanie_r, (i + 1) * sizeof(int));

        gid_r[i] = malloc(strlen(gid_raw) + 1);
        strcpy(gid_r[i], gid_raw);

        pid_r[i] = malloc(strlen(pid_raw) + 1);
        strcpy(pid_r[i], pid_raw);
        
        sid_r[i] = malloc(strlen(sid_raw) + 1);
        strcpy(sid_r[i], sid_raw);

        date_r[i] = malloc(strlen(date_raw) + 1);
        strcpy(date_r[i], date_raw);

        m = atoi(m_raw);
        s = atoi(s_raw);

        trvanie_r[i] = m * 60 + s;
        i++;
    }
    count_r = i;
}

void q(int i)
{
    int j;
    char s[16];
    int n, m, sec;
    if (gid_r == NULL)
    {
        printf("Q: Polia nie su vytvorene.\n");
        return;
    }
    if (i > count_r)
    {
        n = count_r;
    }
    else
    {
        n = i - 1;
    }
    count_r++;

    gid_r = realloc(gid_r, (count_r) * sizeof(char*));
    pid_r = realloc(pid_r, (count_r) * sizeof(char*));
    sid_r = realloc(sid_r, (count_r) * sizeof(char*));
    date_r = realloc(date_r, (count_r) * sizeof(char*));
    trvanie_r = realloc(trvanie_r, count_r * sizeof(int));
    
    for (j = count_r - 1; j > n; j--)
    {
        gid_r[j] = gid_r[j - 1];
        pid_r[j] = pid_r[j - 1];
        sid_r[j] = sid_r[j - 1];
        date_r[j] = date_r[j - 1];
        trvanie_r[j] = trvanie_r[j - 1];
    }
    while(1)
    {
        scanf("%s", s);
        if ( strlen(s) == 7 && s[0] == 'G' && s[1] == 'I' && s[2] == 'D' &&
        s[3] > 'a' && s[3] < 'z' &&
        s[4] > '0' && s[4] < '9' &&
        s[5] > '0' && s[5] < '9' &&
        s[6] > '0' && s[6] < '9')
        {
        gid_r[n] = malloc(strlen(s) + 1);
        break;
        }
        printf("Q: nespravny format vstupu, zadaj znova:");
    }
        strcpy(gid_r[n], s);

    while(1)
    {
        scanf("%s", s);
        if (strlen(s) == 9 && s[0] == 'P' && s[1] == 'I' && s[2] == 'D' &&
        s[3] > 'a' && s[3] < 'z' &&
        s[4] > '0' && s[4] < '9' &&
        s[5] > '0' && s[5] < '9' &&
        s[6] > '0' && s[6] < '9' &&
        s[7] > '0' && s[7] < '9'&&
        s[8] > '0' && s[8] < '9')
        {
        pid_r[n] = malloc(strlen(s) + 1);
        break;
        }
        printf("Q: nespravny format vstupu, zadaj znova:");
    }
        strcpy(pid_r[n], s);

    while(1)
    {
        scanf("%s", s);
        if (strlen(s) == 8 && s[0] == 'S' && s[1] == 'I' && s[2] == 'D' &&
        s[3] > 'A' && s[3] < 'Z' &&
        s[4] > '0' && s[4] < '9' &&
        s[5] > '0' && s[5] < '9' &&
        s[6] > '0' && s[6] < '9' &&
        s[7] > '0' && s[7] < '9')
        {
        sid_r[n] = malloc(strlen(s) + 1);
        break;
        }
        printf("Q: nespravny format vstupu, zadaj znova:");
    }
        strcpy(sid_r[n], s);

    while(1)
    {
        scanf("%s %d %d", s, &m, &sec);
        if (strlen(s) == 8 && s[0] > '0' && s[0] < '9' &&
        s[1] > '0' && s[1] < '9' &&
        s[2] > '0' && s[2] < '9' &&
        s[3] > '0' && s[3] < '9' &&
        s[4] > '0' && s[4] < '9' &&
        s[5] > '0' && s[5] < '9' &&
        s[6] > '0' && s[6] < '9' &&
        s[7] > '0' && s[7] < '9'&& 
        m >= 0 && sec >= 0 && sec < 60 )
        {
            date_r[n] = malloc(strlen(s) + 1);
            break;
        }
        printf("Q: nespravny format vstupu, zadaj znova:");
    }
        strcpy(date_r[n], s);

        trvanie_r[n] = m * 60 + sec;
}