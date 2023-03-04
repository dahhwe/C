#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <windows.h>

struct timespec ts;

#define MAX_STUDENTS 10

int N;
int students_in_exam = 0;
int students_waiting = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t exam_finished = PTHREAD_COND_INITIALIZER;

void *student(void *arg) {
    int id = *(int *) arg;
    pthread_mutex_lock(&mutex);
    while (students_in_exam >= N) {
        students_waiting++;
        pthread_cond_wait(&exam_finished, &mutex);
        students_waiting--;
    }
    students_in_exam++;
    printf("Студент %d готовится сдачи экзамена\n", id);
    pthread_mutex_unlock(&mutex);

    srand(time(NULL) ^ id); // Перезагрузка генератора случайных чисел
    int result = rand() % 3;

    ts.tv_sec = 1 + rand() % 5;
    ts.tv_nsec = 0;
    nanosleep(&ts, NULL);

    pthread_mutex_lock(&mutex);
    if (result == 0) {
        printf("\033[1;32mЭкзаменатор поставил студенту %d оценку %d\n\033[0m", id, rand() % 3 + 3);
        ts.tv_sec = 1; // Добавление задержки между результатами каждого ученика
        ts.tv_nsec = 0;
    } else if (result == 1) {
        printf("\033[1;31mЭкзаменатор пинками выгнал студента %d\n\033[0m", id);
        ts.tv_sec = 1;
        ts.tv_nsec = 0;
    } else {
        printf("\033[1;33mСтудент %d попробовал сдать работу экзаменатору и был отправлен "
               "подумать за парту\n\033[0m", id);
        ts.tv_sec = 1;
        ts.tv_nsec = 0;
        students_in_exam--;
        pthread_cond_signal(&exam_finished);
        pthread_mutex_unlock(&mutex);
        student(arg);
        return NULL;
    }
    students_in_exam--;
    pthread_cond_signal(&exam_finished);
    pthread_mutex_unlock(&mutex);

}

int main(int argc, char **argv) {
    SetConsoleOutputCP(CP_UTF8);
    if (argc < 2) {
        printf("Введите количество парт в аудитории: ");
        scanf("%d", &N);
    } else {
        N = atoi(argv[1]);
    }

    int students[MAX_STUDENTS];
    pthread_t threads[MAX_STUDENTS];

    // Цикл, позволяющий сдавать несколько экзаменов
    while (1) {
        for (int i = 0; i < MAX_STUDENTS; i++) {
            students[i] = i + 1;
            pthread_create(&threads[i], NULL, student, &students[i]);
        }

        for (int i = 0; i < MAX_STUDENTS; i++) {
            pthread_join(threads[i], NULL);
        }

        // Предлагает пользователю начать другой экзамен
        printf("\nНачать новый экзамен? (y/n): ");
        char c;
        scanf(" %c", &c);

        if (c != 'y' && c != 'Y') break;
    }

    return 0;
}
