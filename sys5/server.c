#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>

#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int day_of_week(char *date) {
    struct tm tm = {0};
    int day, month, year;
    sscanf(date, "%d.%d.%d", &day, &month, &year);
    tm.tm_mday = day;
    tm.tm_mon = month - 1;
    tm.tm_year = year - 1900;
    time_t t = mktime(&tm);
    return (localtime(&t)->tm_wday + 6) % 7;
}


int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length;
    char buffer[BUFFER_SIZE];

    // Создание сокета
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Настройка адреса сервера
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    // Привязка сокета к адресу
    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Прослушивание соединений
    if (listen(server_socket, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Принятие соединения
        client_address_length = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_address_length);
        if (client_socket == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Получение данных от клиента
        int length = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        buffer[length] = 0;

// Проверка корректности введенной даты
        int day, month, year;
        if (sscanf(buffer, "%d.%d.%d", &day, &month, &year) != 3 || month < 1 || month > 12 || year < 1601) {
            strcpy(buffer, "Некорректная дата!");
        } else {
            int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
                days_in_month[1] = 29;
            }

            // Отчистка буфера
            if (day < 1 || day > days_in_month[month - 1]) {
                memset(buffer, 0, BUFFER_SIZE);
                strcpy(buffer, "Некорректная дата!");
            } else {
                // Обработка данных и формирование ответа
                int dow = day_of_week(buffer);
                char *days[] = {"Понедельник", "Вторник", "Среда",
                                "Четверг", "Пятница", "Суббота",
                                "Воскресенье",};
                memset(buffer, 0, BUFFER_SIZE);
                strcpy(buffer, days[dow]);
            }
        }

        // Отправка ответа клиенту
        send(client_socket, buffer, sizeof(buffer), 0);

        // Закрытие сокета клиента
        close(client_socket);
    }
}
