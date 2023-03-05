#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>

struct timespec ts;
int results[100] = {0};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t examFinished = PTHREAD_COND_INITIALIZER;

int getInputInRange(int min, int max) {
    int input;
    char c;
    bool valid = false;
    while (!valid) {
        printf("Введите целое число (%d - %d): ", min, max);
        if (scanf("%d%c", &input, &c) == 2 && c == '\n' && input >= min && input <= max) {
            valid = true;
        } else {
            printf("Некорректный ввод!в Попробуйте еще раз.\n");
            while (getchar() != '\n'); // отчистка буфера
        }
    }
    return input;
}


void *student(void *arg) {
    int studID = *(int *) arg;
    int maxNumOfStudAllowed = *(int *) arg;
    int studentsInExam = 0;
    int studentsWaiting = 0;

    pthread_mutex_lock(&mutex);
    while (studentsInExam >= maxNumOfStudAllowed) {
        studentsWaiting++;
        pthread_cond_wait(&examFinished, &mutex);
        studentsWaiting--;
    }
    studentsInExam++;
    printf("Студент #%d готовится к сдаче экзамена\n", studID);
    pthread_mutex_unlock(&mutex);

    srand(time(NULL) ^ studID); // Перезагрузка генератора случайных чисел
    int result = rand() % 3;

    ts.tv_sec = 1 + rand() % 5;
    ts.tv_nsec = 0;
    nanosleep(&ts, NULL);

    printf("Студент #%d подходит сдавать работу\n", studID);
    pthread_mutex_lock(&mutex);
    if (result == 0) {
        printf("\033[1;32mЭкзаменатор поставил студенту #%d оценку %d\n\033[0m", studID, rand() % 3 + 3);
        results[studID - 1] = 1; // Студент сдал экзамен
        ts.tv_sec = 1; // Добавление задержки между результатами каждого ученика
        ts.tv_nsec = 0;
    } else if (result == 1) {
        printf("\033[1;31mЭкзаменатор выгнал студента #%d за списывание!\n\033[0m", studID);
        results[studID - 1] = -1; // Студент не сдал экзамен
        ts.tv_sec = 1;
        ts.tv_nsec = 0;
    } else {
        printf("\033[1;33mЭкзаменатор отправил студента #%d подумать еще за парту\n\033[0m", studID);
        ts.tv_sec = 1;
        ts.tv_nsec = 0;
        studentsInExam--;
        pthread_cond_signal(&examFinished);
        pthread_mutex_unlock(&mutex);
        student(arg);
        return NULL;
    }
    studentsInExam--;
    pthread_cond_signal(&examFinished);
    pthread_mutex_unlock(&mutex);
}

void printResults(int maxStudents) {
    int numPassed = 0;
    int numFailed = 0;
    for (int i = 0; i < maxStudents; i++) {
        if (results[i] == 1) {
            numPassed++;
        } else if (results[i] == -1) {
            numFailed++;
        }
    }
    printf("╭────────────────────────────────────╮\n"
           "│             Результаты             │\n"
           "╰────────────────────────────────────╯\n");
    printf("Студентов сдавших экзамен: %d\n", numPassed);
    printf("Студентов проваливших экзамен: %d\n", numFailed);
}

int main() {
    int maxStudents;
    SetConsoleOutputCP(CP_UTF8);
    printf("Введите количество студентов сдающих экзамен\n");
    maxStudents = getInputInRange(1, 100);
    pthread_t threads[maxStudents];


    while (1) {
        printf("╭────────────────────────────────────╮\n"
               "│          Начало экзамена           │\n"
               "╰────────────────────────────────────╯\n");
        for (int i = 0; i < maxStudents; i++) {
            int *id = malloc(sizeof(int));
            *id = i + 1;
            pthread_create(&threads[i], NULL, student, id);
        }

        for (int i = 0; i < maxStudents; i++) {
            pthread_join(threads[i], NULL);
        }

        printResults(maxStudents);
        char c;

        printf("\nНачать новый экзамен? (y/n): ");
        scanf(" %c", &c);

        if (c != 'y' && c != 'Y') break;
    }

    return 0;
}
