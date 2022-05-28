#include "functions.h"
#include "structs.h"
#include "stdbool.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <intrin.h>


#define BACKSPACE_KEY 8
#define START_CHAR_RANGE 32
#define END_CHAR_RANGE 126
#define MAX_INPUT_ARRAY_LEN 100


DblLinkedList* createDblLinkedList()
{
    DblLinkedList *tmp = (DblLinkedList*) malloc(sizeof(DblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    return tmp;
}

char* getBrand()
{
    char* brand=NULL;
    puts("Enter Accumulators Name:");
    gets(brand);
    return brand;
}


void deleteDblLinkedList(DblLinkedList **list)
{
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while (tmp)
    {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

int inputIntCheck(char valueArray[])
{
    for (int i = 0; i < strlen(valueArray) - 1; ++i)
    {
        if ((valueArray[i] < '0') || (valueArray[i] > '9'))
        {
            return false;
        }
    }
    return true;
}

void addAccumulator(double price, double voltage, double capacity,
                    DblLinkedList* list)
{
    accumulator tmpAcc;

    tmpAcc.price = price;
    tmpAcc.voltage = voltage;
    tmpAcc.capacity = capacity;

    Node *tmp = (Node*) malloc(sizeof(Node));

    tmp->value = tmpAcc;
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail)
    {
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL)
    {
        list->head = tmp;
    }
    list->size++;
}

Node* getNode(DblLinkedList *list, size_t accNumber)
{
    Node *tmp = list->head;
    size_t i = 0;

    while (tmp && i < accNumber)
    {
        tmp = tmp->next;
        i++;
    }

    return tmp;
}

void deleteAcc(size_t accNumber, DblLinkedList* list)
{
    Node* element = NULL;
    element = getNode(list, accNumber);
    if (element == NULL)
    {
        puts("Incorrect value!");
        return;
    }
    if (element->prev)
    {
        element->prev->next = element->next;
    }
    if (element->next)
    {
        element->next->prev = element->prev;
    }

    if (!element->prev)
    {
        list->head = element->next;
    }
    if (!element->next)
    {
        list->tail = element->prev;
    }
    list->size--;
    free(element);
    puts("Deleted");
}

void printStructs(DblLinkedList* list)
{
    Node *tmp = list->head;
    int i = 0;

    if (list->size == 0)
    {
        puts("No structures present");
        return;
    }
    while (tmp)
    {
        printf("Struct number: %d\n", i);
        printf("price: %.3f\n voltage: %.3f\n capacity: %.3f\n\n",
               tmp->value.price, tmp->value.voltage,
               tmp->value.capacity);

        tmp = tmp->next;
        ++i;
    }
}

void filterStructs(DblLinkedList* list)
{
    printStructs(list);
}

void printFilterMenu()
{
    puts("|           FILTRATION MANAGEMENT           |");
    puts("|-------------------------------------------|");
    puts("1. Filter by brand");
    puts("2. Filter by price");
    puts("3. Print by voltage");
    puts("4. Filter by capacity");
    puts("5. Exit");
}

void printMenu()
{
    puts("\n|-------------------------------------------|");
    puts("|          ACCUMULATORS MANAGEMENT          |");
    puts("|-------------------------------------------|");
    puts("1. Add Accumulator information");
    puts("2. Delete Accumulator information");
    puts("3. Print all Accumulators");
    puts("4. Reverse a list");
    puts("5. Save");
    puts("6. Load");
    puts("7. Exit");
}

void swap(Node* node)
{
    Node* prev = node->prev;
    node->prev = node->next;
    node->next = prev;
}

void reverseList(DblLinkedList *list)
{
    Node* prev = NULL;
    Node* curr = list->head;

    while (curr != NULL)
    {
        swap(curr);
        prev = curr;
        curr = curr->prev;
    }

    if (prev != NULL)
    {
        list->head = prev;
    }
}

int save(DblLinkedList* list)
{
    FILE *file = fopen("accumulators.txt", "w");
    Node *tmp = list->head;
    if (!list->head)
    {
        fclose(file);
        puts("Error while reading a file");
    }
    else
    {
        fprintf(file, "%zu\n", list->size);
        for (int i = 0; i < list->size; i++)
        {
            Node *cur_node = getNode(list, i);
            fprintf(file, "price: %.3f\n voltage: %.3f\n capacity: %.3f\n\n",
                    tmp->value.price, tmp->value.voltage,
                    tmp->value.capacity);
        }
    }
    fclose(file);
    return 0;
}

int load()
{
    DblLinkedList* list = createDblLinkedList();

    FILE* file;
    char* line = NULL;
    size_t length = 0;
    ssize_t SizeToread;

    file = fopen("accumulators.txt", "r+");
    if (file == NULL)
        return -1;

    while ((SizeToread = getline(&line, &length, file)) != -1)
    {
        printf("%s", line);
    }

    free(line);
    fclose(file);

    return 0;
}

char* getDynamicString()
{
    char* userStr = (char*) malloc(1 * sizeof(char));
    userStr[0] = '\0';
    char curChar = 0;
    int curSize = 1;

    puts("Enter Accumulators Brand:");
    while(curChar != '\n')
    {
        curChar = getchar();
        int deltaVal = 0;

        int lengthDif = 0;
        if (curChar >= START_CHAR_RANGE &&
            curChar <= END_CHAR_RANGE)
        {
            deltaVal = 1;
            lengthDif = 2;
        }
        else
            continue;

        int newSize = curSize + deltaVal;
        if (newSize == 0)
            continue;
        char* tmpStr = (char*) malloc(newSize * sizeof(char));
        if (tmpStr)
        {
            for (int i = 0; i < newSize - lengthDif; ++i)
                tmpStr[i] = userStr[i];
            if (curChar != BACKSPACE_KEY)
                tmpStr[newSize - 2] = curChar;
            tmpStr[newSize - 1] = '\0';
            free(userStr);
            userStr = tmpStr;
            curSize = newSize;
        }
        else
        {
            printf("Unable to allocate memory!");
            break;
        }
    }
    return userStr;
}

int meetingsCount(const char* str, const char* substr)
{
    return ( str = strstr(str, substr) ) ?
           1 + meetingsCount(str + 1, substr) : 0;
}

int intInputCheck()
{
    char strArrayLen[MAX_INPUT_ARRAY_LEN];
    fgets(strArrayLen, MAX_INPUT_ARRAY_LEN, stdin);
    fflush(stdin);
    if (!(inputIntCheck(strArrayLen))
        || strArrayLen[0] == '\0')
    {
        return -1;
    }

    return strtol(strArrayLen, NULL, 10);
}
