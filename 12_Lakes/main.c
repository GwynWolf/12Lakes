#include <stdio.h>
#include <Windows.h>
#include <locale.h>
#include <conio.h>
int enter_menu = 1;
FILE* Data_lakes;
struct Lake
{
    char Name[20];
    char Country[20];
    int depth;
    double salinity;
    struct Lake* next;
};
struct Lake* Head = NULL;

void file_create()
{
    Data_lakes = fopen("Lakes_inf.txt", "w");
    fclose(Data_lakes);
    Data_lakes = fopen("Lakes_inf.txt", "r");
}

void file_open()
{
    if(!(Data_lakes = fopen("Lakes_inf.txt", "r")))
    {
        file_create();
    }
    else
    {
        while(!feof(Data_lakes))
        {
            struct Lake* new_node = (struct Lake*)malloc(sizeof(struct Lake));
            if(Head != NULL)
                new_node->next = Head;
            else
                new_node->next = NULL;
            fscanf(Data_lakes, "%s %s %d %lf", new_node->Name, new_node->Country, &new_node->depth, &new_node->salinity);
            Head = new_node;
        }
    }
    fclose(Data_lakes);
}
void file_close()
{
    Data_lakes = fopen("Lakes_inf.txt", "w");
    struct Lake* new_node = Head;
    struct Lake* adress;
    while(new_node != NULL)
    {
         fprintf(Data_lakes ,"\n%s %s %d %lf",
            new_node->Name, new_node->Country, new_node->depth,
            new_node->salinity);
         adress = new_node->next;
         free(new_node);
         new_node = adress;
    }
    fclose(Data_lakes);
}

void print_menu()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(enter_menu == 1)
    {
        SetConsoleTextAttribute(hConsole, (WORD) ((15 << 4) | 0));
        printf("Просмотреть информацию про озера\n");
    }
    else
    {
        SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 2));
        printf("Просмотреть информацию про озера\n");
    }

    if(enter_menu == 2)
    {
        SetConsoleTextAttribute(hConsole, (WORD) ((15 << 4) | 0));
        printf("Добавить информацию про озеро\n");
    }
    else
    {
        SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 2));
        printf("Добавить информацию про озеро\n");
    }

    if(enter_menu == 3)
    {
        SetConsoleTextAttribute(hConsole, (WORD) ((15 << 4) | 0));
        printf("Поиск озер с глубиной меньше 50м и соленостью больше 20 процентов\n");
    }
    else
    {
        SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 2));
        printf("Поиск озер с глубиной меньше 50м и соленостью больше 20 процентов\n");
    }
    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 2));
    printf("Для выхода нажмите ESC");
}

void node_print()
{
    system("cls");
    system("color 02");
    printf("Просмотр доступной информации\n");
    printf("\n");
    struct Lake* new_node = Head;
    while(new_node != NULL)
    {
        printf("Название:%s\n Страна:%s\n Глубина:%dм\n Соленость:%.3lf%% \n", new_node->Name,
               new_node->Country, new_node->depth,
               new_node->salinity);
        printf("\n");
        new_node = new_node->next;
    }
    getchar();
}

void node_record()
{
    system("cls");
    system("color 02");
    printf("Добавить запись\n");
    int a = 0;
    struct Lake* new_node;

    new_node = (struct Lake*)malloc(sizeof(struct Lake));
    if(Head != NULL)
        new_node->next = Head;
    else
        new_node->next = NULL;
    Head = new_node;
    printf("Введите название озера\n");
    scanf("%s", new_node->Name);
    printf("Введите название страны, где находится данное озеро\n");
    scanf("%s", new_node->Country);
    while(a == 0)
    {
        fflush(stdin);
        printf("Введите глубину озера в метрах\n");
        a = scanf("%d", &new_node->depth);
    }
    a = 0;
    while(a == 0)
    {
        fflush(stdin);
        printf("Введите соленость озера в процентах\n");
        a = scanf("%lf", &new_node->salinity);
    }
    getchar();
}

void node_search()
{
    system("cls");
    system("color 02");
    struct Lake* new_node = Head;

    printf("\n");
    while(new_node != NULL)
    {
        if(new_node->depth < 50)
            if(new_node->salinity > 20)
            {
                printf("Название:%s\n Страна:%s\n Глубина:%dм\n Соленость:%.3lf%%\n", new_node->Name,
               new_node->Country, new_node->depth,
               new_node->salinity);
               printf("\n");
            }
        new_node = new_node->next;
    }
    getchar();
}
void ENTER()
{
    switch(enter_menu)
    {
        case 1:
            {
                node_print();
                break;
            }
        case 2:
            {
                node_record();
                break;
            }
        case 3:
            {
                node_search();
                break;
            }
    }
}
void UP()
{
    if(enter_menu == 1)
        enter_menu = 3;
    else
        enter_menu--;
}
void DOWN()
{
    if(enter_menu == 3)
        enter_menu = 1;
    else
        enter_menu++;
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choise;
    system("color 02");
    file_open();
    do
    {
        system("cls");
        print_menu();
        fflush(stdin);
        choise = getch();
        if (choise == 224)
        {
            choise = getch();
        }
        switch(choise)
        {
        case 13:
            {
                ENTER();
                break;
            }
        case 72:
            {
                UP();
                break;
            }
        case 80:
            {
                DOWN();
                break;
            }
        }
    }while(choise != 27);
    file_close();
}

