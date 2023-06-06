#include "unity.h"
#include "factorial.h"

void setUp(void)
{

}

void tearDown(void)
{

}

/*! test case function for checking
 *  output of factorial of 0
 */
void test_factorial_of_zero(void)
{
	TEST_ASSERT_EQUAL(1, factorial(0));
}

/*! test case function for checking
 *  output of factorial of 5 
 */
void test_factorial_of_five(void)
{
	TEST_ASSERT_EQUAL(120, factorial(5));
}

/*! test case function for checking
 *  output of factorial of 5 
 */
void test_factorial_of_minusthree(void)
{
	TEST_ASSERT_EQUAL(120, factorial(5));
}

/*! test case function for checking
 *  output of factorial of 5 
 */
void test_factorial_of_twenty(void)
{
	TEST_ASSERT_EQUAL(2432902008176640000, factorial(20));
}

/*! test case function for checking
 *  output of factorial of 12.
 *  providing unexpected value so that
 *  test case should fail
 */
void test_factorial_of_twelve_negative_testcase(void)
{
	TEST_ASSERT_EQUAL(768, factorial(12));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_factorial_of_zero);
	RUN_TEST(test_factorial_of_five);
	RUN_TEST(test_factorial_of_minusthree);
	RUN_TEST(test_factorial_of_twenty);
	RUN_TEST(test_factorial_of_twelve_negative_testcase);
	return (UnityEnd());
}

