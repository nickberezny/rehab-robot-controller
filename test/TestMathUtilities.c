#include "../unity/src/unity.h"
#include "MathUtilities.h"

#include <math.h>

double A[2][2] = {0};
double B[2][2] = {0};
double C[2][2] = {0};

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

} 


void tearDown (void) {} /* Is run after every test, put unit clean-up calls here. */

void test_matrixSquare(void)
{
	squareMatrix(A,C);
	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(B, C, 4);

}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_matrixSquare);
	return UNITY_END();
}