# Практическая работа №2 Синхронизация потоков в ОС GNU/Linux


## Цель работы

Изучение программных средств синхронизации потоков в ОС.

## Задачи

1. Ознакомиться с краткими теоретическими сведениями по синхронизации потоков в ОС GNU/Linux.
2. Получить у преподавателя индивидуальный вариант задания, в которой для выполнения различных частей создаются и
   запускаются потоки выполнения, а для синхронизации доступа к требуемым ресурсам используются соответствующие объекты
   ОС. Студент вправе выполнять инициативный проект, при условии согласования постановки задачи с преподавателем.
3. Используя изученные механизмы, разработать и отладить программу, выполняющую заданную работу.
4. Составить общее описание результатов, инструкции по сборке и использованию программы, а также инструкцию по получению
   документации, сформировать архив формата tar.gz и представить на проверку с исходными текстами программы. Внимание:
   исходные тексты программ должны соответствовать принятому стандарту кодирования, а также содержать комментарии в
   стиле системы doxygen.

## Вариант задания

Студенты (потоки) сдают экзамен. В аудитории N
парт и один стол экзаменатора (разделяемые ресурсы). Студенты подходят к
экзаменатору в произвольном порядке и садятся сдавать экзамен.
Далее экзаменатор либо ставит студенту оценку, либо выгоняет его, либо
отправляет еще раз подумать за парту (это состояние является случайной
величиной с равномерным законом). Когда аудитория освобождается, заходит
новая группа студентов.
Значение N задается пользователем при старте приложения.