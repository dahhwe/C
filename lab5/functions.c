#include "functions.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "stdbool.h"

#define BACKSPACE_KEY 8
#define START_CHAR_RANGE 32
#define END_CHAR_RANGE 126
#define MAX_INPUT_ARRAY_LEN 100


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

void addAccumulator(char* brand, double price, double voltage, double capacity,
                    accumulator **end_ptr)
{
    accumulator *end_p = *end_ptr;

    end_p->brand = brand;
    end_p->price = price;
    end_p->voltage = voltage;
    end_p->capacity = capacity;

    (*end_ptr)++;
}

void deleteGap(int gapNumber, accumulator *gapArray, accumulator **endPtr)
{
    accumulator *endP = *endPtr;
    int gapCount = endP - gapArray;

    if (gapNumber > gapCount || gapNumber == 0)
    {
        puts("Incorrect value!");
        return;
    }

    for (gapArray += gapNumber - 1; gapArray != (endP - 1); ++gapArray)
    {
        accumulator nextGap = *(++gapArray);
        --gapArray;
        *gapArray = nextGap;
    }
    (*endPtr)--;
    puts("Deleted");
}

void printStructs(accumulator *accArray, accumulator *endPtr)
{
    if (accArray == endPtr)
    {
        puts("No structures present");
        return;
    }
    for (int i = 1; accArray != endPtr; ++accArray, ++i)
    {
        printf("Struct number: %d\n", i);
        printf("brand: %s\n price: %.3f\n voltage: %.3f\n capacity: %.3f\n\n",
               accArray->brand, accArray->price, accArray->voltage,
               accArray->capacity);

    }
}

void filterStructs(accumulator *accArray, accumulator *endPtr)
{
    bool printed = false;
    int userChoice;
    char* brandToFilter;
    double priceToFilter;
    double voltageToFilter;
    double capacityToFilter;

    if (accArray == endPtr)
    {
        puts("No structures present");
        return;
    }
    printFilterMenu();
    printf("Enter your choice:\n");
    printf(">");
    userChoice = intInputCheck();
    switch (userChoice)
    {
        case FILTER_BY_BRAND:
        {
            brandToFilter = getBrand();

            for (int i = 1; accArray != endPtr; ++accArray, ++i)
            {
                if (strcmp(accArray->brand, brandToFilter) == 0)
                {
                    printed = true;
                    printf("brand: %s\n price: %f\n voltage: %f\n capacity: %f\n\n",
                           accArray->brand, accArray->price, accArray->voltage,
                           accArray->capacity);
                }
            }
        }
            break;

        case FILTER_BY_PRICE:
        {
            puts("Enter Accumulators Price:");
            priceToFilter = intInputCheck();

            for (int i = 1; accArray != endPtr; ++accArray, ++i)
            {
                if (accArray->price == priceToFilter)
                {
                    printed = true;
                    printf("brand: %s\n price: %f\n voltage: %f\n capacity: %f\n\n",
                           accArray->brand, accArray->price, accArray->voltage,
                           accArray->capacity);
                }
            }
        }
            break;

        case FILTER_BY_VOLTAGE:
        {
            puts("Enter Accumulators Voltage:");
            voltageToFilter = intInputCheck();

            for (int i = 1; accArray != endPtr; ++accArray, ++i)
            {
                if (accArray->voltage == voltageToFilter)
                {
                    printed = true;
                    printf("TEST 1:%d, 2:%d", accArray->voltage, voltageToFilter);
                    printf("brand: %s\n price: %.3f\n voltage: %.3f\n capacity: %.3f\n\n",
                           accArray->brand, accArray->price, accArray->voltage,
                           accArray->capacity);
                }
            }
        }
            break;

        case FILTER_BY_CAPACITY:
        {
            puts("Enter Accumulators Capacity:");
            capacityToFilter = intInputCheck();

            for (int i = 1; accArray != endPtr; ++accArray, ++i)
            {
                if (accArray->capacity == capacityToFilter)
                {
                    printed = true;
                    printf("brand: %s\n price: %.3f\n voltage: %.3f\n capacity: %.3f\n\n",
                           accArray->brand, accArray->price, accArray->voltage,
                           accArray->capacity);
                }
            }
        }
            break;
        default:
            puts("Incorrect value entered");
    }
    if (!printed)
        puts("Nothing was found");
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
    puts("4. Filter");
    puts("5. Save");
    puts("6. Load");
    puts("7. Exit");
}

int save(accumulator *st, int n)
{
    FILE *fp = fopen("gap_s.dat", "w");
    char *c;

    int size = n * sizeof(accumulator);

    c = (char *) &n;
    for (int i = 0; i < sizeof(int); ++i)
    {
        putc(*c++, fp);
    }

    c = (char *) st;
    for (int i = 0; i < size; ++i)
    {
        putc(*c, fp);
        c++;
    }
    fclose(fp);
    return 0;
}

int load()
{
    FILE *fp = fopen("gap_s.dat", "r+");
    char *c;
    int m = sizeof(int);
    int n, i;

    int *pti = (int *) malloc(m);

    c = (char *) pti;
    while (m > 0)
    {
        i = getc(fp);
        if (i == EOF) break;
        *c = i;
        c++;
        m--;
    }
    n = *pti;

    accumulator *ptr = (accumulator *) malloc(n * sizeof(accumulator));
    c = (char *) ptr;
    while ((i = getc(fp)) != EOF) {
        *c = i;
        c++;
    }

    for (int k = 0; k < n; ++k)
    {
        printf("Accumulator %d\n", k+1);
        printf("brand: %s\n price: %.3f\n voltage: %.3f\n capacity: %.3f\n\n",
               (ptr+k)->brand, (ptr+k)->price, (ptr+k)->voltage,
               (ptr+k)->capacity);
    }

    free(pti);
    free(ptr);
    fclose(fp);
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