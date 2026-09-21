/*
 * Sudoku Game Records Manager
 *
 * A command-driven C program that manages three linked datasets loaded from
 * text files: sudoku puzzles/solutions, registered players, and individual
 * game records (which player solved which puzzle, when, and how fast).
 *
 * The program reads single-character commands from stdin and dispatches to
 * one of the functions below. Two parallel data representations are used
 * on purpose, as required by the assignment:
 *   - dynamic arrays (realloc-based) for the raw file data
 *   - singly linked lists (HRACI_DATA / RIESENI_DATA) built from those arrays
 *
 * See README.md for the full command reference and build/run instructions.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct rieseni_data{
    char *SID;
    char NarHry;
    char *GID;
    char NarSut;
    char *DatHry;
    int Trvanie;
    struct rieseni_data *next;
}RIESENI_DATA;

typedef struct hraci_data{
    char *PID;
    char *Idendita;
    char *Krajina;
    int RokNar;
    RIESENI_DATA **Riesenia;
    int pocet_rieseni;
    struct hraci_data *next;
}HRACI_DATA;

void print_players_with_sample_solutions(FILE **sudoku, FILE **hraci, FILE **rieseni);
void export_solutions_by_sid(FILE *rieseni);
void load_arrays_from_files(FILE *sudoku, FILE *hraci, FILE *rieseni,char ***sid_s,
char ***riesen_s, char ***pid_h ,char ***meno_h ,char ***krajina_h, 
char ***rok_h, char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int *count_s, int *count_h, int *count_r);
void insert_solution_record(int i, char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int *count_r);
void delete_solution_records_by_pid(char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int *count_r);
void generate_puzzle_with_gaps(char ***sid_s, char ***riesen_s, int *count_s);
void print_players_with_solutions_arrays(char ***pid_h ,char ***meno_h ,char ***krajina_h, 
char ***rok_h, char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int *count_h, int *count_r);
void build_linked_lists_from_arrays(FILE *sudoku, FILE *hraci, FILE *rieseni, HRACI_DATA **linked_hraci, RIESENI_DATA **linked_rieseni);
void add_player_to_list(HRACI_DATA **linked_hraci);
void delete_solution_by_gid(HRACI_DATA **linked_hraci, RIESENI_DATA **linkes_rieseni);
void sort_players_solutions_by_duration(HRACI_DATA **linked_hraci);
void print_linked_players(HRACI_DATA **linked_hraci);
void cleanup_and_exit(FILE **sudoku, FILE **hraci, FILE **rieseni,char ***sid_s,
char ***riesen_s, char ***pid_h ,char ***meno_h ,char ***krajina_h, 
char ***rok_h, char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int count_s, int count_h, int count_r, HRACI_DATA **linked_hraci, RIESENI_DATA **linked_rieseni);

int main()
{
    FILE *sudoku = NULL;
    FILE *hraci = NULL;
    FILE *rieseni = NULL;
    HRACI_DATA *linked_hraci;
    RIESENI_DATA *linked_rieseni;
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
    srand(time(NULL));
    linked_hraci = NULL;
    linked_rieseni = NULL;
    while(1)
    {
        scanf(" %c", &c); /* read the which function is called */
        if(c == 'v')
        {
            scanf("%d", &i);
            if(i > 3 || i < 1)
            {
                printf("V: Nesprávna volba vypisu.\n");
            }
            if(i == 1)
            {
                print_players_with_sample_solutions(&sudoku, &hraci, &rieseni);
            }
            if(i == 2)
            {
                print_players_with_solutions_arrays(&pid_h, &meno_h, &krajina_h, 
                &rok_h, &gid_r, &pid_r, &sid_r, 
                &date_r, &trvanie_r, &count_h, &count_r);
            }
            if(i == 3)
            {
                print_linked_players(&linked_hraci);
            }
        }
        else if(c == 'h')
        {
            export_solutions_by_sid(rieseni);
        }
        else if(c == 'n')
        {
            load_arrays_from_files(sudoku, hraci, rieseni, &sid_s,
            &riesen_s, &pid_h, &meno_h, &krajina_h, 
            &rok_h, &gid_r, &pid_r, &sid_r, 
            &date_r, &trvanie_r, &count_s, &count_h, &count_r);
        }
        else if(c == 'q')
        {
            scanf("%d", &i);
            insert_solution_record(i, &gid_r, &pid_r, &sid_r, 
            &date_r, &trvanie_r, &count_r);
        }
        else if(c == 'w')
        {
            delete_solution_records_by_pid(&gid_r, &pid_r, &sid_r, 
            &date_r, &trvanie_r, &count_r);
        }
        else if(c == 'e')
        {
            generate_puzzle_with_gaps(&sid_s, &riesen_s, &count_s);
        }
        else if(c == 'm')
        {
            build_linked_lists_from_arrays(sudoku, hraci, rieseni, &linked_hraci, &linked_rieseni);
        }
        else if(c == 'a')
        {
            add_player_to_list(&linked_hraci);
        }
        else if(c == 's')
        {
            delete_solution_by_gid(&linked_hraci, &linked_rieseni);
        }
        else if(c == 'd')
        {
            sort_players_solutions_by_duration(&linked_hraci);
        }
        else if(c == 'k')
        {
            cleanup_and_exit(&sudoku, &hraci, &rieseni, &sid_s,
            &riesen_s, &pid_h, &meno_h, &krajina_h,
            &rok_h, &gid_r, &pid_r, &sid_r,
            &date_r, &trvanie_r, count_s, count_h, count_r, &linked_hraci, &linked_rieseni);
            break;
        }
    }
    return 0;
}

void print_players_with_sample_solutions(FILE **sudoku, FILE **hraci, FILE **rieseni)
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
     
    if(*sudoku == NULL|| *hraci == NULL|| *rieseni == NULL) /* Check if every file is open */
    {
        *sudoku = fopen("Sudoku.txt", "r");/* If not open then open it */
        *hraci = fopen("RegisterHracov.txt", "r");
        *rieseni = fopen("RegisterRieseni.txt", "r");
    }
    if(!*sudoku || !*hraci || !*rieseni) /* Check if every file is open */
    {
        printf("V1: Neotvorene txt subory.\n");
        return;
    }
    rewind(*sudoku);
    rewind(*hraci);
    rewind(*rieseni);
    while(fgets(buffer, sizeof(buffer), *hraci) != NULL)/* Read a riadok */
    {
        pid_raw = strtok(buffer, "#");/* variable pid is every char in buffer that is limited by first # */
        meno = strtok(NULL, "#");/* variable the same like pid but start from where pid is ended */
        krajina = strtok(NULL, "#");
        rok = strtok(NULL, "#");

        /* copy the string pid_raw because we will rewrite buffer */
        strcpy(pid_copy, pid_raw);

        printf("Identifikator: %s\n", pid_copy);/* print the result */
        printf("Meno a priezvisko: %s\n", meno);
        printf("Krajina: %s\n", krajina);
        printf("Rok: %s\n", rok);
        j = 0; /* counter of vzorkov */
        rewind(*rieseni); /* Go to the start of the file */
        printf("Vzorka:\n");
        while((fgets(buffer, sizeof(buffer), *rieseni) != NULL) && j < 10)/* read from rieseni */
        {
            /* Make copy of bufer because strtok cut buffer to pid to compare */ 
            strcpy(buffer_copy, buffer);
            strtok(buffer, "#");
            pd = strtok(NULL, "#");
                
            strcpy(clean_pid_copy, pid_copy);

            if (pd != NULL && strcmp(clean_pid_copy, pd) == 0)
            {
                printf("\t%s", buffer_copy);
                j++;
            }
        }
        printf("\n");/* The gap between players */
    }
}

void export_solutions_by_sid(FILE *rieseni)
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
        printf("H: Nespravny vstup.\n");
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

void load_arrays_from_files(FILE *sudoku, FILE *hraci, FILE * rieseni,char ***sid_s,
char ***riesen_s, char ***pid_h ,char ***meno_h ,char ***krajina_h, 
char ***rok_h, char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int *count_s, int *count_h, int *count_r)
{
    char buffer[512];/*buffer for read files*/
    int i, j; 
    /*temporary variables*/
    char *raw_sid_s, *raw_reseni_s; 
    char **tm_sid_s, **tm_reseni_s;

    char *pid_raw_h, *meno_raw_h, *krajina_raw_h, *rok_raw_h;
    char **tm_pid_h, **tm_meno_h, **tm_krajina_h, **tm_rok_h;

    char *gid_raw_r, *pid_raw_r, *sid_raw_r, *date_raw_r, *m_raw_r, *s_raw_r; 
    char **tm_gid_r, **tm_pid_r, **tm_sid_r, **tm_date_r;
    int *tm_trvanie_r, m_val, s_val;
    /*check if files are already opened*/
    if (sudoku == NULL || hraci == NULL || rieseni == NULL)
    {
        printf("N: Neotvoreny subor.\n");
        return;
    }
    /*check if dynamicky polia su uz vytvorene*/
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

    while(fgets(buffer, sizeof(buffer), sudoku) != NULL) /*read file sudoku*/
    {
        raw_sid_s = strtok(buffer, "#");/*separate information*/
        raw_reseni_s = strtok(NULL, "#");
        
        tm_sid_s = realloc(*sid_s, (i + 1) * sizeof(char *));/*create space for iformation*/
        tm_reseni_s = realloc(*riesen_s, (i + 1) * sizeof(char *));

        if(tm_sid_s != NULL && tm_reseni_s != NULL)/*check if realloc is done*/
        {
            *sid_s = tm_sid_s;
            *riesen_s = tm_reseni_s;
        }
        else
        {
            return;
        }
        
        (*sid_s)[i] = malloc(strlen(raw_sid_s) + 1);/*give space for data*/
        (*riesen_s)[i] = malloc(strlen(raw_reseni_s) + 1); 

        strcpy((*sid_s)[i], raw_sid_s);/*copy data*/
        strcpy((*riesen_s)[i], raw_reseni_s);
        i++;
    }
    *count_s = i;/*increase the count of data*/
    i = 0;
    /*the same as sudoku*/
    while(fgets(buffer, sizeof(buffer), hraci) != NULL)
    {
        pid_raw_h = strtok(buffer, "#");
        meno_raw_h = strtok(NULL, "#");
        krajina_raw_h = strtok(NULL, "#");
        rok_raw_h = strtok(NULL, "#");
        if(pid_raw_h == NULL){
            pid_raw_h = "";
        }
        if(meno_raw_h == NULL){
            meno_raw_h = "";
        }
        if(krajina_raw_h == NULL){
            krajina_raw_h = "";
        }
        if(rok_raw_h == NULL){
            rok_raw_h = "";
        }
        
        tm_pid_h = realloc(*pid_h, (i + 1) * sizeof(char*));
        tm_meno_h = realloc(*meno_h, (i + 1) * sizeof(char*));
        tm_krajina_h = realloc(*krajina_h, (i + 1) * sizeof(char*));
        tm_rok_h = realloc(*rok_h, (i + 1) * sizeof(char*));

        if(tm_pid_h != NULL && tm_meno_h != NULL && tm_krajina_h != NULL && tm_rok_h != NULL)
        {
            *pid_h = tm_pid_h;
            *meno_h = tm_meno_h;
            *krajina_h = tm_krajina_h;
            *rok_h = tm_rok_h;
        }
        else
        {
            return;
        }
        (*pid_h)[i] = malloc(strlen(pid_raw_h) + 1); 

        (*meno_h)[i] = malloc(strlen(meno_raw_h) + 1); 
        
        (*krajina_h)[i] = malloc(strlen(krajina_raw_h) + 1); 

        (*rok_h)[i] = malloc(strlen(rok_raw_h) + 1); 
        strcpy((*pid_h)[i], pid_raw_h);
        strcpy((*meno_h)[i], meno_raw_h);
        strcpy((*krajina_h)[i], krajina_raw_h);
        strcpy((*rok_h)[i], rok_raw_h);
        i++;
    }
    *count_h = i;
    i = 0;
    /*the same as sudoku*/
    while(fgets(buffer, sizeof(buffer), rieseni) != NULL)
    {
        gid_raw_r = strtok(buffer, "#");
        pid_raw_r = strtok(NULL, "#");
        sid_raw_r = strtok(NULL, "#");
        date_raw_r = strtok(NULL, "#");
        m_raw_r = strtok(NULL, "#");
        s_raw_r = strtok(NULL, "#");
        
        tm_gid_r = realloc(*gid_r, (i + 1) * sizeof(char*));
        tm_pid_r = realloc(*pid_r, (i + 1) * sizeof(char*));
        tm_sid_r = realloc(*sid_r, (i + 1) * sizeof(char*));
        tm_date_r = realloc(*date_r, (i + 1) * sizeof(char*));
        tm_trvanie_r = realloc(*trvanie_r, (i + 1) * sizeof(int));

        if(tm_gid_r != NULL && tm_pid_r != NULL && tm_sid_r != NULL && tm_date_r != NULL && tm_trvanie_r != NULL)
        {
            *gid_r = tm_gid_r;
            *pid_r = tm_pid_r;
            *sid_r = tm_sid_r;
            *date_r = tm_date_r;
            *trvanie_r = tm_trvanie_r;
        }
        else
        {
            return;
        }

        (*gid_r)[i] = malloc(strlen(gid_raw_r) + 1); 

        (*pid_r)[i] = malloc(strlen(pid_raw_r) + 1); 
        
        (*sid_r)[i] = malloc(strlen(sid_raw_r) + 1); 

        (*date_r)[i] = malloc(strlen(date_raw_r) + 1); 
        strcpy((*gid_r)[i], gid_raw_r);
        strcpy((*pid_r)[i], pid_raw_r);
        strcpy((*sid_r)[i], sid_raw_r);
        strcpy((*date_r)[i], date_raw_r);
        m_val = atoi(m_raw_r);
        s_val = atoi(s_raw_r);
        (*trvanie_r)[i] = m_val * 60 + s_val;
        i++;
    }
    *count_r = i;
}

void insert_solution_record(int i, char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int *count_r)
{
    int j;
    char s[16];
    int n, m, sec;
    char **tm_gid, **tm_pid, **tm_sid, **tm_date;
    int *tm_trvanie; 
    if (*gid_r == NULL)/*check if polia su vytvorene*/
    {
        printf("Q: Polia nie su vytvorene.\n");
        return;
    }
    if (i > *count_r)/*check if i is in range of arrray*/
    {
        n = *count_r;
    }
    else
    {
        n = i - 1;
    }
    (*count_r)++; 
    /*give space for new data*/
    tm_gid = realloc(*gid_r, (*count_r) * sizeof(char*));
    tm_pid = realloc(*pid_r, (*count_r) * sizeof(char*));
    tm_sid = realloc(*sid_r, (*count_r) * sizeof(char*));
    tm_date = realloc(*date_r, (*count_r) * sizeof(char*));
    tm_trvanie = realloc(*trvanie_r, (*count_r) * sizeof(int));
    /*make i-th space empty*/
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
        /*check if input has correct format*/
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
            ((s[3] >= 'a' && s[3] <= 'z') || (s[3] >= 'A' && s[3] <= 'Z')) &&
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

void delete_solution_records_by_pid(char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int *count_r)
{
    char s[16];
    int j, i, total;
    char **tm_gid, **tm_pid, **tm_sid, **tm_date;
    int *tm_trvanie; 
    /*check if polia su vytvorene*/
    if(*pid_r == NULL)
    {
        printf("W: Polia nie su vytvorene.\n");
        return; 
    }
    scanf("%s", s);
    
    total = 0;
    /*free memory and move elemnts*/
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
    /*chenge size*/
    tm_gid = realloc(*gid_r, (*count_r) * sizeof(char*));
    tm_pid = realloc(*pid_r, (*count_r) * sizeof(char*));
    tm_sid = realloc(*sid_r, (*count_r) * sizeof(char*));
    tm_date = realloc(*date_r, (*count_r) * sizeof(char*));
    tm_trvanie = realloc(*trvanie_r, (*count_r) * sizeof(int));
    /*check*/
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

void generate_puzzle_with_gaps(char ***sid_s, char ***riesen_s, int *count_s)
{
    char sid[9], *rieseni;
    int x, i, s, j, p, copy, t;
    int r[5];
    FILE *file;
    s = -1;
    if(!(*sid_s) || !(*riesen_s))/*check if polia su vytvorene*/
    {
        printf("E: Polia nie su vytvorene.\n");
        return;
    }
    if(scanf("%s %d", sid, &x) != 2)/*check if input has correct format*/
    {
        printf("E: Nespravny vstup.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    if(x < 1 || x > 5)
    {
        printf("E: Nespravny vstup.\n");
        return;
    }
    for(i = 0; i < *count_s; i++)
    {
        if(strcmp(sid, (*sid_s)[i]) == 0)
        {
            s = i;
            break;
        }
    }
    if (s == -1)
    {
        printf("E: Nespravny vstup.\n");
        return;
    }
    rieseni = malloc(strlen((*riesen_s)[s]) + 1);
    strcpy(rieseni, (*riesen_s)[s]);/*copy because riesen_s cannot be change*/
    rieseni[strlen((*riesen_s)[s])] = '\0';
    file = fopen("Vystup_E.txt", "w");/*create file for output*/
    if(file == NULL)/*check*/
    {
        free(rieseni);
        return;
    }
    for(i = 0; i < 9; i++)
    {
        do/*generate random numberand check if they arent copy*/
        {
            copy = 0;
            for(j = 0;  j < x; j++)
            {
                r[j] = rand() % 9;
            }
            for(j = 0; j < x; j++)
            {
                for(t = j + 1; t < x; t++)
                {
                    if(j != t)
                    {
                        if(r[j] == r[t])
                        {
                            copy = 1;
                            break;
                        }
                    }
                }
                if(copy == 1)
                {
                    break;
                }
            }
        }while(copy);
        for(j = 0;  j < x; j++)/*creat gaps*/
        {
            rieseni[i * 9 + r[j]] = '0';
        }      
        for(j = 0; j < 9; j++)/*write in file*/
        {
            p = i * 9 + j;
            if(rieseni[p] == '0')
            {
                fprintf(file, "| ");
            }
            else
            {
                fprintf(file,"|%c", rieseni[p]);
            }
        }
        fprintf(file, "|\n");
    }
     printf("E: Vytvorene.\n");
    fclose(file);/*close file and free memory*/
    free(rieseni);
}

void print_players_with_solutions_arrays(char ***pid_h ,char ***meno_h ,char ***krajina_h, 
char ***rok_h, char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int *count_h, int *count_r)
{
    int i, j, n;
    if(*pid_h == NULL || *gid_r == NULL)/*check if polia su naplnene*/
    {
        printf("V2: Nenaplnene polia.\n");
        return;
    }
    for (i = 0; i < *count_h; i++)/*print output*/
    {
        printf("PID: %s / %s / %s\n", (*pid_h)[i], (*rok_h)[i], (*krajina_h)[i]);
        printf("Idendita: %s\n", (*meno_h)[i]);
        printf("Vysledok:\n");
        j = 0;
        for(n = 0; n < *count_r; n++)
        {
            if(strcmp((*pid_r)[n],(*pid_h)[i]) == 0)
            {
                printf("\t%s / %s / %s / %s / %c / %c / %d\n", (*gid_r)[n], (*pid_r)[n], (*sid_r)[n], (*date_r)[n], (*gid_r)[n][3], (*sid_r)[n][3],(*trvanie_r)[n]);
                j++;
            }
            if(j == 10)
            {
                break;
            }
        }
        printf("\n");
    }
}

void build_linked_lists_from_arrays(FILE *sudoku, FILE *hraci, FILE * rieseni, HRACI_DATA **linked_hraci, RIESENI_DATA **linked_rieseni){
    char buffer[512], temp[512];
    char *pid_h, *idendita_h, *krajina_h, *rok_h;
    char *gid_r, *pid_r, *sid_r, *data_r, *min, *sec;
    HRACI_DATA *n, *tmp_n;
    RIESENI_DATA *r, *tmp_r;
    int rok, m, s, time, zaznamy, i;
    if(!sudoku || !hraci || !rieseni){
        printf("M: Neotvorene txt subory.\n");
        return;
    }

    n = *linked_hraci;
    r = *linked_rieseni;

    if(*linked_hraci != NULL)
    {
        while(n != NULL){
            tmp_n = n;
            free(n->PID);
            free(n->Idendita);
            free(n->Krajina);
            if(n->Riesenia != NULL){
                for (i = 0; i < n->pocet_rieseni; i++){
                    free(n->Riesenia[i]);
                }
                free(n->Riesenia);
            }
            n = n->next;
            free(tmp_n);
        }    
    }

    if(*linked_rieseni != NULL)
    {
        while(r != NULL){
            tmp_r = r;
            free(r->SID);
            free(r->GID);
            free(r->DatHry);
            r = r->next;
            free(tmp_r);
        }
    }
    rewind(sudoku);
    rewind(hraci);
    rewind(rieseni);
    *linked_hraci = NULL;
    *linked_rieseni = NULL;

    zaznamy = 0;
    while(fgets(buffer, sizeof(buffer), hraci) != NULL){
        strcpy(temp, buffer);
        n = malloc(sizeof(HRACI_DATA));
        if(!n){
            return;
        }
        pid_h = strtok(temp, "#");
        idendita_h = strtok(NULL, "#");
        krajina_h = strtok(NULL, "#");
        rok_h = strtok(NULL, "#");
        rok = atoi(rok_h);
        if(pid_h == NULL){
            pid_h = "";
        }
        if(idendita_h == NULL){
            idendita_h = "";
        }
        if(krajina_h == NULL){
            krajina_h = "";
        }
        if(rok_h == NULL){
            rok = 0;
        }

        n->PID = malloc(strlen(pid_h) + 1);
        n->Idendita = malloc(strlen(idendita_h) + 1);
        n->Krajina = malloc(strlen(krajina_h) + 1);

        if(!n->PID || !n->Idendita || !n->Krajina){
            return;
        }

        strcpy(n->PID, pid_h);
        strcpy(n->Idendita, idendita_h);
        strcpy(n->Krajina, krajina_h);
        n->RokNar = rok;
        n->Riesenia = NULL;
        n->pocet_rieseni = 0;
        n->next = NULL;
        zaznamy++;
        if (!*linked_hraci){
            *linked_hraci = n;
        }
        else{
            tmp_n->next = n;
        } 
        tmp_n = n;
    }
    
    while(fgets(buffer, sizeof(buffer), rieseni) != NULL){
        strcpy(temp, buffer);
        r = malloc(sizeof(RIESENI_DATA));
        if(!r){
            return;
        } 
        gid_r = strtok(temp, "#");
        pid_r = strtok(NULL, "#");
        sid_r = strtok(NULL, "#");
        data_r = strtok(NULL, "#");
        min = strtok(NULL, "#");
        sec = strtok(NULL, "#");
        m = atoi(min);
        s = atoi(sec);
        time = m*60 + s;

        r->SID = malloc(strlen(sid_r) + 1);
        r->GID = malloc(strlen(gid_r) + 1);
        r->DatHry = malloc(strlen(data_r) + 1);

        if(!r->SID || !r->GID || !r->DatHry){
            return;
        }
        strcpy(r->SID, sid_r);
        r->NarHry = sid_r[3];
        strcpy(r->GID, gid_r);
        r->NarSut = gid_r[3];
        strcpy(r->DatHry, data_r);
        r->Trvanie = time;
        r->next = NULL;
        zaznamy++;
        n = *linked_hraci;
        while(n != NULL && strcmp(n->PID, pid_r) != 0){
            n = n->next;
        }
        if(n != NULL){
            n -> Riesenia = realloc(n -> Riesenia, (n->pocet_rieseni + 1) * sizeof(RIESENI_DATA *));
            n -> Riesenia[n->pocet_rieseni] = r;
            n->pocet_rieseni++;
        }
        if (!*linked_rieseni){
            *linked_rieseni = r;
        }
        else{
            tmp_r->next = r;
        }
        tmp_r = r;
    }
    printf("M: Nacitalo sa %d zaznamov.\n", zaznamy);
}

void add_player_to_list(HRACI_DATA **linked_hraci){
    HRACI_DATA *n, *m, *tmp;
    int i, rok, j, order, last;
    char name[100], krajina[100],pid[10], number[6];

    scanf("%d", &i);
    scanf("%s", name);
    scanf("%s", krajina);
    scanf("%d", &rok);
    n = *linked_hraci;
    while(n != NULL){
        if (strcmp(n->Idendita, name) == 0 && n->RokNar == rok){
            printf("A: Duplicita zaznamu.\n");
            return;
        }
        n = n->next;
    }
    last = 0;
    n = *linked_hraci;
    while(n != NULL){
        if(n->PID[3] == 'a'){
            number[0] = n->PID[4];
            number[1] = n->PID[5];
            number[2] = n->PID[6];
            number[3] = n->PID[7];
            number[4] = n->PID[8];
            number[5] = '\0';
            order = atoi(number);
            if (order > last){
                last = order;
            }
        }
        n = n->next;
    }
    last++;
    pid[0] = 'P';
    pid[1] = 'I';
    pid[2] = 'D';
    pid[3] = 'a';
    pid[4] = (last / 10000) % 10 + '0';
    pid[5] = (last / 1000) % 10 + '0';
    pid[6] = (last / 100) % 10 + '0';
    pid[7] = (last /10)% 10 + '0';
    pid[8] = (last % 10) + '0';
    n = (HRACI_DATA *) malloc(sizeof(HRACI_DATA));
    n->PID = malloc(strlen(pid) + 1);
    n->Idendita = malloc(strlen(name) + 1);
    n->Krajina = malloc(strlen(krajina) + 1);
    strcpy(n->PID, pid);
    strcpy(n->Idendita,name);
    strcpy(n->Krajina, krajina);
    n->RokNar = rok;
    n->Riesenia = NULL;
    n->pocet_rieseni = 0;
    n->next = NULL;
    m = *linked_hraci;
    j = 0;
    if(i == 1){
         n->next = m;
        *linked_hraci = n;
        }
    else{
        while(m != NULL && j < i - 1){
            j++;
            tmp = m;
            m = m->next;
        }
        n->next = m;
        tmp->next = n;
    }
    printf("A: Uspesne pridany zaznam na poziciu %d.\n", i);
}

void delete_solution_by_gid(HRACI_DATA **linked_hraci, RIESENI_DATA **linkes_rieseni){
    RIESENI_DATA *r, *tmp_r, *n, **vysledky;
    HRACI_DATA *h;
    char gid_r[8];
    int i, j;
    if(*linkes_rieseni == NULL){
        printf("S: Spajany zoznam nie je vytvoreny.\n");
        return;
    }
    scanf("%s", gid_r);
    r = *linkes_rieseni;
    h = *linked_hraci;
    while(h != NULL){
        if (h->pocet_rieseni > 0){
            for(i = 0; i < h->pocet_rieseni; i++){
                if (strcmp(h->Riesenia[i]->GID, gid_r) == 0){
                    for (j = i; j < h->pocet_rieseni - 1; j++){
                        h->Riesenia[j] = h->Riesenia[j+1];
                    }
                    h->pocet_rieseni--;
                    vysledky = realloc(h->Riesenia, h->pocet_rieseni * sizeof(RIESENI_DATA*));
                    if (!vysledky && h->pocet_rieseni > 0){
                        return;
                    }
                    else{
                        h->Riesenia = vysledky;
                    }
                }
            }
        }
        h = h->next;
    }
    i = 0;
    while(r != NULL){
        while(r != NULL && strcmp(r->GID, gid_r) !=0){
            n = r;
            r = r->next;
        }
        if(r != NULL){
            tmp_r = r;
            r = r->next;
            free(tmp_r->GID);
            free(tmp_r->SID);
            free(tmp_r->DatHry);
            free(tmp_r);
            n->next = r;
            i++;
        }
    }
    printf("S: Vymazalo sa: %d zaznamov!\n", i);
}

void sort_players_solutions_by_duration(HRACI_DATA **linked_hraci){
    HRACI_DATA *n;
    RIESENI_DATA *r;
    int i, j;
    if(*linked_hraci == NULL){
        printf("D: Spajany zoznam nie je vytvoreny.\n");
        return;
    }
    n =*linked_hraci;
    i = 0;
    while(n != NULL){
        if(n->Riesenia != NULL && n->pocet_rieseni > 1){
        // Bubble sort
        for(i = 0; i < n->pocet_rieseni - 1; i++){
            for(j = i + 1; j < n->pocet_rieseni; j++){
                if(n->Riesenia[i]->Trvanie > n->Riesenia[j]->Trvanie){
                    r = n->Riesenia[i];
                    n->Riesenia[i] = n->Riesenia[j];
                    n->Riesenia[j] = r;
                    }
                }
            }
        }
        n = n->next;
    }
}

void print_linked_players(HRACI_DATA **linked_hraci){
    HRACI_DATA *n;
    int i;
    if (*linked_hraci == NULL){
        printf("V3: Nenaplneny spajany zoznam.\n");
        return;
    }
    n = *linked_hraci;
    while(n != NULL){
        printf("PID: %s\n", n->PID);
        printf("Idendita: %s\n", n->Idendita);
        printf("Krajina: %s\n", n->Krajina);
        printf("RokNar: %d\n", n->RokNar);
        if(n->Riesenia != NULL){
            printf("Vysledky:");
            for(i = 0; i < n->pocet_rieseni; i++){
                printf(" %s / %c / %s / %c / %s / %d\n", n->Riesenia[i]->GID, n->Riesenia[i]->NarSut, n->Riesenia[i]->SID, n->Riesenia[i]->NarHry, n->Riesenia[i]->DatHry, n->Riesenia[i]->Trvanie);
            }
        }
        n = n->next;
        printf("\n");
    }
}
void cleanup_and_exit(FILE **sudoku, FILE **hraci, FILE **rieseni,char ***sid_s,
char ***riesen_s, char ***pid_h ,char ***meno_h ,char ***krajina_h, 
char ***rok_h, char ***gid_r ,char ***pid_r, char ***sid_r, 
char ***date_r, int **trvanie_r, int count_s, int count_h, int count_r, HRACI_DATA **linked_hraci, RIESENI_DATA **linked_rieseni){
    int i;
    HRACI_DATA *n, *tmp_n;
    RIESENI_DATA *r, *tmp_r;
    /*close sid_s and riesen_s*/
    if (*sid_s != NULL) {
        for (i = 0; i < count_s; i++) {
            if ((*sid_s)[i] != NULL) free((*sid_s)[i]);
            if ((*riesen_s)[i] != NULL) free((*riesen_s)[i]);
        }
        free(*sid_s);
        free(*riesen_s);
    }

    /*free pid_h, meno_h, krajina_h, rok_h*/
    if (*pid_h != NULL) {
        for (i = 0; i < count_h; i++) {
            if ((*pid_h)[i] != NULL) free((*pid_h)[i]);
            if ((*meno_h)[i] != NULL) free((*meno_h)[i]);
            if ((*krajina_h)[i] != NULL) free((*krajina_h)[i]);
            if ((*rok_h)[i] != NULL) free((*rok_h)[i]);
        }
        free(*pid_h);
        free(*meno_h);
        free(*krajina_h);
        free(*rok_h);
    }
    
    /*free gid_r, pid_r, sid_r, date_r, trvanie_r*/
    if (*gid_r != NULL) {
        for (i = 0; i < count_r; i++) {
            if ((*gid_r)[i] != NULL) free((*gid_r)[i]);
            if ((*pid_r)[i] != NULL) free((*pid_r)[i]);
            if ((*sid_r)[i] != NULL) free((*sid_r)[i]);
            if ((*date_r)[i] != NULL) free((*date_r)[i]);
        }
        free(*gid_r);
        free(*pid_r);
        free(*sid_r);
        free(*date_r);
        free(*trvanie_r);
    }
    n = *linked_hraci;
    r = *linked_rieseni;

    if(*linked_hraci != NULL)
    {
        while(n != NULL){
            tmp_n = n;
            free(n->PID);
            free(n->Idendita);
            free(n->Krajina);
            if(n->Riesenia != NULL){
                for (i = 0; i < n->pocet_rieseni; i++){
                    free(n->Riesenia[i]);
                }
                free(n->Riesenia);
            }
            n = n->next;
            free(tmp_n);
        }    
    }
    if(*linked_rieseni != NULL)
    {
        while(r != NULL){
            tmp_r = r;
            free(r->SID);
            free(r->GID);
            free(r->DatHry);
            r = r->next;
            free(tmp_r);
        }
    }

    /*close all files*/
    if (*sudoku != NULL) fclose(*sudoku);
    if (*hraci != NULL) fclose(*hraci);
    if (*rieseni != NULL) fclose(*rieseni);
}
