#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>

#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int timeout;
int serverSocket;
int checkDiskUsage = 0;
char *logFileName;
FILE *logFile;

void writeToLog(char *event) {
    time_t currentTime = time(NULL);
    char *timeStr = ctime(&currentTime);
    timeStr[strlen(timeStr) - 1] = '\0'; // Удаление символа новой строки
    fprintf(logFile, "[%s] %s\n", timeStr, event);
}

void printUsage() {
    printf("Usage: server [-l logFileName] [-t timeout] [-c]\n");
    printf("  -l logFileName: имя файла для записи логов\n");
    printf("  -t timeout: время неактивности клиента в секундах\n");
    printf("  -c: включить проверку заполнения дисков\n");
}


int main(int argc, char *argv[]) {
    int opt;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientAddressLength;
    char buffer[BUFFER_SIZE];

    // Проверка идентификатора пользователя
    if (getuid() != 0) {
        fprintf(stderr, "Серверная часть должна запускаться только привилегированным пользователем\n");
        exit(EXIT_FAILURE);
    }

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


    writeToLog("Сервер запущен");

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
        clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);
        if (clientSocket == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        writeToLog("Соединение с клиентом установлено");

        // Получение данных от клиента
        int length = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
        buffer[length] = 0;

        writeToLog("Данные от клиента получены сервером");

        // Обработка данных и формирование ответа
        // ...

        writeToLog("Данные обработаны сервером, сформирован ответ");

        // Отправка ответа клиенту
        send(clientSocket, buffer, sizeof(buffer), 0);

        writeToLog("Ответ отправлен клиенту");

        // Закрытие сокета клиента
        close(clientSocket);

        writeToLog("Закрываю сокет клиента");
    }
}

