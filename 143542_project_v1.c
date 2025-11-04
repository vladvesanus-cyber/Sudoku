/* Myslim ze 4/5*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void v(int i, FILE *sudoku, FILE *hraci, FILE * rieseni);
void h(FILE * rieseni);
void n(FILE *sudoku, FILE *hraci, FILE * rieseni,char ***sid_s,
char ***riesen_s, char ***pid_h ,char ***meno_h ,char ***krajina_h, 
char ***rok_h, char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int *count_s, int *count_h, int *count_r);
void q(int i, char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int *count_r);
void w(char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int *count_r);

int main()
{
    FILE *sudoku;
    FILE *hraci;
    FILE *rieseni;
    char **sid_s = NULL; 
    char **riesen_s = NULL;
    char **pid_h = NULL;
    char **meno_h = NULL;
    char **krajina_h = NULL;
    char **rok_h = NULL;
    char **gid_r = NULL;
    char **pid_r = NULL;
    char **sid_r = NULL;
    char **date_r = NULL;
    int *trvanie_r = NULL;
    int count_s = 0; 
    int count_h = 0;
    int count_r = 0;
    char c;
    int i;
    sudoku = fopen("Sudoku.txt", "r");/* Open files */
    hraci = fopen("RegisterHracov.txt", "r");
    rieseni = fopen("RegisterRieseni.txt", "r");

    scanf(" %c %d", &c, &i); /* read the which function is called */
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
        n(sudoku, hraci, rieseni, &sid_s,
        &riesen_s, &pid_h, &meno_h, &krajina_h, 
        &rok_h, &gid_r, &pid_r, &sid_r, 
        &date_r, &trvanie_r, &count_s, &count_h, &count_r);
    }
    else if(c == 'q')
    {
        q(i, &gid_r, &pid_r, &sid_r, 
        &date_r, &trvanie_r, &count_r);
    }
    else if(c == 'w')
    {
        w(&gid_r, &pid_r, &sid_r, 
        &date_r, &trvanie_r, &count_r);
    }
    return 0;
}

void v(int i, FILE *sudoku, FILE *hraci, FILE * rieseni)
{
    if(i == 1)
    {
        char buffer[512]; /* buffer for read a hraci */
        char *pid_raw;
        char *meno;
        char *krajina;
        char *rok;
        int j; 
        char pid_copy[16];
        char clean_pid_copy[16]; 
        char buffer_copy[512]; 
        char *pd; 
        size_t len;
        size_t pid_len;
        
        if(!sudoku || !hraci || !rieseni)
        {
            sudoku = fopen("Sudoku.txt", "r");/* If not open then open it */
            hraci = fopen("RegisterHracov.txt", "r");
            rieseni = fopen("RegisterRieseni.txt", "r");
        }
        if(!sudoku || !hraci || !rieseni) /* Check if every file is open */
        {
            printf("V1: Neotvorene txt subory.\n");
            return;
        }
        while(fgets(buffer, sizeof(buffer), hraci) != NULL)/* Read a riadok */
        {
            pid_raw = strtok(buffer, "#");/* variable pid is every char in buffer that is limited by first # */
            meno = strtok(NULL, "#");/* variable the same like pid but start from where pid is ended */
            krajina = strtok(NULL, "#");
            rok = strtok(NULL, "#");

            /* copy the string pid_raw because we will rewrite buffer */
            strcpy(pid_copy, pid_raw);

            printf("Identifikator: %s\n", pid_copy);/* print the result */
            printf("Meno a prezvisko: %s\n", meno);
            printf("Krajina: %s\n", krajina);
            printf("Rok: %s\n", rok);
            j = 0; /* counter of vzorkov */
            rewind(rieseni); /* Go to the start of the file */
            printf("Vzorka:\n");
            while((fgets(buffer, sizeof(buffer), rieseni) != NULL) && j < 10)/* read from rieseni */
            {
                /* Make copy of bufer because strtok cut buffer to pid to compare */ 
                strcpy(buffer_copy, buffer);
                strtok(buffer, "#");
                pd = strtok(NULL, "#");
                
                if (pd != NULL) {
                    len = strlen(pd);
                    while (len > 0 && (pd[len - 1] == ' ' || pd[len - 1] == '\n' || pd[len - 1] == '\r')) {
                        pd[--len] = '\0';
                    }
                }
                
                strcpy(clean_pid_copy, pid_copy);
                pid_len = strlen(clean_pid_copy);
                while (pid_len > 0 && (clean_pid_copy[pid_len - 1] == ' ' || clean_pid_copy[pid_len - 1] == '\n' || clean_pid_copy[pid_len - 1] == '\r')) {
                    clean_pid_copy[--pid_len] = '\0';
                }

                if (pd != NULL && strcmp(clean_pid_copy, pd) == 0)
                {
                    printf("\t%s", buffer_copy);
                    j++;
                }
            }
            printf("\n");/* The gap between players */
        }
    }
    else if(i == 2)
    {
        
    }
}

void h(FILE * rieseni)
{
    char s[9];
    char buffer[512];/* buffer for reading the rieseni */
    FILE *vystup;
    char *sid; 
    
    scanf("%s", s);/* read SID */
    if (s[0] != 'S' || s[1] != 'I' || s[2] != 'D' ||
    s[3] < 'A' || s[3] > 'Z' ||
    s[4] < '0' || s[4] > '9' ||
    s[5] < '0' || s[5] > '9' ||
    s[6] < '0' || s[6] > '9' ||
    s[7] < '0' || s[7] > '9')/* check if input is right */
    {
        printf("H: Nespravny vstup.");
        return;
    }
    if (rieseni == NULL)/* check if rieseni is opened */
    {
        printf("H: Neotvoreny txt subor.\n");
        return;
    }
    vystup = fopen("Vystup_H.txt", "w");/* open new file for write results */
    if(!vystup)
    {
        printf("H: Neotvoreny txt subor.\n");
        return;
    }
    rewind(rieseni);/* go to the start of file */
    while(fgets(buffer, sizeof(buffer), rieseni) != NULL)/*read the rieseni*/
    {
        sid = strstr(buffer, s);/*search the sid in buffer(return the string which is the same(pointer))*/
        if(sid)/*check if sid isnt empty(check if this pointer != NULL)*/
        {
            fprintf(vystup, "%s", buffer);
        }
    }
    fclose(vystup);/*close file*/
    printf("H: Uspesne vytvoreny sumar.\n");
}

void n(FILE *sudoku, FILE *hraci, FILE * rieseni,char ***sid_s,
char ***riesen_s, char ***pid_h ,char ***meno_h ,char ***krajina_h, 
char ***rok_h, char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int *count_s, int *count_h, int *count_r)
{
    char buffer[512];
    int i;
    int j; 

    char *raw_sid_s;
    char *raw_reseni_s;
    char temp_sid_s[16];
    char temp_reseni_s[500];

    char *pid_raw_h;
    char *meno_raw_h;
    char *krajina_raw_h;
    char *rok_raw_h;
    char temp_pid_h[16];
    char temp_meno_h[100];
    char temp_krajina_h[100];
    char temp_rok_h[10];

    char *gid_raw_r;
    char *pid_raw_r;
    char *sid_raw_r;
    char *date_raw_r;
    char *m_raw_r;
    char *s_raw_r;
    char temp_gid_r[16];
    char temp_pid_r[16];
    char temp_sid_r[16];
    char temp_date_r[16];
    char temp_m_r[10];
    char temp_s_r[10];
    int m_val;
    int s_val;

    if (sudoku == NULL || hraci == NULL || rieseni == NULL)
    {
        printf("N:Neotvoreny subor.\n");
        return;
    }
    if (*sid_s != NULL) {
        for (j = 0; j < *count_s; j++) {
            free((*sid_s)[j]); 
            free((*riesen_s)[j]);
        }
        free(*sid_s);
        free(*riesen_s);
        *sid_s = NULL;
        *riesen_s = NULL;
    }

    if (*pid_h != NULL) {
        for (j = 0; j < *count_h; j++) {
            free((*pid_h)[j]); 
            free((*meno_h)[j]); 
            free((*krajina_h)[j]); 
            free((*rok_h)[j]); 
        }
        free(*pid_h);
        free(*meno_h);
        free(*krajina_h);
        free(*rok_h);
        *pid_h = NULL;
        *meno_h = NULL;
        *krajina_h = NULL;
        *rok_h = NULL;
    }

    if (*gid_r != NULL) {
        for (j = 0; j < *count_r; j++) {
            free((*gid_r)[j]); 
            free((*pid_r)[j]); 
            free((*sid_r)[j]); 
            free((*date_r)[j]); 
        }
        free(*gid_r);
        free(*pid_r);
        free(*sid_r);
        free(*date_r);
        free(*trvanie_r);
        *gid_r = NULL;
        *pid_r = NULL;
        *sid_r = NULL;
        *date_r = NULL;
        *trvanie_r = NULL;
    }
    
    /* Start read files from the start */
    rewind(sudoku);
    rewind(hraci);
    rewind(rieseni);
    i = 0;
    while(fgets(buffer, sizeof(buffer), sudoku) != NULL)
    {
        raw_sid_s = strtok(buffer, "#");
        raw_reseni_s = strtok(NULL, "#"); 
        
        if (raw_sid_s == NULL || raw_reseni_s == NULL) continue;

        strcpy(temp_sid_s, raw_sid_s);
        strcpy(temp_reseni_s, raw_reseni_s);
        
        *sid_s = realloc(*sid_s, (i + 1) * sizeof(char *));
        *riesen_s = realloc(*riesen_s, (i + 1) * sizeof(char *));
        
        (*sid_s)[i] = malloc(strlen(temp_sid_s) + 1); 
        strcpy((*sid_s)[i], temp_sid_s);
        
        (*riesen_s)[i] = malloc(strlen(temp_reseni_s) + 1); 
        strcpy((*riesen_s)[i], temp_reseni_s);
        i++;
    }
    *count_s = i;
    i = 0;
    while(fgets(buffer, sizeof(buffer), hraci) != NULL)
    {
        pid_raw_h = strtok(buffer, "#");
        meno_raw_h = strtok(NULL, "#");
        krajina_raw_h = strtok(NULL, "#");
        rok_raw_h = strtok(NULL, "#");
        
        if (pid_raw_h == NULL || meno_raw_h == NULL || krajina_raw_h == NULL || rok_raw_h == NULL) continue;

        strcpy(temp_pid_h, pid_raw_h);
        strcpy(temp_meno_h, meno_raw_h);
        strcpy(temp_krajina_h, krajina_raw_h);
        strcpy(temp_rok_h, rok_raw_h);

        *pid_h = realloc(*pid_h, (i + 1) * sizeof(char*));
        *meno_h = realloc(*meno_h, (i + 1) * sizeof(char*));
        *krajina_h = realloc(*krajina_h, (i + 1) * sizeof(char*));
        *rok_h = realloc(*rok_h, (i + 1) * sizeof(char*));

        (*pid_h)[i] = malloc(strlen(temp_pid_h) + 1); 
        strcpy((*pid_h)[i], temp_pid_h);

        (*meno_h)[i] = malloc(strlen(temp_meno_h) + 1); 
        strcpy((*meno_h)[i], temp_meno_h);
        
        (*krajina_h)[i] = malloc(strlen(temp_krajina_h) + 1); 
        strcpy((*krajina_h)[i], temp_krajina_h);

        (*rok_h)[i] = malloc(strlen(temp_rok_h) + 1); 
        strcpy((*rok_h)[i], temp_rok_h);
        i++;
    }
    *count_h = i;
    i = 0;
    while(fgets(buffer, sizeof(buffer), rieseni) != NULL)
    {
        gid_raw_r = strtok(buffer, "#");
        pid_raw_r = strtok(NULL, "#");
        sid_raw_r = strtok(NULL, "#");
        date_raw_r = strtok(NULL, "#");
        m_raw_r = strtok(NULL, "#");
        s_raw_r = strtok(NULL, "#");
        
        if (gid_raw_r == NULL || pid_raw_r == NULL || sid_raw_r == NULL || date_raw_r == NULL || m_raw_r == NULL || s_raw_r == NULL) continue;

        strcpy(temp_gid_r, gid_raw_r);
        strcpy(temp_pid_r, pid_raw_r);
        strcpy(temp_sid_r, sid_raw_r);
        strcpy(temp_date_r, date_raw_r);
        strcpy(temp_m_r, m_raw_r);
        strcpy(temp_s_r, s_raw_r);
        
        *gid_r = realloc(*gid_r, (i + 1) * sizeof(char*));
        *pid_r = realloc(*pid_r, (i + 1) * sizeof(char*));
        *sid_r = realloc(*sid_r, (i + 1) * sizeof(char*));
        *date_r = realloc(*date_r, (i + 1) * sizeof(char*));
        *trvanie_r = realloc(*trvanie_r, (i + 1) * sizeof(int));

        (*gid_r)[i] = malloc(strlen(temp_gid_r) + 1); 
        strcpy((*gid_r)[i], temp_gid_r);

        (*pid_r)[i] = malloc(strlen(temp_pid_r) + 1); 
        strcpy((*pid_r)[i], temp_pid_r);
        
        (*sid_r)[i] = malloc(strlen(temp_sid_r) + 1); 
        strcpy((*sid_r)[i], temp_sid_r);

        (*date_r)[i] = malloc(strlen(temp_date_r) + 1); 
        strcpy((*date_r)[i], temp_date_r);

        m_val = atoi(temp_m_r);
        s_val = atoi(temp_s_r);

        (*trvanie_r)[i] = m_val * 60 + s_val; 
        i++;
    }
    *count_r = i;
}

void q(int i, char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int *count_r)
{
    int j;
    char s[16];
    int n, m, sec;
    char **tm_gid, **tm_pid, **tm_sid, **tm_date;
    int *tm_trvanie; 
    if (*gid_r == NULL)
    {
        printf("Q: Polia nie su vytvorene.\n");
        return;
    }
    if (i > *count_r)
    {
        n = *count_r;
    }
    else
    {
        n = i - 1;
    }
    (*count_r)++; 

    tm_gid = realloc(*gid_r, (*count_r) * sizeof(char*));
    tm_pid = realloc(*pid_r, (*count_r) * sizeof(char*));
    tm_sid = realloc(*sid_r, (*count_r) * sizeof(char*));
    tm_date = realloc(*date_r, (*count_r) * sizeof(char*));
    tm_trvanie = realloc(*trvanie_r, (*count_r) * sizeof(int));

    if(tm_gid != NULL && tm_pid != NULL && tm_sid != NULL && tm_date != NULL && tm_trvanie != NULL)
    {
        *gid_r = tm_gid;
        *pid_r = tm_pid;
        *sid_r = tm_sid;
        *date_r = tm_date;
        *trvanie_r = tm_trvanie;
    
        for (j = (*count_r) - 1; j > n; j--) 
        {
            (*gid_r)[j] = (*gid_r)[j - 1]; 
            (*pid_r)[j] = (*pid_r)[j - 1]; 
            (*sid_r)[j] = (*sid_r)[j - 1]; 
            (*date_r)[j] = (*date_r)[j - 1]; 
            (*trvanie_r)[j] = (*trvanie_r)[j - 1]; 
        }
        while(1)
        {
            scanf("%s", s);
            if ( strlen(s) == 7 && s[0] == 'G' && s[1] == 'I' && s[2] == 'D' &&
            s[3] >= 'a' && s[3] <= 'z' && 
            s[4] >= '0' && s[4] <= '9' && 
            s[5] >= '0' && s[5] <= '9' && 
            s[6] >= '0' && s[6] <= '9') 
            {
            (*gid_r)[n] = malloc(strlen(s) + 1); 
            break;
            }
            printf("Q: nespravny format vstupu, zadaj znova:");
        }
            strcpy((*gid_r)[n], s); 

        while(1)
        {
            scanf("%s", s);
            if (strlen(s) == 9 && s[0] == 'P' && s[1] == 'I' && s[2] == 'D' &&
            s[3] >= 'a' && s[3] <= 'z' &&
            s[4] >= '0' && s[4] <= '9' && 
            s[5] >= '0' && s[5] <= '9' && 
            s[6] >= '0' && s[6] <= '9' && 
            s[7] >= '0' && s[7] <= '9' && 
            s[8] >= '0' && s[8] <= '9') 
            {
            (*pid_r)[n] = malloc(strlen(s) + 1); 
            break;
            }
            printf("Q: nespravny format vstupu, zadaj znova:");
        }
            strcpy((*pid_r)[n], s); 

        while(1)
        {
            scanf("%s", s);
            if (strlen(s) == 8 && s[0] == 'S' && s[1] == 'I' && s[2] == 'D' &&
            s[3] >= 'A' && s[3] <= 'Z' &&
            s[4] >= '0' && s[4] <= '9' && 
            s[5] >= '0' && s[5] <= '9' && 
            s[6] >= '0' && s[6] <= '9' && 
            s[7] >= '0' && s[7] <= '9') 
            {
            (*sid_r)[n] = malloc(strlen(s) + 1); 
            break;
            }
            printf("Q: nespravny format vstupu, zadaj znova:");
        }
            strcpy((*sid_r)[n], s); 

        while(1)
        {
            scanf("%s %d %d", s, &m, &sec);
            if (strlen(s) == 8 && s[0] >= '0' && s[0] <= '9' && 
            s[1] >= '0' && s[1] <= '9' && 
            s[2] >= '0' && s[2] <= '9' && 
            s[3] >= '0' && s[3] <= '9' && 
            s[4] >= '0' && s[4] <= '9' && 
            s[5] >= '0' && s[5] <= '9' && 
            s[6] >= '0' && s[6] <= '9' && 
            s[7] >= '0' && s[7] <= '9'&& 
            m >= 0 && sec >= 0 && sec < 60 )
            {
                (*date_r)[n] = malloc(strlen(s) + 1); 
                break;
            }
            printf("Q: nespravny format vstupu, zadaj znova:");
        }
            strcpy((*date_r)[n], s); 

            (*trvanie_r)[n] = m * 60 + sec; 
    }
}

void w(char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int *count_r)
{
    char s[16];
    int j, i, total;
    char **tm_gid, **tm_pid, **tm_sid, **tm_date;
    int *tm_trvanie; 
    
    if(*pid_r == NULL)
    {
        printf("W: Polia nie su vytvorene.\n");
        return; 
    }
    scanf("%s", s);

    if (!(strlen(s) == 9 && s[0] == 'P' && s[1] == 'I' && s[2] == 'D' &&
        s[3] >= 'a' && s[3] <= 'z' &&
        s[4] >= '0' && s[4] <= '9' && 
        s[5] >= '0' && s[5] <= '9' && 
        s[6] >= '0' && s[6] <= '9' && 
        s[7] >= '0' && s[7] <= '9' && 
        s[8] >= '0' && s[8] <= '9')) 
    {
        printf("W: Nespravny format vstupu.\n");
        return;
    }
    
    total = 0;
    for(j = 0; j < *count_r; j++) 
    {
        if(strcmp((*pid_r)[j],s) == 0) 
        {
            free((*gid_r)[j]); 
            free((*pid_r)[j]); 
            free((*sid_r)[j]); 
            free((*date_r)[j]); 
            for(i = j; i < *count_r - 1; i++)
            {
                (*gid_r)[i] = (*gid_r)[i + 1]; 
                (*pid_r)[i] = (*pid_r)[i + 1]; 
                (*sid_r)[i] = (*sid_r)[i + 1]; 
                (*date_r)[i] = (*date_r)[i + 1]; 
                (*trvanie_r)[i] = (*trvanie_r)[i + 1]; 
            }
            (*count_r)--; 
            total++;
            j--; 
        }
    }
    tm_gid = realloc(*gid_r, (*count_r) * sizeof(char*));
    tm_pid = realloc(*pid_r, (*count_r) * sizeof(char*));
    tm_sid = realloc(*sid_r, (*count_r) * sizeof(char*));
    tm_date = realloc(*date_r, (*count_r) * sizeof(char*));
    tm_trvanie = realloc(*trvanie_r, (*count_r) * sizeof(int));

    if(tm_gid != NULL && tm_pid != NULL && tm_sid != NULL && tm_date != NULL && tm_trvanie != NULL)
    {
        *gid_r = tm_gid;
        *pid_r = tm_pid;
        *sid_r = tm_sid;
        *date_r = tm_date;
        *trvanie_r = tm_trvanie;
    }
    printf("W: Vymazalo sa : %d zaznamov !\n", total);
}