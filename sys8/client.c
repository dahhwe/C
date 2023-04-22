#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>
#include <time.h>
#include <sys/statvfs.h>

#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int clientSocket;
char *logFileName;
int timeout;
FILE *logFile;
int checkDiskUsage = 0;

void writeToLog(char *event) {
    time_t currentTime = time(NULL);
    char *timeStr = ctime(&currentTime);
    timeStr[strlen(timeStr) - 1] = '\0'; // Удаление символа новой строки
    fprintf(logFile, "[%s] %s\n", timeStr, event);
}


void signalHandler() {
    // Обработка сигналов
    writeToLog("Сигнал получен, закрываю сокет сервера");
    if (checkDiskUsage) {
        struct statvfs stat;
        if (statvfs(logFileName, &stat) != 0) {
            perror("statvfs");
            exit(EXIT_FAILURE);
        }
        time_t currentTime = time(NULL);
        char *timeStr = ctime(&currentTime);
        timeStr[strlen(timeStr) - 1] = '\0'; // Удаление символа новой строки
        double usedSpace = (double) (stat.f_blocks - stat.f_bfree) / stat.f_blocks * 100;
        fprintf(logFile, "[%s] Использование диска: %.2f%%\n", timeStr, usedSpace);
    }
    // Закрытие сокета сервера
    close(clientSocket);
    fclose(logFile);
    exit(EXIT_SUCCESS);
}

void alarmHandler() {
    // Обработка срабатывания таймера
    writeToLog("Время работы вышло, закрытие сокета клиента");
    if (checkDiskUsage) {
        struct statvfs stat;
        if (statvfs(logFileName, &stat) != 0) {
            perror("statvfs");
            exit(EXIT_FAILURE);
        }
        time_t currentTime = time(NULL);
        char *timeStr = ctime(&currentTime);
        timeStr[strlen(timeStr) - 1] = '\0'; // Удаление символа новой строки
        double usedSpace = (double) (stat.f_blocks - stat.f_bfree) / stat.f_blocks * 100;
        fprintf(logFile, "[%s] Использование диска: %.2f%%\n", timeStr, usedSpace);
    }
    // Закрытие сокета сервера
    close(clientSocket);
    fclose(logFile);
    exit(EXIT_SUCCESS);
}

void printUsage() {
    printf("Usage: client [-l logFileName] [-t timeout] [-c]\n");
    printf("  -l logFileName: имя файла для записи логов\n");
    printf("  -t timeout: время неактивности пользователя в секундах\n");
    printf("  -c: включить проверку заполнения дисков\n");
}

int main(int argc, char *argv[]) {
    int opt;
    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE];

    // Обработка аргументов командной строки
    while ((opt = getopt(argc, argv, "l:t:c")) != -1) {
        switch (opt) {
            case 'l':
                logFileName = optarg;
                logFile = fopen(logFileName, "a");
                if (logFile == NULL) {
                    perror("fopen");
                    exit(EXIT_FAILURE);
                }
                break;
            case 't':
                timeout = atoi(optarg);
                break;
            case 'c':
                checkDiskUsage = 1;
                break;
            default:
                printUsage();
                exit(EXIT_FAILURE);
        }
    }

    if (argc == 1) {
        printUsage();
        exit(EXIT_SUCCESS);
    }
    writeToLog("Клиент запущен");

    // Перехват сигналов
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    // Настройка таймера неактивности пользователя
    signal(SIGALRM, alarmHandler);
    alarm(timeout);

    // Создание сокета
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Настройка адреса сервера
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    // Подключение к серверу
    if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    writeToLog("Установлено подключение к серверу");

    // Отправка данных серверу
    printf("Введите дату (DD.MM.YYYY): ");
    fgets(buffer, BUFFER_SIZE, stdin);
    send(clientSocket, buffer, strlen(buffer), 0);

    writeToLog("Данные отправлены на сервер для обработки");

    // Получение ответа от сервера
    recv(clientSocket, buffer, BUFFER_SIZE, 0);
    printf("Ответ сервера: %s\n", buffer);

    writeToLog("Получен ответ от сервера");

    // Закрытие сокета
    close(clientSocket);
    writeToLog("Работа клиента завершена");
    fclose(logFile);

    return 0;
}
