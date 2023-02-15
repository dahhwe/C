/*!
 * \file unit_tests.c
 * \brief Тестирование функций программы.
 */

#include <stdbool.h>
#include <CUnit/Basic.h>

#define UNIT_TESTS_LAUNCH

#include "child.c"
#include "structure.h"

/*!
 * \brief Первый тест
 */
void FirstTest() {
    Date getDate = {31, 12, 2007};
    bool dateValid = dateCheck(&getDate);
    CU_ASSERT_EQUAL(dateValid, true)

}

/*!
 * \brief Второй тест
 */
void SecondTest() {
    Date getDate = {31, 2, 2012};
    bool dateValid = dateCheck(&getDate);
    CU_ASSERT_EQUAL(dateValid, false)
}

/*!
 * \brief Третий тест
 */
void ThirdTest() {
    int min = 0;
    int max = 10;
    int num = 322;
    bool numInRange = isInRange(min, max, num);
    CU_ASSERT_EQUAL(numInRange, false)
}

/*!
 * \brief Четвертый тест
 */
void FourthTest() {
    int min = 1;
    int max = 3;
    int num = 2;
    bool numInRange = isInRange(min, max, num);
    CU_ASSERT_EQUAL(numInRange, true)
}

/*!
 * \brief Точка входа
 */
int main() {
    CU_pSuite suite;
    CU_initialize_registry();
    suite = CU_add_suite("main_suite", NULL, NULL);
    CU_ADD_TEST(suite, FirstTest);
    CU_ADD_TEST(suite, SecondTest);
    CU_ADD_TEST(suite, ThirdTest);
    CU_ADD_TEST(suite, FourthTest);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
