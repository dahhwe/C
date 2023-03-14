//
// Created by dahhw on 13-Mar-23.
//

#ifndef SYS3_FUNCTIONS_H
#define SYS3_FUNCTIONS_H

/**
 * Выводит графическое меню программы.
 */
void printMenu();

/**
 * Проверка ввода.
 * @param count Максимальное значение.
 * @return Корректное значение.
 */
int getVariant(int count);

/**
 * Проверяет является ли char числом.
 * @param str Строка.
 * @return Корректный ввод.
 */
int isNumber(char *str);

/**
 * Проверяет состоит ли вся строка исключительно из чисел.
 * @param str Строка для проверки.
 */
void checkString(char *str);

/**
 * Проверяет корректное значение для указания прибыли / убытка.
 * @param profitLoss Значение для проверки.
 */
void checkProfitLoss(char *profitLoss);

/**
 * Создает новый элемент структуры данных Data,
 * заполняет его переданными параметрами и добавляет его в начало списка.
 */
void add();

/**
 * Возвращает количество организаций.
 * @return Количество организаций.
 */
int countOrganizations();

/**
 * Возвращает корректный номер организации выбранный пользователем для изменения.
 * @param numOfOrg Номер организации.
 * @return Корректный номер организации для изменения.
 */
int GetOrganizationChoice(int numOfOrg);

/**
 * Изменение данных организации.
 * @param current Организация для изменений.
 */
void editOrganization(Data *current);

/**
 * Находит элемент в списке, соответствующий переданным
 * параметрам компании и подразделения, и изменяет его поля
 * прибыли или убытка и значения связанные с этим.
 */
void modify();

/**
 * Находит элемент в списке, соответствующий переданным
 * параметрам компании и подразделения, и удаляет его из списка.
 */
void delete();

/**
 * Находит элемент в списке, соответствующий
 * переданным параметрам компании и подразделения,
 * и возвращает его. Если элемент не найден, возвращается NULL.
 */
Data *read();

/**
 * Печатает все элементы списка, начиная с головы.
 */
void displayAll();

/**
 * Вывод информации о выбранных пользователем организациях.
 */
void displayCompanies();

/**
 * Вычисляет выводит все организации отсортированные по их прибыли в порядке убывания.
 */
void calculateProfitLoss();

#endif //SYS3_FUNCTIONS_H
