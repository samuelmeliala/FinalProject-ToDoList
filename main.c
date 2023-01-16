#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char selectedMenu[6];

struct List{
    char name[1001];
    int priority;
};

void showToDoList(){
    system("cls");
    //Menampilkan judul
    printf("\033[0;34m");
    for(int i = 0; i < 5; i++){
        printf("%33s", " ");
        if(i == 0 || i == 4){
            for(int j = 0; j < 33; j++){
                printf("-");
            }
            printf("\n");
        }else{
            for(int j = 0; j < 33; j++){
                if(j == 0 || j == 32){
                    printf("|");
                }else{
                    printf(" ");
                }

                if(i == 2){
                    if(j == 10){
                        printf("\033[0m");
                        printf("My To do List");
                        j = 23;
                        printf("\033[0;34m");
                        continue;
                    }
                }
            }
            printf("\n");
        }
    }
    printf("\033[0m");
    printf("\n\n\n");

    int numberOfList = 1;
    char line[100];

    FILE *fp;
    fp = fopen("data/list.txt","r");

    if(fp == NULL){
        printf("Error!");   
        exit(1);             
    }
    
    while (fgets(line, sizeof(line), fp)) {
        if(strchr(line, '1'))
        {
            printf("\033[0;31m");    
            printf("\t%d. %s", numberOfList++, line);
            printf("\033[0m");
        }else if(strchr(line, '2')){
            printf("\033[0;33m");    
            printf("\t%d. %s", numberOfList++, line);
            printf("\033[0m");
        }
    }

    fclose(fp);
}
    
void selectMenu(){
    printf("\n\n\n");
    printf("\033[0;34m");
    for(int i = 0; i < 100; i++)printf("-");
    printf("\033[;32m");
    printf("\nADD");
    printf("\033[0m");
    printf(": to add an activity                             ");
    printf("\033[;32m");
    printf("DEL");
    printf("\033[0m");
    printf(": to delete an activity\n");
    printf("\033[;32m");
    printf("SORT");
    printf("\033[0m");
    printf(": to sort activity list according to priority   ");
    printf("\033[;32m");
    printf("SEARCH");
    printf("\033[0m");
    printf(": to find activity list by number   \n");
    printf("\033[0;34m");
    for(int i = 0; i < 100; i++)printf("-");
    printf("\033[0m");
    printf("\nSELECT: ");
    scanf("%s", selectedMenu);
    getchar();
}

void addActivity(){

    struct List lst;

    showToDoList();

    printf("\n\n\n");
    printf("\033[0;34m");
    for(int i = 0; i < 100; i++)printf("-");
    printf("\033[;32m");
    printf("\nPRIORITY");
    printf("\033[0m");
    printf(": enter 1 for important, 2 for unimportant\n");
    printf("\033[0;34m");
    for(int i = 0; i < 100; i++)printf("-");
    printf("\033[0m");

    FILE *fp;
    fp = fopen("data/list.txt", "a+");

    if(fp == NULL){
        printf("Error!");   
        exit(1);             
    }

    printf("\nActivity: ");
    scanf("%[^\n]",lst.name);
    getchar();
    printf("\nPriority: ");
    scanf("%d",&lst.priority);
    getchar();
    fprintf(fp,"%s-%d\n",lst.name, lst.priority);
    fclose(fp);
}

void deleteActivity(){
    int deleteLine;
    int currentLine = 1;

    showToDoList();
    printf("\n\n\n");
    printf("\033[0;34m");
    for(int i = 0; i < 100; i++)printf("-");
    printf("\033[;32m");
    printf("\nENTER ACTIVITY NUMBER YOU WANT TO DELETE\n");
    printf("\033[0;34m");
    for(int i = 0; i < 100; i++)printf("-");
    printf("\033[0m");
    printf("\nDELETE: ");
    scanf("%d", &deleteLine);

    FILE *fp, *temp;
    char line[100];

    fp = fopen("data/list.txt", "r");
    temp = fopen("data/temp.txt", "w");

    while (fgets(line, sizeof(line), fp)) {
        if (currentLine != deleteLine) {
            fputs(line, temp);
        }
        currentLine++;
    }

    fclose(fp);
    fclose(temp);

    remove("data/list.txt");
    rename("data/temp.txt", "data/list.txt");
}

void searchActivity(){
    int searchLine;
    int currentLine = 1;

    showToDoList();
    printf("\n\n\n");
    printf("\033[0;34m");
    for (int i = 0; i < 100; i++)
        printf("-");
    printf("\033[;32m");
    printf("\nENTER ACTIVITY NUMBER YOU WANT TO SEARCH\n");
    printf("\033[0;34m");
    for (int i = 0; i < 100; i++)
        printf("-");
    printf("\033[0m");
    printf("\nSEARCH: ");
    scanf("%d", &searchLine);

    FILE *fp;
    char line[100];

    fp = fopen("data/list.txt", "r");

    while (fgets(line, sizeof(line), fp))
    {
        if (currentLine == searchLine)
        {
            printf("\033[;32m");
            printf("LIST : %s\n\n\n", line);
            printf("\033[0m");
            break;
        }
        currentLine++;
    }  
    printf("ENTER TO CONTINUE\n");
    getchar();

    fclose(fp);
}

int compare(const void *a, const void *b)
{
    char *line1 = *(char **)a;
    char *line2 = *(char **)b;
    char *ptr1 = strchr(line1, '-');
    char *ptr2 = strchr(line2, '-');
    int num1 = (ptr1 != NULL) ? atoi(ptr1 + 1) : 0;
    int num2 = (ptr2 != NULL) ? atoi(ptr2 + 1) : 0;
    return num1 - num2;
}


void sortActivity()
{
    FILE *fp = fopen("data/list.txt", "r");
    char line[100];
    char* lines[100];
    int line_count = 0;

    
    while (fgets(line, sizeof(line), fp)) {
        lines[line_count] = strdup(line);
        line_count++;
    }

    qsort(lines, line_count, sizeof(char*), compare);

    fclose(fp);
    fp = fopen("data/list.txt", "w");
    
    for (int i = 0; i < line_count; i++) {
        fprintf(fp, "%s", lines[i]);
    }
    fclose(fp);
    
    printf("LIST HAVE BEEN SORTED");
    getchar();
}


int main(){
    do{
        showToDoList();
        selectMenu();
        if(strcmp(selectedMenu, "ADD") == 0){ 
            addActivity();
        } 
        else if (strcmp(selectedMenu, "DEL") == 0)
        {
            deleteActivity();
        }
        else if (strcmp(selectedMenu, "SORT") == 0)
        {
            sortActivity();
        }
        else if (strcmp(selectedMenu, "SEARCH") == 0)
        {
            searchActivity();
            getchar();
        }
    }while(strcmp(selectedMenu, "0") != 0);

    return 0;
}