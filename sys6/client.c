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

#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int clientSocket;
char *logFileName;
int timeout;
FILE *logFile;

void writeToLog(char *event) {
    time_t currentTime = time(NULL);
    char *timeStr = ctime(&currentTime);
    timeStr[strlen(timeStr) - 1] = '\0'; // Удаление символа новой строки
    fprintf(logFile, "[%s] %s\n", timeStr, event);
}

void signalHandler() {
    // Обработка сигналов
    writeToLog("Сигнал получен, закрываю сокет клиента");
    // Закрытие сокета клиента
    close(clientSocket);
    fclose(logFile);
    exit(EXIT_SUCCESS);
}

void alarmHandler() {
    // Обработка срабатывания таймера
    writeToLog("Время работы вышло, закрываю сокет со стороны клиента");
    // Закрытие сокета клиента
    close(clientSocket);
    fclose(logFile);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    int opt;
    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE];

    // Обработка аргументов командной строки
    while ((opt = getopt(argc, argv, "l:t:")) != -1) {
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
            default:
                fprintf(stderr, "Usage: %s [-l logFileName] [-t timeout]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
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
