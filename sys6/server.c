#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>

#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int serverSocket;
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
    writeToLog("Сигнал получен, закрываю сокет сервера");
    // Закрытие сокета сервера
    close(serverSocket);
    fclose(logFile);
    exit(EXIT_SUCCESS);
}

void alarmHandler() {
    // Обработка срабатывания таймера
    writeToLog("Время работы вышли, закрываю сокет сервера");
    // Закрытие сокета сервера
    close(serverSocket);
    fclose(logFile);
    exit(EXIT_SUCCESS);
}


int dayOfWeek(char *date) {
    struct tm tm = {0};
    int day, month, year;
    sscanf(date, "%d.%d.%d", &day, &month, &year);
    tm.tm_mday = day;
    tm.tm_mon = month - 1;
    tm.tm_year = year - 1900;
    time_t t = mktime(&tm);
    return (localtime(&t)->tm_wday + 6) % 7;
}

int main(int argc, char *argv[]) {
    int opt;
    struct sockaddr_in serverAddress, client_address;
    socklen_t client_address_length;
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

    writeToLog("Сервер запущен");
    // Перехват сигналов
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    // Настройка таймера неактивности клиентской стороны
    signal(SIGALRM, alarmHandler);
    alarm(timeout);

    // Создание сокета
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Настройка адреса сервера
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    // Привязка сокета к адресу
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    writeToLog("Сокет сервера прикреплен к адресу");

    // Прослушивание соединений
    if (listen(serverSocket, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    writeToLog("Сервер ожидает соединений");

    while (1) {
        // Принятие соединения
        client_address_length =sizeof(client_address);
        int clientSocket = accept(serverSocket, (struct sockaddr *) &client_address, &client_address_length);
        if (clientSocket == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        writeToLog("Соединение с клиентом установлено");

        // Получение данных от клиента
        int length = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
        buffer[length] = 0;

        writeToLog("Данные от клиента получены сервером");

        // Проверка корректности введенной даты
        int day, month, year;
        if (sscanf(buffer, "%d.%d.%d", &day, &month, &year) != 3 || month < 1 || month > 12 || year < 1601) {
            strcpy(buffer, "Некорректная дата!");
        } else {
            int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
                daysInMonth[1] = 29;
            }

            // Отчистка буфера
            if (day < 1 || day > daysInMonth[month - 1]) {
                memset(buffer, 0, BUFFER_SIZE);
                strcpy(buffer, "Некорректная дата!");
            } else {
                // Обработка данных и формирование ответа
                int dow = dayOfWeek(buffer);
                char *days[] = {"Понедельник", "Вторник", "Среда",
                                "Четверг", "Пятница", "Суббота",
                                "Воскресенье",};
                memset(buffer, 0, BUFFER_SIZE);
                strcpy(buffer, days[dow]);
            }
        }

        writeToLog("Данные обработаны сервером, сформирован ответ");

        // Отправка ответа клиенту
        send(clientSocket, buffer, sizeof(buffer), 0);

        writeToLog("Ответ отправлен клиенту");

        // Закрытие сокета клиента
        close(clientSocket);

        writeToLog("Закрываю сокет клиента");
    }
}
