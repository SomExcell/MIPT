#include "matrix.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	Matrix<int> matrix =Matrix<int>::eye(3,3);
	Matrix<int> matrixTwo(matrix);
	cout << matrix;
	cout << matrixTwo;
	return 0;
}
