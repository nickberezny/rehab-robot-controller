#include <math.h>
#include <string.h>

#include "MathUtilities.h"

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