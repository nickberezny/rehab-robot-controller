#include "../unity/src/unity.h"
#include "MathUtilities.h"

#include <math.h>

double A[2][2] = {0};
double B[2][2] = {0};
double C[2][2] = {0};
double Z[2][2] = {0};

double ans;

void setUp (void) 

{

	A[0][0] = 1;
	A[0][1] = 2;
	A[1][0] = 3;
	A[1][1] = 4;

	B[0][0] = 7;
	B[0][1] = 10;
	B[1][0] = 15;
	B[1][1] = 22;

	C[0][0] = -2;
	C[0][1] = 1;
	C[1][0] = 1.5;
	C[1][1] = -0.5;


} 


void tearDown (void) {} /* Is run after every test, put unit clean-up calls here. */

void test_squareMatrix(void)
{
	squareMatrix(A,Z);
	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(B, Z, 4);

}

void test_expMatrix(void)
{

}

void test_invertMatrix(void)
{
	invertMatrix(A,Z);
	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(C, Z, 4);
}

void test_factorial(void)
{
	factorial(1.0,&ans);
	TEST_ASSERT_EQUAL_DOUBLE(1.0,ans);
	factorial(10.0,&ans);
	TEST_ASSERT_EQUAL_DOUBLE(3628800.0,ans);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_squareMatrix);
	RUN_TEST(test_factorial);
	RUN_TEST(test_invertMatrix);
	return UNITY_END();
}