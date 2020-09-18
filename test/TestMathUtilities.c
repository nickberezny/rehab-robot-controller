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

void test_matrixVectorMultiplication(void)
{
	double array[3][3] = {1,2,3,4,5,6,7,8,9};
	double vector[3] = {1,2,3};
	double result[3];
	matrixVectorMultiplication(array, vector, result);
	double ans[3] = {14,32,50};

	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(ans, result, 3);

	double vector2[3] = {0,0,0};
	matrixVectorMultiplication(array, vector2, result);
	double ans2[3] = {0,0,0};

	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(ans2, result, 3);
}

void test_vectorMatrixMultiplication(void)
{
	double array[3][3] = {1,2,3,4,5,6,7,8,9};
	double vector[3] = {1,2,3};
	double result[3];
	vectorMatrixMultiplication(array, vector, result);
	double ans[3] = {30,36,42};

	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(ans, result, 3);

	double vector2[3] = {0,0,0};
	vectorMatrixMultiplication(array, vector2, result);
	double ans2[3] = {0,0,0};

	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(ans2, result, 3);
}

void test_backshiftDoubleArray(void)  
{
	double array[4] = {1,2,3,4};
	double ans[4] = {9,1,2,3};

	backshiftDoubleArray(array, 9, 4);

	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(ans, array, 4);

}


int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_squareMatrix);
	RUN_TEST(test_factorial);
	RUN_TEST(test_invertMatrix);
	RUN_TEST(test_matrixVectorMultiplication);
	RUN_TEST(test_vectorMatrixMultiplication);
	RUN_TEST(test_backshiftDoubleArray);
	return UNITY_END();
}