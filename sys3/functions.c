#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "structs.h"

Data *head = NULL;

void printMenu() {
    printf("\n╭────────────────────────────────────╮\n"
           "│            Главное Меню            │\n"
           "╰────────────────────────────────────╯");
    printf("\n#1 Добавить организацию\n");
    printf("#2 Модифицировать организацию\n");
    printf("#3 Удалить организацию\n");
    printf("#4 Вывести информацию о конкретной организации\n");
    printf("#5 Отобразить прибыль / убыток организаций\n");
    printf("#6 Вывести выбранные организации\n");
    printf("#7 Выход\n");

}

int getVariant(int count) {
    int variant;
    char *string = (char *) malloc(100 * sizeof(char));
    char *endptr;
    scanf("%s", string);

    variant = strtol(string, &endptr, 10);

    while (*endptr != '\0' || variant < 1 || variant > count) {
        printf("Некорректный ввод, повторите:\n");
        printf(">");
        scanf("%s", string);
        variant = strtol(string, &endptr, 10);
    }

    free(string);
    return variant;
}

int isNumber(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

void checkString(char *str) {
    while (isNumber(str)) {
        printf("Недопустимый ввод. Пожалуйста, введите строку: ");
        scanf("%s", str);
    }
}

void checkProfitLoss(char *profitLoss) {
    while (*profitLoss != '+' && *profitLoss != '-') {
        printf("Недопустимый ввод! Пожалуйста, введите + или -: ");
        scanf(" %c", profitLoss);
    }
}

void add() {
    char *company;
    char *department;
    char profitLoss;
    int value;

    company = (char *) malloc(100);
    department = (char *) malloc(100);

    printf("Введите название организации: ");
    scanf("%s", company);

    checkString(company);

    printf("Введите отдел организации: ");
    scanf("%s", department);

    checkString(department);

    printf("Укажите, получила ли организация прибыль или убыток? (+/-): ");
    scanf(" %c", &profitLoss);

    checkProfitLoss(&profitLoss);

    printf("Введите сумму: ");
    scanf("%d", &value);

    Data *newData = (Data *) malloc(sizeof(Data));

    newData->company = (char *) realloc(company, strlen(company) + 1);
    newData->department = (char *) realloc(department, strlen(department) + 1);
    newData->profitLoss = profitLoss;
    newData->value = value;
    newData->next = head;
    head = newData;
}

int countOrganizations() {
    int count = 0;
    Data *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int GetOrganizationChoice(int numOfOrg) {
    int choice;
    bool correctAnswer = false;

    char *input = malloc(100 * sizeof(char));
    char *endptr;

    while (!correctAnswer) {
        fgets(input, 100, stdin);
        choice = strtol(input, &endptr, 10);

        if (endptr == input || *endptr != '\n') {
            printf("Недопустимый ввод. Введите число.\n");
            continue;
        }

        if (choice >= 1 && choice <= numOfOrg) {
            correctAnswer = true;
        } else {
            printf("Недопустимый ввод. Пожалуйста, выберите какую организацию вы хотите удалить (1 — %d)\n",
                   numOfOrg);
        }
    }

    free(input);

    return choice;
}

void editOrganization(Data *current) {
    char *input = malloc(100);
    int choice;

    printf("Организация для изменения: ");
    printf("%s | %s | %c | %d\n", current->company, current->department,
           current->profitLoss, current->value);

    printf("Выберите поле для изменения:\n");
    printf("#1 — Название компании\n");
    printf("#2 — Название отдела\n");
    printf("#3 — Прибыль/Убыток\n");
    printf("#4 — Значение\n");

    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1:
            printf("Введите новое название компании: ");
            fgets(input, 100, stdin);
            input[strcspn(input, "\n")] = 0;
            free(current->company);
            current->company = strdup(input);
            break;
        case 2:
            printf("Введите новое название отдела: ");
            fgets(input, 100, stdin);
            input[strcspn(input, "\n")] = 0;
            free(current->department);
            current->department = strdup(input);
            break;
        case 3:
            printf("Введите новый прибыль/убыток (+/-): ");
            scanf("%c", &current->profitLoss);
            break;
        case 4:
            printf("Введите новое значение: ");
            scanf("%d", &current->value);
            break;
        default:
            printf("Недопустимый выбор.\n");
    }
    printf("Изменено.");
    free(input);
}

void modify() {
    if (head == NULL) {
        printf("Организаций нет!\n");
        return;
    }
    Data *organizationToEdit = head;
    printf("Введите номер организации для изменения:");

    bool correctAnswer = false;

    int numOfOrg = countOrganizations();
    int choice = GetOrganizationChoice(numOfOrg);

    for (int i = 1; i < choice; i++) {
        organizationToEdit = organizationToEdit->next;
    }
    printf("%s | %s | %c | %d\n", organizationToEdit->company, organizationToEdit->department,
           organizationToEdit->profitLoss, organizationToEdit->value);

    editOrganization(organizationToEdit);

}

void delete() {
    if (head == NULL) {
        printf("Организаций нет!\n");
        return;
    }

    Data *current = head;
    printf("Введите номер организации для удаления:");

    int numOfOrg = countOrganizations();
    int choice = GetOrganizationChoice(numOfOrg);

    if (choice == 1) {
        head = head->next;
        free(current->company);
        free(current->department);
        free(current);
    } else {
        for (int i = 1; i < choice - 1; i++) {
            current = current->next;
        }
        Data *temp = current->next;
        current->next = temp->next;
        free(temp->company);
        free(temp->department);
        free(temp);
    }
}

void read() {
    printf("Введите название компании, которое вы хотите вывести: ");

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    char *input = malloc(100 * sizeof(char));
    fgets(input, 100, stdin);

    input[strcspn(input, "\n")] = 0;

    Data *current = head;
    int count = 1;
    bool found = false;
    while (current != NULL) {
        if (strcmp(current->company, input) == 0) {
            printf("#%d | %s | %s | %c | %d\n", count, current->company, current->department,
                   current->profitLoss, current->value);
            found = true;
            break;
        }
        current = current->next;
        count++;
    }

    if (!found) {
        printf("Организация с названием '%s' не была найдена.\n", input);
    }

    free(input);
}

void displayAll() {
    Data *current = head;
    int count = 1;
    while (current != NULL) {
        printf("#%d | %s | %s | %c | %d\n", count, current->company, current->department,
               current->profitLoss, current->value);
        current = current->next;
        count++;
    }
}

void displayCompanies() {
    Data *current = head;
    int count = 1;
    while (current != NULL) {
        printf("#%d | %s\n", count, current->company);
        current = current->next;
        count++;
    }
    printf("Введите номера организаций, информацию о которых вы хотите получить (через пробел): ");

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    char *input = malloc(100 * sizeof(char));
    fgets(input, 100, stdin);

    int choice;
    char *token = strtok(input, " ");

    while (token != NULL) {
        choice = atoi(token);

        current = head;
        count = 1;
        while (current != NULL) {
            if (count == choice) {
                printf("#%d | %s | %s | %c | %d\n", count, current->company, current->department,
                       current->profitLoss, current->value);
                break;
            }
            current = current->next;
            count++;
        }

        token = strtok(NULL, " ");
    }

    free(input);
}


void calculateProfitLoss() {
    int size = 0;
    Data *current = head;
    while (current != NULL) {
        size++;
        current = current->next;
    }

    Data **companies = malloc(size * sizeof(Data *));

    current = head;
    int i = 0;
    while (current != NULL) {
        companies[i] = current;
        i++;
        current = current->next;
    }

    for (int companyNum = 0; companyNum < size - 1; companyNum++) {
        for (int j = 0; j < size - companyNum - 1; j++) {
            int value1 = companies[j]->value;
            if (companies[j]->profitLoss == '-') {
                value1 *= -1;
            }

            int value2 = companies[j + 1]->value;
            if (companies[j + 1]->profitLoss == '-') {
                value2 *= -1;
            }

            if (value1 < value2) {
                Data *temp = companies[j];
                companies[j] = companies[j + 1];
                companies[j + 1] = temp;
            }
        }
    }

    for (int companyToPrint = 0; companyToPrint < size; companyToPrint++) {
        printf("#%d | %s | %s | %c | %d\n", companyToPrint + 1, companies[companyToPrint]->company,
               companies[companyToPrint]->department,
               companies[companyToPrint]->profitLoss, companies[companyToPrint]->value);
    }

    free(companies);
}
