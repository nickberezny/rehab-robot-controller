#include <math.h>
#include <string.h>

#include "MathUtilities.h"
#include "SystemVariables.h"

void squareMatrix(double A[2][2], double C[2][2])
{

/*------------------------------------------------------------------------
	Squares a 2x2 matrices
		C = A*A
------------------------------------------------------------------------*/

	double B[2][2] = {0};
	memcpy(B, A, 4*sizeof(double));

	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			C[i][j] = (A[i][i]) * (B[i][j]) + A[i][i+1-2*i]*B[i+1-2*i][j];
		}
		
	}

	return;
}

void factorial(double n, double * ans)
{

/*------------------------------------------------------------------------
	Factorial of number n 
		ans = n!
------------------------------------------------------------------------*/
	*ans = 1.0;

	for(int i = 0; i < n; i++)
		*ans = *ans * (i + 1);
	
	return;
}

void expMatrix(double A[2][2], double B[2][2])
{

/*------------------------------------------------------------------------
Approximates matrix exponentiation for discrete to continuous conversion
Uses MAT_EXP_ITERATIONS iterations for numerical estimate
	B = exp(A) = I + A + A^2/fact(2) + A^3/fact(3) ...
------------------------------------------------------------------------*/


	//B = {0,0,0,0};
	double C[2][2] = {0};
	double D[2][2] = {0};
	double k = 0.0;

	C[0][0] = STEP_NSEC/NSEC_IN_SEC * A[0][0];
	C[1][0] = STEP_NSEC/NSEC_IN_SEC * A[1][0];
	C[0][1] = STEP_NSEC/NSEC_IN_SEC * A[0][1];
	C[1][1] = STEP_NSEC/NSEC_IN_SEC * A[1][1];

	memcpy(D, C, 4*sizeof(double));
	memcpy(B, C, 4*sizeof(double));


	for(int i = 1; i<MAT_EXP_ITERATIONS; i++)
	{
		k = 1.0;
		factorial(i+1, &k);
		squareMatrix(D, C);
	
		for(int j = 0; j<2; j++) 
		{
			B[j][0] += C[j][0]/k;
			B[j][1] += C[j][1]/k;
		}
	}

	B[0][0] += 1.0; //add unity matrix
	B[1][1] += 1.0;

	return;
}

void invertMatrix(double A[2][2], double B[2][2])
{

/*------------------------------------------------------------------------
	Invert 2x2 matrix 
		B = A^-1
------------------------------------------------------------------------*/
	//printf("a to invert: %.2f,%.2f,%.2f,%.2f\n", A[0][0], A[0][1], A[1][0], A[1][1]);

	if(A[0][0]*A[1][1] - A[0][1]*A[1][0] == 0)
	{
		//printf("Matrix is singular \n");
		return;
	}

	B[0][0] = A[1][1] / ( A[0][0]*A[1][1] - A[0][1]*A[1][0]);
	B[1][0] = -A[1][0] / ( A[0][0]*A[1][1] - A[0][1]*A[1][0]);
	B[0][1] = -A[0][1] / ( A[0][0]*A[1][1] - A[0][1]*A[1][0]);
	B[1][1] = A[0][0] / ( A[0][0]*A[1][1] - A[0][1]*A[1][0]);

	//printf("Ainv: %.4f, %.4f, %.4f, %.4f\n", B[0][0], B[0][1], B[1][0], B[1][1]);

	return;
}

void matrixVectorMultiplication(double array[3][3], double vector[3], double newVector[3])
{

	for(int i = 0; i < 3; i++)
	{
		newVector[i] = array[i][0]*vector[0] + array[i][1]*vector[1] + array[i][2]*vector[2];
	}

	return;
}

void vectorMatrixMultiplication(double array[3][3], double vector[3], double newVector[3])
{
	
	for(int i = 0; i < 3; i++)
	{
		newVector[i] = array[0][i]*vector[0] + array[1][i]*vector[1] + array[2][i]*vector[2];
	}

	return;
}

void backshiftDoubleArray(double * array, double newValue, int size)
{
	for(int i = size - 1; i > 0; i--)
	{
		array[i] = array[i-1];
	}

	array[0] = newValue;
}