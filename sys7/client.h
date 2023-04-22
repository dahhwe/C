//
// Created by super on 04.04.23.
//
#ifndef SYS5_CLIENT_H
#define SYS5_CLIENT_H


#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

/*!
 * @brief Записывает логи в файл.
 * @param event Действие.
 */
void writeToLog(char *event);

/*!
 * @brief Закрывает сокет сервера.
 */
void signalHandler();


/*!
 * @brief Таймер, по истечению которого закрывает сокет сервера
 */
void alarmHandler();


/*!
 * @brief Пример использования команд для парсинга аргументов
 */
void printUsage();

/**
 * @brief Основная функция клиента.
 *
 * Создает сокет клиента и подключается к серверу.
 * Отправляет данные серверу и получает ответ от сервера.
 * Выводит ответ сервера на экран.
 * @return Завершение программы.
 */
int main();


#endif //SYS5_CLIENT_H
