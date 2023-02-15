/*!
 * \file main.c
 * \brief Код родительского процесса программы
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*!
 * Создаёт новый дочерний поток методом fork-and-exec
 * \param[in] program Имя программы для запуска в дочернем процессе
 * \param[in] argList[] Список аргументов для запуска дочерней программы
 * \retun PID дочернего процесса
*/
int spawn(char *program, char **argList)
{
    pid_t childPid;

    /* Дупликация этого процесса.  */
    childPid = fork();
    if (0 != childPid)
    {
        /* Это родительский процесс.  */
        return childPid;
    } else
    {
        /* Запускаем PROGRAM. */
        execvp(program, argList);

        /* Функция execvp возвращает значение только если случилась ошибка */
        fprintf(stderr, "случилась ошибка в execvp\n");
        abort();
    }
}

/*!
 * Основная точка входа программы
 * \return Код завершения программы
*/
int main()
{
    int childStatus;

    /* Список аргументов */
    char *argList[] = {};

    printf("Запуск дочернего процесса...\n");

    /* Запускает дочерний процесс. */
    spawn("./child", argList);

    /* Ждём, пока закончится дочерний процесс.  */
    wait(&childStatus);
    if (WIFEXITED(childStatus))
    {
        printf("Дочерний процесс завершился нормально с кодом %d.\n",
               WEXITSTATUS(childStatus)
        );
    } else
    {
        printf("Дочерний процесс закончился ненормально.\n");
    }
    return 0;
}
